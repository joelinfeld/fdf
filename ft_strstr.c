/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 19:59:28 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 14:34:45 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strmatch(const char *big, const char *little, int index)
{
	int	lenfind;
	int	j;

	lenfind = ft_strlen((char *)little);
	j = 0;
	while (j < lenfind)
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

char		*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		match;
	char	*rtrn;

	match = 0;
	i = 0;
	if (!ft_strlen((char *)little))
		return ((char *)big);
	while (big[i] != '\0')
	{
		if (big[i] == *little)
			match = strmatch(big, little, i);
		if (match == 1)
		{
			rtrn = (char *)&big[i];
			return ((char *)rtrn);
		}
		else
			i++;
	}
	return (0);
}
