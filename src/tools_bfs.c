/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_bfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:02:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/26 00:50:30 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			printpath_update_data(t_antfarm *atf, unsigned long rounds
				, t_list **pth)
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
	ft_lstrev(pth);
	if (atf->options & DISPLAY_PATH)
		print_all_paths(*pth);
	atf->rounds = rounds;
}

static void		increase_sent_values(t_list *path)
{
	while (path)
	{
		((t_path *)path->content)->sent++;
		path = path->next;
	}
}

t_list			*select_path_to_send_ants(t_list *path, unsigned int ant_qty)
{
	t_list			*head;
	unsigned int	path_capacity;
	int				head_path_len;
	if (!path->next)
		return (path);
	head = path;
	head_path_len = ((t_path *)path->content)->len;
	path_capacity = 0;
	path = path->next; // skip start_room
	while (path)
	{
		path_capacity += head_path_len - ((t_path *)path->content)->len + 1; // relation PATH/ANT
		path = path->next;
	}
	if (path_capacity >= ant_qty)
		return (select_path_to_send_ants(head->next, ant_qty));
	return (head);
	// if (path_capacity < ant_qty)
	// 	return (head);
	// return (select_path_to_send_ants(head->next, ant_qty));
}

unsigned long	solution_rounds(t_antfarm *atf, t_list *pth
				, unsigned int ant_qty)
{
	t_list			*used_path;
	unsigned long	rounds;

	rounds = 0;
	used_path = pth;
	while (ant_qty > 0)
	{
		used_path = select_path_to_send_ants(used_path, ant_qty);
		increase_sent_values(used_path);
		ant_qty -= ft_lstlen(used_path);
		rounds++;
	}
	rounds += ((t_path *)used_path->content)->len - 1;
	if (atf->options & DISPLAY_PATH)
	{
		if (rounds >= atf->rounds)
			ft_printf("This solution would take %ld rounds\n", rounds);
		else
			ft_printf("This solution would take %ld rounds\n", rounds);
	}
	return (rounds);
}

/*
** Description:
**
** Return:
**	TRUE  : 
**	FALSE : 
*/

bool			bfs_route(t_list *start, t_list *end, t_list **route)
{
	t_list		*elem;
	t_route		new_route;
	bool		found_new_path;

	found_new_path = false;
	if (!(*route = ft_lstnew(&new_route, sizeof(t_route)))) // no initialization of new_route, thus in lstnew, random value will be given to the inner variable of route no ?
		return (false);
	else
		((t_route *)(*route)->content)->room = start; //the only thing inside new_route is a list pointer of rooms, so it's fine
	// if (!malloc_route(route, start))
	// 	return (false);
	((t_room *)start->content)->visited = true; // Why setting visited status variable of start ? multiple bfs will be done, and will begins at start 
	elem = *route;
	while (elem)
	{
		if (!complete_route(elem, end)) //construct the queue of rooms, putting them in the queue of room elem under condition of usability
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_new_path = true;
			break ;
		}
		elem = elem->next;
	}
	return (found_new_path);
}

/*
** Description:
**	Allocation memory of the 
** Return:
**	1: no mem allocation issue for the link new_route route
**	0: if mem allocation issue for the link
*/

// static int		malloc_route(t_list **route, t_list *start)
// {
// 	t_route		new_route; 

// 	if (!(*route = ft_lstnew(&new_route, sizeof(t_route))))
// 		return (0);
// 	((t_route *)(*route)->content)->room = start;
// 	return (1);
// }