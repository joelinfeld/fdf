/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:35:59 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 14:22:13 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*source;
	unsigned char	cc;

	source = (unsigned char *)s;
	cc = c;
	while (n--)
	{
		if (*source == cc)
		{
			return (source);
		}
		source++;
	}
	return (NULL);
}
