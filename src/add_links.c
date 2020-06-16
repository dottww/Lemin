/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 12:20:27 by pimichau          #+#    #+#             */
/*   Updated: 2020/06/16 03:29:44 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	link_already_exists(t_list *origin, t_list *dest)
{
	t_list	*elem;

	elem = origin;
	while (elem)
	{
		if (((t_link *)elem->content)->room == dest)
			return (1);
		elem = elem->next;
	}
	return (0);
}

static int	create_link(t_list *room1, t_list *room2)
{
	t_list		*tlist_of_a_link;
	t_link		new_link;
	t_room		*origin_room;

	origin_room = (t_room *)(room1->content);
	new_link.usage = 0;
	new_link.room = NULL;
	if (link_already_exists(origin_room->links, room2))
		return (0);
	if (!(tlist_of_a_link = ft_lstnew(&new_link, sizeof(t_link))))
		return (0);
	((t_link *)tlist_of_a_link->content)->room = room2;
	ft_lstappend(&origin_room->links, tlist_of_a_link);
	return (1);
}

static int	rooms_exist(t_list *head, t_list **room1,
			t_list **room2, char **tab)
{
	t_list	*elem;
	t_room	*tmp;
	int		check;

	check = 0;
	elem = head;
	while (elem && check < 2)
	{
		tmp = (t_room *)elem->content;
		if (ft_strequ(tab[0], tmp->name))
		{
			check++;
			*room1 = elem;
		}
		if (ft_strequ(tab[1], tmp->name))
		{
			check++;
			*room2 = elem;
		}
		elem = elem->next;
	}
	return (check == 2);
}

static int	link_checker(t_antfarm *atf, char **tab)
{
	t_list	*head;
	t_list	*room1;
	t_list	*room2;

	room1 = NULL;
	room2 = NULL;
	if (tab[0][0] == '#')
		return (1);
	head = atf->rooms;
	if (!tab[0] || !tab[1] || tab[2]
		|| !rooms_exist(head, &room1, &room2, tab))
		// return (0);
	{ft_printf("link_checker1\n");	return (0);}
	return (create_link(room1, room2) && create_link(room2, room1));
}

int			add_link(t_antfarm *atf, char *line)
{
	char	**tab;

	tab = NULL;
	if (line[0] == '#')
		return (1);
	if (ft_count_c(line, '-') != 1 || !(tab = ft_strsplit_c(line, '-')))
	{ft_printf("addlink2\n");	return (0);}
	if (!link_checker(atf, tab))
	{ft_printf("addlink3\n");	return (ret_strtab_free(tab, 0));}
		// return (ret_strtab_free(tab, 0));
	return (ret_strtab_free(tab, 1));
}
