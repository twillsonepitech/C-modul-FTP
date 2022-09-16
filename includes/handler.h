/**
 * @file handler.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Command handler, list of all command available for the client.
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <stddef.h>
#include <stdint.h>
#include "struct.h"
#include "define.h"

__attribute__((unused)) static const char *COMMANDS_LIST[] = {
    "USER", "PASS", "CWD", "HELP",
    "CDUP", "QUIT", "DELE", "PWD",
    "PASV", "PORT", "NOOP", "RETR",
    "STOR", "LIST", NULL
};

__attribute__((unused)) static const char *COMMANDS_LIST_AVAILABLE_BEFORE_CONNECT[] = {
    "USER", "PASS", "NOOP",
    "QUIT", "HELP", NULL
};

struct command_send_s {
    const char *key;
    const enum commands_e value;
};

static const struct command_send_s COMMAND_SEND_LIST[] = {
    {.key = "USER", .value = USER},
    {.key = "PASS", .value = PASS},
    {.key = "NOOP", .value = NOOP},
    {.key = "QUIT", .value = QUIT},
    {.key = "HELP", .value = HELP},
    {.key = "PWD",  .value = PWD},
    {.key = "CWD",  .value = CWD},
    {.key = "CDUP", .value = CDUP},
    {.key = "PASV", .value = PASV},
    {.key = "PORT", .value = PORT},
    {.key = "RETR", .value = RETR},
    {.key = "STOR", .value = STOR},
    {.key = "LIST", .value = LIST},
    {.key = "DELE", .value = DELE},
    {.key = NULL,   .value = NILL},
};

struct command_function_s {
    uint8_t (*cmd_ptr)(const uint64_t dbl_lineptr_length, const uint8_t *lineptr, struct clients_s *client);
};

static const struct command_function_s COMMAND_FUNCTION[] = {
    #include "functions.h"
    [USER] = { .cmd_ptr = &user },
    [PASS] = { .cmd_ptr = &pass },
    [NOOP] = { .cmd_ptr = &noop },
    [QUIT] = { .cmd_ptr = &quit },
    [HELP] = { .cmd_ptr = &help },
    [PWD]  = { .cmd_ptr = &pwd },
    [CWD]  = { .cmd_ptr = &cwd },
    [CDUP] = { .cmd_ptr = &cdup },
    [PASV] = { .cmd_ptr = &pasv },
    [PORT] = { .cmd_ptr = &port },
    [RETR] = { .cmd_ptr = &retr },
    [STOR] = { .cmd_ptr = &stor },
    [LIST] = { .cmd_ptr = &list },
    [DELE] = { .cmd_ptr = &dele },
};
