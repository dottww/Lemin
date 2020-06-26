/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 00:06:23 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 15:40:00 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				is_comment(char *line)
{
	return (line[0] == '#');
}

int				is_start_end(char *line)
{
	return (ft_strequ("##start", line) || ft_strequ("##end", line));
}

/*
** ___Description___:
**	Check the line after '##start' or '##end'
**	Function check if there is 2 spaces in the line and there is no '-'
**	within the line (if it may be a edge)
*/

int				is_legal_terminal(t_list *alst)
{
	alst = alst->next;
	return ((ft_count_c(L1, ' ') == 2 && !ft_strchr(L1, '-')) ? 1 : 0);
}

/*
** ___Description___:
**	Some check on the line stock in input linked list.
**	The check are:
**	-if line is different of NULL, not empty, and does not start by 'L'
**	-if line is '#start' or '##end', and the following line could be a room
**	-if the line is a number of type unsigned long long (for the number of ants)
**	- 
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
		if (!L1 || ft_strequ(L1, "\0") || L1[0] =='L')
			return (0);
		else if (ant && ft_strequ("##start", L1))
			t[0] += is_legal_terminal(alst);
		else if (ant && ft_strequ("##end", L1))
			t[1] += is_legal_terminal(alst);
		else if (ft_isnumber(L1) == 1)
			ant = ft_atoull(L1);
		else if ((is_comment(L1) && !ant) || (!is_comment(L1) && ant
					&& !(((ft_wd(L1) == 1) && ft_count_c(L1, '-') == 1) // one 'word' with one '-'
					|| ((ft_wd(L1) == 3) && ft_count_c(L1, ' ') == 2)))) // or 3 words with 2 spaces
			return (0);
		alst = alst->next;
	}
	return ((t[0] == 1 && t[1] == 1 && ant) ? 1 : 0);
}

/*
** ___Description___:
**	Read of the input in standard input (STDIN via '<') line by line
**	Each lines is stock in a link (create on the fly) added to input
**	
*/

int				read_input(t_list **alst)
{
	char				*gnl;
	t_list				*new_list;
	t_input				new_input;
	int					ret;

	gnl = NULL;
	ret = 0 ;
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
