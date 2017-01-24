/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:01:41 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 14:01:44 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tube		*list_push_tube(t_list *list, t_list *second)
{
	t_tube	*tmp;

	tmp = list->tube;
	if (list->tube == NULL)
	{
		list->tube = (t_tube *)malloc(sizeof(t_tube));
		list->tube->adress = second;
		list->tube->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_tube *)malloc(sizeof(t_tube));
		tmp->next->adress = second;
		tmp->next->next = NULL;
	}
	return (list->tube);
}

t_tube		*push_tube(t_tube *tube, t_list *list)
{
	t_tube	*tmp;

	tmp = tube;
	if (tube == NULL)
	{
		tube = (t_tube *)malloc(sizeof(t_tube));
		tube->adress = list;
		tube->next = NULL;
		tube->prev = NULL;
		return (tube);
	}
	else
	{
		tmp = (t_tube *)malloc(sizeof(t_tube));
		tmp->adress = list;
		tube->prev = tmp;
		tmp->next = tube;
	}
	return (tmp);
}

t_list		*init_one_list(char *str, int x, int y, t_env *env)
{
	t_list	*temp;

	temp = (t_list *)malloc(sizeof(t_list));
	temp->next = NULL;
	temp->tube = NULL;
	temp->salle = ft_strdup(str);
	temp->x = x;
	temp->y = y;
	temp->ants = 0;
	temp->string_ants = NULL;
	if (env->prepare_start && env->prepare_end)
		ft_error(env, 1);
	else
	{
		if (env->prepare_start)
			temp->room_start = 1;
		else
			temp->room_start = 0;
		if (env->prepare_end)
			temp->room_end = 1;
		else
			temp->room_end = 0;
	}
	return (temp);
}

t_list		*ft_listpush(char **str, t_list *list, t_env *env)
{
	t_list	*tmp;
	int		str1;
	int		str2;

	tmp = list;
	str1 = ft_atoi(str[1]);
	str2 = ft_atoi(str[2]);
	if (ft_strchr(str[0], '-'))
		ft_error(env, 6);
	if (list == NULL)
	{
		list = init_one_list(str[0], str1, str2, env);
		return (list);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_one_list(str[0], str1, str2, env);
	}
	return (list);
}

t_file		*push_fd(t_file *file, char *str)
{
	t_file	*tmp;

	tmp = file;
	if (file == NULL)
	{
		file = (t_file *)malloc(sizeof(t_file));
		file->str = ft_strdup(str);
		file->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_file *)malloc(sizeof(t_file));
		tmp->next->str = ft_strdup(str);
		tmp->next->next = NULL;
	}
	free(str);
	return (file);
}
