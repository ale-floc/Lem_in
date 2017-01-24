/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:59:56 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 19:00:00 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parse_get_ants(t_env *env, char *line)
{
	int i;
	int ants;

	i = 0;
	ants = 0;
	while (line[i])
	{
		if (line[i] != '\0' && ft_isdigit(line[i]))
			i++;
		if (line[i] == '\0' || !ft_isdigit(line[i]))
		{
			if (line[i] == '\0')
			{
				ants = ft_atoi(line);
				if (ants < 1 || ft_strlen(line + 1) > 8)
					ft_error(env, 5);
				else
					break ;
			}
			else
				ft_error(env, 1);
		}
	}
	return (ants);
}

t_env	*parse_diese(t_env *env, char *line)
{
	int o;

	o = 0;
	if (line[o] == '#' && line[o + 1] == '#')
		check_command(env, line);
	return (env);
}

t_list	*parse_room(t_env *env, char *line)
{
	t_list	*list;
	char	**tmp;
	int		i;

	i = 0;
	list = env->begin;
	tmp = ft_strsplit_fn(line, is_space_or_tab);
	if (is_strnb(env, tmp[1], tmp[2]))
		list = ft_listpush(tmp, list, env);
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (list);
}

int		parse_check(t_env *env, char *line)
{
	if (env->nb_ants != -1)
	{
		if (line[0] == 'L')
			ft_error(env, 1);
		else if (space_room(env, line))
			return (1);
		else if (!space_room(env, line) && ft_strstr(line, "-") &&
			env->start && env->end)
			return (1);
		else if (!space_room(env, line) && ft_strstr(line, "-") &&
			(!env->start || !env->end))
			ft_error(env, 10);
	}
	return (0);
}

t_tube	*parse_list(t_env *env)
{
	t_tube *tmp;
	t_tube *temp;

	tmp = env->path;
	temp = env->path;
	if (temp->next)
	{
		if (temp->next->next)
		{
			temp = temp->next->next;
			while (temp)
			{
				if (check_if_exist(tmp->adress->tube, temp))
					env->path->next = temp;
				temp = temp->next;
			}
		}
	}
	return (env->path);
}
