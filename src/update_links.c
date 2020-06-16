/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:01:32 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/16 00:09:03 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*get_link(t_list *src, t_list *dest)
{
	t_list	*link;
	t_list	*room;

	link = ((t_room *)src->content)->links;
	while (link)
	{
		room = ((t_link *)link->content)->room;
		if (room == dest)
			return (link);
		link = link->next;
	}
	return (NULL);
}

static void		set_usage(t_list *src, t_list *dest, bool is_previous)
{
	t_list	*link;

	if (!(link = get_link(src, dest)))
		return ;
	if (((t_link *)link->content)->usage == 0 && is_previous)
		((t_link *)link->content)->usage = -1;
	else if (((t_link *)link->content)->usage == 0 && !is_previous)
		((t_link *)link->content)->usage = 1;
	else
		((t_link *)link->content)->usage = 0;
}

void			set_links_usage(t_list *end, t_list **queue)
{
	t_list	*room;
	t_list	*previous;

	ft_lstdel(queue, del_steps);
	room = end;
	while (room)
	{
		previous = ((t_room *)room->content)->previous;
		if (previous)
		{
			set_usage(previous, room, true);
			set_usage(room, previous, false);
		}
		room = ((t_room *)room->content)->previous;
	}
}
