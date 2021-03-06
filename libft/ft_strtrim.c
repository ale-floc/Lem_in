/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:55:21 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 18:55:23 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_space(char c)
{
	return (c == ' ' || c == '\v' || c == '\n' || c == '\t' || c == '\f'
	|| c == '\r');
}

char	*ft_strtrim(char const *s)
{
	int		i;
	int		size;
	char	*str;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	while (ft_space(s[size - 1]))
		size--;
	i = -1;
	while (ft_space(s[++i]))
		size--;
	if (size <= 0)
		size = 0;
	str = (char*)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	s += i;
	i = -1;
	while (++i < size)
		str[i] = *s++;
	str[i] = '\0';
	return (str);
}
