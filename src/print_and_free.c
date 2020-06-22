/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 02:56:12 by weilin            #+#    #+#             */
/*   Updated: 2020/06/21 15:09:42 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			free_input(t_list **alst, char *exit_msg)
{
	ft_lstdel(alst, del_input);
	if (exit_msg)
	{
		write(2, exit_msg, ft_strlen(exit_msg));
		ft_putchar('\n');
	}
	return (exit_msg ? 1 : 0);
}

int			print_and_free(t_antfarm *atf, t_list **input
			, t_list **paths, char *msg)
{
	if (atf->rooms)
		ft_lstdel(&atf->rooms, del_room);
	if (atf->ants)
		ft_lstdel(&atf->ants, ft_delcontent);
	ft_lstdel(paths, ft_delcontent);
	return (free_input(input, msg));
}
