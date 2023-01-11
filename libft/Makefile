# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 16:37:12 by shinfray          #+#    #+#              #
#    Updated: 2023/01/11 17:44:39 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	src/libft/ft_isalpha.c \
				src/libft/ft_isdigit.c \
				src/libft/ft_isalnum.c \
				src/libft/ft_isascii.c \
				src/libft/ft_isprint.c \
				src/libft/ft_strlen.c \
				src/libft/ft_memset.c \
				src/libft/ft_bzero.c \
				src/libft/ft_memcpy.c \
				src/libft/ft_memmove.c \
				src/libft/ft_strlcpy.c \
				src/libft/ft_strlcat.c \
				src/libft/ft_toupper.c \
				src/libft/ft_tolower.c \
				src/libft/ft_strchr.c \
				src/libft/ft_strrchr.c \
				src/libft/ft_strncmp.c \
				src/libft/ft_memchr.c \
				src/libft/ft_memcmp.c \
				src/libft/ft_strnstr.c \
				src/libft/ft_atoi.c \
				src/libft/ft_calloc.c \
				src/libft/ft_strdup.c \
				src/libft/ft_substr.c \
				src/libft/ft_strjoin.c \
				src/libft/ft_strtrim.c \
				src/libft/ft_split.c \
				src/libft/ft_itoa.c \
				src/libft/ft_strmapi.c \
				src/libft/ft_striteri.c \
				src/libft/ft_putchar_fd.c \
				src/libft/ft_putstr_fd.c \
				src/libft/ft_putendl_fd.c \
				src/libft/ft_putnbr_fd.c \
				src/libft/ft_lstnew_bonus.c \
				src/libft/ft_lstadd_front_bonus.c \
				src/libft/ft_lstsize_bonus.c \
				src/libft/ft_lstlast_bonus.c \
				src/libft/ft_lstadd_back_bonus.c \
				src/libft/ft_lstdelone_bonus.c \
				src/libft/ft_lstclear_bonus.c \
				src/libft/ft_lstiter_bonus.c \
				src/libft/ft_lstmap_bonus.c \
				src/ft_printf/ft_printf.c \
				src/ft_printf/ft_printf_flags.c \
				src/ft_printf/ft_printf_hexa.c \
				src/get_next_line/get_next_line_bonus.c \
				src/get_next_line/get_next_line_utils_bonus.c

HEADERS		= includes/

OBJS		= ${SRCS:.c=.o}

.c.o		:
				${CC} ${CFLAGS} -I ${HEADERS} -c $< -o ${<:.c=.o}

NAME		= libft.a

CC			= @gcc

RM			= @rm -f

CFLAGS		= -Wall -Wextra -Werror

${NAME}:	${OBJS}
			@ar rcs ${NAME} ${OBJS}
			@echo "libft.a is ready to use"

all:		${NAME}

clean:
			${RM} ${OBJS}
			@echo "libft objects files cleaned"

fclean:		clean
			${RM} ${NAME}
			@echo "libft.a deleted"

re:			fclean all

.PHONY:		all clean fclean re
