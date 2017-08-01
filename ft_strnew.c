/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:11:42 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/19 00:36:01 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	res[size] = '\0';
	if (res)
	{
		ft_bzero(res, size + 1);
	}
	return (res);
}
