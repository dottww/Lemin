/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 18:06:49 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		init_path_sub(t_list **pth, t_list *room)
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
	ft_lstprepend(pth, new_path); // append of the head of the new path in the list of differents pth
	return (1);
}

int				init_path(t_list **pth, t_list *start, unsigned int options)
{
	t_list		*room;
	t_list		*link;

	room = start;
	link = ((t_room *)(room->content))->links; //catching all the links of start
	while (link)
	{
		if (((t_link *)link->content)->usage == -1)
		{
			if (!init_path_sub(pth, ((t_link *)link->content)->room))
				return (0);
		}
		link = link->next;
	}
	if (options & DISPLAY_PATH)
	{
		ft_printf("Initialized %lu path%s"
		, ft_lstlen(*pth)
		, ft_lstlen(*pth) > 1 ? "s:\n" : ":\n");
	}
	return (1);
}

static bool		find_path(t_antfarm *atf, t_list **pth)
{
	unsigned long	ret;
	t_list			*route;
	t_list			*previous_pth;

	route = NULL;
	while (bfs_route(atf->start, atf->end, &route)) //list out all possible routes and complying to rules
	{
		previous_pth = *pth;
		*pth = NULL;
		set_links_usage(atf->end, &route);
		if (!init_path(pth, atf->start, atf->options)) //unique id: path_id created on the fly
			return (false);
		full_path(pth);
		ret = solution_rounds(atf, *pth, atf->ant_qty);
		if (ret >= atf->rounds || ret == 0) // control sequence, if ret is bigger to LONG_MAX (stocked in atf->rounds)
		{
			ft_lstdel(pth, ft_delcontent);
			*pth = previous_pth;
			break ;
		}
		printpath_update_data(atf, ret, pth);
		ft_lstdel(&previous_pth, ft_delcontent);
	}
	ft_lstdel(&route, ft_delcontent);
	return (atf->rounds != LONG_MAX && ret != 0);
}

/*
** Description:
**	Check if the room start has the room end as a neighbor.
**	If so, only one path is constructed.
**	Otherwise, function 'find_path()' is called to find multiple pth
** Return:
**	TRUE  : if no mem allocation issue in init_unique_path or .....
**	FLASE : if mem allocation in init_unique_path or ......
*/

bool			get_path(t_antfarm *atf, t_list *start, t_list *end
			, t_list **pth)
{
	if (start_connected_to_end(start, end)) //wei
		return (init_unique_path(pth, atf));
	return (find_path(atf, pth));
}
