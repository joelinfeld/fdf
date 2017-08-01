/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:55:46 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/19 16:05:15 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
					int c, size_t n)
{
	unsigned char	*source;
	unsigned char	*dest;
	unsigned char	cc;

	cc = (unsigned char)c;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (n--)
	{
		if (*source == cc)
		{
			*dest++ = *source++;
			dst = dest;
			return (dst);
		}
		*dest++ = *source++;
	}
	return (NULL);
}
