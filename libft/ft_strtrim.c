/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 13:19:07 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/26 14:53:52 by ale-floc         ###   ########.fr       */
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
	char	*str;
	int		start;
	int		end;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	while (s && ft_space(s[start]))
		start++;
	end = ft_strlen((char *)s) - 1;
	str = (char *)malloc(sizeof(char) * (end - start) + 1);
	while (s && ft_space(s[end]))
		end--;
	while (str && s)
	{
		i = -1;
		while ((++i + start) <= end)
			str[i] = s[start + i];
		str[i] = 0;
		return (str);
	}
	return (NULL);
}
