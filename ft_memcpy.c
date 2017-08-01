/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 17:40:56 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/19 16:06:00 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *source;
	char *dest;

	source = (char *)src;
	dest = (char *)dst;
	while (n--)
	{
		*dest++ = *source++;
	}
	return (dst);
}
