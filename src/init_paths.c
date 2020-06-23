/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/23 20:17:05 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	init_path_sub(t_list **paths, t_list *room)
{
	t_list		*new_path;
	t_path		path;
	static int	path_id = 0;

	path.len = 1; // initialization of the length of the path based on the 1st room received (*room)
	path.id = ++path_id; // definition ofthe path id, here static, thus last value keep in mem and increased at each round
	path.sent = 0; // number of ants which will be sent
	path.room = NULL; //
	path.complete = false; // init of flag saying path reach the end or not (not by default)
	if (!(new_path = ft_lstnew(&path, sizeof(t_path)))) // allocation of the head link from which the path starts
		return (0);
	((t_path *)new_path->content)->room = room; // adding the room being the first of the path (not start but the one after, because start obviously the 1st and is present every time)
	ft_lstprepend(paths, new_path); // append of the head of the new path in the list of differents paths
	return (1);
}

int			init_paths(t_list **paths, t_list *start, unsigned int option)
{
	t_list		*room;
	t_list		*link;

	room = start;
	link = ((t_room *)(room->content))->links; //catching all the links of start
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
