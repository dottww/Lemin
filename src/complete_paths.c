/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:55:42 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/23 20:17:58 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		elem_complete_path(t_list *path, t_list *room) // reconstruction of path based on usage of link (follow the -1)
{
	t_list	*link;
	t_list	*next_room;
	int		path_id;

	path_id = ((t_path *)path->content)->id;
	link = ((t_room *)room->content)->links;
	if (((t_room *)room->content)->s_t == 1)
		((t_path *)path->content)->complete = true;
	while (link)
	{
		if (((t_link *)link->content)->usage == -1)
		{
			// ft_printf("-------path[%s],len=%d\n"
			// ,(char *)((t_room *)((t_link *)link->content)->room->content)->name
			// ,((t_path *)path->content)->len);
			((t_path *)path->content)->len++;
			next_room = ((t_link *)link->content)->room;
			((t_room *)room->content)->new_next = next_room;
			((t_room *)room->content)->new_path_id = path_id;
			elem_complete_path(path, next_room);
			return ;
		}
		link = link->next;
	}
}

static int		sort_by_len(void *a, void *b)
{
	t_path	*path1;
	t_path	*path2;

	path1 = (t_path *)a;
	path2 = (t_path *)b;
	return (path1->len < path2->len);
}

void			complete_paths(t_list **paths)
{
	t_list	*room;
	t_list	*elem;

	elem = *paths; // pointer on paths list
	while (elem)
	{
		room = ((t_path *)elem->content)->room; // catching the first room of the path under processing
		elem_complete_path(elem, room);
		elem = elem->next;
	}
	ft_lst_mergesort(paths, sort_by_len);
	elem = *paths;
}
