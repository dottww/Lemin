/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:24:56 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 16:55:20 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_options(t_antfarm *atf, int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strequ(av[1], "--paths"))
			atf->options |= DISPLAY_PATH;
		else if (ft_strequ(av[1], "--solution"))
			atf->options |= ONLY_DISPLAY_SOLUTION;
	}
}

/*
** Description:
**	read_input		: parsing with basic tests on the format of input
**	get_antfarm	: construction of the struct vatiable which contain the graph
**	get_path		: algorithm of multi-paths finding based on BFS
**	print_antfarm		: print of the input
**	print_ant_moves	: print of the ouput/solution (description of ants action)
*/

int		main(int ac, char **av)
{
	t_antfarm	atf;
	t_list		*alst;
	t_list		*pth;
	
	// if (ac == 1) // pending avoid issue of "--" 
	// {
		alst = NULL;
		pth = NULL;
		if (!read_input(&alst))
			return (free_input_lst(&alst, "ERROR1"));
		if (!get_antfarm(&atf, alst))
			return (print_free(&atf, &alst, &pth, "ERROR2"));
		get_options(&atf, ac, av);
		if (!(get_path(&atf, atf.start, atf.end, &pth)))
			return (print_free(&atf, &alst, &pth, "ERROR3"));
		init_ant(&atf);
		if (!atf.options)
			print_antfarm(alst);
		print_ant_moves(&atf, pth);
		return (print_free(&atf, &alst, &pth, NULL));
	// }
	// return (0);
	// system("leaks lem-in");
}
