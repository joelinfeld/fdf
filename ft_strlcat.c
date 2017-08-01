/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 14:38:28 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 19:22:19 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		srclen;
	size_t	destend;

	srclen = ft_strlen(src);
	i = 0;
	while (dst[i] && i < size)
		i++;
	destend = i;
	if (!size)
		return (destend + srclen);
	while (src[i - destend] && i < size - 1)
	{
		dst[i] = src[i - destend];
		i++;
	}
	if (destend < size)
		dst[i] = '\0';
	return (destend + srclen);
}
