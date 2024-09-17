/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:32:51 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/27 15:39:22 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	if (get_val((long *)&philo->info->death_flg, &philo->info->death_mutex) < 0)
	{
		set_val((long *)&philo->info->death_flg,
			&philo->info->death_mutex, philo->num);
		usleep(100);
		printf("%ld %d died\n", get_time(philo->info->t0), philo->num);
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->info->write_mutex));
	if (get_val((long *)&philo->info->death_flg, &philo->info->death_mutex) < 0)
		printf("%ld %d %s\n", get_time(philo->info->t0), philo->num, msg);
	pthread_mutex_unlock(&(philo->info->write_mutex));
	return ;
}

void	take_fork(pthread_mutex_t *fork, t_philo *philo)
{
	if ((get_time(philo->info->t0) - get_val(&philo->l_meal,
				&philo->l_meal_mutex)) >= philo->info->die)
	{
		die(philo);
		return ;
	}
	pthread_mutex_lock(fork);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	set_val(&philo->l_meal, &philo->l_meal_mutex,
		get_time(philo->info->t0));
	print_action(philo, "is eating");
	set_val((long *)&philo->n_meal, &philo->n_meal_mutex,
		get_val((long *)&philo->n_meal, &philo->n_meal_mutex) + 1);
	usleep(philo->info->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	print_action(philo, "is sleeping");
	usleep(philo->info->sleep);
	print_action(philo, "is thinking");
}
