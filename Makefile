# START of Makefile color and typo of messages
_END='\033[0m'
_BOLD='\033[1m'
_UNDER='\033[4m'

_RED='\033[31m'
_GREEN='\033[32m'
_YELLOW='\033[33m'
_BLUE='\033[34m'
# END	of Makefile color and typo of messages

CC	?=	gcc

MAKE	?=	make

RM	?=	rm -rf

STATIC_LIB_FOLDERS	=	Get-Next-Line Lib-IO
LDLIBS				+=	-lgnl -lio
LDFLAGS				+=	${addprefix -L ./, ${STATIC_LIB_FOLDERS}}

NAME	:=	c-modular-ftp-server

TESTS_BIN	:=	*.gc*
TESTS_BIN_NAME	:=	unit_tests
TESTS_LIBS	:=	-lcriterion --coverage

CPPFLAGS	+=	-iquote ./includes
CPPFLAGS	+=	${addprefix -iquote ./, ${addsuffix ./includes, ${STATIC_LIB_FOLDERS}}}
CFLAGS		+=	-Wall -Wextra -Werror -fPIC -pedantic

MAIN	=	${addsuffix .c, ${addprefix ./, main}}
SRCS	=	${addsuffix .c,								\
				${addprefix srcs/, init new array \
				activate_ftp_server getter_and_setter \
				init_server_ftp handle_server_ftp	\
				client_linked_list manage_client }	\
			}
CMDS	=	${addsuffix .c,		\
				${addprefix srcs/commands/, user pass quit noop help \
				pwd cwd cdup list dele pasv retr stor port }			\
			}
ALL_SRCS	:=	${MAIN}
ALL_SRCS	+=	${SRCS}
ALL_SRCS	+=	${CMDS}

TESTS_SRCS	:=	${SRCS}
TESTS_SRCS	+=	${CMDS}
TESTS_SRCS	+=	${addsuffix .c,									\
					${addprefix tests/tests_, }	\
				}												\

OBJS	=	${ALL_SRCS:.c=.o}
TESTS_OBJS	:=	${TESTS_SRCS:.c=.o}

%.o : %.c
	@$ ${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@
	@echo "${CC} ${CFLAGS} ${CPPFLAGS} -c $< -o $@ ["${_GREEN}"OK"${_END}"]"
.SUFFIXES: .o .c

all:	dependencies ${NAME}

${NAME}:	${OBJS}
	@${CC} ${OBJS} ${LDFLAGS} ${LDLIBS} -o ${NAME}

dependencies:
	for folder in ${STATIC_LIB_FOLDERS} ; do \
		${MAKE} -C $$folder static ; \
	done

clean:
	${RM} ${OBJS}
	${RM} ${NAME}
	${RM} *.so
	${RM} *.out
	for folder in ${STATIC_LIB_FOLDERS} ; do \
		${MAKE} -C $$folder clean ; \
	done

fclean:	clean
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}
	${RM} ./srcs/${TESTS_BIN}
	${RM} ./tests/${TESTS_BIN}
	${RM} ./tests/fifo
	${RM} ./tests/outfile
	for folder in ${STATIC_LIB_FOLDERS} ; do \
		${MAKE} -C $$folder fclean ; \
	done

re:	fclean all

debug:	CFLAGS	+=	-g3
debug:	re

tests_run:	${TESTS_OBJS}
	${CC} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

valgrind:	CFLAGS	+=	-g3
valgrind:	${TESTS_OBJS}
	${CC} ${TESTS_LIBS} ${TESTS_OBJS} -o ${TESTS_BIN_NAME}
	valgrind --trace-children=yes --quiet ./${TESTS_BIN_NAME}
	${RM} ${TESTS_OBJS}
	${RM} ${TESTS_BIN_NAME}

.PHONY:	all clean fclean re debug tests_run valgrind
