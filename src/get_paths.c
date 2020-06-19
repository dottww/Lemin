/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/19 03:25:09 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

bool			bfs(t_list *start, t_list *end, t_list **route)
{
	t_list	*elem;
	// t_list	*list_tmproom;
	bool	found_augmented_path;

	found_augmented_path = false;
	if (!init_route(route, start))
		return (false);
	((t_room *)start->content)->visited = true;
	elem = *route;
	while (elem)
	{
		// list_tmproom = ((t_route *)elem->content)->room;
		if (!complete_route(elem, end)) //find possible route to end
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		elem = elem->next;
	}
	return (found_augmented_path);
}

static bool		find_paths(t_antfarm *atf, t_list **paths)
{
	unsigned long	ret;
	t_list			*route;
	t_list			*previous_paths;

	route = NULL;
	while (bfs(atf->start, atf->end, &route))
	{
		previous_paths = *paths;
		*paths = NULL;
		set_links_usage(atf->end, &route);
		if (!init_paths(paths, atf->start, atf->option))
			return (false);
		complete_paths(paths);
		ret = test_solution(atf, *paths, atf->ant_qty);
		if (ret >= atf->rounds || ret == 0)
		{
			ft_lstdel(paths, ft_delcontent);
			*paths = previous_paths;
			break ;
		}
		update_data(atf, ret, paths);
		ft_lstdel(&previous_paths, ft_delcontent);
	}
	ft_lstdel(&route, ft_delcontent);
	return (atf->rounds != LONG_MAX && ret != 0);
}

bool			get_paths(t_antfarm *atf, t_list *start, t_list *end
			, t_list **paths)
{
	if (start_linked_to_end(start, end))
		return (init_the_only_path(paths, atf));
	return (find_paths(atf, paths));
}
