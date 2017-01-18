/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:43:25 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/18 16:43:28 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_arg(t_env *e, char *str)
{
	int i;

	i = 1;
	if (str[i] == '\0')
		error_usage();
	while (str[i])
	{
		if (str[i] == 'e')
			options_on(&(*e), str[i]);
		else
			error_usage();
		i++;
	}
	return (0);
}

void	options_on(t_env *e, char c)
{
	if (c == 'e')
		e->e = 1;
}

t_env	*lem_init(void)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	env->nb_ants = -1;
	env->start = 0;
	env->end = 0;
	env->error = 0;
	env->prepare_start = 0;
	env->prepare_end = 0;
	env->begin = NULL;
	env->get_end = 0;
	env->path = NULL;
	env->tube = 0;
	env->move = 0;
	env->e = 0;
	return (env);
}
