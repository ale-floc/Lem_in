#include "lem_in.h"

void	ft_error(void)
{
	ft_putendl_fd("ERROR", 2);
	exit(2);
}

t_env	*lem_init()
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
	return (env);
}

int		parse_get_ants(char *line)
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
				if (ants == 0)
					ft_error();
				else
					break;
			}
			else
				ft_error();
		}
	}
	return (ants);
}

t_env	*check_command(t_env *env, char *line)
{
	line = ft_strtrim(line);
	if (!ft_strcmp("##start", line))
	{
		if (env->start == 0)
		{
			env->start = 1;
			env->prepare_start = 1;
		}
		else
			ft_error();
		printf("[START]");
	}
	else if (!ft_strcmp("##end", line))
	{
		if (env->end == 0)
		{
			env->end = 1;
			env->prepare_end = 1;
		}
		else
			ft_error();
		printf("[END]");
	}
	else
		printf("[COMMENTAIRE]");
	return (env);
}

t_env	*parse_diese(t_env *env, char *line)
{
	int o;

	o = 0;
	if (line[o] == '#' && line[o + 1] == '#')
		check_command(env, line);
	else
		printf("[COMMENTAIRE]");
	return (env);
}

int 	space_room(char *line)
{
	int i;
	int space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			space++;
		i++;
	}
	if (space == 2)
		return (1);
	else if (space != 0 && space != 2)
		ft_error();
	return (0);
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
	if (env->prepare_start && env->prepare_end)
		ft_error();
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

int 	is_strnb(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i])
	{
		if (!ft_isdigit(str1[i]))
			ft_error();
		i++;
	}
	i = 0;
	while (str2[i])
	{
		if (!ft_isdigit(str2[i]))
			ft_error();
		i++;
	}
	return (1);
}

t_list	*parse_room(t_env *env, char *line)
{
	t_list *list;
	char **tmp;

	list = env->begin;
	tmp = ft_strsplit(line, ' ');
	if (is_strnb(tmp[1], tmp[2]))
		list = ft_listpush(tmp, list, env);
	return (list);
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

t_env	*check_tube(t_env *env, char *line)
{
	t_list *list;
	t_list *second;
	t_tube *tube;
	int pass;

	list = env->begin;
	pass = 0;
	while (list)
	{
		second = env->begin;
		while (second)
		{
			if (!ft_strcmp(line, ft_strjoin(list->salle, ft_strjoin("-", second->salle))))
			{
				list->tube = list_push_tube(list, second);
				tube = list->tube;
				while(tube)
				{
					tube = tube->next;
				}
				pass = 1;
			}
			second = second->next;
		}
		list = list->next;
	}
	if (pass)
		printf("[MATCH TUBE]");
	else
		ft_error();

	return (env);
}

t_env	*check_room_or_tube(t_env *env, char *line)
{
	int o;

	o = 0;
	if (space_room(line))
	{
		printf("[ROOM]");
		env->begin = parse_room(env, line);
		if (env->prepare_start)
			env->prepare_start = 0;
		if (env->prepare_end)
			env->prepare_end = 0;
	}
	else if (!space_room(line) && ft_strstr(line, "-"))
	{
		if (!env->prepare_end && !env->prepare_start &&
			env->start && env->end)
		{
			check_tube(env, line);
			env->tube = 1;
		}
		else
			ft_error();
	}
	return (env);
}

int 	parse_check(t_env *env, char *line)
{
	if (env->nb_ants != -1)
	{
		if (line[0] == 'L')
			ft_error();
		else if (space_room(line))
			return (1);
		else if (!space_room(line) && ft_strstr(line, "-") && 
			env->start && env->end)
			return (1);
	}
	return (0);
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

t_tube	*push_tube(t_tube *tube, t_list *list)
{
	t_tube *tmp;

	tmp = tube;
	if (tube == NULL)
	{
		tube = (t_tube *)malloc(sizeof(t_tube));
		tube->adress = list;
		tube->next = NULL;
		return (tube);
	}
	else
	{
		tmp = (t_tube *)malloc(sizeof(t_tube));
		tmp->adress = list;
		tmp->next = tube;
	}
	return (tmp);
}

void	print_tmp(t_tube *tmp)
{
	while (tmp)
	{
		printf("{{{{%s}}}}\n", tmp->adress->salle);
		tmp = tmp->next;
	}
}

t_env 	*ft_recursive_tube(t_tube *tube, t_env *env, t_tube *tmp, t_tube *save)
{
	while (tube)
	{
		if (!check_if_exist(tmp, tube))
		{
			if (tube->adress->room_end)
				env->get_end = 1;
			if (!env->get_end)
				env = ft_recursive_tube(tube->adress->tube, env, push_tube(tmp, tube->adress), save);
			if (env->get_end == 1)
			{
				env->path = push_tube(env->path, tube->adress);
				break;
			}
		}
		tube = tube->next;
	}
	return (env);
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

int 	ft_recursive_possible(t_list *start, t_env *env)
{
	t_list *list;
	t_tube *tmp;
	t_tube *save;

	tmp = NULL;
	save = NULL;
	tmp = push_tube(tmp, start);
	list = env->begin;
	ft_recursive_tube(start->tube, env, tmp, save);
	env->path = parse_list(env);
	push_tube(env->path, start);
	print_tmp(env->path);
	return (0);
}

t_file	*push_fd(t_file *file, char *str)
{
	t_file *tmp;

	tmp = file;
	if (file == NULL)
	{
		file = (t_file *)malloc(sizeof(t_file));
		file->str = str;
		file->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_file *)malloc(sizeof(t_file));
		tmp->next->str = str;
		tmp->next->next = NULL;
	}
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
	printf("{%s}\n", start->salle);
	printf("{%s}\n", end->salle);

}

t_list	*get_start(t_env *env)
{
	t_list *tmp;

	tmp = env->begin;
	while (tmp)
	{
		if (tmp->room_start)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}

t_list	*get_end(t_env *env)
{
	t_list *tmp;

	tmp = env->begin;
	while (tmp)
	{
		if (tmp->room_end)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_ants_move(t_env *env)
{
	t_tube *tube;
	t_list *start;
	t_list *end;
	t_tube *tmp;

	tube = env->path;
	start = get_start(env);
	end = get_end(env);
	while (end->ants != env->nb_ants)
	{
		while (end != start)
		{
			
		}
		printf("%s\n", tube->adress->salle);
		tube = tube->next;
	}
}

int 	main()
{
	char *line;
	t_env *env;
	t_file *file;

	env = lem_init();
	file = NULL;
	while (get_next_line(0, &line))
	{
		line = ft_strtrim(line);
		if (env->nb_ants == -1 && ft_isdigit(line[0]))
			env->nb_ants = parse_get_ants(line);
		else if ('#' == line[0])
			env = parse_diese(env, line);
		else if (parse_check(env, line))
			env = check_room_or_tube(env, line);
		else
			ft_error();
		file = push_fd(file, line);
		printf("%s\n", line);
	}
	if (!file || !env->start || !env->end || !env->tube)
		ft_error();
	printf("\n");
	lem_in_begin(env);
	if (env->get_end)
	{
		while (file)
		{
			printf("%s\n", file->str);
			file = file->next;
		}
		ft_ants_move(env);
	}
	else
		ft_error();
	return (0);
}