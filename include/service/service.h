#pragma once

#define MAX_SERVICE_COUNT     1024
#define MAX_SERVICE_NAME_SIZE 64

typedef enum sd_service_status
{
  SERVICE_STOP,
  SERVICE_START,
  SERVICE_RESTART
} sd_service_status;

typedef struct sd_service
{
  char Name[MAX_SERVICE_NAME_SIZE];
  sd_service_status Status;
} sd_service;

int
sd_service_get_count();

int
sd_service_get_list(int Count, sd_service* ResArray);

int
sd_service_find_by_name(const char* Name);

int
sd_service_add(const char* Name);

int
sd_service_start(const char* Name);

int
sd_service_stop(const char* Name);

int
sd_service_restart(const char* Name);
