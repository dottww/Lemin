/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:24:56 by weilin            #+#    #+#             */
/*   Updated: 2020/06/15 23:33:36 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_option(t_antfarm *atf, int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strequ(av[1], "--paths"))
			atf->option |= DISPLAY_PATHS;
		else if (ft_strequ(av[1], "--solution"))
			atf->option |= ONLY_DISPLAY_SOLUTION;
	}
}

int		main(int ac, char **av)
{
	t_antfarm	atf;
	t_list		*alst;
	t_list		*paths;

	alst = NULL;
	paths = NULL;
	if (!get_input(&alst))
		return (free_input(&alst, "ERROR1"));
	if (!register_rooms(&atf, alst))
		return (print_and_free(&atf, &alst, &paths, "ERROR2"));
	// (void)ac;
	// (void)av;
	get_option(&atf, ac, av);
	// if (!(get_paths(&atf, atf.start, atf.end, &paths)))
	// 	return (print_and_free(&atf, &alst, &paths, "ERROR3"));
	// init_ants(&atf);
	// if (!atf.option)
	// 	print_input(alst);
	// print_output(&atf, paths);
	return (print_and_free(&atf, &alst, &paths, NULL));
}
