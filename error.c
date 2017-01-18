/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:40:55 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/18 16:41:04 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_error(t_env *env, int error)
{
	ft_putendl_fd("ERROR", 2);
	if (env->e)
	{
		if (error == 1)
			ft_putendl_fd("File is not correct format", 2);
		if (error == 2)
			ft_putendl_fd("Impossible to reach exit", 2);
		if (error == 3)
			ft_putendl_fd("Can not bind the same room", 2);
		if (error == 4)
			ft_putendl_fd("X or Y not correct", 2);
		if (error == 5)
			ft_putendl_fd("Number of Ants is not correct", 2);
		if (error == 6)
			ft_putendl_fd("Name of room is not correct", 2);
		if (error == 8)
			ft_putendl_fd("Multi Start detected", 2);
		if (error == 9)
			ft_putendl_fd("Multi End detected", 2);
		if (error == 10)
			ft_putendl_fd("Start or End not defined", 2);
	}
	exit(2);
}

void	error_usage(void)
{
	ft_putendl("Lem_in: illegal option");
	ft_putendl("usage: Lem_in [-e] < ([file] (optional))");
	exit(2);
}
