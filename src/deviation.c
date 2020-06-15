/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:33:41 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/12 07:18:34 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		reset_visited_rooms(t_list *dev_room
		, t_list *prev_room, t_list *queue, t_list *end)
{
	t_list	*room;

	while (queue)
	{
		room = ((t_queue *)queue->content)->room;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->previous = NULL;
		queue = queue->next;
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

static t_list	*get_previous_room(t_list *tunnel)
{
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == 1)
			return (((t_tunnel *)tunnel->content)->room);
		tunnel = tunnel->next;
	}
	return (NULL);
}

bool			deviation_reaches_end(t_list *deviation_room, t_list *end)
{
	t_list	*prev_room;
	t_list	*tunnels;
	t_list	*queue;
	bool	ret;

	queue = NULL;
	prev_room = NULL;
	tunnels = ((t_room *)deviation_room->content)->tunnels;
	if (!(prev_room = get_previous_room(tunnels)))
		return (false);
	if (((t_room *)prev_room->content)->end == 0)
		return (false);
	ret = false;
	if (((t_room *)prev_room->content)->visited == false
	&& ((t_room *)deviation_room->content)->dead_end == false)
	{
		((t_room *)deviation_room->content)->visited = true;
		((t_room *)prev_room->content)->visited = true;
		ret = bfs(prev_room, end, &queue);
		if (!ret)
			((t_room *)deviation_room->content)->dead_end = true;
		reset_visited_rooms(deviation_room, prev_room, queue, end);
		ft_lstdel(&queue, del_steps);
	}
	return (ret);
}

bool			going_to_deviate(t_list *current, t_list *room)
{
	t_room	*src;
	t_room	*dest;
	t_list	*tunnel;
	int		tunnel_used;

	tunnel_used = 0;
	src = (t_room *)current->content;
	dest = (t_room *)room->content;
	tunnel = dest->tunnels;
	while (tunnel)
	{
		if (((t_tunnel *)tunnel->content)->usage == 1)
		{
			tunnel_used = 1;
			break ;
		}
		tunnel = tunnel->next;
	}
	return (!src->deviation && tunnel_used
	&& src->path_id != dest->path_id && dest->path_id != 0);
}
