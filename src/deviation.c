/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:33:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/19 02:39:48 by weilin           ###   ########.fr       */
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
	if (((t_room *)prev_room->content)->end == 0)
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

bool			going_to_deviate(t_list *current, t_list *room)
{
	t_room	*src;
	t_room	*dest;
	t_list	*link;
	int		link_used;

	link_used = 0;
	src = (t_room *)current->content;
	dest = (t_room *)room->content;
	link = dest->links;
	while (link)
	{
		if (((t_link *)link->content)->usage == 1)
		{
			link_used = 1;
			break ;
		}
		link = link->next;
	}
	return (!src->deviation && link_used
	&& src->path_id != dest->path_id && dest->path_id != 0);
}
