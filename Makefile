# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/01/12 18:14:47 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=	srcs/main.c
OBJS=	${SRCS:.c=.o}
NAME=	fdf
LIBFTNAME= libft.a
LIBFTPATH= libft/
CFLAGS=	-Wall -Wextra -Werror
INC_DIR= includes/ libft/includes/ FdF_files/minilibx_macos/
LIB_DIR= libft/ FdF_files/minilibx_macos/
CPPFLAGS= ${addprefix -I,${INC_DIR}}
LDFLAGS= ${addprefix -L,${LIB_DIR}}
LDLIBS=	-lm -lft -lmlx -framework OpenGL -framework Appkit

all			:	${NAME}

${NAME}		:	${OBJS} ${LIBFTNAME}
				${CC} ${CPPFLAGS} ${LDFLAGS} ${LDLIBS} ${OBJS} -o ${NAME}

${LIBFTNAME}:
				make -C ${LIBFTPATH}

clean		:
				make clean -C ${LIBFTPATH}
				${RM} ${OBJS} ${MAIN}

fclean		:	clean
				${RM} ${LIBFTPATH}${LIBFTNAME}
				${RM} ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re
