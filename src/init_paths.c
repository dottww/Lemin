/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/22 20:32:56 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	init_path_sub(t_list **paths, t_list *room)
{
	t_list		*new_path;
	t_path		path;
	static int	path_id = 0;

	path.len = 1;
	path.id = ++path_id;
	path.sent = 0;
	path.room = NULL;
	path.complete = false;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (0);
	((t_path *)new_path->content)->room = room;
	ft_lstprepend(paths, new_path);
	return (1);
}

int			init_paths(t_list **paths, t_list *start, unsigned int option)
{
	t_list		*room;
	t_list		*link;

	room = start;
	link = ((t_room *)(room->content))->links;
	while (link)
	{
		if (((t_link *)link->content)->usage == -1)
		{
			if (!init_path_sub(paths, ((t_link *)link->content)->room))
				return (0);
		}
		link = link->next;
	}
	if (option & DISPLAY_PATHS)
	{
		ft_printf("Initialized %lu path%s"
		, ft_lstlen(*paths)
		, ft_lstlen(*paths) > 1 ? "s:\n" : ":\n");
	}
	return (1);
}
