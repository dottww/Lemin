/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_route.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:30:47 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 20:34:25 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** ___Description___:
**	Check if adjacent (neighbor) room can be added in the queue (list of room),
**	an adjacent room can be added if it is not start, if the usage of the link
**	between the current room and the adjacent room is not a part of a path and
**	and of course if the neighbor has not been visited during the current bfs.
** ___Return___:
**	1: if the room can be added to the queue
**	0: otherwise
*/

static bool		room_viable(t_list *curr_link, t_room *adj)
{
	return (!is_visited(adj) && !go_link(curr_link) && !is_start(adj));
}

/*
** ___Description___:
**	It checks if a deviation process has to be performed.
*/

static bool		pending_detour(t_room *curr, int usage)
{
	return (curr->deviation && usage == 0);
}

/*
** ___Decription___:
**	It checks if the adjacent room is viable or if it is already in a path
**	that is different from current room, and will decide to detour the src_adj
**	if it is possible.
** ___Remarks___:
**	The checks are performed to decide if the neighbor room should be added to
**	bfs_route loop.
**	_Common case_ (last return):
**		The adj room is not a visited yet and not a part of any path, adj will
**		then be added to queue of route.
**	_Specific case_ (detour_src_of_adj call):
**		The adj room is a part of a path, but not visited yet by the current
**		bfs_route. The function detour_src_of_adj will thus be called.
** ___Return___:
**	TRUE: If adj_room is not available and detouring the src_of_adj is possible
**		or current room is not on a detouring mission and adj is available.
**	FALSE: adj is not viable or is a dead end or src_of_adj cannot be detoured
**		or current room is on a detouring mission.
*/

static bool		route_viable(t_list *current, t_list *curr_link, t_list *end)
{
	t_list		*adj_room;
	t_room		*adj;
	t_room		*curr;
	int			usage;

	curr = (t_room *)current->content;
	adj_room = ((t_link *)curr_link->content)->room;
	adj = (t_room *)adj_room->content;
	usage = ((t_link *)curr_link->content)->usage;
	if (room_viable(curr_link, adj) && adj_part_of_path(current, adj_room))
		return (detour_src_of_adj(adj_room, end));
	return (room_viable(curr_link, adj) && !pending_detour(curr, usage));
}

/*
** ___Description___:
**	Append a link containing the adj_room.
**	In the adj_room are noted the origin room where it comes from and the
**	flag visited is changed to TRUE.
** ___Remarks___:
**	Marking the room of origin in each room is convenient for the path
**	reconstruction
** ___Return___:
**	1: the link has been successfully appended to the route (ie added to queue).
**	0: if memory allocation issue (lstnew).
*/

static int		add_to_route(t_list **route, t_list *adj_room, t_list *current)
{
	t_route		new;
	t_list		*new_node;

	if (!(new_node = ft_lstnew(&new, sizeof(t_route))))
		return (0);
	((t_route *)new_node->content)->room = adj_room;
	ft_lstappend(route, new_node);
	((t_room *)adj_room->content)->previous = current;
	((t_room *)adj_room->content)->visited = true;
	return (1);
}

/*
** ___Description___:
**	Core part of the bfs, function performs the tests and constructs the queue/
**	route of rooms.
**	To decide if the neighbors of a room have to be add in the queue, tests
**	are performed (see route_viable to further details)
**	Also, intialization of deviation is performed (adj_part_of_path for more
**	details).
** ___Return___:
**	1: when all the neighbors of the current room are processed
**	   or if the room end is reached.
**	0: if mem allocation issue (in add_route)
*/

int				explore_route(t_list *route, t_list *end)
{
	t_list	*link;
	t_list	*target_room;
	t_list	*current_room;

	current_room = ((t_route *)route->content)->room;
	link = ((t_room *)current_room->content)->links;
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
				((t_room *)target_room->content)->deviation = true;
		}
		link = link->next;
	}
	if (((t_room *)current_room->content)->deviation == true)
		((t_room *)current_room->content)->deviation = false;
	return (1);
}
