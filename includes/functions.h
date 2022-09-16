/**
 * @file functions.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief All functions are here, they are all managing the creation
 * of the ftp server.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stdint.h>
#include "object.h"
#include "define.h"

// main.c
uint8_t helper(const enum return_code_e return_code);
uint8_t error_handling(int32_t argc, char const *argv[]);

// manage_client.c
uint8_t manage_eol_lineptr(uint8_t *lineptr, const int64_t rd);
uint8_t manage_client_message(uint8_t ***dbl_lineptr, const int32_t fd);
void compare_given_command_with_list(const uint8_t *lineptr, const char *LIST[], int8_t *marker);
uint8_t handle_client_message(const uint8_t *lineptr, const struct clients_s *client);
void catch_command_index(const uint8_t *lineptr, uint16_t *command_index);
uint8_t execute_client_command(uint8_t **dbl_lineptr, struct clients_s *client);
uint8_t manage_responding_client(struct clients_s *client);

// init_server_ftp_.c
uint8_t init_server_socket(struct server_ftp_s *server_ftp);
uint8_t init_server_address(struct server_ftp_s *server_ftp, const uint32_t port);
uint8_t bind_and_listen_server_socket(struct server_ftp_s *server_ftp);
uint8_t init_server_ftp_struct(struct server_ftp_s *server_ftp, const uint32_t port);

// handle_server_ftp.c
uint8_t handle_incoming_client(fd_set *rfds, struct clients_s **clients, struct socket_s socket, const uint8_t *path);
uint8_t client_quitting_server(struct clients_s **clients, struct clients_s *client, fd_set *rfds);
uint8_t handle_message_client(struct clients_s **clients, const int32_t fd, fd_set *rfds);
uint8_t manage_clients(struct server_ftp_s *server_ftp, struct clients_s **clients, const int32_t fd, const uint8_t *path);
uint8_t handle_clients(struct server_ftp_s *server_ftp, struct clients_s **clients, const uint8_t *path);
uint8_t setup_signal_and_server_socket(const int32_t server_fd, fd_set *rfds);
uint8_t handle_server_ftp(struct server_ftp_s *server_ftp, const uint8_t *path);

// client_linked_list.c
struct clients_s *create_client_node(struct socket_s socket, const uint8_t *path);
uint8_t add_incoming_client_in_linked_list(struct clients_s **clients, struct socket_s socket, const uint8_t *path);
void free_clients_linked_list(struct clients_s **clients);
void free_clients_linked_list_by_key(struct clients_s **clients, const int32_t fd_key);

// array.c
int32_t endswith(const uint8_t *str, const uint8_t *suffix);
uint8_t *lineptr_to_upper_lineptr(uint8_t *lineptr);
uint64_t length_dbl_array_pointer(const uint8_t **dbl_lineptr);
void print_content_dbl_array_pointer(const int fd, const uint8_t **dbl_lineptr);
uint8_t **lineptr_to_dbl_lineptr(uint8_t *lineptr, const uint8_t *delim);
void free_dbl_array_pointer(uint8_t **dbl_ptr);
uint8_t xstrtoul(uint64_t *ulong, const uint8_t *lineptr, int32_t base);
uint64_t count_number_c_in_lineptr(const uint8_t *lineptr, const uint8_t c);
uint8_t *make_message(const char *__restrict __fmt, ...);

// activate_ftp_server.c
uint8_t *xgetcwd(const uint8_t *path);
uint8_t activate_ftp_server(const uint32_t port, const uint8_t *path);

// user.c
uint8_t user(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// pass.c
uint8_t pass(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// quit.c
uint8_t quit(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// noop.c
uint8_t noop(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// help.c
uint8_t help(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// pwd.c
uint8_t pwd(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// cwd.c
uint8_t cwd(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// cdup.c
uint8_t cdup(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// dele.c
uint8_t error_handling_dele(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);
uint8_t dele(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// pasv.c
uint8_t create_data_socket_pasv(struct clients_s *client);
uint8_t set_host_port(struct clients_s *client, uint8_t **host_port);
uint8_t manage_pasv_command(struct clients_s *client);
uint8_t pasv(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// port.c
uint8_t error_handling_port(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);
uint8_t checkout_port_number(const uint8_t *f_portn, const uint8_t *s_portn, uint32_t *port);
uint8_t create_data_socket_port(uint32_t port, const uint8_t *ip, struct clients_s *client);
uint8_t manage_port_command(const uint8_t *lineptr, struct clients_s *client);
uint8_t port(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));

// retr.c
uint8_t error_handling_retr(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);
uint8_t download_file(const uint8_t *lineptr, struct clients_s *client);
uint8_t retr(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// stor.c
uint8_t error_handling_stor(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);
uint8_t upload_file(const uint8_t *lineptr, struct clients_s *client);
uint8_t stor(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((2, 3));

// list.c
void print_dir_list_content_file(const uint32_t data_socket, const uint8_t **dbl_ptr_dir_list_content, const uint8_t *lineptr);
uint8_t directory_listing(const uint8_t *lineptr, struct clients_s *client, const int8_t is_file);
uint8_t list(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);//__nonnull((3));
