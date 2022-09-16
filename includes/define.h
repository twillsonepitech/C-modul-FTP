/**
 * @file define.h
 * @author Thomas Willson (thomas.willson@epitech.eu)
 * @brief Define, constant that are used for return value or check function return.
 * @version 0.1
 * @date 2022-07-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#define ZERO    (0)
#define ONE     (1)
#define TWO     (2)
#define THREE   (3)
#define FOUR    (4)
#define FIVE    (5)

#if !defined(EXIT_SUCCESS)
# define EXIT_SUCCESS    (0)
#endif // EXIT_SUCCESS
#if !defined(EXIT_FAILURE)
# define EXIT_FAILURE    (1)
#endif // EXIT_FAILURE

#define EXIT_FAILURE_FTP    (2)
#define EXIT_FAILURE_EPI    (84)
#define FUNCTION_RETURN_ERROR   (-1)

#define NUMBER_OF_ARGUMENTS_HELP    (2)
#define NUMBER_OF_ARGUMENTS (3)
#define HELP_INDEX  (1)
#define PORT_INDEX  (1)
#define PATH_INDEX  (2)
#define INIT_INTEGER    (0)
#define INIT_POINTER    (NULL)
#define INIT_STRUCT     (0)
#define MODE_INFO   (1)
#define MODE_PRNT   (2)
#define MIN_PORT    (1024)
#define MAX_PORT    (64000)
#define READ_SIZE   (50)
#define IPv1        (0)
#define IPv2        (1)
#define IPv3        (2)
#define IPv4        (3)
#define PORT1       (4)
#define PORT2       (5)
#define BASE_TEN    (10)
#define NETWORK_SUCCESS         (1)
#define NETWORK_FAILURE_ADDR    (0)
#define NETWORK_FAILURE_AF      (-1)

#define sizeof_array(array) (sizeof(array) / sizeof(array[0]))

#define SOCK_PROTOCOL   (0)
#define LISTEN_BACKLOG  (50)
#define RESPONDING_CLIENT(fd, in_fd)    (fd == in_fd)
#define NETCAT(i, j)    (i == '\n' && j != '\r')
#define TELNET(i, j)    (i == '\n' && j == '\r')
#define TELNET_EOL  ("\r\n")

#if !defined(FILE_EXIST)
# include <unistd.h>
# define FILE_EXIST(pathname)   (access(pathname, F_OK) == 0)
# define NO_SUCH_FILE           ("No such file or directory")
#endif // FILE_EXIST

#if !defined(FILE_PERMISSION)
# include <unistd.h>
# define FILE_PERMISSION(pathname)  (access(pathname, R_OK) == 0)
# define PERMISSION_DENIED          ("Permission denied")
#endif // FILE_PERMISSION

static const enum return_code_e {
    SUCCESS,
    FAILURE,
} return_code_e;

#define LOG_INFO(__msg__)       fprintf(stderr, "[\033[0;36mINFO\033[0m] [FILE: %s], [LINE: %d], [FUNCTION: %s], [MESSAGE: %s].\n", __FILE__, __LINE__, __func__, __msg__);
#define LOG_WARN(__msg__)       fprintf(stderr, "[\033[0;33mWARN\033[0m] [FILE: %s], [LINE: %d], [FUNCTION: %s], [MESSAGE: %s].\n", __FILE__, __LINE__, __func__, __msg__);
#define LOG_ERROR(__msg__)      fprintf(stderr, "[\033[0;31mERROR\033[0m] [FILE: %s], [LINE: %d], [FUNCTION: %s], [MESSAGE: %s].\n", __FILE__, __LINE__, __func__, __msg__);
#define LOG_CLIENT(fd, __msg__) fprintf(stderr, "   [\033[0;32mCLIENT\033[0m] [FROM FD: n°%d], [MESSAGE: %s].\n", fd, __msg__);

#if !defined(IO_STREAM_DEFINITION)
# define IO_STREAM_DEFINITION    (1)
# include <stdio.h>
typedef FILE *(*__io_stream_open_fn_t)(const char *, const char *);
typedef int (*__io_stream_close_fn_t)(FILE *);
#endif // IO_STREAM_DEFINITION

#define IO_FILE_ERR "/bin/ls: cannot access '%s': No such file or directory.\n"

/**
 * @brief   FILE TRANSFER CODE
 * 
 */
#define FTP_CODE_120    ("120 Service ready in nnn minutes.")
#define FTP_CODE_125    ("125 Data connection already open; transfer starting.")
#define FTP_CODE_150    ("150 File status okay; about to open data connection.")

/**
 * @brief   SUCCESS CODE FTP
 * 
 */
#define FTP_CODE_200    ("200 Command okay.")
#define FTP_CODE_214_1  ("214- The following commands are recognized.")
#define FTP_CODE_214_2  ("\r\n214 Help message.")
#define FTP_CODE_220    ("220 Service ready for new user.")
#define FTP_CODE_221    ("221 Service closing control connection.")
#define FTP_CODE_226    ("226 Closing data connection.")
#define FTP_CODE_227    ("227 Entering Passive Mode (%s)")
#define FTP_CODE_230    ("230 User logged in, proceed.")
#define FTP_CODE_250    ("250 Requested file action okay, completed.")
#define FTP_CODE_257    ("257 \"%s\" is current directory.")
#define FTP_CODE_331    ("331 User name okay, need password.")

/**
 * @brief   FAILURE CODE FTP
 * 
 */
#define FTP_CODE_425    ("425 Can't build data connection: Connection refused.")
#define FTP_CODE_500    ("500 Command not understood.")
#define FTP_CODE_502    ("502 Unknown command.")
#define FTP_CODE_503    ("503 Login with USER first.")
#define FTP_CODE_530_1  ("530 Please login with USER and PASS.")
#define FTP_CODE_530_2  ("530 Login incorrect.")
#define FTP_CODE_550    ("550 %s: %s.")
#define FTP_CODE_553    ("553 %s: Permission denied.")

static const enum commands_e {
    USER, PASS, NOOP, QUIT,
    HELP, PWD, CWD, CDUP,
    PASV, PORT, RETR, STOR,
    LIST, DELE, NILL
} commands_e;

#if !defined(WRITE_CODE)
# include <stdio.h>
# include "functions.h"
# define WRITE_CODE(fd, fmt, ...)      \
    do {                               \
        uint8_t *nfmt = make_message(fmt, __VA_ARGS__); \
        dprintf(fd, (const char *)nfmt, __VA_ARGS__);   \
        dprintf(fd, "%s", TELNET_EOL);  \
        free(nfmt);                     \
    } while (SUCCESS);
#endif // WRITE_CODE
