/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:18:27 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 14:48:27 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*src;
	int		len;

	cc = (char)c;
	src = (char*)s;
	len = ft_strlen(src);
	src = &src[len];
	while (*src != cc && len--)
	{
		src--;
	}
	if (*src == cc)
		return (src);
	else
		return (NULL);
}
