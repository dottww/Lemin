/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 03:53:34 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 19:43:06 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_ant(t_antfarm *atf, t_list *alst, t_list *pth)
{
	int		i;
	t_ant	ant;
	t_list	*new_ant;

	atf->ants = NULL;
	i = atf->ant_qty + 1;
	while (--i)
	{
		ant.id = i;
		ant.at_room = (t_room *)(atf->start->content);
		if (!(new_ant = ft_lstnew(&ant, sizeof(t_ant))))
			return (0);
		ft_lstprepend(&atf->ants, new_ant);
	}
	if (!atf->options)
		print_antfarm(alst);
	print_ant_moves(atf, pth);
	return (1);
}
