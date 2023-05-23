# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 16:37:12 by shinfray          #+#    #+#              #
#    Updated: 2023/01/29 23:41:36 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:

NAME:=	libft.a

BUILD_DIR:= build
SRCS_DIR:= srcs

LIBFT_SRCS:=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

FTPRINTF_SRCS:=	ft_printf.c \
				ft_printf_flags.c \
				ft_printf_hexa.c

GNL_SRCS:=	get_next_line.c \
			get_next_line_utils.c

SRCS:=	${addprefix ${SRCS_DIR}/libft/, ${LIBFT_SRCS}}
SRCS+=	${addprefix ${SRCS_DIR}/ft_printf/, ${FTPRINTF_SRCS}}
SRCS+=	${addprefix ${SRCS_DIR}/get_next_line/, ${GNL_SRCS}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

CFLAGS:= -Wall -Wextra -Werror

ROOT_INC_DIRS:= includes
INC_DIRS:= ${shell find ${ROOT_INC_DIRS} -type d}

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP

ARFLAGS:= crs

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${AR} ${ARFLAGS} $@ ${OBJS}

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${BUILD_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

-include ${DEPS}
