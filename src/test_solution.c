/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:43:17 by bwan-nan          #+#    #+#             */
/*   Updated: 2020/06/25 18:09:09 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			printpath_update_data(t_antfarm *atf, unsigned long rounds
				, t_list **paths)
{
	t_list	*room;

	room = atf->rooms;
	while (room)
	{
		((t_room *)room->content)->next = ((t_room *)room->content)->new_next;
		((t_room *)room->content)->path_id = ((t_room *)room->content)
		->new_path_id;
		((t_room *)room->content)->previous = NULL;
		((t_room *)room->content)->visited = false;
		((t_room *)room->content)->deviation = false;
		((t_room *)room->content)->dead_end = false;
		((t_room *)room->content)->new_next = NULL;
		((t_room *)room->content)->new_path_id = 0;
		room = room->next;
	}
	ft_lstrev(paths);
	if (atf->option & DISPLAY_PATHS)
		print_paths(*paths);
	// { ft_printf("HELLO, rds=%lu\n",rounds);	print_paths(*paths);}
	atf->rounds = rounds;
}

static void		increment_sent_values(t_list *path)
{
	while (path)
	{
		((t_path *)path->content)->sent++;
		path = path->next;
	}
}

t_list	*select_path_to_send_ants(t_list *path, unsigned int ant_qty)
{
	t_list			*head;
	unsigned int	ant_qty_out;
	int				path_len;

	if (!path->next)
		return (path);
	head = path;
	path_len = ((t_path *)path->content)->len;
	ant_qty_out = 0;
	path = path->next; // skip start_room
	while (path)
	{
		ant_qty_out += path_len - ((t_path *)path->content)->len + 1; // relation PATH/ANT
		path = path->next;
	}
	if (ant_qty_out < ant_qty)
		return (head);
	return (select_path_to_send_ants(head->next, ant_qty));
}

/*
** Description:
**	Receiving the paths (as parameter)
**
**
*/

unsigned long	test_solution(t_antfarm *atf, t_list *paths)
{
	t_list			*used_path;
	unsigned long	rounds;
	unsigned		ant_qty;

	rounds = 0;
	used_path = paths;
	ant_qty = atf->ant_qty;
	while (ant_qty > 0)
	{
		used_path = select_path_to_send_ants(used_path, ant_qty);
		increment_sent_values(used_path);
		ant_qty -= ft_lstlen(used_path);
		rounds++;
	}
	rounds += ((t_path *)used_path->content)->len - 1;
	if (atf->option & DISPLAY_PATHS)
	{
		if (rounds >= atf->rounds)
			ft_printf("This solution would take %ld rounds\n", rounds);
		else
			ft_printf("This solution would take %ld rounds\n", rounds);
	}
	return (rounds);
}
