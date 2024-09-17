/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:37:26 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/24 14:37:28 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*set_philo(t_info *info, int i)
{
	t_philo	*philo_i;

	philo_i = malloc(sizeof(t_philo));
	if (!philo_i)
		return (NULL);
	philo_i->num = i;
	philo_i->info = info;
	philo_i->l_meal = 0;
	philo_i->n_meal = 0;
	pthread_mutex_init(&(philo_i->fork), NULL);
	pthread_mutex_init(&(philo_i->l_meal_mutex), NULL);
	pthread_mutex_init(&(philo_i->n_meal_mutex), NULL);
	return (philo_i);
}

static t_philo	*add_philo(t_philo **table, t_info *info, int i)
{
	t_philo	*philo_new;
	t_philo	*philo_i;

	philo_new = set_philo(info, i);
	if (!philo_new)
		return (NULL);
	philo_i = *table;
	if (!(*table))
	{
		philo_new->right = philo_new;
		*table = philo_new;
		return (*table);
	}
	while (philo_i->right != *table)
		philo_i = philo_i->right;
	philo_new->right = *table;
	philo_i->right = philo_new;
	return (*table);
}

int	set_table(t_philo **table, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		if (!add_philo(table, info, i))
		{
			free_table(*table);
			printf("<malloc error>\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_table(t_philo *table)
{
	t_philo	*philo_i;
	t_philo	*philo_free;

	philo_free = table->right;
	philo_i = table->right->right;
	while (philo_free != table)
	{
		pthread_mutex_destroy(&philo_free->fork);
		pthread_mutex_destroy(&philo_free->l_meal_mutex);
		pthread_mutex_destroy(&philo_free->n_meal_mutex);
		free(philo_free);
		philo_free = philo_i;
		philo_i = philo_i->right;
	}
	free(table);
	return ;
}
