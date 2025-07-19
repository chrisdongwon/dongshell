# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwon <cwon@student.42bangkok.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 16:52:39 by cwon              #+#    #+#              #
#    Updated: 2025/07/17 15:21:29 by cwon             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

HEADER = \
	libft.h \
	ft_printf/ft_printf.h \
	ft_string/ft_string.h \
	get_next_line/get_next_line.h
SRC = \
	ft_abs.c \
	ft_atof.c \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_fnmatch.c \
	ft_fnmatch.c \
	ft_greater_than.c \
	ft_indexof.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isfloat.c \
	ft_isinteger.c \
	ft_ismember.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_less_than.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_str_realloc.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strndup.c \
	ft_strnlen.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strstr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_utoa.c
PRINTF_SRC = \
	ft_printf/convert.c \
	ft_printf/convert_literal.c \
	ft_printf/convert_pointer.c \
	ft_printf/ft_printf.c \
	ft_printf/pad.c \
	ft_printf/convert_hex.c \
	ft_printf/convert_numeric.c \
	ft_printf/extract.c
STRING_SRC = ft_string/ft_string.c
GNL_SRC = get_next_line/get_next_line.c
OBJ = $(SRC:.c=.o) $(PRINTF_SRC:.c=.o) $(GNL_SRC:.c=.o) $(STRING_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
