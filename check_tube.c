/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:22:32 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 16:22:35 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_env			*check_and_push(t_env *env, t_list *list, int *i, char *line)
{
	t_list		*second;
	t_tube		*tube;

	second = env->begin;
	tube = NULL;
	while (second)
	{
		if (!ft_strcmp_join(line, ft_strjoin_join(list->salle,
			ft_strjoin("-", second->salle))))
		{
			if (!ft_strcmp(list->salle, second->salle))
				ft_error(env, 3);
			if (!check_if_exist_in_tube(list->tube, second))
				list->tube = list_push_tube(list, second);
			else
				return (env);
			tube = list->tube;
			while (tube)
				tube = tube->next;
			*i = 1;
		}
		second = second->next;
	}
	return (env);
}

t_env			*check_tube(t_env *env, char *line)
{
	t_list		*list;
	t_tube		*tube;
	char		**split;
	int			i;

	i = 0;
	tube = NULL;
	split = ft_strsplit(line, '-');
	list = env->begin;
	while (list)
	{
		if (!ft_strcmp(list->salle, split[0]))
			check_and_push(env, list, &i, line);
		list = list->next;
	}
	if (!i)
		ft_error(env, 1);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (env);
}

t_env			*check_room_or_tube(t_env *env, char *line)
{
	int			o;

	o = 0;
	if (space_room(env, line))
	{
		env->begin = parse_room(env, line);
		if (env->prepare_start)
			env->prepare_start = 0;
		if (env->prepare_end)
			env->prepare_end = 0;
	}
	else if (!space_room(env, line) && ft_strstr(line, "-"))
	{
		if (!env->prepare_end && !env->prepare_start &&
			env->start && env->end)
		{
			check_tube(env, line);
			env->tube = 1;
		}
		else
			ft_error(env, 10);
	}
	return (env);
}
