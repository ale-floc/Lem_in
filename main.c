#include "lem_in.h"

t_env	*check_command(t_env *env, char *line)
{
	char *tmp;

	tmp = NULL;
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

int 	space_room(t_env *env, char *line)
{
	int i;
	int space;

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

t_tube	*push_tube(t_tube *tube, t_list *list)
{
	t_tube *tmp;

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

t_list	*init_one_list(char *str, int x, int y, t_env *env)
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
	int     str1;
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

int 	check_if_exist(t_tube *tube1, t_tube *tube2)
{
	while (tube1)
	{
		if (tube1->adress == tube2->adress)
			return (1);
		tube1 = tube1->next;
	}
	return (0);
}


int 	check_if_exist_in_tube(t_tube *tube1, t_list *tube2)
{
	while (tube1)
	{
		if (tube1->adress == tube2)
			return (1);
		tube1 = tube1->next;
	}
	return (0);
}

int 	is_strnb(t_env *env, char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i])
	{
		if (!ft_isdigit(str1[i]))
			ft_error(env, 4);
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (!ft_isdigit(str2[i]))
			ft_error(env, 4);
		i++;
	}
	return (1);
}

t_tube	*list_push_tube(t_list *list, t_list *second)
{
	t_tube *tmp;

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

int 	ft_recursive_possible(t_list *start, t_env *env)
{
	t_list *list;
	t_tube *tmp;

	tmp = NULL;
	tmp = push_tube(tmp, start);
	list = env->begin;
	ft_recursive_tube(start->tube, env, tmp);
	if (!env->get_end || !env->path)
		ft_error(env, 2);
	env->path = parse_list(env);
	return (0);
}

t_file	*push_fd(t_file *file, char *str)
{
	t_file *tmp;

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

void	lem_in_begin(t_env *env)
{
	t_list	*start;
	t_list	*end;
	int i;

	i = 0;
	start = env->begin;
	end = env->begin;
	while (start)
	{
		if (start->room_start)
			break;
		start = start->next;
	}
	while (end)
	{
		if (end->room_end)
			break;
		end = end->next;
	}
	ft_recursive_possible(start, env);
}

void	move_ants(t_env *env, int nb_ants)
{
	t_list *start;
	t_list *end;
	t_tube *list;
	int move = 0;

	start = get_start(env);
	start->ants = env->nb_ants;
	end = get_end(env);
	printf("\n");
	while (end->ants != nb_ants)
	{
		list = get_end_tube(env, end);
		while (42)
		{
			if (list->adress->ants && list->adress != end)
			{
				list->adress->ants--;
				printf("%s-%s ", list->adress->string_ants, list->next->adress->salle);
				if (list->next->adress == end)
					end->ants++;
				else
				{
					list->next->adress->ants++;
					list->next->adress->string_ants = list->adress->string_ants;
				}
			}
			if (list == env->path)
			{
				start->ants--;
				move++;
				if (move <= nb_ants)
				{
					list->adress->ants++;
					list->adress->string_ants = ft_strdup(ft_strjoin("L", ft_itoa(move)));
					printf("%s-%s ", list->adress->string_ants, list->adress->salle);
				}
				break;
			}
			list = list->prev;
		}
		printf("\n");
	}
}

void	free_final(t_env *env, t_file *file)
{
	while (file)
	{
		free(file->str);
		free(file);
		file = file->next;
	}
	while (env->begin)
	{
		free(env->begin->salle);
		free(env->begin);
		env->begin = env->begin->next;
	}
}

char	*line_parse(t_env *env, char *line)
{
	char *tmp;

	tmp = NULL;
	if (ft_space(line[0]))
		ft_error(env, 1);
	tmp = ft_strtrim(line);
	free(line);
	return (tmp);
}

int 	main(int argc, char **argv)
{
	char *line;
	t_env *env;
	t_file *file;

	(void)argc;
	env = lem_init();
	file = NULL;
	if (argv[1])
		check_arg(env, ft_strtrim(argv[1]));
	while (get_next_line(0, &line))
	{
		line = line_parse(env, line);
		if (env->nb_ants == -1 && ft_isdigit(line[0]))
			env->nb_ants = parse_get_ants(env, line);
		else if ('#' == line[0])
			env = parse_diese(env, line);
		else if (parse_check(env, line))
			env = check_room_or_tube(env, line);
		else
			ft_error(env, 1);
		file = push_fd(file, line);
	}
	if (!file || !env->start || !env->end || !env->tube)
		ft_error(env, 1);
	lem_in_begin(env);
	if (env->get_end)
	{
		while (file)
		{
			ft_putendl(file->str);
			free(file->str);
			free(file);
			file = file->next;
		}
		move_ants(env, env->nb_ants);
	}
	else
		ft_error(env, 1);
	free_final(env, file);
	return (0);
}
