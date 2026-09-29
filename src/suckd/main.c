#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "network/common.h"
#include "suckd/control.h"

// TODO: Proper error handling
int main(void)
{
  int err = 0;
  sd_unix_socket ControlSocket;

  // Create control socket
  err = sd_create_unix_socket(CONTROL_SOCKET_PATH, &ControlSocket);
  if (err != 0)
  {
    printf("Fatal: Failed to create socket: %s\n", strerror(errno));
    return -1;
  }

  // Handle socket
  char Buffer[MAX_CONTROL_PACKET_SIZE] = {0};
  int  Bytes = 0;

  for(;;)
  {
    Bytes = sd_read_control_socket(sd_unix_socket* ControlSocket, char* Buffer);
    sd_handle_control_packet(Buffer, Bytes);
  }
  
  return 0;  
}
