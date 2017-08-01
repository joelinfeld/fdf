/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 21:33:20 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/29 18:43:16 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list *trace;

	if (alst)
	{
		trace = *alst;
		del(trace->content, trace->content_size);
		free(trace);
		trace = NULL;
		*alst = NULL;
	}
}
