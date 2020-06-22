/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/22 20:47:36 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool		find_paths(t_antfarm *atf, t_list **paths)
{
	unsigned long	ret;
	t_list			*route;
	t_list			*previous_paths;

	route = NULL;
	while (bfs(atf->start, atf->end, &route)) //list out all possible routes and complying to rules
	{
		// print_route(route);
		previous_paths = *paths;
		*paths = NULL;
		set_links_usage(atf->end, &route);
		if (!init_paths(paths, atf->start, atf->option)) //unique id: path_id created on the fly
			return (false);
		complete_paths(paths);
		ret = test_solution(atf, *paths, atf->ant_qty);
		// ft_printf("0path_len=%d\n",((t_path *)(*paths)->content)->len);
		if (ret >= atf->rounds || ret == 0)
		{
			// ft_printf(
			// "-------------ret >= atf->rounds || ret == 0\nret = {%lu} atf->rounds = {%lu}\npaths="
			// , ret, atf->rounds);
			// print_paths(*paths);
			ft_lstdel(paths, ft_delcontent);
			*paths = previous_paths;
			break ;
		}
		printpath_update_data(atf, ret, paths);
		ft_lstdel(&previous_paths, ft_delcontent);
	}
	ft_lstdel(&route, ft_delcontent);
	return (atf->rounds != LONG_MAX && ret != 0);
}

/*
** Description:
**	Check if the room start has the room end as a neighbor.
**	If so, only one path is constructed.
**	Otherwise, function 'find_paths()' is called to find multiple paths
** Return:
**	TRUE  : if no mem allocation issue in init_the_only_path or .....
**	FLASE : if mem allocation in init_the_only_path or ......
*/

bool			get_paths(t_antfarm *atf, t_list *start, t_list *end
			, t_list **paths)
{
	if (start_linked_to_end(start, end)) //re
		return (init_the_only_path(paths, atf));
	return (find_paths(atf, paths));
}
