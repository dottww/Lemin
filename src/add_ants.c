/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 11:53:19 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/15 22:14:12 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		add_ant(int id, t_antfarm *atf)
{
	t_ant	ant;
	t_list	*new_ant;

	ant.id = id;
	ant.position = atf->start->content;
	if (!(new_ant = ft_lstnew(&ant, sizeof(t_ant))))
		return (0);
	ft_lstprepend(&atf->ants, new_ant);
	return (1);
}
