/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinfeld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 13:39:10 by jinfeld           #+#    #+#             */
/*   Updated: 2017/08/01 13:41:04 by jinfeld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void			wordcount(const char *str, char c, int *wc)
{
	int	i;
	
	i = -1;
	while (str[++i])
	{
		if (str[i] == 'c')
			*wc++;
	}
}

static	char		*letters(const char *str, int *j, char c)
{
	int	i;

	i = *j;
	while (str[++*j])
	{
		if (str[*j] == c)
		{
			str[*j] == '\0';
			break ;
		}
	}
	*j++;
	return (&str[i]);
}

char		**strsplit(const char *str, char c)
{
	char	**ret;
	int		wc;
	int		i;
	int		j;

	i = -1;
	j = -1;
	wc = 0;
	wordcount(str, c, &wc);
	ret = (char**)malloc(sizeof(char*) * wc);
	while (++i < wc)
		ret[i] = ft_strdup(letters(str, &j, c));
	return (ret);
}

int		main()
{
	char *str = "fill me up you pansy";
	char **ret;
	int	i;

	i = -1;
	ret = strsplit(str, ' ');
	while (++i < 5)
		printf("%s\n", ret[i]);
	return (0);
}
