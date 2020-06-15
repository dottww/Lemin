/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:55:42 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/12 07:18:34 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		complete_path(t_list *path, t_list *room)
{
	t_list	*tunnel;
	t_list	*next_room;
	int		path_id;

	path_id = ((t_path *)path->content)->id;
	tunnel = ((t_room *)room->content)->tunnels;
	if (((t_room *)room->content)->end == 1)
		((t_path *)path->content)->complete = true;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == -1)
		{
			((t_path *)path->content)->len++;
			next_room = ((t_tunnel *)tunnel->content)->room;
			((t_room *)room->content)->new_next = next_room;
			((t_room *)room->content)->new_path_id = path_id;
			complete_path(path, next_room);
			return ;
		}
		tunnel = tunnel->next;
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

	elem = *paths;
	while (elem)
	{
		room = ((t_path *)elem->content)->room;
		complete_path(elem, room);
		elem = elem->next;
	}
	ft_lst_mergesort(paths, sort_by_len);
	elem = *paths;
}
