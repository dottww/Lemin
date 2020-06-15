/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_tunnels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 14:01:32 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 12:46:21 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*get_tunnel(t_list *src, t_list *dest)
{
	t_list	*tunnel;
	t_list	*room;

	tunnel = ((t_room *)src->content)->tunnels;
	while (tunnel)
	{
		room = ((t_tunnel *)tunnel->content)->room;
		if (room == dest)
			return (tunnel);
		tunnel = tunnel->next;
	}
	return (NULL);
}

static void		set_usage(t_list *src, t_list *dest, bool is_previous)
{
	t_list	*tunnel;

	if (!(tunnel = get_tunnel(src, dest)))
		return ;
	if (((t_tunnel *)tunnel->content)->usage == 0 && is_previous)
		((t_tunnel *)tunnel->content)->usage = -1;
	else if (((t_tunnel *)tunnel->content)->usage == 0 && !is_previous)
		((t_tunnel *)tunnel->content)->usage = 1;
	else
		((t_tunnel *)tunnel->content)->usage = 0;
}

void			set_tunnels_usage(t_list *end, t_list **queue)
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
