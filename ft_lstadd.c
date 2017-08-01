/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 12:04:22 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/29 18:41:26 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*current;

	if (alst)
	{
		current = *alst;
		if (!*alst)
			*alst = new;
		else
		{
			new->next = current;
			*alst = new;
		}
		current = NULL;
		new = NULL;
	}
}
