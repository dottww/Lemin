/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:02:18 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 22:35:51 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*reverse(t_list *previous, t_list *current, t_list *next)
{
	if (current == NULL)
		return (previous);
	next = current->next;
	current->next = previous;
	previous = current;
	return (reverse(previous, next, NULL));
}

void			ft_lstrev(t_list **alst)
{
	*alst = reverse(NULL, *alst, NULL);
}
