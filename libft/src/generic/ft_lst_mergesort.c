/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 03:01:30 by weilin            #+#    #+#             */
/*   Updated: 2020/06/25 22:47:54 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*combine_lists(t_list *a, t_list *b, int (*cmp)(void *, void *))
{
	t_list		*merged_list;

	merged_list = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (cmp(a->content, b->content) <= 0)
	{
		merged_list = a;
		merged_list->next = combine_lists(a->next, b, cmp);
	}
	else
	{
		merged_list = b;
		merged_list->next = combine_lists(a, b->next, cmp);
	}
	return (merged_list);
}

static void		chunk(t_list *head, t_list **front, t_list **back)
{
	t_list		*fast;
	t_list		*slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

void			ft_lst_mergesort(t_list **source, int (*cmp)(void *, void *))
{
	t_list		*head;
	t_list		*a;
	t_list		*b;

	head = *source;
	a = NULL;
	b = NULL;
	if (head == NULL || head->next == NULL)
		return ;
	chunk(head, &a, &b);
	ft_lst_mergesort(&a, cmp);
	ft_lst_mergesort(&b, cmp);
	*source = combine_lists(a, b, cmp);
}
