/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:02:58 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/18 18:03:02 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list	*get_end(t_env *env)
{
	t_list	*end;

	end = env->begin;
	while (end)
	{
		if (end->room_end)
			break ;
		end = end->next;
	}
	return (end);
}

t_list	*get_start(t_env *env)
{
	t_list	*start;

	start = env->begin;
	while (start)
	{
		if (start->room_start)
			break ;
		start = start->next;
	}
	return (start);
}

t_tube	*get_end_tube(t_env *env, t_list *end)
{
	t_tube *tube;

	tube = env->path;
	while (tube)
	{
		if (tube->adress != end)
			tube->next->prev->adress = tube->adress;
		if (tube->adress == end)
			break ;
		tube = tube->next;
	}
	return (tube);
}

int		nb_of_rooms(t_env *env)
{
	t_list	*tmp;
	int		nb;

	nb = 0;
	tmp = env->begin;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

t_tube	*search_end(t_tube *tmp)
{
	t_tube *tamp;

	tamp = tmp;
	while (tamp)
	{
		if (tamp->adress->tube && tamp->adress->room_end)
			return (tamp);
		tamp = tamp->next;
	}
	return (NULL);
}
