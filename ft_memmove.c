/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 14:31:12 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 14:44:43 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *source;
	char *dest;

	source = (char *)src;
	dest = (char *)dst;
	if (src == dst)
		return (dst);
	if (src < dst)
	{
		source = &source[len - 1];
		dest = &dest[len - 1];
		while (len--)
			*dest-- = *source--;
	}
	else
	{
		while (len--)
			*dest++ = *source++;
	}
	return (dst);
}
