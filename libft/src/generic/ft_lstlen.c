/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:55:02 by weilin            #+#    #+#             */
/*   Updated: 2020/06/19 13:28:12 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlen(t_list *lst)
{
	t_list *tmp;
	size_t len;

	len = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
}
