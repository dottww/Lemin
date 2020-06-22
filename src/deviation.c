/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:33:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/22 16:50:37 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_visited_rooms(t_list *dev_room
		, t_list *prev_room, t_list *route, t_list *end)
{
	t_list	*room;

	while (route)
	{
		room = ((t_route *)route->content)->room;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->previous = NULL;
		route = route->next;
	}
	((t_room *)dev_room->content)->visited = false;
	((t_room *)prev_room->content)->visited = false;
	((t_room *)dev_room->content)->deviation = false;
	((t_room *)prev_room->content)->deviation = false;
	((t_room *)dev_room->content)->previous = NULL;
	((t_room *)prev_room->content)->previous = NULL;
	((t_room *)end->content)->visited = false;
	((t_room *)end->content)->deviation = false;
}

static t_list	*get_previous_room(t_list *link)
{
	while (link)
	{
		if (((t_link *)link->content)->usage == 1)
			return (((t_link *)link->content)->room);
		link = link->next;
	}
	return (NULL);
}

bool			deviation_reaches_end(t_list *deviation_room, t_list *end)
{
	t_list	*prev_room;
	t_list	*links;
	t_list	*route;
	bool	ret;

	route = NULL;
	prev_room = NULL;
	links = ((t_room *)deviation_room->content)->links;
	if (!(prev_room = get_previous_room(links)))
		return (false);
	if (((t_room *)prev_room->content)->s_t == 0)
		return (false);
	ret = false;
	if (((t_room *)prev_room->content)->visited == false
	&& ((t_room *)deviation_room->content)->dead_end == false)
	{
		((t_room *)deviation_room->content)->visited = true;
		((t_room *)prev_room->content)->visited = true;
		ret = bfs(prev_room, end, &route);
		if (!ret)
			((t_room *)deviation_room->content)->dead_end = true;
		reset_visited_rooms(deviation_room, prev_room, route, end);
		ft_lstdel(&route, ft_delcontent);
	}
	return (ret);
}

/*
** Description:
**	I do not understand the objective of this function, what does the concept of deviation mean ?
** Return:
**	True if:
**		src->deviation is false
**		+ link_used = 1
**		+ src->path_id different from dest->path_id
**		+ dest->path_id different from 0 ()
*/

bool			going_to_deviate(t_list *current, t_list *adj_room)
{
	t_room	*src;
	t_room	*dest;
	t_list	*link_dest;
	int		link_used;

	link_used = 0;
	src = (t_room *)current->content; // access to the source room (opening of the encapsulation)
	dest = (t_room *)adj_room->content; // access to the destination room (opening of the encapsulation)
	link_dest = dest->links; //
	while (link_dest)
	{
		if (((t_link *)link_dest->content)->usage == 1) // dest already visited by src/curr
		{
			link_used = 1;
			break ;
		}
		link_dest = link_dest->next;
	}// src->deviation are initialized to false, not changed at first
	return (!src->deviation && link_used // !DV(src) && LINK(src, dest) && PATH(dest) && !PATH(src && dest) 
	&& dest->path_id != 0 && src->path_id != dest->path_id); // [[DV(src)]]
}
