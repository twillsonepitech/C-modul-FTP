/**
 * @file help.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief HELP FTP command.
 * @version 0.1
 * @date 2022-08-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <string.h>
#include "struct.h"
#include "functions.h"
#include "define.h"
#include "handler.h"

struct helper_command_s {
    const char *helper;
};

static const struct helper_command_s __helper_command[] = {
    [USER] = { .helper = "214 Syntax: USER <sp> username"},
    [PASS] = { .helper = "214 Syntax: PASS <sp> password"},
    [CWD] = { .helper = "214 Syntax: CWD [ <sp> directory-name ]"},
    [CDUP] = { .helper = "214 Syntax: CDUP (change to parent directory)"},
    [QUIT] = { .helper = "214 Syntax: QUIT (terminate service)"},
    [DELE] = { .helper = "214 Syntax: DELE <sp> file-name"},
    [PWD] = { .helper = "214 Syntax: PWD (return current directory)"},
    [PASV] = { .helper = "214 Syntax: PASV (set server in passive mode)"},
    [PORT] = { .helper = "214 Syntax: PORT <sp> b0, b1, b2, b3, b4"},
    [HELP] = { .helper = "214 Syntax: HELP [ <sp> <string> ]"},
    [NOOP] = { .helper = "214 Syntax: NOOP"},
    [RETR] = { .helper = "214 Syntax: RETR <sp> file-name"},
    [STOR] = { .helper = "214 Syntax: STOR <sp> file-name"},
    [LIST] = { .helper = "214 Syntax: LIST [ <sp> path-name ]"},
};

uint8_t help(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client)
{
    int32_t index_per_iteration;
    uint16_t command_index;
    uint8_t *dup_lineptr;

    if (THREE <= dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_502, NULL);
        return EXIT_FAILURE_FTP;
    }
    if (TWO == dbl_lineptr_length)
    {
        dup_lineptr = (uint8_t *) strdup((const char *) lineptr);
        dup_lineptr = lineptr_to_upper_lineptr(dup_lineptr);
        catch_command_index(dup_lineptr, &command_index);
        free(dup_lineptr);
        if (NILL != command_index)
        {
            WRITE_CODE(client->socket.fd, __helper_command[command_index].helper, NULL);
        }
        else
        {
            WRITE_CODE(client->socket.fd, FTP_CODE_502, NULL);
            return EXIT_FAILURE_FTP;
        }
    }
    if (ONE == dbl_lineptr_length)
    {
        WRITE_CODE(client->socket.fd, FTP_CODE_214_1, NULL);
        index_per_iteration = INIT_INTEGER;
        while (COMMANDS_LIST[index_per_iteration] != NULL)
        {
            dprintf(client->socket.fd, "    %s", COMMANDS_LIST[index_per_iteration]);
            index_per_iteration++;
        }
        WRITE_CODE(client->socket.fd, FTP_CODE_214_2, NULL);
    }
    return EXIT_SUCCESS;
}
