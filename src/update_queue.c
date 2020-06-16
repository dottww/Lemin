/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:19:06 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/16 00:05:12 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_to_queue(t_list **queue, t_list *room, t_list *current)
{
	t_queue		new;
	t_list		*node;

	if (!(node = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	((t_queue *)node->content)->room = room;
	ft_lstappend(queue, node);
	((t_room *)room->content)->previous = current;
	((t_room *)room->content)->visited = true;
	return (1);
}

static bool		link_is_usable(t_list *current, t_list *link, t_list *end)
{
	t_list		*room;
	t_room		*dest;
	t_room		*src;
	int			usage;

	src = (t_room *)current->content;
	room = ((t_link *)link->content)->room;
	dest = (t_room *)room->content;
	usage = ((t_link *)link->content)->usage;
	if (usage != -1 && dest->end != 0 && src->path_id != dest->path_id
	&& !dest->visited && dest->path_id != 0 && going_to_deviate(current, room))
		return (deviation_reaches_end(room, end));
	return (!dest->visited && usage != -1 && dest->end != 0
	&& !(src->deviation && usage == 0));
}

int				complete_queue(t_list *queue, t_list *end)
{
	t_list	*link;
	t_list	*room;
	t_list	*current;

	current = ((t_queue *)queue->content)->room;
	link = ((t_room *)current->content)->links;
	while (link)
	{
		room = ((t_link *)link->content)->room;
		if (!link_is_usable(current, link, end))
		{
			link = link->next;
			continue ;
		}
		if (!add_to_queue(&queue, room, current))
			return (0);
		if (((t_room *)room->content)->end == 1)
			return (1);
		if (going_to_deviate(current, room))
			((t_room *)room->content)->deviation = true;
		link = link->next;
	}
	if (((t_room *)current->content)->deviation == true)
		((t_room *)current->content)->deviation = false;
	return (1);
}

int				init_queue(t_list **queue, t_list *start)
{
	t_queue		new;

	if (!(*queue = ft_lstnew(&new, sizeof(t_list))))
		return (0);
	((t_queue *)(*queue)->content)->room = start;
	return (1);
}
