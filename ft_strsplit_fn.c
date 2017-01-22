/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_fn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramos <anramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 14:04:52 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/20 17:15:55 by anramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_space_or_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static int	ft_count(char const *str1, int (*f) (char))
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (str1[j] != '\0')
	{
		while (f(str1[j]))
			j++;
		if (str1[j] == '\0')
			k--;
		while (!f(str1[j]) && str1[j] != '\0')
			j++;
		k++;
	}
	return (k);
}

static int	ft_strclen(char *str, int (*f) (char))
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (f(str[i]))
			return (i);
		i++;
	}
	return (i);
}

char		**ft_strsplit_fn(char const *s, int (*f) (char))
{
	size_t	m;
	int		nbr;
	char	**str;

	m = 0;
	if (!s || !f)
		return (NULL);
	nbr = ft_count(s, f);
	str = (char **)malloc(sizeof(char *) * ((size_t)nbr + 1));
	if (!str || s == 0)
		return (NULL);
	while (nbr--)
	{
		while (f(*s) && *s != '\0')
			s++;
		str[m] = ft_strsub((const char *)s, 0, ft_strclen((char *)s, f));
		if (str[m] == NULL)
			return (NULL);
		s += ft_strclen((char *)s, f);
		m++;
	}
	str[m] = NULL;
	free(str[m]);
	return (str);
}
