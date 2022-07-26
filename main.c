/**
 * @file main.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Main, create ftp executable and handle error.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "raise.h"
#include "define.h"
#include "functions.h"

static uint32_t helper(const enum return_code_e return_code)
{
    const char *help_message[] = {
        "USAGE: ./myftp port path",
        "\tport  is the port number on which the server socket listens",
        "\tpath  is the path to the home directory for the Anonymous user",
    };

    for (uint32_t i = 0; i < sizeof_array(help_message); i += 1) {
        fprintf(return_code == SUCCESS ? stdout : stderr, "%s\n", help_message[i]);
    }
    return return_code == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE_EPI;
}

static uint32_t error_handling(int32_t argc, char const *argv[])
{
    const uint8_t *port;
    const uint8_t *path;
    struct stat sb;

    if (NUMBER_OF_ARGUMENTS != argc) {
        error("Bad number of arguments.", EXIT_FAILURE);
    }
    port = (const uint8_t *) argv[PORT_INDEX];
    path = (const uint8_t *) argv[PATH_INDEX];
    for (uint32_t i = 0; i < strlen((const char *) port); i += 1) {
        if (false == isdigit(port[i]))
            error("Port contains other than digits.", EXIT_FAILURE);
    }
    if (FUNCTION_RETURN_ERROR == stat((const char *) path, &sb) || false == S_ISDIR(sb.st_mode)) {
        error("Path doesn't exist or is not a directory.", EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int32_t main(int32_t argc, char const *argv[])
{
    uint32_t port;
    const uint8_t *path;

    if (NUMBER_OF_ARGUMENTS_HELP == argc && EXIT_SUCCESS == strcmp(argv[HELP_INDEX], "--help"))
        return helper(SUCCESS);
    if (EXIT_FAILURE == error_handling(argc, argv))
        return helper(FAILURE);
    port = (uint32_t) atoi(argv[PORT_INDEX]);
    path = (const uint8_t *) argv[PATH_INDEX];
    if (EXIT_FAILURE == activate_ftp_server(port, path))
        return EXIT_FAILURE_EPI;
    return EXIT_SUCCESS;
}
