/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:30:47 by weilin            #+#    #+#             */
/*   Updated: 2020/06/29 02:39:54 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool		room_viable(t_list *curr_link, t_room *adj)
{
	return (!is_visited(adj) && !go_link(curr_link) && !is_start(adj));
}

static bool		pending_detour(t_room *curr, int usage)
{
	return (curr->deviation && usage == 0);
}

/*
** Decription:
**
** if with the 1st return:
**	if usage != -1 => usage is 0/1 meaning either the link/edge not used yet
**  or going in opposite direction than a path taking this linke/edge
**	+ dst != 0 => room is not the end
**	+ curr->path_id != dst->path_id => curr and dst constituting the edge are
**	  from 2 differents paths and dst room are on a path
**	+ dst->path_id != 0            => either curr and dst are in 2 differents
**	  paths or curr not in any path and dst already in a path
**	+ !dst->visited => the dst room has not be visited yet
**	+ adj_part_of_path is TRUE = the link toward adj_room is 1, it means adj_room
**    is already part of other route, so now should deviate //wei
** Return:
**	check if 
*/

static bool		route_viable(t_list *current, t_list *curr_link, t_list *end)
{
	t_list		*adj_room;
	t_room		*adj;
	t_room		*curr;
	int			usage;

	curr = (t_room *)current->content; // room from which links/edges will be inspect
	adj_room = ((t_link *)curr_link->content)->room; // catching the neighbor room of the edge encapsulate in t_list type
	adj = (t_room *)adj_room->content;
	usage = ((t_link *)curr_link->content)->usage;
	if (room_viable(curr_link, adj)	&& adj_part_of_path(current, adj_room))
		return (detour_src_of_adj(adj_room, end));
	return (room_viable(curr_link, adj)	&& !pending_detour(curr, usage)); //weib
}

// IN ROUTE VIABLE, NO USE OF USAGE, THERE MAY BE A PROLEM, JUST BELOW HOW IT WAS PREVIOUSLY
//	if (!golink(curr_link) && !is_start(adj) && !samepath(src, adj) //pas bon sens && !ISSTART(adj) && !PATH(src, adj)
//	&& !is_visited(adj) && is_in_path(adj) && adj_part_of_path(curr, adj_room)) // && !VISITED(adj) && PATH(adj) && 
//		return (deviation_src_of_adj(adj_room, end));
//	// return (!adj->visited && usage != -1 && adj->s_t != 0 // 1!VISITED(adj) && 1pas bon sens && 1!ISSTART(adj)
//	return (!is_visited(adj) && !golink(curr_link) && !is_start(adj) // 1!VISITED(adj) && 1pas bon sens && 1!ISSTART(adj)
//	&& !(src->deviation && usage == 0)); // 1!(0[[0DV(src)]] && 1!LINK(0src, adj))

/*
** Description:
**	Append a link containing the dst room.
**	In the dst room are noted the origin room where it comes from and the
**	flag visited is changed to TRUE
*/

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
** try to find possible routes to endroom through rooms not visited 
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
		if (route_viable(current_room, link, end))
		{
			if (!add_to_route(&route, target_room, current_room))
				return (0);
			if (((t_room *)target_room->content)->s_t == 1)
				return (1);
			if (adj_part_of_path(current_room, target_room))
				((t_room *)target_room->content)->deviation = true; //weib
		}
		link = link->next;
	}
	if (((t_room *)current_room->content)->deviation == true)
		((t_room *)current_room->content)->deviation = false;
	return (1);
}
