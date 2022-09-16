/**
 * @file port.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief PORT FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t error_handling_port(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;

    if (TWO != dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    return_from_function = count_number_c_in_lineptr(lineptr, ',');
    if (FIVE != return_from_function)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    return EXIT_SUCCESS;
}

uint8_t checkout_port_number(const uint8_t *f_portn, const uint8_t *s_portn, uint32_t *port)
{
    int32_t return_from_function;
    uint64_t f_porti, s_porti;

    return_from_function = xstrtoul(&f_porti, f_portn, BASE_TEN);
    if (EXIT_FAILURE == return_from_function)
    {
        return EXIT_FAILURE;
    }
    return_from_function = xstrtoul(&s_porti, s_portn, BASE_TEN);
    if (EXIT_FAILURE == return_from_function)
    {
        return EXIT_FAILURE;
    }
    *port = f_porti * 256 + s_porti;
    return EXIT_SUCCESS;
}

uint8_t create_data_socket_port(uint32_t port, const uint8_t *ip, struct clients_s *client)
{
    int32_t return_from_function;

    client->port.socket.fd = socket(AF_INET, SOCK_STREAM, SOCK_PROTOCOL);
    if (FUNCTION_RETURN_ERROR == client->port.socket.fd)
    {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    return_from_function = setsockopt(client->port.socket.fd, SOL_SOCKET, SO_REUSEPORT | SO_REUSEADDR, &(int){1}, sizeof(int));
    if (FUNCTION_RETURN_ERROR == return_from_function)
    {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    client->port.socket.address.sin_family = AF_INET;
    client->port.socket.address.sin_port = htons(port);
    dprintf(STDERR_FILENO, "ip: %s\n", ip);
    return_from_function = inet_pton(AF_INET, (const char *)ip, &client->port.socket.address.sin_addr);
    if (NETWORK_FAILURE_AF == return_from_function)
    {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    else if (NETWORK_FAILURE_ADDR == return_from_function)
    {
        LOG_ERROR("inet_pton() function: ADDRESS FAILURE.");
        return EXIT_FAILURE_FTP;
    }
    else
    {
    }
    return_from_function = connect(client->port.socket.fd, (const struct sockaddr *)&client->port.socket.address, sizeof(client->port.socket.address));
    if (FUNCTION_RETURN_ERROR == return_from_function)
    {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    dprintf(STDOUT_FILENO, "PORT: ip = %s, port = %d\n", inet_ntoa(client->port.socket.address.sin_addr), ntohs(client->port.socket.address.sin_port));
    return EXIT_SUCCESS;
}

uint8_t manage_port_command(const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;
    uint32_t port;
    uint64_t length_ip;
    uint8_t **dbl_lineptr;
    uint8_t *ip;

    dbl_lineptr = lineptr_to_dbl_lineptr((uint8_t *)lineptr, (const uint8_t *)",");
    if (NULL == dbl_lineptr || NULL == *dbl_lineptr)
    {
        return EXIT_FAILURE;
    }
    else
    {
        length_ip = strlen((const char *)dbl_lineptr[IPv1]) + strlen((const char *)dbl_lineptr[IPv2]) + strlen((const char *)dbl_lineptr[IPv3]) + strlen((const char *)dbl_lineptr[IPv4]) + THREE;
    }
    ip = (uint8_t *)malloc(sizeof(uint8_t) * (length_ip + 1));
    if (NULL == ip)
    {
        LOG_ERROR(strerror(errno));
        return EXIT_FAILURE;
    }
    snprintf((char *)ip, length_ip + 1, "%s.%s.%s.%s", dbl_lineptr[IPv1], dbl_lineptr[IPv2], dbl_lineptr[IPv3], dbl_lineptr[IPv4]);
    return_from_function = checkout_port_number(dbl_lineptr[PORT1], dbl_lineptr[PORT2], &port);
    if (EXIT_FAILURE == return_from_function)
    {
        return EXIT_FAILURE;
    }
    return_from_function = create_data_socket_port(port, ip, client);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function)
    {
        return return_from_function;
    }
    free(ip);
    free_dbl_array_pointer(dbl_lineptr);
    return EXIT_SUCCESS;
}

uint8_t port(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;
    void *ptr_return_from_function;

    return_from_function = error_handling_port(dbl_lineptr_length, lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function)
    {
        return EXIT_FAILURE;
    }
    return_from_function = manage_port_command(lineptr, client);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function)
    {
        return return_from_function;
    }
    if (true == client->pasv.activated)
    {
        ptr_return_from_function = memset(&client->pasv, INIT_INTEGER, sizeof(struct pasv_s));
        if (NULL == ptr_return_from_function)
        {
            LOG_ERROR(strerror(errno));
            return EXIT_FAILURE;
        }
    }
    client->port.activated = true;
    WRITE_CODE(client->socket.fd, FTP_CODE_200, NULL);
    return EXIT_SUCCESS;
}
