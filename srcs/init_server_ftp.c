/**
 * @file init_server_ftp.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Function that init server ftp struct,
 * create socket, bind and listen it.
 * @version 0.1
 * @date 2022-07-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "object.h"
#include "define.h"

uint8_t init_server_socket(struct server_ftp_s *server_ftp)
{
    int32_t return_from_function;

    server_ftp->socket.fd = socket(AF_INET, SOCK_STREAM, SOCK_PROTOCOL);
    if (FUNCTION_RETURN_ERROR == server_ftp->socket.fd) {
        LOG_ERROR("socket() function: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("socket() function: SUCCESS.");
    }
    return_from_function = fcntl(server_ftp->socket.fd, F_SETFL, O_NONBLOCK);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    return_from_function = setsockopt(server_ftp->socket.fd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &(int){1}, sizeof(int));
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("setsockopt() function: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("setsockopt() function: SUCCESS.");
    }
    return EXIT_SUCCESS;
}

uint8_t init_server_address(struct server_ftp_s *server_ftp, const uint32_t port)
{
    (void) memset(&server_ftp->socket.address, INIT_STRUCT, sizeof(struct sockaddr_in));
    server_ftp->socket.address.sin_family = AF_INET;
    server_ftp->socket.address.sin_addr.s_addr = INADDR_ANY;
    server_ftp->socket.address.sin_port = htons(port);
    server_ftp->socket.address_length = sizeof(server_ftp->socket.address);
    return EXIT_SUCCESS;
}

uint8_t bind_and_listen_server_socket(struct server_ftp_s *server_ftp)
{
    int32_t return_from_function;

    return_from_function = bind(server_ftp->socket.fd, (const struct sockaddr *)&server_ftp->socket.address, server_ftp->socket.address_length);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("bind() function: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("bind() function: SUCCESS.");
    }
    return_from_function = listen(server_ftp->socket.fd, LISTEN_BACKLOG);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("listen() function: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("listen() function: SUCCESS.");
        LOG_WARN("listen() connection requests: 50.");
    }
    return EXIT_SUCCESS;
}

uint8_t init_server_ftp_struct(struct server_ftp_s *server_ftp, const uint32_t port)
{
    int32_t return_from_function;

    (void) memset(server_ftp, INIT_STRUCT, sizeof(struct server_ftp_s));
    return_from_function = init_server_socket(server_ftp);
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    return_from_function = init_server_address(server_ftp, port);
    if (EXIT_FAILURE == return_from_function) {
        LOG_ERROR("init_server_address() function: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_INFO("init_server_address() function: SUCCESS.");
    }
    return_from_function = bind_and_listen_server_socket(server_ftp);
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
