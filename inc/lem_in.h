/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:49:34 by weilin            #+#    #+#             */
/*   Updated: 2020/06/23 20:19:09 by mdavid           ###   ########.fr       */
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
# define STARTROOM ((t_room *)atf->start->content)
# define ENDROOM ((t_room *)atf->end->content)
# define NEXTROOM ((t_room *)position->next->content)
# define ANT ((t_ant *)ant_troop->content)->position
# define NEXTANT (((t_ant *)ant_troop->next->content)->position


typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					s_t;
	int					path_id;
	int					ant_id;
	int					population;
	int					new_path_id; //PATH
	bool				deviation;//BFS route
	bool				visited;//BFS route
	bool				dead_end;
	t_list				*next;
	t_list				*new_next; //PATH
	t_list				*previous; //BFS route
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

typedef struct			s_link // What the point !?!? link is encapsulated in t_list and room also thus 2 lyers of encapsulation !!
{
	int					usage;
	t_list				*room;
}						t_link;

/*
** id = index to distinguish the different path 
** sent = number of ants which will take the path
** len = number of link/edge constituting the path
** complete = boolean var, 
** room
*/
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

typedef struct			s_route
{
	t_list				*room;
}						t_route;

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
bool					bfs(t_list *start, t_list *end, t_list **route);
unsigned long			test_solution(t_antfarm *antfarm, t_list *paths
						, unsigned int ant_qty);
void					printpath_update_data(t_antfarm *antfarm, unsigned long rounds
						, t_list **paths);
void					complete_paths(t_list **paths);
void					set_links_usage(t_list *end, t_list **route);
// int						init_route(t_list **route, t_list *start);
int						complete_route(t_list *route, t_list *end);
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
void		print_route(t_list *rt);//DEL LATER

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
void					ft_delcontent(void *content, size_t size);
void					del_room(void *content, size_t size);
void					del_input(void *content, size_t size);
// void					del_route_elem(void *content, size_t size);
#endif