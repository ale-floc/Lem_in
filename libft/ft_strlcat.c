/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 06:04:26 by ale-floc          #+#    #+#             */
/*   Updated: 2015/01/19 03:55:12 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		len_dst;

	len_dst = ft_strlen(dst);
	i = 0;
	if (size <= len_dst)
		return (size + ft_strlen(src));
	while (len_dst + i < (size - 1) && src[i] != '\0')
	{
		dst[i + len_dst] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + ft_strlen(src));
}
