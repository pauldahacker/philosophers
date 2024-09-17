/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:36:46 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/24 14:36:49 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	else if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			n = 10 * n + str[i] - '0';
		else
			return (-1);
		i++;
	}
	return (n);
}

t_info	info_init(int ac, char **av)
{
	t_info	info;

	info.n_philo = ft_atoi(av[1]);
	info.die = ft_atoi(av[2]);
	info.eat = ft_atoi(av[3]) * 1000;
	info.sleep = ft_atoi(av[4]) * 1000;
	if (ac > 5)
		info.max_meals = ft_atoi(av[5]);
	else
		info.max_meals = 0;
	info.t0 = get_time(0);
	pthread_mutex_init(&info.write_mutex, NULL);
	pthread_mutex_init(&info.death_mutex, NULL);
	info.th = malloc(info.n_philo * sizeof(pthread_t));
	if (!info.th)
	{
		info.th = NULL;
		return (info);
	}
	info.death_flg = -1;
	return (info);
}

int	check_arg(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (printf("4(5) arguments needed\n"));
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			return (printf("Invalid arguments\n"));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_params	params;
	pthread_t	ctrl;
	t_info		info;

	if (check_arg(ac, av))
		return (1);
	info = info_init(ac, av);
	if (!info.th)
		return (printf("<malloc error>\n"));
	params.info = &info;
	params.table = NULL;
	if (set_table(&params.table, params.info))
	{
		start_threads(params.table, &params);
		pthread_create(&ctrl, NULL, monitor, &params);
		pthread_join(ctrl, NULL);
		free_table(params.table);
	}
	free(info.th);
	pthread_mutex_destroy(&params.info->write_mutex);
	pthread_mutex_destroy(&params.info->death_mutex);
	return (0);
}
