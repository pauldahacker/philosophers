/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:37:38 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/27 15:43:13 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void	*void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (philo->info->death_flg < 0)
	{
		take_fork(&philo->fork, philo);
		take_fork(&philo->right->fork, philo);
		eat(philo);
	}
	return (NULL);
}

int	meals_ctrl(t_philo *table)
{
	t_philo	*philo_i;
	int		max_meals;
	int		i;

	if (table->info->max_meals)
	{
		philo_i = table;
		max_meals = table->info->max_meals;
		i = 0;
		while (i < table->info->n_philo)
		{
			if (get_val((long *)&philo_i->n_meal,
					&philo_i->n_meal_mutex) < max_meals)
				return (0);
			philo_i = philo_i->right;
			i++;
		}
		pthread_mutex_lock(&philo_i->info->death_mutex);
		philo_i->info->death_flg = 0;
		pthread_mutex_unlock(&philo_i->info->death_mutex);
	}
	else
		return (0);
	return (1);
}

int	hunger_ctrl(t_philo	*table)
{
	t_philo	*philo_i;
	int		dth_time;
	long	t0;
	int		i;

	philo_i = table;
	dth_time = table->info->die;
	t0 = table->info->t0;
	i = 0;
	while (i < table->info->n_philo)
	{
		if ((get_time(t0)
				- get_val(&philo_i->l_meal, &philo_i->l_meal_mutex))
			>= dth_time)
		{
			die(philo_i);
			return (1);
		}
		philo_i = philo_i->right;
		i++;
	}
	return (0);
}

void	*monitor(void	*void_params)
{
	t_params	*params;

	params = (t_params *)void_params;
	while ((get_val((long *)&params->info->death_flg,
				&params->info->death_mutex) < 0)
		&& !meals_ctrl(params->table) && !hunger_ctrl(params->table))
		usleep(10);
	close_threads(*params->info);
	return (NULL);
}
