# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/01/16 15:55:17 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR:= srcs/
SRCSFDF:= main.c
SRCS:=	${addprefix ${SRCSDIR},${SRCSFDF}}
OBJS:=	${SRCS:%.c=%.o}
NAME:=	fdf
LIBFT:=	libft/libft.a
CFLAGS:= -Wall -Wextra -Werror
INC_DIR:= includes/ libft/includes/ FdF_files/minilibx_macos/
LIB_DIR:= libft/ FdF_files/minilibx_macos/
CPPFLAGS:= ${addprefix -I,${INC_DIR}}
LDFLAGS:= ${addprefix -L,${LIB_DIR}}
LDLIBS:= -lm -lft -lmlx -framework OpenGL -framework Appkit

all			:	${NAME}

${NAME}		:	${OBJS} ${LIBFT}
				${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@

${LIBFT}:
				${MAKE} -C ${dir ${LIBFT}}

clean		:
				${MAKE} clean -C ${dir ${LIBFT}}
				${RM} ${OBJS}

fclean		:	clean
				${RM} ${LIBFT}
				${RM} ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re
