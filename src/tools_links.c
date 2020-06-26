/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:02:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 22:55:10 by weilin           ###   ########.fr       */
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

static void		set_link_usage(t_list *src, t_list *dest, bool is_previous)
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

/*
** Description:
**	After a successful BFS, route (queue of rooms) is free/destroyed here,
**	plus the function update the usage of the links of the rooms constituting
**	the path:
**		usage of the link is set to -1 in the direction "start -> end",
**		usage of the link is set to -1 in the direction "end -> start"
*/

void			set_links_usage(t_list *end, t_list **route)
{
	t_list	*room;
	t_list	*previous;

	ft_lstdel(route, ft_delcontent);
	room = end;
	while (room)
	{
		previous = ((t_room *)room->content)->previous;
		if (previous)
		{
			set_link_usage(previous, room, true);
			set_link_usage(room, previous, false);
		}
		room = ((t_room *)room->content)->previous;
	}
}
