/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 13:49:27 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/22 20:33:53 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_steps(t_list *room)
{
	ft_printf("# %2d: ", ((t_room *)room->content)->path_id);
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
