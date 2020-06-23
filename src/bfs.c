/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 18:02:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/23 14:32:35 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Description:
**	Allocation memory of the 
** Return:
**	1: no mem allocation issue for the link new_route route
**	0: if mem allocation issue for the link
*/

static int				malloc_route(t_list **route, t_list *start)
{
	t_route		new_route; // no initialization of new_route, thus in lstnew, random value will be given to the inner variable of route no ?

	if (!(*route = ft_lstnew(&new_route, sizeof(t_route))))
		return (0);
	((t_route *)(*route)->content)->room = start;
	return (1);
}

//temporary funtion to print out all routes, can delete later
static void		print_routes(t_list *room)
{
	// if(0)
	{while (room)
	{
		ft_printf("%s%s"
		, ((t_room *)room->content)->name
		, ((t_room *)room->content)->next ? "-" : "");
		room = ((t_room *)room->content)->next;
	}}
}

//temporary funtion to print out all routes, can delete later
void		print_route(t_list *rt)
{
	t_list	*room;

	int x=1;
	
	x=0;
	
	if(x)
	{while (rt)
	{
		room = ((t_route *)rt->content)->room;
		print_routes(room);
		rt = rt->next;
	ft_putchar('\n');}
	}
}

/*
** Description:
**
** Return:
**	TRUE  : 
**	FALSE : 
*/

bool			bfs(t_list *start, t_list *end, t_list **route)
{
	t_list	*elem;
	// t_list	*list_tmproom;
	bool	found_augmented_path;

	found_augmented_path = false;
	if (!malloc_route(route, start))
		return (false);
	((t_room *)start->content)->visited = true; // Why setting visited status variable of start ? multiple bfs will be done, and will begins at start 
	elem = *route;
	while (elem) //LOOP I: SA, SB
	{
		// list_tmproom = ((t_route *)elem->content)->room;
		if (!complete_route(elem, end)) //construct the queue of rooms, putting them in the queue of room elem under condition of usability
			return (false);
		if (((t_room *)end->content)->visited)
		{
			found_augmented_path = true;
			break ;
		}
		elem = elem->next;
	}
	return (found_augmented_path);
}