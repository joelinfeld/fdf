/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 13:44:38 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 13:42:35 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	size_t	len;
	int		i;

	if (s)
	{
		i = 0;
		len = ft_strlen((char *)s);
		res = (char *)malloc(sizeof(char) * len + 1);
		if (!res)
			return (NULL);
		while (s[i])
		{
			res[i] = f((char)s[i]);
			i++;
		}
		res[i] = '\0';
		return (res);
	}
	return (NULL);
}
