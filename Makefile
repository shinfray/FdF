# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/06/01 12:15:40 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:

NAME:=	fdf

BUILD_DIR:= build
SRCS_DIR:= srcs

SRCS_FDF:= 	actions.c \
			bresenham.c \
			initialize_quit.c \
			interface.c \
			keyboard_events.c \
			main.c \
			mouse_events.c \
			parse.c \
			parse_utils.c \
			print_screen.c \
			projection.c
SRCS:=	${addprefix ${SRCS_DIR}/,${SRCS_FDF}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

LIBFT:=	libs/libft/libft.a
MLX:=	libs/minilibx_macos/libmlx.a
CFLAGS:= -Wall -Wextra -Werror

# ROOT_INC_DIRS:= includes libs/libft/includes libs/minilibx_macos
# INC_DIRS:= ${shell find ${ROOT_INC_DIRS} -type d}
INC_DIRS:= includes libs/libft/includes libs/minilibx_macos

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP

LIB_DIR:= libs/libft libs/minilibx_macos
LDFLAGS:= ${addprefix -L,${LIB_DIR}}
LDLIBS:= -lm -lft -lmlx -framework OpenGL -framework Appkit

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${MLX}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@

${LIBFT}:
	${MAKE} -C ${dir ${LIBFT}}

${MLX}:
	${MAKE} -C ${dir ${MLX}}

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	${MAKE} clean -C ${dir ${LIBFT}}
	${RM} ${BUILD_DIR}

fclean: clean
	${MAKE} clean -C ${dir ${MLX}}
	${RM} ${LIBFT}
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}
