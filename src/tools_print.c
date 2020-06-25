/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 16:23:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 00:51:29 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_antfarm(t_list *alst)
{
	while (alst)
	{
		ft_putendl(L1);
		alst = alst->next;
	}
}

void			print_all_steps(t_list *room)
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

void			print_all_paths(t_list *path)
{
	t_list	*room;

	while (path)
	{
		room = ((t_path *)path->content)->room;
		print_all_steps(room);
		path = path->next;
	}
}
