#pragma once

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>

#define MAX_CONTROL_PACKET_SIZE    70
#define MAX_CONTROL_PACKET_PAYLOAD 64
#define MIN_CONTROL_PACKET_SIZE    4
#define MIN_CONTROL_PACKET_PAYLOAD 2

#define CONTROL_PACKET_SIZE_BYTE 0
#define CONTROL_PACKET_COMMAND_BYTE 1
#define CONTROL_PACKET_PAYLOAD_BYTE 2

typedef struct sd_packet
{
  uint8_t Size;
  uint8_t Command;
  char*   ServiceName;
} sd_packet;

typedef struct sd_unix_socket
{
  int FD;
  struct sockaddr_un Address;
} sd_unix_socket;

struct sockaddr_un
sd_create_address(int Domain, const char* Address);

int
sd_create_socket(int Domain, int Type, int Protocol, const char* Address, sd_unix_socket* ResSocket);

int
sd_create_unix_socket(const char* Address, sd_unix_socket* ResSocket);
