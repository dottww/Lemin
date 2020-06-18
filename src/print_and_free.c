/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:56:12 by weilin            #+#    #+#             */
/*   Updated: 2020/06/15 23:27:19 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_input(t_list **alst, char *exit_msg)
{
	ft_lstdel(alst, del_input);
	if (exit_msg)
		ft_putendl(exit_msg);
	return (exit_msg ? -1 : 0);
}

int			print_and_free(t_antfarm *atf, t_list **input
			, t_list **paths, char *msg)
{
	if (atf->rooms)
		ft_lstdel(&atf->rooms, del_room);
	if (atf->ants)
		ft_lstdel(&atf->ants, del_steps);
	ft_lstdel(paths, del_steps);
	return (free_input(input, msg));
}
