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
#include "new.h"
#include "init.h"
#include "define.h"
#include "functions.h"

uint32_t activate_ftp_server(const uint32_t port, const uint8_t *path)
{
    Object *ftp;

    ftp = new(_Ftp, port, path);
    if (NULL == ftp)
        return EXIT_FAILURE;
    fprintf(stdout, "Port: [%d] & Path: [%s].\n", ((Class *)ftp)->__gport__(ftp), ((Class *)ftp)->__gpath__(ftp));
    return EXIT_SUCCESS;
}

static const Ftp _description = {
    {
        .__size__ = sizeof(Ftp),
        .__name__ = "c-modular-ftp-server",
        .__ctor__ = (ctor_t)&ctor,
        .__dtor__ = (dtor_t)&dtor,
        .__gport__ = (get_port_t)&get_port,
        .__gpath__ = (get_path_t)&get_path,
        .__sport__ = (set_port_t)&set_port,
        .__spath__ = (set_path_t)&set_path,
    },
    .port = INIT_INTEGER,
    .path = INIT_POINTER
};

const Class *_Ftp = (const Class *)&_description;
