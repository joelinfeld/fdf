/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 13:50:33 by jinfeld           #+#    #+#             */
/*   Updated: 2017/01/18 13:43:04 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		c;
	char	swap;

	i = 0;
	c = ft_strlen(str);
	while (i < (c / 2))
	{
		swap = str[c - i - 1];
		str[c - i - 1] = str[i];
		str[i] = swap;
		i++;
	}
	ft_putstr(str);
	return (str);
}
