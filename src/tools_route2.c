/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 00:52:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 16:42:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_route(t_list *deviation_room
		, t_list *previous_room, t_list *route, t_list *end_room)
{
	t_room	*room;
	t_room	*deviation;
	t_room	*prev;
	t_room	*end;

	deviation = (t_room *)deviation_room->content;
	prev = (t_room *)previous_room->content;
	end = (t_room *)end_room->content;
	while (route)
	{
		room = (t_room *)((t_route *)route->content)->room->content;
		room->visited = false;
		room->deviation = false;
		room->previous = NULL;
		route = route->next;
	}
	deviation->visited = false;
	prev->visited = false;
	deviation->deviation = false;
	prev->deviation = false;
	deviation->previous = NULL;
	prev->previous = NULL;
	end->visited = false;
	end->deviation = false;
}

static t_list	*back_to_src_of_adj(t_list *link)
{
	while (link)
	{
		if (((t_link *)link->content)->usage == 1)
			return (((t_link *)link->content)->room);
		link = link->next;
	}
	return (NULL);
}

/* //weib
** Description:
**	When adj_room is already part of other route, it will try to go to
**	src_of_adj , and see if there is another link in src_of_adj that can
**	go to end, so that adj itself will be available for curr
** Return:
**	True if:
**		src->deviation is false
**		+ link_used = 1
**		+ src->path_id different from dest->path_id
**		+ dest->path_id different from 0 ()
*/

bool			deviation_src_of_adj(t_list *adj_room, t_list *end) //wei
{
	t_list	*src_of_adj;
	t_list	*links;
	t_list	*route;
	bool	ret;

	route = NULL;
	src_of_adj = NULL;
	links = ((t_room *)adj_room->content)->links;
	if (!(src_of_adj = back_to_src_of_adj(links)))
		return (false);
	if (((t_room *)src_of_adj->content)->s_t == 0)
		return (false);
	ret = false;
	if (((t_room *)src_of_adj->content)->visited == false //b
	&& ((t_room *)adj_room->content)->dead_end == false) //b
	{
		((t_room *)src_of_adj->content)->visited = true;
		((t_room *)adj_room->content)->visited = true;
		ret = bfs_route(src_of_adj, end, &route);
		if (!ret)
			((t_room *)adj_room->content)->dead_end = true;
		reset_route(adj_room, src_of_adj, route, end);
		ft_lstdel(&route, ft_delcontent);
	}
	return (ret);
}

/*
** Description:
**	If adj_room is already part of other route, so current bfs_route:curr_adj
**	cannot be created from so go back to previous room
**	
**	by default src->deviation are initialized to false, not changed at first
** Return:
**	True if:
**		src->deviation is false
**		+ link_used = 1
**		+ src->path_id different from dest->path_id
**		+ dest->path_id different from 0 ()
*/

bool			adj_part_of_path(t_list *current, t_list *adj_room) //wei
{
	t_room	*curr;
	t_room	*adj;
	t_list	*link_of_adj;
	int		adj_taken_by_another_path;

	adj_taken_by_another_path = 0;
	curr = (t_room *)current->content; // access to the source room (opening of the encapsulation)
	adj = (t_room *)adj_room->content; // access to the destination room (opening of the encapsulation)
	link_of_adj = adj->links; //
	while (link_of_adj)
	{
		if (((t_link *)link_of_adj->content)->usage == 1) // dest already visited by curr
		{
			adj_taken_by_another_path = 1;
			break ;
		}
		link_of_adj = link_of_adj->next;
	}// curr->deviation are initialized to false, not changed at first
	return (!curr->deviation && adj_taken_by_another_path // ![[DV(curr)]] && LINK(curr, dest) && PATH(dest) && !PATH(curr && dest) 
	&& !is_start(adj) && !samepath(curr, adj));
	// && dest->path_id != 0 && curr->path_id != dest->path_id);
}
