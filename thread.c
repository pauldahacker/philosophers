/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:37:55 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/27 15:38:49 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_val(long int *val, pthread_mutex_t *lock)
{
	int	res;

	pthread_mutex_lock(lock);
	res = *val;
	pthread_mutex_unlock(lock);
	return (res);
}

void	set_val(long int *val, pthread_mutex_t *lock, int new_val)
{
	pthread_mutex_lock(lock);
	*val = new_val;
	pthread_mutex_unlock(lock);
	return ;
}

long int	get_time(long int t0)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - t0);
}

void	start_threads(t_philo *table, t_params *params)
{
	t_philo	*philo;
	int		i;
	int		j;

	philo = table;
	i = 0;
	j = 1;
	while (i < params->info->n_philo)
	{
		pthread_create(&(params->info->th[i]), NULL, philosopher, philo);
		philo = philo->right->right;
		i += 2;
		usleep(100);
	}
	philo = table->right;
	while (j < params->info->n_philo)
	{
		pthread_create(&(params->info->th[j]), NULL, philosopher, philo);
		philo = philo->right->right;
		j += 2;
		usleep(100);
	}
}

void	close_threads(t_info info)
{
	int	i;

	i = 0;
	while (i < info.n_philo)
	{
		pthread_join(info.th[i], NULL);
		i++;
	}
	return ;
}
