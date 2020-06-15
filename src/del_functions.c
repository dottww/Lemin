/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:12:54 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/15 23:45:20 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_steps(void *content, size_t size)
{
	if (content && size)
		free(content);
}

void		del_room(void *content, size_t size)
{
	t_room	*room;

	room = (t_room *)content;
	if (content && size)
	{
		ft_strdel(&room->name);
		ft_lstdel(&room->tunnels, del_steps);
		free(content);
	}
}

void		del_input(void *content, size_t size)
{
	t_input		*input;

	input = (t_input *)content;
	if (content && size)
	{
		ft_strdel(&input->line);
		free(content);
	}
}

void		del_lists(t_list **a, t_list **b)
{
	ft_lstdel(a, del_steps);
	ft_lstdel(b, del_steps);
}
