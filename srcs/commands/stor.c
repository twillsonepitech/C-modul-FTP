/**
 * @file stor.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief STOR FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include "struct.h"
#include "define.h"
#include "functions.h"

uint8_t error_handling_stor(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    if (false == client->pasv.activated && false == client->port.activated)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_425, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (ONE == dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (THREE <= dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_550, lineptr, NO_SUCH_FILE);
        return EXIT_FAILURE_FTP;
    }
    if (false == FILE_PERMISSION((const char *)lineptr))
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_553, lineptr);
        return EXIT_FAILURE_FTP;
    }
    return EXIT_SUCCESS;
}

uint8_t upload_file(const uint8_t *lineptr, struct clients_s *client)
{
    int32_t data_socket;
    int32_t fd;
    int32_t return_from_function;
    int64_t readline, writeline;
    uint8_t input[READ_SIZE + 1];

    fd = open((const char *)lineptr, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (FUNCTION_RETURN_ERROR == fd)
    {
        LOG_ERROR("open() function: FAILURE.");
        return EXIT_FAILURE;
    }
    data_socket = true == client->port.activated ? client->port.socket.fd : accept(client->pasv.socket.fd, NULL, NULL);
    WRITE_CODE(client->socket.fd, FTP_CODE_150, NULL);
    while (true)
    {
        readline = read(data_socket, input, READ_SIZE);
        if (FUNCTION_RETURN_ERROR == readline)
        {
            LOG_ERROR("read() function: FAILURE.");
            return EXIT_FAILURE;
        }
        else
        {
            input[readline] = '\0';
        }
        writeline = write(fd, input, strlen((const char *)input));
        if (FUNCTION_RETURN_ERROR == writeline)
        {
            LOG_ERROR("write() function: FAILURE");
            return EXIT_FAILURE;
        }
    }
    WRITE_CODE(client->socket.fd, FTP_CODE_226, NULL);
    return_from_function = close(fd);
    if (FUNCTION_RETURN_ERROR == return_from_function)
    {
        LOG_ERROR("close() function: FAILURE");
        return EXIT_FAILURE;
    }
    return_from_function = close(data_socket);
    if (FUNCTION_RETURN_ERROR == return_from_function)
    {
        LOG_ERROR("close() function: FAILURE");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

uint8_t stor(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t return_from_function;
    void *ptr_return_from_function;

    return_from_function = error_handling_stor(dbl_lineptr_length, lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function)
    {
        return EXIT_FAILURE_FTP;
    }
    return_from_function = upload_file(lineptr, client);
    if (true == client->pasv.activated)
    {
        return_from_function = close(client->pasv.socket.fd);
        if (FUNCTION_RETURN_ERROR == return_from_function)
        {
            LOG_ERROR("close() function: FAILURE.");
            return EXIT_FAILURE;
        }
        ptr_return_from_function = memset(&client->pasv, INIT_STRUCT, sizeof(struct pasv_s));
        if (NULL == ptr_return_from_function)
        {
            LOG_ERROR("memset() function: FAILURE.");
            return EXIT_FAILURE;
        }
    }
    else
    {
        return_from_function = close(client->port.socket.fd);
        if (FUNCTION_RETURN_ERROR == return_from_function)
        {
            LOG_ERROR("close() function: FAILURE.");
            return EXIT_FAILURE;
        }
        ptr_return_from_function = memset(&client->port, INIT_STRUCT, sizeof(struct port_s));
        if (NULL == ptr_return_from_function)
        {
            LOG_ERROR("memset() function: FAILURE.");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
