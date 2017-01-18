/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 11:59:10 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/26 14:28:03 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*s1;
	const char	*s2;

	s1 = dst;
	s2 = src;
	i = 0;
	while (i < n)
	{
		s1[i] = s2[i];
		if (s2[i] == c)
		{
			return (dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
