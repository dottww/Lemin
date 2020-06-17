# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weilin <weilin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/11 16:48:33 by weilin            #+#    #+#              #
#    Updated: 2020/06/16 08:12:59 by weilin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_IN = lem-in

LEM_IN_FILES += lem_in
LEM_IN_FILES += get_input
LEM_IN_FILES += add_rooms
LEM_IN_FILES += add_links
LEM_IN_FILES += init_antfarm
LEM_IN_FILES += find_paths
LEM_IN_FILES += init_paths
LEM_IN_FILES += init_ants
LEM_IN_FILES += add_ants
LEM_IN_FILES += update_queue
LEM_IN_FILES += deviation
LEM_IN_FILES += complete_paths
LEM_IN_FILES += update_links
LEM_IN_FILES += test_solution
LEM_IN_FILES += print_solution
LEM_IN_FILES += start_linked_to_end
LEM_IN_FILES += print_and_free
LEM_IN_FILES += print_paths
LEM_IN_FILES += print_input
LEM_IN_FILES += del_functions
LEM_IN_FILES += is_comment

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

CC = clang
FLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LINC_DIR)
RM = rm -rf

LEM_IN_SRC = $(addprefix $(SRC_DIR),$(addsuffix .c,$(LEM_IN_FILES)))
LEM_IN_OBJ = $(addprefix $(CCH_DIR),$(addsuffix .o,$(LEM_IN_FILES)))

vpath  %.h inc/
vpath  %.h libft/inc/

all: $(LEM_IN)

$(LEM_IN): $(LIBFT) $(CCH_DIR) $(LEM_IN_OBJ) $(INCS)
	$(CC) $(FLAGS) -o $@ $< $(LEM_IN_OBJ) -L $(LIB_DIR) -lft

$(LIBFT): force
	@make -C libft all
#it will call the makefile in the destination

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
