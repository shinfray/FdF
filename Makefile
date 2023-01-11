# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/01/11 19:04:54 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	

MAINSRCS	= 	main.c

HEADERS		= 	includes/

LFT_HEADERS	=	libft/includes/

MLX_HEADERS	=	FdF_files/minilibx_macos/

OBJS		= 	${SRCS:.c=.o}

MAIN		= 	${MAINSRCS:.c=.o}

NAME		= 	fdf

LIBFTNAME	= 	libft.a

LIBFTPATH	=	libft/

LIBMLXPATH	=	FdF_files/minilibx_macos/

CC			= 	@gcc

RM			= 	@rm -f

CFLAGS		= 	-Wall -Wextra -Werror

.c.o		:
				${CC} ${CFLAGS} \
				-I ${HEADERS} -I ${LFT_HEADERS} -I ${MLX_HEADERS} \
				-c $< -o ${<:.c=.o}

${NAME}		:	${LIBFTNAME} ${MAIN} ${OBJS}
				${CC} -o ${NAME} \
				-I ${HEADERS} -I ${LFT_HEADERS} -I ${MLX_HEADERS} \
				${MAIN} ${OBJS} \
				-L${LIBFTPATH} -lft -L${LIBMLXPATH} -lmlx \
				-framework OpenGL -framework Appkit
				@echo "fdf is ready to use"

${LIBFTNAME}:
				@make -C ${LIBFTPATH}

all			:	${NAME}

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
