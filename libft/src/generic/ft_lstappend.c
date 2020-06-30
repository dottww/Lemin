/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:31:48 by weilin            #+#    #+#             */
/*   Updated: 2020/06/30 21:06:33 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	tmp = *alst == NULL ? NULL : *alst;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}
