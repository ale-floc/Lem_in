/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 15:58:52 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/16 05:37:46 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *s1;

	s1 = (unsigned char*)malloc(sizeof(*s1) * len);
	if (s1 == NULL)
		return (NULL);
	memcpy(s1, src, len);
	memcpy(dst, s1, len);
	free(s1);
	return (dst);
}
