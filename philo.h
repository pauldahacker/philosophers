/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:40:09 by pde-masc          #+#    #+#             */
/*   Updated: 2024/07/24 14:40:11 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_info
{
	int				die;
	int				eat;
	int				sleep;
	int				n_philo;
	int				max_meals;
	long int		t0;
	pthread_t		*th;
	int				death_flg;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_mutex;
}	t_info;

typedef struct s_philo
{
	t_info				*info;
	int					num;
	pthread_mutex_t		fork;
	long int			l_meal;
	int					n_meal;
	pthread_mutex_t		l_meal_mutex;
	pthread_mutex_t		n_meal_mutex;
	struct s_philo		*right;
}	t_philo;

typedef struct s_params
{
	t_info		*info;
	t_philo		*table;
}	t_params;

// Table functions
int			set_table(t_philo **table, t_info *info);
void		free_table(t_philo *table);
// Thread functions
void		start_threads(t_philo *philo, t_params *params);
void		close_threads(t_info info);
void		*philosopher(void	*void_philo);
void		*monitor(void	*void_params);
//GET/SET
int			get_val(long int *val, pthread_mutex_t *lock);
void		set_val(long int *val, pthread_mutex_t *lock, int new_val);
//PHILO
void		print_action(t_philo *philo, char *msg);
void		take_fork(pthread_mutex_t *fork, t_philo *philo);
void		eat(t_philo *philo);
void		die(t_philo *philo);
//TIME
long int	get_time(long int t0);
//UTILS
int			ft_atoi(const char *str);

#endif
