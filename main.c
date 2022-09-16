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
#include <time.h>
#include "raise.h"
#include "define.h"
#include "functions.h"

uint8_t helper(const enum return_code_e return_code)
{
    const char *help_message[] = {
        "USAGE: ./myftp port path",
        "\tport  is the port number on which the server socket listens",
        "\tpath  is the path to the home directory for the Anonymous user",
        NULL
    };
    int32_t index_per_iteration;

    index_per_iteration = INIT_INTEGER;
    while (help_message[index_per_iteration] != NULL)
    {
        fprintf(return_code == SUCCESS ? stdout : stderr, "%s\n", help_message[index_per_iteration]);
        index_per_iteration++;
    }
    return return_code == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE_EPI;
}

uint8_t error_handling(int32_t argc, char const *argv[])
{
    const uint8_t *port;
    const uint8_t *path;
    struct stat sb;
    int32_t index_per_iteration;

    if (NUMBER_OF_ARGUMENTS != argc)
    {
        LOG_ERROR("Bad number of arguments.");
        return EXIT_FAILURE;
    }
    port = (const uint8_t *) argv[PORT_INDEX];
    path = (const uint8_t *) argv[PATH_INDEX];
    index_per_iteration = INIT_INTEGER;
    while (port[index_per_iteration] != '\0')
    {
        if (false == isdigit(port[index_per_iteration]))
        {
            LOG_ERROR("Port contains other than digits.");
            return EXIT_FAILURE;
        }
        index_per_iteration++;
    }
    if (FUNCTION_RETURN_ERROR == stat((const char *) path, &sb) || false == S_ISDIR(sb.st_mode))
    {
        LOG_ERROR("Path doesn't exist or is not a directory.");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int32_t main(int32_t argc, char const *argv[])
{
    srandom(time(NULL));
    int32_t return_from_function;
    uint32_t port;
    const uint8_t *path;

    return_from_function = strcmp(argv[HELP_INDEX], "--help");
    if (NUMBER_OF_ARGUMENTS_HELP == argc && EXIT_SUCCESS == return_from_function)
    {
        return helper(SUCCESS);
    }
    return_from_function = error_handling(argc, argv);
    if (EXIT_FAILURE == return_from_function)
    {
        return helper(FAILURE);
    }
    port = (uint32_t) atoi(argv[PORT_INDEX]);
    path = (const uint8_t *) argv[PATH_INDEX];
    return_from_function = activate_ftp_server(port, path);
    if (EXIT_FAILURE == return_from_function)
    {
        return EXIT_FAILURE_EPI;
    }
    return EXIT_SUCCESS;
}
