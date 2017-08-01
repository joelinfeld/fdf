/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:42:44 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 19:18:16 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int i;
	int j;
	int s2len;

	s2len = ft_strlen((char *)s2);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (n-- && j < s2len)
	{
		s1[i] = (char)s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
