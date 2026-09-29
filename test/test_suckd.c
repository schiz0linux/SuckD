#include "network/common.h"
#include "service/service.h"
#include "suckd/control.h"

#include <criterion/criterion.h>

// Network
Test(network_test, sd_create_address) {
  // Normal
  struct sockaddr_un ResAddress = sd_create_address(AF_UNIX, "bin/control_test.sock");
  cr_assert(ResAddress.sun_family == AF_UNIX);
}

Test(network_test, sd_create_unix_socket) {
  int err = 0;

  sd_unix_socket ResSocket;

  // Fuzzy
  err = sd_create_unix_socket("bin/!@#!@}#>6sdpoaskdLASpoiwq#!@>123123psioad", &ResSocket);
  cr_assert(err == 0);

  // Normal
  err = sd_create_unix_socket("bin/control_test.sock", &ResSocket);
  cr_assert(err == 0);
}

// Services
Test(service_test, sd_service_add) {
  int err = 0;

  // Normal
  err = sd_service_add("test_service");
  cr_assert(err == 0);
}

Test(service_test, sd_service_find_by_name) {
  int err = 0;

  // Normal
  err = sd_service_add("test_service");
  cr_assert(err == 0);
  int Index = sd_service_find_by_name("test_service");
  cr_assert(Index != -1);
}

Test(service_test, sd_service_start) {
  int err = 0;

  // Fuzzy
  err = sd_service_start("test_service");
  cr_assert(err != 0);

  // Normal
  err = sd_service_add("test_service");
  cr_assert(err == 0);
  err = sd_service_start("test_service");
  cr_assert(err == 0);
}

Test(service_test, sd_service_stop) {
  int err = 0;

  // Fuzzy
  err = sd_service_stop("test_service");
  cr_assert(err != 0);

  // Normal
  err = sd_service_add("test_service");
  cr_assert(err == 0);
  err = sd_service_stop("test_service");
  cr_assert(err == 0);
}

Test(service_test, sd_service_restart) {
  int err = 0;

  // Fuzzy
  err = sd_service_restart("test_service");
  cr_assert(err != 0);

  // Normal
  err = sd_service_add("test_service");
  cr_assert(err == 0);
  err = sd_service_restart("test_service");
  cr_assert(err == 0);
}

Test(service_test, sd_service_get_list) {
  sd_service ResArray[4];

  sd_service_add("test_service");
  sd_service_add("test_service2");
  sd_service_add("test_service3");
  sd_service_add("test_service4");
  
  // Fuzzy
  sd_service_get_list(999, ResArray);  
}

// Control
Test(control_test, sd_handle_control_packet) {
  int err = 0;

  char Packet[MAX_CONTROL_PACKET_SIZE] = {
    6, 0, 'h', 'e', 'l', 'l', 'o', '\0'
  };

  sd_service_add("hello");

  // Fuzzy
  err = sd_handle_control_packet(Packet, -1);
  cr_assert(err == 0);

  err = sd_handle_control_packet(Packet, -100);
  cr_assert(err != 0);

  // err = sd_handle_control_packet(Packet, 999);
  // cr_assert(err != 0);

  // Normal
  err = sd_handle_control_packet(Packet, 8);
  cr_assert(err == 0);
}
