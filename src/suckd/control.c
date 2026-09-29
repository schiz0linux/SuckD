#include <errno.h>
#include <ctype.h>

#include "network/common.h"
#include "service/service.h"
#include "util/util.h"

#include "suckd/control.h"

int
sd_read_control_socket(sd_unix_socket* ControlSocket, char* Buffer)
{
  ssize_t Bytes = recv(ControlSocket->FD, Buffer, MAX_CONTROL_PACKET_SIZE, MSG_DONTWAIT);
  Buffer[MAX_SERVICE_NAME_SIZE] = '\0'; // Force-terminate service name

  return Bytes;
}

int
sd_handle_control_packet(char* Packet, int Bytes)
{    
    if (Bytes == -1)
    {
      // Since MSG_DONTWAIT is set, ignore it
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        return 0;

      // Warning
      return -1;
    }

    // Validate packet
    char  PayloadSize = Packet[CONTROL_PACKET_SIZE_BYTE];
    char  Command     = Packet[CONTROL_PACKET_COMMAND_BYTE]; // TODO: Separate status from commands?
    char* Payload     = (Packet + CONTROL_PACKET_PAYLOAD_BYTE);

    // Packet is too small
    if (Bytes < MIN_CONTROL_PACKET_SIZE)
      return -1;

    // Payload is too small or too big
    if (PayloadSize < MIN_CONTROL_PACKET_PAYLOAD || PayloadSize > MAX_CONTROL_PACKET_PAYLOAD)
      return -1;

    // Payload contains non-alnum characters
    if (sd_is_alnum(Payload) != 0)
      return -1;
    

    // TODO: Malformed service name handling  


    // TODO: Add proper error handling
    switch (Command) {
      case SERVICE_STOP:
        sd_service_stop(Payload);
        break;
      case SERVICE_START:
        sd_service_start(Payload);
        break;
      case SERVICE_RESTART:
        sd_service_restart(Payload);
        break;
    }

    return 0;
}
