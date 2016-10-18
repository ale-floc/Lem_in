/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <ale-floc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/15 16:10:12 by ale-floc          #+#    #+#             */
/*   Updated: 2014/11/27 15:21:50 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counter(int nb)
{
	int counter;

	if (nb > 0)
		counter = 1;
	else
		counter = 2;
	while (nb >= 10 || nb <= -10)
	{
		nb = nb / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	int		i;
	int		o;
	char	*str;

	o = 0;
	i = ft_counter(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
		return (ft_strdup("0"));
	str[i--] = '\0';
	if (n < 0)
		o = 1;
	while (i >= 0)
	{
		if (o == 0)
			str[i--] = ((n % 10) + '0');
		if (o == 1)
			str[i--] = (-(n % 10) + '0');
		n = n / 10;
	}
	if (o == 1)
		str[0] = '-';
	return (str);
}
