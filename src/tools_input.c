/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 00:06:23 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 20:56:27 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Check if the 1st character of the input line is '#', meaning it can be
**	a comment (or a command different from '##start' and '##end')
** ___Return___:
**	1: if the line is a comment or an ignored command
**	0: otherwise
*/

int				is_comment(char *line)
{
	return (line[0] == '#');
}

/*
** ___Description___:
**	Function check if the line is exactly '##start' or '##end'.
** ___Return___:
**	1: if the input line is '##start' or '##end'.
**	0: otherwise.
*/

int				is_start_end(char *line)
{
	return (ft_strequ("##start", line) || ft_strequ("##end", line));
}

/*
** ___Description___:
**	Check the line after '##start' or '##end'
**	Function check if there is 2 spaces in the line and there is no '-'
**	within the line (if it may be a edge)
** ___Return___:
**	1: the input line tested has 2 spaces and no '-' within
**	0: otherwise
*/

int				is_legal_terminal(t_list *alst)
{
	alst = alst->next;
	return ((ft_count_c(L1, ' ') == 2 && !ft_strchr(L1, '-')) ? 1 : 0);
}

/*
** ___Description___:
**	It checks the lines stored in linked list with content of t_input
**	The tests do not cover all the cases, but basic tests to detect if
**	there is any major invalid format input lines.
**	The checks are:
**	-if line is NULL, empty, or starts by 'L'
**	-if line is '#start' or '##end', and the following line has 3 words
**	separated by a space and has no '-'
**	-if the line is a number (for the number of ants)
** ___Return___:
**	1: if all the input lines passed the basic tests
**	0: if there is an error
*/

static int		checkinput(t_list *alst)
{
	int					t[2];
	unsigned long long	ant;

	t[0] = 0;
	t[1] = 0;
	ant = 0;
	if (!alst)
		return (0);
	while (alst && t[0] <= 1 && t[1] <= 1)
	{
		if (!L1 || ft_strequ(L1, "\0") || L1[0] == 'L')
			return (0);
		else if (ant && ft_strequ("##start", L1))
			t[0] += is_legal_terminal(alst);
		else if (ant && ft_strequ("##end", L1))
			t[1] += is_legal_terminal(alst);
		else if (ft_isnumber(L1) == 1)
			ant = ft_atoull(L1);
		else if ((is_comment(L1) && !ant) || (!is_comment(L1) && ant
					&& !(((ft_wd(L1) == 1) && ft_count_c(L1, '-') == 1)
					|| ((ft_wd(L1) == 3) && ft_count_c(L1, ' ') == 2))))
			return (0);
		alst = alst->next;
	}
	return ((t[0] == 1 && t[1] == 1 && ant) ? 1 : 0);
}

/*
** ___Description___:
**	Read of the input from standard input (STDIN via '<') line by line.
**	Each lines is stored in a string in t_input (create on the fly) and
**	added as content of each item of a link list.
** ___Return___:
**	1 : if checks performed by checkinput return there is no major
**		invalid format in the lines read on the standard input.
**	0 : error from GNL or mem allocation issue with lstnew or checkinput fail
*/

int				read_input(t_list **alst)
{
	char				*gnl;
	t_list				*new_list;
	t_input				new_input;
	int					ret;

	gnl = NULL;
	ret = 0;
	while ((ret = get_next_line(0, &gnl)) > 0)
	{
		if (!(new_input.line = ft_strdup(gnl))
		|| !(new_list = ft_lstnew(&new_input, sizeof(t_input))))
		{
			new_input.line ? ft_strdel(&new_input.line) : 0;
			gnl ? ft_strdel(&gnl) : 0;
			return (0);
		}
		ft_lstappend(alst, new_list);
		gnl ? ft_strdel(&gnl) : 0;
	}
	gnl ? ft_strdel(&gnl) : 0;
	return ((ret == -1) ? 0 : checkinput(*alst));
}
