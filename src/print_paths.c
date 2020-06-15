/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:49:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/02 12:48:40 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_steps(t_list *room)
{
	ft_printf("{green}# %2d:{nc} ", ((t_room *)room->content)->path_id);
	while (room)
	{
		ft_printf("%s%c"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->next ? '-' : '\n');
		room = ((t_room *)room->content)->next;
	}
}

void		print_paths(t_list *path)
{
	t_list	*room;

	while (path)
	{
		room = ((t_path *)path->content)->room;
		print_steps(room);
		path = path->next;
	}
}
