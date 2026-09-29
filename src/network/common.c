#include <string.h>
#include <sys/stat.h>

#include <errno.h>

#include "network/common.h"

struct sockaddr_un
sd_create_address(int Domain, const char* Address)
{    
  struct sockaddr_un SocketAddress = {0};
  SocketAddress.sun_family = Domain;
  strcpy(SocketAddress.sun_path, Address);

  return SocketAddress;
}

int
sd_create_socket(int Domain, int Type, int Protocol, const char* Address, sd_unix_socket* ResSocket)
{    
  // Create socket
  int SocketFD = socket(Domain, Type, Protocol);
  if (SocketFD == -1)
    return -1; 

  // Create address
  struct sockaddr_un SocketAddress = sd_create_address(Domain, Address);
  unlink(Address);

  // Bind address
  int err = bind(SocketFD, (struct sockaddr*) &SocketAddress, sizeof(SocketAddress));
  if (err != 0)
  {
    unlink(Address);
    return -1;    
  }

  ResSocket->FD      = SocketFD;
  ResSocket->Address = SocketAddress;

  return 0;
}

int
sd_create_unix_socket(const char* Address, sd_unix_socket* ResAddress)
{
  return sd_create_socket(AF_UNIX, SOCK_DGRAM, 0, Address, ResAddress);
}
