/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:59:31 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/26 12:51:21 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cont(char const *str1, char c)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (str1[j] != '\0')
	{
		while (str1[j] == c)
			j++;
		if (str1[j] == '\0')
			k--;
		while (str1[j] != c && str1[j] != '\0')
			j++;
		k++;
	}
	return (k);
}

int		ft_strclen(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	m;
	int		nbr;
	char	**str;

	m = 0;
	if (!s || !c)
		return (NULL);
	nbr = ft_cont(s, c);
	str = (char **)malloc(sizeof(char *) * ((size_t)nbr + 1));
	if (!str || s == 0)
		return (NULL);
	while (nbr--)
	{
		while (*s == c && *s != '\0')
			s++;
		str[m] = ft_strsub((const char *)s, 0, ft_strclen((char *)s, c));
		if (str[m] == NULL)
			return (NULL);
		s += ft_strclen((char *)s, c);
		m++;
	}
	str[m] = NULL;
	return (str);
}
