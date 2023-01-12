# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/01/12 01:00:18 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=	
MAINSRC= main.c
OBJS=	${SRCS:.c=.o}
MAIN=	${MAINSRC:.c=.o}
NAME=	fdf
LIBFTNAME= libft.a
LIBFTPATH= libft/
CC=		@gcc
RM=		@rm -f
CFLAGS=	-Wall -Wextra -Werror
CPPFLAGS= -Iincludes/ -Ilibft/includes/ -IFdF_files/minilibx_macos/
LDFLAGS= -Llibft -LFdF_files/minilibx_macos
LDLIBS=	-lft -lmlx ${FRAMEWORKS}
FRAMEWORKS= -framework OpenGL -framework Appkit

all			:	${NAME}

${NAME}		:	${LIBFTNAME} ${MAIN} ${OBJS}
				${CC} ${CPPFLAGS} ${LDFLAGS} ${LDLIBS} \
				${MAIN} ${OBJS} \
				-o ${NAME}
				@echo "fdf is ready to use"

${LIBFTNAME}:
				@make -C ${LIBFTPATH}

clean		:
				@make clean -C ${LIBFTPATH}
				${RM} ${OBJS} ${MAIN}
				@echo "fdf objects files deleted"

fclean		:	clean
				${RM} ${LIBFTPATH}${LIBFTNAME}
				${RM} ${NAME}
				@echo "fdf executable and libft.a deleted"

re			:	fclean all

.PHONY		:	all clean fclean re
