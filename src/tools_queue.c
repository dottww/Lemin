/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 22:30:47 by weilin            #+#    #+#             */
/*   Updated: 2020/06/19 17:16:27 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		add_to_route(t_list **route, t_list *room, t_list *current)
{
	t_route		new;
	t_list		*new_node;

	if (!(new_node = ft_lstnew(&new, sizeof(t_route))))
		return (0);
	((t_route *)new_node->content)->room = room;
	ft_lstappend(route, new_node);
	((t_room *)room->content)->previous = current;
	((t_room *)room->content)->visited = true;
	return (1);
}

static bool		link_is_usable(t_list *current, t_list *link, t_list *end)
{
	t_list		*room;
	t_room		*dest;
	t_room		*ori;
	int			usage;

	ori = (t_room *)current->content;
	room = ((t_link *)link->content)->room;
	dest = (t_room *)room->content;
	usage = ((t_link *)link->content)->usage;//wei
	if (usage != -1 && dest->s_t != 0 && ori->path_id != dest->path_id
	&& !dest->visited && dest->path_id != 0 && going_to_deviate(current, room))
		return (deviation_reaches_end(room, end));
	return (!dest->visited && usage != -1 && dest->s_t != 0
	&& !(ori->deviation && usage == 0));
}

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

int				complete_route(t_list *route, t_list *end)
{
	t_list	*link;
	t_list	*target_room;
	t_list	*current_room;

	current_room = ((t_route *)route->content)->room;
	link = ((t_room *)current_room->content)->links;
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


