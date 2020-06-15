# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by weilin            #+#    #+#              #
#    Updated: 2020/06/15 23:10:09 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OTH_DIR = other/
OTH_FILES = get_next_line

LIB_DIR = generic/
LIB_FILES = ft_tolower\
		ft_toupper\
		ft_isalpha\
		ft_isdigit\
		ft_isalnum\
		ft_isascii\
		ft_isprint\
		ft_isnumber\
		ft_strlen\
		ft_strcpy\
		ft_strncpy\
		ft_strcmp\
		ft_strncmp\
		ft_strcat\
		ft_strncat\
		ft_strlcat\
		ft_atoi\
		ft_strdup\
		ft_strdup_sec\
		ft_strstr\
		ft_strnstr\
		ft_strchr\
		ft_strrchr\
		ft_memset\
		ft_memcpy\
		ft_memccpy\
		ft_memmove\
		ft_memchr\
		ft_memcmp\
		ft_bzero\
		ft_memalloc\
		ft_memdel\
		ft_strnew\
		ft_strnew_c\
		ft_strdel\
		ft_strclr\
		ft_striter\
		ft_striteri\
		ft_strmap\
		ft_strmapi\
		ft_strequ\
		ft_strnequ\
		ft_strsub\
		ft_strjoin\
		ft_strtrim\
		ft_strsplit_c\
		ft_strsplit_wd\
		ft_itoa\
		ft_putchar\
		ft_putstr\
		ft_putnbr\
		ft_putendl\
		ft_putchar_fd\
		ft_putstr_fd\
		ft_putnbr_fd\
		ft_putendl_fd\
		ft_lstnew\
		ft_lstdelone\
		ft_lstdel\
		ft_lstadd\
		ft_lstiter\
		ft_lstmap\
		ft_int_len\
		ft_sqrt\
		ft_count_if\
		ft_print_words_tables\
		ft_wd\
		ft_wd_c\
		ft_wd_num\
		ft_count_c\
		ft_strreset\
		ft_strtolower\
		ft_strtab_free\
		ft_lstlen\
		ft_lstappend\
		ft_atoull\
		ft_isinteger\
		ft_iswhitespace\
		ft_split_whitespaces\
		ft_lstprepend\
		ft_lstcount\
		ft_lst_mergesort\
		ft_lstrev\
		ft_atoi_int\
		ret_strtab_free
		
#ft_split_whitespaces might be slow
#ft_lstlen del
#re-check ft_lst_mergesort
#re-check ft_lstrev

PTF_DIR = ft_printf/
PTF_FILES = ft_printf parse tool type_csp print_chars print_addr type_di base \
		type_ox print_int type_uint parse_flags

FILES+= $(addprefix $(OTH_DIR),$(OTH_FILES))
FILES+= $(addprefix $(LIB_DIR),$(LIB_FILES))
FILES+= $(addprefix $(PTF_DIR),$(PTF_FILES))

CC = gcc
FLAG = -Wall -Wextra -Werror -g -I $(INC_DIR)

RM = rm -rf

CCH_DIR = cache/
SRC_DIR = src/
INC_DIR = inc/

SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(FILES)))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^
	ranlib $@
# Running "ar s" on an archive is equivalent to running ranlib on it.
# $^ means the all prerequisites

$(CCH_DIR)%.o: $(SRC_DIR)%.c | $(CCH_DIR)
	$(CC) $(FLAG) -c $< -o $@
#if .o is older than .c, then do the content
# $< means the first prerequisite
# | The names of all the order-only prerequisites, with spaces between them.

$(CCH_DIR):
	mkdir $@
	mkdir $(CCH_DIR)$(OTH_DIR)
	mkdir $(CCH_DIR)$(LIB_DIR)
	mkdir $(CCH_DIR)$(PTF_DIR)

clean:
	$(RM) $(CCH_DIR)
	$(RM) *.o
	$(RM) *.out*

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

norm:
	norminette $(SRC) $(INC_DIR) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm
