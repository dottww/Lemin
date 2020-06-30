/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 00:52:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 16:24:16 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_room(t_room *room)
{
	room->visited = false;
	room->deviation = false;
	room->previous = NULL;
}

static void		reset_route(t_list *adj_room
		, t_list *src_of_adj, t_list *route, t_list *end_room)
{
	t_room	*room;

	while (route)
	{
		room = (t_room *)((t_route *)route->content)->room->content;
		reset_room(room);
		route = route->next;
	}
	reset_room((t_room *)adj_room->content);
	reset_room((t_room *)src_of_adj->content);
	reset_room((t_room *)end_room->content);
}

static t_list	*get_src_of_adj(t_list *link)
{
	while (link)
	{
		if (((t_link *)link->content)->usage == 1)
		{
			if (is_start((t_room *)((t_link *)link->content)->room->content))
				return (NULL);
			else
				return (((t_link *)link->content)->room);
		}
		link = link->next;
	}
	return (NULL);
}

/*
** Description:
**	If adj_room is already part of another path, and in current bfs_route
**	the src_of_adj is still not yet parsed, it runs a temporary bfs to see if
**	it is possible to create a new route from src_of_adj, so by this, we can
**	have 2 parallel routes: src_of_adj-somewhere_else and curr-adj
** Return:
**	True if:
**		src_of_adj is not Start_room
**		+ src_of_adj is not yet visited by current bfs
**		+ adj_room is not marked as dead_end
**		+ src_of_adj has another detouring possibility, if not, adj_room
**		  will be marked as dead_end, adj is then not viable.
**	False if:
**		one of the requirements listed above is false
*/

bool			detour_src_of_adj(t_list *adj_room, t_list *end) //wei
{
	t_list	*src_of_adj;
	t_list	*links;
	t_list	*tmp_test_route;
	bool	ret;

	tmp_test_route = NULL;
	src_of_adj = NULL;
	ret = false;
	links = ((t_room *)adj_room->content)->links;
	if (!(src_of_adj = get_src_of_adj(links)))
		return (false);
	if (((t_room *)src_of_adj->content)->visited == false
		&& ((t_room *)adj_room->content)->dead_end == false)
	{
		((t_room *)src_of_adj->content)->visited = true;
		((t_room *)adj_room->content)->visited = true;
		ret = bfs_route(src_of_adj, end, &tmp_test_route);
		if (!ret)
			((t_room *)adj_room->content)->dead_end = true;
		reset_route(adj_room, src_of_adj, tmp_test_route, end);
		ft_lstdel(&tmp_test_route, ft_delcontent);
	}
	return (ret);
}

/*
** Description:
**	Check if adj_room is already part of another path, and the current is not
**	in the same path of adj_room.
**	
**	by default curr->deviation are initialized to false, not changed at first
** Return:
**	True if:
**		curr->deviation is false
**		+ adj->path_id different from 0, means it is already part of a path
**		+ curr->path_id different from adj->path_id
*/

bool			adj_part_of_path(t_list *current, t_list *adj_room) //wei
{
	t_room	*curr;
	t_room	*adj;

	curr = (t_room *)current->content;
	adj = (t_room *)adj_room->content;
	return (!curr->deviation && is_in_path(adj) && !samepath(curr, adj));
}

bool			adj_part_of_path(t_list *current, t_list *adj_room) //wei
{
	t_room	*curr;
	t_room	*adj;
	t_list	*link_of_adj;
	int		adj_taken_by_another_path;

	adj_taken_by_another_path = 0;
	curr = (t_room *)current->content;
	adj = (t_room *)adj_room->content;
	link_of_adj = adj->links;
	while (link_of_adj)
	{
		if (((t_link *)link_of_adj->content)->usage == 1)
		{
			adj_taken_by_another_path = 1;
			break ;
		}
		link_of_adj = link_of_adj->next;
	}
	return (!curr->deviation && is_in_path(adj) && !samepath(curr, adj)
			&& adj_taken_by_another_path);
}
