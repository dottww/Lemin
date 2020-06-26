/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:53:36 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 18:25:24 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		link_used(t_list *link)
{
	// return (((t_link *)link->content)->usage == -1);
	return (((t_link *)link->content)->usage != 0);
}

int		is_start(t_room *room)
{
	return (room->s_t == 0);
}

int		samepath(t_room *src, t_room *room)
{
	return (src->path_id == room->path_id);
}

int		is_visited(t_room *room)
{
	return (room->visited);
}

int		is_in_path(t_room *room)
{
	return (room->path_id != 0);
}
