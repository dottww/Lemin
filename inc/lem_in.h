/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/17 17:56:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define ONLY_DISPLAY_SOLUTION	2
# define DISPLAY_PATHS			4
# define L1 ((t_input *)(alst->content))->line
# define L2 ((t_input *)((*alst)->content))->line

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					end;
	int					path_id;
	int					ant_id;
	 int		population;
	int					new_path_id;
	bool				deviation;
	bool				visited;
	bool				dead_end;
	t_list				*next;
	t_list				*new_next;
	t_list				*previous;
	t_list				*links;
}						t_room;

typedef struct			s_antfarm
{
	int					ant_qty;
	unsigned long		rounds;
	unsigned int		option;
	int					id;
	t_list				*rooms;
	t_list				*start;
	t_list				*end;
	t_list				*ants;
}						t_antfarm;

typedef struct			s_link
{
	int					usage;
	t_list				*room;
}						t_link;

typedef struct			s_path
{
	int					id;
	unsigned long		sent;
	int					len;
	bool				complete;
	t_list				*room;
}						t_path;

typedef struct			s_ant
{
	int					id;
	t_room				*position;
}						t_ant;

typedef struct			s_queue
{
	t_list				*room;
}						t_queue;

typedef struct			s_input
{
	char				*line;
}						t_input;

/*
** ----------------------------- INIT ------------------------------------------
*/
int						register_rooms(t_antfarm *antfarm, t_list *alst);
int						init_paths(t_list **paths, t_list *start
						, unsigned int option);
int						init_ants(t_antfarm *antfarm);
/*
** ------------------------------ ADD ------------------------------------------
*/
int						add_room(t_antfarm *antfarm, t_list **alst);
int						add_link(t_antfarm *antfarm, char *line);
int						add_step(t_list **steps, t_list *room);
int						add_path(t_list **paths);
int						add_ant(int id, t_antfarm *antfarm);
/*
** ----------------------------- ALGO -----------------------------------------
*/
bool					get_paths(t_antfarm *antfarm, t_list *start
						, t_list *end, t_list **paths);
bool					bfs(t_list *start, t_list *end, t_list **queue);
unsigned long			test_solution(t_antfarm *antfarm, t_list *paths
						, unsigned int ant_qty);
void					update_data(t_antfarm *antfarm, unsigned long rounds
						, t_list **paths);
void					complete_paths(t_list **paths);
void					set_links_usage(t_list *end, t_list **queue);
int						init_queue(t_list **queue, t_list *start);
int						complete_queue(t_list *queue, t_list *end);
bool					going_to_deviate(t_list *current, t_list *room);
bool					deviation_reaches_end(t_list *deviation_room
						, t_list *end);
bool					start_linked_to_end(t_list *start, t_list *end);
bool					init_the_only_path(t_list **paths, t_antfarm *antfarm);
/*
** ---------------------------- DISPLAY ----------------------------------------
*/
void					print_paths(t_list *paths);
void					print_steps(t_list *steps);
void					print_output(t_antfarm *antfarm, t_list *paths);
void					print_input(t_list *alst);
/*
** ---------------------------- TOOLS ------------------------------------------
*/
int						free_input(t_list **lst, char *exit_msg);
// int						ret_strtab_free(int ret, char **tab);
int						print_and_free(t_antfarm *antfarm, t_list **input
						, t_list **paths, char *msg);
void					del_path(void *content, size_t size);
int						get_input(t_list **alst);
int						is_comment(char *line);
int						is_start_end(char *line);
void					del_steps(void *content, size_t size);
void					del_room(void *content, size_t size);
void					del_input(void *content, size_t size);
// void					del_queue_elem(void *content, size_t size);
#endif
