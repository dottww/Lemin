/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_linked_to_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:58:24 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/16 00:05:10 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool		start_linked_to_end(t_list *start, t_list *end)
{
	t_list	*link;
	t_list	*dest_room;

	link = ((t_room *)start->content)->links;
	while (link)
	{
		dest_room = ((t_link *)link->content)->room;
		if (dest_room == end)
			return (true);
		link = link->next;
	}
	return (false);
}

bool		init_the_only_path(t_list **paths, t_antfarm *atf)
{
	t_path	path;
	t_list	*new_path;

	path.room = atf->end;
	path.len = 1;
	path.sent = atf->ant_qty;
	path.id = 1;
	path.complete = true;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (false);
	if (atf->option & DISPLAY_PATHS)
	{
		ft_printf("{ul}{bold}Initialized 1 path:{nc}\n");
		ft_printf("{green}# 1:{nc} End\n");
	}
	ft_lstprepend(paths, new_path);
	return (true);
}
