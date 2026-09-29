#include <string.h>
#include <stdio.h>

#include "util/util.h"

#include "service/service.h"

static sd_service Services[MAX_SERVICE_COUNT];
static int ServiceCount = 0;

int
sd_service_get_count()
{
  return ServiceCount;
}

int
sd_service_get_list(int Count, sd_service* ResArray)
{
  if (Count > ServiceCount || Count <= 0)
    Count = ServiceCount;
    
  for (int Index = 0; Index < Count; Index++)
    ResArray[Index] = Services[Index];

  return 0;
}

int
sd_service_find_by_name(const char* Name)
{
  for (int Index = 0; Index < ServiceCount; Index++)
  {
    if (strcmp(Name, Services[Index].Name) == 0)
      return Index;
  }

  return -1;
}

int
sd_service_add(const char* Name)
{
  if (ServiceCount + 1 >= MAX_SERVICE_COUNT || sd_service_find_by_name(Name) != -1)
    return -1;

  strcpy(Services[ServiceCount].Name, Name); 
  Services[ServiceCount].Status = SERVICE_STOP;

  ServiceCount++;

  return 0;
}

int
sd_service_start(const char* Name)
{
  int Index = sd_service_find_by_name(Name);
  if (Index == -1)
    return -1;

  Services[Index].Status = SERVICE_START;

  printf("Service %s started\n", Services[Index].Name);  
  return 0;
}

int
sd_service_stop(const char* Name)
{
  int Index = sd_service_find_by_name(Name);
  if (Index == -1)
    return -1;

  Services[Index].Status = SERVICE_STOP;

  printf("Service %s stopped\n", Services[Index].Name);  
  return 0;
}

int
sd_service_restart(const char* Name)
{
  int Index = sd_service_find_by_name(Name);
  if (Index == -1)
    return -1;

  Services[Index].Status = SERVICE_RESTART;

  printf("Service %s restarted\n", Services[Index].Name);  
  return 0;
}
