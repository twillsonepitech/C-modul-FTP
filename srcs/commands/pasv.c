/**
 * @file pasv.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief PASV FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t create_data_socket_pasv(struct clients_s *client)
{
    int32_t return_from_function;

    client->pasv.socket.fd = socket(AF_INET, SOCK_STREAM, SOCK_PROTOCOL);
    if (FUNCTION_RETURN_ERROR == client->pasv.socket.fd) {
        LOG_ERROR("socket() function: FAILURE.");
        return EXIT_FAILURE;
    }
    return_from_function = setsockopt(client->pasv.socket.fd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &(int){1}, sizeof(int));
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("setsockopt() function: FAILURE.");
        return EXIT_FAILURE;
    }
    client->pasv.socket.address.sin_family = AF_INET;
    client->pasv.socket.address.sin_addr.s_addr = inet_addr(inet_ntoa(client->socket.address.sin_addr));
    client->pasv.socket.address.sin_port = INIT_INTEGER;
    client->pasv.socket.address_length = sizeof(client->socket.address);
    return_from_function = bind(client->pasv.socket.fd, (const struct sockaddr *)&client->pasv.socket.address, sizeof(client->pasv.socket.address));
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("bind() function: FAILURE.");
        return EXIT_FAILURE;
    }
    return_from_function = getsockname(client->pasv.socket.fd, (struct sockaddr *)&client->pasv.socket.address, &client->pasv.socket.address_length);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("getsockname() function: FAILURE.");
        return EXIT_FAILURE;
    }
    return_from_function = listen(client->pasv.socket.fd, LISTEN_BACKLOG);
    if (FUNCTION_RETURN_ERROR == return_from_function) {
        LOG_ERROR("listen() function: FAILURE.");
        return EXIT_FAILURE;
    }
    dprintf(STDOUT_FILENO, "PASV: ip = %s, port = %d\n", inet_ntoa(client->pasv.socket.address.sin_addr), ntohs(client->pasv.socket.address.sin_port));
    return EXIT_SUCCESS;
}

uint8_t set_host_port(struct clients_s *client, uint8_t **host_port)
{
    int32_t index_per_iteration;
    uint16_t port;
    uint8_t *host;

    host = (uint8_t *)inet_ntoa(client->pasv.socket.address.sin_addr);
    port = ntohs(client->pasv.socket.address.sin_port);
    *host_port = (uint8_t *)malloc(sizeof(uint8_t) * (strlen((const char *)host) * 2 + 1));
    if (NULL == *host_port) {
        LOG_ERROR("malloc() function: FAILURE.");
        return EXIT_FAILURE;
    }
    sprintf((char *)*host_port, "%s,%d,%d", host, port / 256, port % 256);
    index_per_iteration = INIT_INTEGER;
    while ((*host_port)[index_per_iteration] != '\0') {
        if ((*host_port)[index_per_iteration] == '.') {
            (*host_port)[index_per_iteration] = ',';
        }
        index_per_iteration++;
    }
    return EXIT_SUCCESS;
}

uint8_t manage_pasv_command(struct clients_s *client)
{
    int32_t return_from_function;
    uint8_t *host_port;
    void *ptr_return_from_function;

    return_from_function = create_data_socket_pasv(client);
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    return_from_function = set_host_port(client, &host_port);
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    if (true == client->port.activated) {
        ptr_return_from_function = memset(&client->port, INIT_INTEGER, sizeof(struct port_s));
        if (NULL == ptr_return_from_function) {
            LOG_ERROR(strerror(errno));
            return EXIT_FAILURE;
        }
    }
    client->pasv.activated = true;
    WRITE_CODE(client->socket.fd, FTP_CODE_227, host_port);
    return EXIT_SUCCESS;
}

uint8_t pasv(const uint64_t dbl_lineptr_length, __attribute__((unused)) const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;

    if (ONE != dbl_lineptr_length) {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    return_from_function = manage_pasv_command(client);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function) {
        return return_from_function;
    }
    return EXIT_SUCCESS;
}
