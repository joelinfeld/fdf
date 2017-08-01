/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 12:13:53 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/26 01:08:55 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *trace;

	if (!lst)
		return (NULL);
	new = f(lst);
	trace = new;
	while (lst->next)
	{
		lst = lst->next;
		trace->next = f(lst);
		trace = trace->next;
	}
	if (!new)
		return (NULL);
	return (new);
}
