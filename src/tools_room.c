/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:53:36 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 00:31:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		golink(t_list *curr_link)
{
	return (((t_link *)curr_link->content)->usage == -1);
}

int		is_start(t_room *dst)
{
	return (dst->s_t == 0);
}
// int		is_start(t_list *curr_link)
// {
// 	return (!((t_room *)((t_link *)(curr_link->content))->room->content)->s_t);
// }

int		samepath(t_room *src, t_room *dst)
{
	return (src->path_id == dst->path_id);
	// return (((t_room *)current->content)->path_id
	// 	==
	// ((t_room *)((t_link *)(curr_link->content))->room->content)->path_id);
}

int		is_visited(t_room *dst)
{
	return (dst->visited);
}

int		is_in_path(t_room *dst)
{
	return (dst->path_id != 0);
	// return (((t_room *)((t_link *)(curr_link->content))->room->content)->path_id);
}
