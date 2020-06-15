/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:10:05 by weilin            #+#    #+#             */
/*   Updated: 2018/11/23 11:54:33 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;
	t_list	*process;

	tmp = alst[0];
	while (tmp)
	{
		process = tmp;
		del(process->content, process->content_size);
		tmp = process->next;
		free(process);
	}
	alst[0] = NULL;
}
