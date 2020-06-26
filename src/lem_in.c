/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:24:56 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 23:14:48 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Initialization of all the inner variables of t_antfarm struct var
**	except ant_qty which is initialized by another function just after
*/

static void		init_antfarm_values(t_antfarm *atf)
{
	atf->rooms = NULL;
	atf->start = NULL;
	atf->end = NULL;
	atf->rounds = LONG_MAX;
	atf->options = 0;
	atf->ants = NULL;
}

static int		get_options(t_antfarm *atf, int ac, char **av)
{
	int i;
	
	init_antfarm_values(atf);
	i = 1;
	if (ac > 1)
	{
		while (i < ac)
		{
			if (ft_strequ(av[i], "--paths"))
				atf->options |= SHOW_PATH;
			else if (ft_strequ(av[i], "--solution"))
				atf->options |= ONLY_SOLUTION;
			i++;
		}
		if(!atf->options)
		{
			ft_putendl("Usage: ./lem-in [--paths] [--solution] < antfarm_map");
			return(0);
		}
	}
	return (1);
}

/*
** ___Description___:
**	read_input		: parsing with basic tests on the format of input
**	get_antfarm		: construction of struct variable which containing graph
**	get_path		: algorithm of multi-paths finding based on BFS
**	print_antfarm	: print in the standard output the input
**	print_ant_moves	: print of the ouput/solution (description of ants action)
*/

int				main(int ac, char **av)
{
	t_antfarm	atf;
	t_list		*alst;
	t_list		*pth;

	alst = NULL;
	pth = NULL;
	if (!get_options(&atf, ac, av))
		return (0);
	if (!read_input(&alst))
		return (free_input_lst(&alst, "ERROR"));
	if (!get_antfarm(&atf, alst))
		return (print_free(&atf, &alst, &pth, "ERROR"));
	if (!(get_path(&atf, atf.start, atf.end, &pth)))
		return (print_free(&atf, &alst, &pth, "ERROR"));
	init_ant(&atf);
	if (!atf.options)
		print_antfarm(alst);
	print_ant_moves(&atf, pth);
	return (print_free(&atf, &alst, &pth, NULL));
}
