# START of Makefile color and typo of messages
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m

_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
# END	of Makefile color and typo of messages

CC	?=	gcc

RM	?=	rm -rf

NAME	:=	c-modular-ftp-server
LIBS	=	# can be [-lm -> math], [-lpthread -> pthreads]...

TESTS_BIN	:=	*.gc*
TESTS_BIN_NAME	:=	unit_tests
TESTS_LIBS	:=	-lcriterion --coverage

CPPFLAGS	+=	-Wall -Wextra -iquote ./includes

CFLAGS	+=	-fPIC -pedantic

MAIN	=	${addsuffix .c, ${addprefix ./, main}}
SRCS	=	${addsuffix .c,								\
				${addprefix srcs/, init new \
				activate_ftp_server getter_and_setter }	\
			}
ALL_SRCS	:=	${MAIN}
ALL_SRCS	+=	${SRCS}

TESTS_SRCS	:=	${SRCS}
TESTS_SRCS	+=	${addsuffix .c,									\
					${addprefix tests/tests_, }	\
				}												\

OBJS	=	${ALL_SRCS:.c=.o}
TESTS_OBJS	:=	${TESTS_SRCS:.c=.o}

all:	${NAME} ${STATIC_NAME}

${NAME}:	${OBJS}
	@${CC} -o ${NAME} ${OBJS}
	@echo "${_BOLD}${_GREEN}Executable has been compiled.${_END}"

clean:
	${RM} ${OBJS}
	${RM} ${NAME}
	${RM} logs.out

fclean:	clean
	${RM} ${TESTS_OBJS}
	${RM} ./srcs/${TESTS_BIN}
	${RM} ./tests/${TESTS_BIN}
	${RM} ${TESTS_BIN_NAME}

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
