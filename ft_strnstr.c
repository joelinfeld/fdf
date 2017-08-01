/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:52:50 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 13:27:13 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		strnmatch(const char *big,
				const char *little, int index, size_t len)
{
	int lenfind;
	int j;

	lenfind = ft_strlen((char *)little);
	j = 0;
	while (j < lenfind && len--)
	{
		if (little[j] == big[index + j])
			j++;
		else
			break ;
	}
	if (j == lenfind)
		return (1);
	else
		return (0);
}

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		match;
	char	*rtrn;

	match = 0;
	i = 0;
	if (!ft_strlen((char *)little))
		return ((char *)big);
	while (big[i] != '\0' && len)
	{
		if (big[i] == *little)
			match = strnmatch(big, little, i, len);
		if (match == 1)
		{
			rtrn = (char *)&big[i];
			return (rtrn);
		}
		i++;
		len--;
	}
	return (NULL);
}
