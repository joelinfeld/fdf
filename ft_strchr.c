/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 20:08:26 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/17 22:06:18 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char cc;
	char *src;

	cc = (char)c;
	src = (char *)s;
	while (*src != cc && *src)
	{
		src++;
	}
	if (*src == cc)
		return (src);
	else
		return (NULL);
}
