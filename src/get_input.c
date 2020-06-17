/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:46:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/16 04:37:47 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_legal_terminal(t_list *alst)
{
	alst = alst->next;
	return ((ft_count_c(L1, ' ') == 2 && !ft_strchr(L1, '-')) ? 1 : 0);
}

static int		check_input(t_list *alst)
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
		else if (!is_comment(L1) && ant &&
					!(((ft_wd(L1) == 1) && ft_count_c(L1, '-') == 1)
						|| ((ft_wd(L1) == 3) && ft_count_c(L1, ' ') == 2)))
			return (0);
		alst = alst->next;
	}
	return ((t[0] == 1 && t[1] == 1 && ant) ? 1 : 0);
}

int				get_input(t_list **alst)
{
	char				*gnl;
	t_list				*new_list;
	t_input				new_input;
	gnl = NULL;
	while (get_next_line(0, &gnl) > 0)
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
	return (check_input(*alst));
}
