/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:25:22 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 18:38:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		sort_by_len(void *a, void *b)
{
	t_path	*path1;
	t_path	*path2;

	path1 = (t_path *)a;
	path2 = (t_path *)b;
	return (path1->len < path2->len);
}

/*
** ___Parameters___:
**	*atf: pointer on the struct variable t_antfarm, containing full
**		  description of the antfarm.
**	**paths: adress of pointer on t_list struct variable, being list
**			 of the differents paths and descriptive variable within
** ___Remarks___:
**	As paths is a list, the t_path inner variable is at content:
**	paths: [cnt:path1 & next->]--[cnt:path2 & next->]--{...}--[NULL]
** ___Description___:
**	Function manages the BFS algo, followed by the step of path construction
**	and calculate the number of ants per paths and evaluate the performance
**	(in how many rounds all the ants will reach the END)
** ___Return___:
**	TRUE  : 
**	FALSE : if rounds != LONG_MAX(initialization value) || ret = 0
*/

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
		if (!init_paths(paths, atf->start, atf->option)) //unique id: path_id created on the fly
			return (false);
		complete_paths(paths);
		ft_lst_mergesort(paths, sort_by_len);
		ret = test_solution(atf, *paths);
		if (ret >= atf->rounds || ret == 0) // control sequence, if ret is bigger to LONG_MAX (stocked in atf->rounds)
		{
			ft_lstdel(paths, ft_delcontent);
			*paths = previous_paths;
			break ;
		}
		printpath_update_data(atf, ret, paths);
		ft_lstdel(&previous_paths, ft_delcontent);
	}
	ft_lstdel(&route, ft_delcontent);
	// return (atf->rounds != LONG_MAX && ret != 0); // check of ret != 0 seems to be useless, think about how to get ret (round actually) = 0
	return (atf->rounds != LONG_MAX);
}

/*
** ___Description___:
**	Check if the room start has the room end as a neighbor.
**	If so, only one path is constructed.
**	Otherwise, function 'find_paths()' is called to find multiple paths
** ___Return___:
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
