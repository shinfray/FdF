# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/01/11 23:19:09 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=	

MAINSRC= main.c

HEADERS= includes/

LFT_HEADERS= libft/includes/

MLX_HEADERS= FdF_files/minilibx_macos/

OBJS=	${SRCS:.c=.o}

MAIN=	${MAINSRC:.c=.o}

NAME=	fdf

LIBFTNAME= libft.a

LIBFTPATH= libft/

LIBMLXPATH= FdF_files/minilibx_macos/

CC=		@gcc

RM=		@rm -f

CFLAGS=	-Wall -Wextra -Werror

all			:	${NAME}

${NAME}		:	${LIBFTNAME} ${MAIN} ${OBJS}
				${CC} -o ${NAME} \
				-I ${HEADERS} -I ${LFT_HEADERS} -I ${MLX_HEADERS} \
				${MAIN} ${OBJS} \
				-L${LIBFTPATH} -lft -L${LIBMLXPATH} -lmlx \
				-framework OpenGL -framework Appkit
				@echo "fdf is ready to use"

.c.o		:
				${CC} ${CFLAGS} \
				-I ${HEADERS} -I ${LFT_HEADERS} -I ${MLX_HEADERS} \
				-c $< -o ${<:.c=.o}

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
