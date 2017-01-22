/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramos <anramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:07:21 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/22 20:04:44 by anramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_strcmp_join(char *s1, char *s2)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	result = (unsigned char)s1[i] - (unsigned char)s2[i];
	free(s2);
	return (result);
}

char	*ft_strjoin_join(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
		ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free((char *)s2);
	return (str);
}


t_env	*check_tube(t_env *env, char *line)
{
	t_list	*list;
	t_list	*second;
	t_tube	*tube;
	int		pass;
	char	**split;
	int i;

	i = 0;
	split = ft_strsplit(line, '-');
	list = env->begin;
	pass = 0;
	while (list)
	{
		if (!ft_strcmp(list->salle, split[0]))
		{
			second = env->begin;
			while (second)
			{
				if (!ft_strcmp_join(line, ft_strjoin_join(list->salle, ft_strjoin("-", second->salle))))
				{
					if (!ft_strcmp(list->salle, second->salle))
						ft_error(env, 3);
					if (!check_if_exist_in_tube(list->tube, second))
						list->tube = list_push_tube(list, second);
					else
					{
						while (split[i])
						{
							free(split[i]);
							i++;
						}
						free(split);
						return (env);
					}
					tube = list->tube;
					while (tube)
						tube = tube->next;
					pass = 1;
				}
				second = second->next;
			}
		}
		list = list->next;
	}
	if (!pass)
		ft_error(env, 1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (env);
}

t_env	*check_room_or_tube(t_env *env, char *line)
{
	int o;

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

t_tube	*end_exist_in_tube(t_tube *tmp)
{
	t_tube	*secu;
	t_tube	*sous_tube;
	t_tube	*my_tube;

	secu = tmp;
	sous_tube = NULL;
	my_tube = NULL;
	my_tube = search_end(tmp);
	if (my_tube)
		return (my_tube);
	else
	{
		my_tube = tmp;
		while (my_tube)
		{
			if (my_tube->adress->room_end)
				return (my_tube);
			sous_tube = my_tube->adress->tube;
			while (sous_tube)
			{
				if (sous_tube->adress->room_end)
					return (my_tube);
				sous_tube = sous_tube->next;
			}
			my_tube = my_tube->next;
		}
	}
	return (secu);
}

t_env	*ft_recursive_tube(t_tube *tube, t_env *env, t_tube *tmp)
{
	t_tube *secu;

	secu = tube;
	while (tube)
	{
		if (env->move > nb_of_rooms(env) * 2)
			ft_error(env, 2);
		if (tube->adress->room_end)
			env->get_end = 1;
		else if (tube && tube->adress && tube->adress->tube)
			tube = end_exist_in_tube(tube);
		else
			break ;
		if (!check_if_exist(tmp, tube))
		{
			if (tube->adress->room_end)
				env->get_end = 1;
			if (!tube->adress)
				break ;
			if (!env->get_end && tube->adress)
			{
				env->move++;
				env = ft_recursive_tube(tube->adress->tube, env, push_tube(tmp, tube->adress));
			}
			if (env->get_end == 1)
			{
				env->path = push_tube(env->path, tube->adress);
				break ;
			}
		}
		tube = tube->next;
		env->move++;
		if (secu == tube)
			break ;
	}
	return (env);
}
