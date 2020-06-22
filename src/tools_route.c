/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:30:47 by weilin            #+#    #+#             */
/*   Updated: 2020/06/22 16:50:36 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_to_route(t_list **route, t_list *target_room, t_list *current)
{
	t_route		new;
	t_list		*new_node;

	if (!(new_node = ft_lstnew(&new, sizeof(t_route))))
		return (0);
	((t_route *)new_node->content)->room = target_room;
	ft_lstappend(route, new_node);
	((t_room *)target_room->content)->previous = current;
	((t_room *)target_room->content)->visited = true;
	return (1);
}

/*
** Decription:
**
** 1st return:
**	if usage != -1
**	+ dest room is not the end
**	+ path index of the current room different from the path index of the dest room
**	+ the dest room has not be visited yet
**	+ the path index of the dest room != 0 (meaning ?)
**	+ going_to_deviate is TRUE = 
** Return:
**	
*/

static bool		link_is_usable(t_list *current, t_list *curr_link, t_list *end)
{
	t_list		*adj_room;
	t_room		*dest;
	t_room		*src;
	int			usage;

	src = (t_room *)current->content; // room from which links/edges will be inspect
	adj_room = ((t_link *)curr_link->content)->room; // catching the neighbor room of the edge encapsulate in t_list type
	dest = (t_room *)adj_room->content;
	usage = ((t_link *)curr_link->content)->usage; //
	if (usage != -1 && dest->s_t != 0 && src->path_id != dest->path_id //pas bon sens && !ISSTART(dest) && !PATH(src, dest)
	&& !dest->visited && dest->path_id != 0 && going_to_deviate(current, adj_room)) // && !VISITED(dest) && PATH(dest) && 
		return (deviation_reaches_end(adj_room, end));
	return (!dest->visited && usage != -1 && dest->s_t != 0 // !VISITED(dest) && pas bon sens && !ISSTART(dest)
	&& !(src->deviation && usage == 0)); // !([[DV(src)]] && !LINK(src, dest))
}

// (t_room *)RoomA->link: (t_room *)B , usage default:0

// Start-"A-B"-C-End
// RoomA->link:A-B: -1
// RoomB->link:B-A: 1


// static void		print_rts(t_list *room)
// {
// 	// if(0)
// 	{while (room)
// 	{
// 		ft_printf("%s%s"
// 		, ((t_room *)room->content)->name
// 		, ((t_room *)room->content)->next ? "-" : "");
// 		room = ((t_room *)room->content)->next;
// 	}}
// }

// static void		print_rt(t_list *rt)
// {
// 	t_list	*room;

// 	// if(0)
// 	{while (rt)
// 	{
// 		room = ((t_route *)rt->content)->room;
// 		print_rts(room);
// 		rt = rt->next;
// 	}}
// 	ft_putchar('\n');
// }

/*
** Description:
**
** Return:
**	
*/

int				complete_route(t_list *route, t_list *end)
{
	t_list	*link;
	t_list	*target_room;
	t_list	*current_room;

	current_room = ((t_route *)route->content)->room; // pointer on the room encapsulated in type t_list
	link = ((t_room *)current_room->content)->links; // pointer on the list links of the current room, the pointer is an encapsulate list of t_link in t_list struct var (if I understand)
	while (link)
	{
		target_room = ((t_link *)link->content)->room;
		if (link_is_usable(current_room, link, end)) //check path_id
		{
			if (!add_to_route(&route, target_room, current_room))
				return (0);
			if (((t_room *)target_room->content)->s_t == 1)
				return (1);
			if (going_to_deviate(current_room, target_room))
				((t_room *)target_room->content)->deviation = true;
		}
		link = link->next;
	}
	if (((t_room *)current_room->content)->deviation == true)
		((t_room *)current_room->content)->deviation = false;
	return (1);
}

/*
** routes are all possible routes
*/


