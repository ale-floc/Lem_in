/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 10:53:57 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/29 22:26:16 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		k;

	i = 0;
	if (!s1)
		return (NULL);
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		k = 0;
		while (s1[i + k] && s2[k] && s1[i + k] == s2[k])
			k++;
		if (s2[k] == '\0')
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}
