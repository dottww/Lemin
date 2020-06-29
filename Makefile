# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 16:25:20 by weilin            #+#    #+#              #
#    Updated: 2020/06/29 21:27:40 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

LEM_IN_FILES += add_link
LEM_IN_FILES += add_room
LEM_IN_FILES += get_ant
LEM_IN_FILES += get_antfarm
LEM_IN_FILES += get_path
LEM_IN_FILES += lem_in
LEM_IN_FILES += tools_ant
LEM_IN_FILES += tools_bfs
LEM_IN_FILES += tools_exit
LEM_IN_FILES += tools_input
LEM_IN_FILES += tools_links
LEM_IN_FILES += tools_path
LEM_IN_FILES += tools_print
LEM_IN_FILES += tools_room
LEM_IN_FILES += tools_route
LEM_IN_FILES += tools_route2

CCH_DIR = cache/
SRC_DIR = src/
INC_DIR = inc/
LINC_DIR = libft/inc/
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a

INCS += $(INC_DIR)lem_in.h 
INCS += $(LINC_DIR)libft.h 
INCS += $(LINC_DIR)ft_printf.h 
INCS += $(LINC_DIR)get_next_line.h

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LINC_DIR)
LEAKS = -fsanitize=address
RM = rm -rf

LEM_IN_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(LEM_IN_FILES)))
LEM_IN_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(LEM_IN_FILES)))

vpath  %.h inc/
vpath  %.h libft/inc/

all: $(LEM_IN)

$(LEM_IN): $(LIBFT) $(CCH_DIR) $(LEM_IN_OBJ) $(INCS)
	$(CC) $(FLAGS) -o $@ $< $(LEM_IN_OBJ) -L $(LIB_DIR) -lft

debug: $(LIBFT) $(CCH_DIR) $(LEM_IN_OBJ) $(INCS)
	$(CC) $(FLAGS) $(LEAKS) -o $@ $< $(LEM_IN_OBJ) -L $(LIB_DIR) -lft

$(LIBFT): force
	@make -C libft all

force:
	@true

$(CCH_DIR)%.o: $(SRC_DIR)%.c $(INCS)| $(CCH_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(CCH_DIR):
	mkdir $@

clean:
	$(RM) $(CCH_DIR)
	$(RM) $(LEM_IN).dSYM
	$(RM) *.o
	$(RM) *.out*
	make -C libft clean
	
fclean: clean
	$(RM) $(LEM_IN)
	make -C libft fclean

re: fclean
	$(MAKE) all

norm:
	norminette $(SRC_DIR) $(INC_DIR) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm
