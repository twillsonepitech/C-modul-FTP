/**
 * @file activate_ftp_server.c
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Initializing ftp class object to manage server.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdint.h>
#include <limits.h>
#include <unistd.h>
#include "new.h"
#include "init.h"
#include "define.h"
#include "functions.h"

uint8_t *xgetcwd(const uint8_t *path)
{
    uint8_t *cwd;

    cwd = (uint8_t *)calloc(PATH_MAX, sizeof(uint8_t));
    if (NULL == cwd) {
        LOG_ERROR("calloc() function: FAILURE.");
        return NULL;
    }
    if (FUNCTION_RETURN_ERROR == chdir((const char *)path)) {
        LOG_ERROR("chdir() function: FAILURE.");
        return NULL;
    }
    if (NULL == getcwd((char *)cwd, PATH_MAX)) {
        LOG_ERROR("getcwd() function: FAILURE.");
        return NULL;
    }
    return cwd;
}

uint8_t activate_ftp_server(const uint32_t port, const uint8_t *path)
{
    int32_t return_from_function;
    Object *ftp;
    uint8_t *new_path;
    struct server_ftp_s server_ftp;

    new_path = xgetcwd(path);
    if (NULL == new_path) {
        LOG_ERROR("Change working directory: FAILURE.");
        return EXIT_FAILURE;
    }
    else {
        LOG_WARN("Change working directory: SUCCESS.");
    }
    ftp = new(_Ftp, port, new_path, INIT_STRUCT);
    if (NULL == ftp) {
        return EXIT_FAILURE;
    }
    return_from_function = init_server_ftp_struct(&server_ftp, ((Class *)ftp)->__gprt__(ftp));
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    return_from_function = handle_server_ftp(&server_ftp, ((Class *)ftp)->__gpth__(ftp));
    if (EXIT_FAILURE == return_from_function) {
        return EXIT_FAILURE;
    }
    free(new_path);
    delete(ftp);
    return EXIT_SUCCESS;
}

static const Ftp _description = { {
        .__size__ = sizeof(Ftp),
        .__name__ = "c-modular-ftp-server",
        .__ctor__ = (ctor_t)&Ctor,
        .__dtor__ = (dtor_t)&Dtor,
        .__gprt__ = (get_port_t)&Get_port,
        .__gpth__ = (get_path_t)&Get_path,
        .__sprt__ = (set_port_t)&Set_port,
        .__spth__ = (set_path_t)&Set_path,
    },
    .port = INIT_INTEGER,
    .path = INIT_POINTER
};

const Class *_Ftp = (const Class *)&_description;
