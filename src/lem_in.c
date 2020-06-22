/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 16:24:56 by weilin            #+#    #+#             */
/*   Updated: 2020/06/21 15:47:11 by mdavid           ###   ########.fr       */
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

/*
** Description:
**	get_input		: parsing with basic tests on the format of input
**	register_rooms	: construction of the struct vatiable which contain the graph
**	get_option		: [TO BE PRECISE, it will probably be remove]
**	get_paths		: algorithm of multi-paths finding based on BFS
**	print_input		: print of the input
**	print_output	: print of the ouput/solution (description of ants action)
*/

int		main(int ac, char **av)
{
	t_antfarm	atf;
	t_list		*alst;
	t_list		*paths;

	alst = NULL;
	paths = NULL;
	if (!get_input(&alst))
		// return (free_input(&alst, "ERROR"));
		return (free_input(&alst, "ERROR1"));
	if (!register_rooms(&atf, alst))
		// return (print_and_free(&atf, &alst, &paths, "ERROR"));
		return (print_and_free(&atf, &alst, &paths, "ERROR2"));
	// (void)ac;
	// (void)av;
	get_option(&atf, ac, av);
	if (!(get_paths(&atf, atf.start, atf.end, &paths)))
		// return (print_and_free(&atf, &alst, &paths, "ERROR"));
		return (print_and_free(&atf, &alst, &paths, "ERROR3"));
	init_ants(&atf);
	if (!atf.option)
		print_input(alst);
	print_output(&atf, paths);
	// system("leaks lem-in");
	// char t='t';
	// bool try=true;
	// int tryint=(int)true;
	// int8_t i8t=(int8_t)true;
	// ft_printf("szofchar=%zu\n",sizeof(t));
	// ft_printf("szofbool=%zu\n",sizeof(try));
	// ft_printf("szofint=%zu\n",sizeof(tryint));
	// ft_printf("szofint=%lu\n",sizeof(i8t));
	return (print_and_free(&atf, &alst, &paths, NULL));
}
