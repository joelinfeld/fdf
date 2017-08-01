/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:52:53 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/17 22:21:20 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		strstart;
	int		strend;
	char	*res;

	if (s)
	{
		i = 0;
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		strstart = i;
		while (s[i])
			i++;
		if (i == strstart)
			strend = strstart;
		else
		{
			while (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n')
				i--;
			strend = i;
		}
		res = ft_strsub(s, strstart, (size_t)(strend - strstart));
		return (res);
	}
	return (NULL);
}
