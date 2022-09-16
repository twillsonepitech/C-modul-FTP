/**
 * @file object.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Main functions of Class and Object
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdarg.h>
#include "raise.h"
#include "struct.h"

typedef void Object;
typedef void (*ctor_t)(Object *this, va_list *va_list_args);
typedef void (*dtor_t)(Object *this);
typedef uint32_t (*get_port_t)(Object *this);
typedef const uint8_t *(*get_path_t)(Object *this);
typedef Object *(*set_port_t)(Object *this, const uint32_t port);
typedef Object *(*set_path_t)(Object *this, const uint8_t *path);

typedef struct {
    const size_t __size__;
    const char *__name__;
    ctor_t __ctor__;
    dtor_t __dtor__;
    get_port_t __gprt__;
    get_path_t __gpth__;
    set_port_t __sprt__;
    set_path_t __spth__;
} Class;

typedef struct {
    Class __base__;
    uint32_t port;
    const uint8_t *path;
    struct server_ftp_s server_ftp;
} Ftp;

extern const Class *_Ftp;
