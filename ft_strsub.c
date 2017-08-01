/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 21:56:38 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/17 22:28:01 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*src;
	int		i;

	if (s)
	{
		i = 0;
		src = (char *)s;
		if (!(res = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (len--)
		{
			res[i++] = src[start++];
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
