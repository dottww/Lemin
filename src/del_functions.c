/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:57:28 by weilin            #+#    #+#             */
/*   Updated: 2020/06/19 02:39:48 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_delcontent(void *content, size_t size)
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
		ft_lstdel(&room->links, ft_delcontent);
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
	ft_lstdel(a, ft_delcontent);
	ft_lstdel(b, ft_delcontent);
}
