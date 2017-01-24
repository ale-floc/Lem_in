/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 13:54:09 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 13:54:10 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_strcmp_join(char *s1, char *s2)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	result = (unsigned char)s1[i] - (unsigned char)s2[i];
	free(s2);
	return (result);
}

char	*ft_strjoin_join(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
		ft_strlen(s2) + 1));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free((char *)s2);
	return (str);
}

int		is_strnb(t_env *env, char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i])
	{
		if (!ft_isdigit(str1[i]))
			ft_error(env, 4);
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (!ft_isdigit(str2[i]))
			ft_error(env, 4);
		i++;
	}
	return (1);
}
