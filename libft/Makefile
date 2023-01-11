# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 16:37:12 by shinfray          #+#    #+#              #
#    Updated: 2023/01/11 23:21:23 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	srcs/libft/ft_isalpha.c \
				srcs/libft/ft_isdigit.c \
				srcs/libft/ft_isalnum.c \
				srcs/libft/ft_isascii.c \
				srcs/libft/ft_isprint.c \
				srcs/libft/ft_strlen.c \
				srcs/libft/ft_memset.c \
				srcs/libft/ft_bzero.c \
				srcs/libft/ft_memcpy.c \
				srcs/libft/ft_memmove.c \
				srcs/libft/ft_strlcpy.c \
				srcs/libft/ft_strlcat.c \
				srcs/libft/ft_toupper.c \
				srcs/libft/ft_tolower.c \
				srcs/libft/ft_strchr.c \
				srcs/libft/ft_strrchr.c \
				srcs/libft/ft_strncmp.c \
				srcs/libft/ft_memchr.c \
				srcs/libft/ft_memcmp.c \
				srcs/libft/ft_strnstr.c \
				srcs/libft/ft_atoi.c \
				srcs/libft/ft_calloc.c \
				srcs/libft/ft_strdup.c \
				srcs/libft/ft_substr.c \
				srcs/libft/ft_strjoin.c \
				srcs/libft/ft_strtrim.c \
				srcs/libft/ft_split.c \
				srcs/libft/ft_itoa.c \
				srcs/libft/ft_strmapi.c \
				srcs/libft/ft_striteri.c \
				srcs/libft/ft_putchar_fd.c \
				srcs/libft/ft_putstr_fd.c \
				srcs/libft/ft_putendl_fd.c \
				srcs/libft/ft_putnbr_fd.c \
				srcs/libft/ft_lstnew_bonus.c \
				srcs/libft/ft_lstadd_front_bonus.c \
				srcs/libft/ft_lstsize_bonus.c \
				srcs/libft/ft_lstlast_bonus.c \
				srcs/libft/ft_lstadd_back_bonus.c \
				srcs/libft/ft_lstdelone_bonus.c \
				srcs/libft/ft_lstclear_bonus.c \
				srcs/libft/ft_lstiter_bonus.c \
				srcs/libft/ft_lstmap_bonus.c \
				srcs/ft_printf/ft_printf.c \
				srcs/ft_printf/ft_printf_flags.c \
				srcs/ft_printf/ft_printf_hexa.c \
				srcs/get_next_line/get_next_line_bonus.c \
				srcs/get_next_line/get_next_line_utils_bonus.c

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
