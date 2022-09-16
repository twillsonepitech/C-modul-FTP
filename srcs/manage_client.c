/**
 * @file manage_client.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Manage messages that send the client to the server
 * (including server responses).
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include "object.h"
#include "define.h"
#include "functions.h"
#include "handler.h"
#include "../Get-Next-Line/includes/get_next_line.h"

uint8_t manage_eol_lineptr(uint8_t *lineptr, const int64_t rd)
{
    if (NETCAT(lineptr[rd - 1], lineptr[rd - 2]))
    {
        lineptr[rd - 1] = '\0';
    }
    if (TELNET(lineptr[rd - 1], lineptr[rd - 2]))
    {
        lineptr[rd - 2] = '\0';
    }
    lineptr[rd - 1] = '\0';
    if (*lineptr == '\0')
    {
        return EXIT_FAILURE_FTP;
    }
    return EXIT_SUCCESS;
}

uint8_t manage_client_message(uint8_t ***dbl_lineptr, const int32_t fd)
{
    int32_t return_from_function;
    uint8_t *lineptr;

    *dbl_lineptr = INIT_POINTER;
    lineptr = (uint8_t *) get_next_line(fd, SIMPLE_MODE);
    if (NULL == lineptr)
    {
        return EXIT_FAILURE_FTP;
    }
    return_from_function = manage_eol_lineptr(lineptr, strlen((const char *) lineptr));
    if (EXIT_FAILURE_FTP == return_from_function)
    {
        free(lineptr);
        return EXIT_FAILURE_FTP;
    }
    else
    {
        LOG_CLIENT(fd, lineptr);
    }
    *dbl_lineptr = lineptr_to_dbl_lineptr(lineptr, (const uint8_t *) " ");
    if (NULL == *dbl_lineptr || NULL == **dbl_lineptr)
    {
        free(lineptr);
        return EXIT_FAILURE;
    }
    **dbl_lineptr = lineptr_to_upper_lineptr(**dbl_lineptr);
    free(lineptr);
    return EXIT_SUCCESS;
}

void compare_given_command_with_list(const uint8_t *lineptr, const char *LIST[], int8_t *marker)
{
    int32_t return_from_function;
    int32_t index_per_iteration;

    *marker = false;
    index_per_iteration = INIT_INTEGER;
    while (LIST[index_per_iteration] != NULL)
    {
        return_from_function = strcmp((const char *)lineptr, LIST[index_per_iteration]);
        if (EXIT_SUCCESS == return_from_function)
        {
            *marker = true;
        }
        index_per_iteration++;
    }
}

uint8_t handle_client_message(const uint8_t *lineptr, const struct clients_s *client)
{
    int8_t marker;

    compare_given_command_with_list(lineptr, COMMANDS_LIST, &marker);
    if (false == marker)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_500, NULL);
        return EXIT_FAILURE_FTP;
    }
    compare_given_command_with_list(lineptr, COMMANDS_LIST_AVAILABLE_BEFORE_CONNECT, &marker);
    if (false == client->connected && false == marker)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_530_1, NULL);
        return EXIT_FAILURE_FTP;
    }
    return EXIT_SUCCESS;
}

void catch_command_index(const uint8_t *lineptr, uint16_t *command_index)
{
    int32_t return_from_function;
    int32_t index_per_iteration;

    *command_index = NILL;
    index_per_iteration = INIT_INTEGER;
    while (COMMAND_SEND_LIST[index_per_iteration].key != NULL)
    {
        return_from_function = strcmp((const char *) lineptr, COMMAND_SEND_LIST[index_per_iteration].key);
        if (EXIT_SUCCESS == return_from_function)
        {
            *command_index = COMMAND_SEND_LIST[index_per_iteration].value;
        }
        index_per_iteration++;
    }
}

uint8_t execute_client_command(uint8_t **dbl_lineptr, struct clients_s *client)
{
    uint16_t command_index;
    uint64_t dbl_lineptr_length;

    catch_command_index(*dbl_lineptr, &command_index);
    dbl_lineptr_length = length_dbl_array_pointer((const uint8_t **)dbl_lineptr);
    return COMMAND_FUNCTION[command_index].cmd_ptr(dbl_lineptr_length, dbl_lineptr[1], client);
}

uint8_t manage_responding_client(struct clients_s *client)
{
    int32_t return_from_function;
    uint8_t **dbl_lineptr;

    return_from_function = manage_client_message(&dbl_lineptr, client->socket.fd);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function)
    {
        return return_from_function;
    }
    return_from_function = handle_client_message(*dbl_lineptr, client);
    if (EXIT_FAILURE_FTP == return_from_function)
    {
        free_dbl_array_pointer(dbl_lineptr);
        return EXIT_FAILURE_FTP;
    }
    return_from_function = execute_client_command(dbl_lineptr, client);
    if (EXIT_FAILURE == return_from_function || EXIT_FAILURE_FTP == return_from_function)
    {
        free_dbl_array_pointer(dbl_lineptr);
        return return_from_function;
    }
    free_dbl_array_pointer(dbl_lineptr);
    return EXIT_SUCCESS;
}
