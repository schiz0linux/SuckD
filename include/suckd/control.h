#pragma once

#include "network/common.h"

#define CONTROL_SOCKET_PATH "/tmp/sd_control.sock"

int
sd_read_control_socket(sd_unix_socket* ControlSocket, char* Buffer);

int
sd_handle_control_packet(char* Packet, int Bytes);
