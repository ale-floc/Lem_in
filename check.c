/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:07:29 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 14:07:31 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_env		*check_command(t_env *env, char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line);
	if (!ft_strcmp("##start", line))
	{
		if (env->start == 0)
		{
			env->start = 1;
			env->prepare_start = 1;
		}
		else
			ft_error(env, 8);
	}
	else if (!ft_strcmp("##end", line))
	{
		if (env->end == 0)
		{
			env->end = 1;
			env->prepare_end = 1;
		}
		else
			ft_error(env, 9);
	}
	free(tmp);
	return (env);
}

int			space_room(t_env *env, char *line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (ft_space(line[i]))
			space++;
		i++;
	}
	if (space == 2)
		return (1);
	else if (space != 0 && space != 2)
		ft_error(env, 4);
	return (0);
}

int			check_if_exist(t_tube *tube1, t_tube *tube2)
{
	while (tube1)
	{
		if (tube1->adress == tube2->adress)
			return (1);
		tube1 = tube1->next;
	}
	return (0);
}

int			check_if_exist_in_tube(t_tube *tube1, t_list *tube2)
{
	while (tube1)
	{
		if (tube1->adress == tube2)
			return (1);
		tube1 = tube1->next;
	}
	return (0);
}

char		*line_parse(t_env *env, char *line)
{
	char	*tmp;

	tmp = NULL;
	if (ft_space(line[0]))
		ft_error(env, 1);
	tmp = ft_strtrim(line);
	free(line);
	return (tmp);
}
