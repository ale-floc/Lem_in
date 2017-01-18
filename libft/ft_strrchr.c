/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 11:57:55 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/17 15:27:43 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int o;

	i = 0;
	o = -1;
	while (s[i] != '\0')
	{
		if ((char)c == s[i])
			o = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	if (o != -1)
		return ((char *)&s[o]);
	return (NULL);
}
