/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/25 11:54:28 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_msg(char *msg, t_philo *philo)
{
	size_t	from_start;

	pthread_mutex_lock(&philo->data->print_lock);
	if (philo->data->is_dead == false)
	{
		from_start = get_current_time() - philo->data->ps_start;
		printf("%zu %d %s", from_start, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

static void	take_forks(t_philo *philo)
{
	if (philo->fork_one)
	{
		pthread_mutex_lock(&philo->fork_one->fork_lock);
		write_msg("has taken a fork\n", philo);
	}
	if (philo->fork_two)
	{
		pthread_mutex_lock(&philo->fork_two->fork_lock);
		write_msg("has taken a fork\n", philo);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->fork_one)
		pthread_mutex_unlock(&philo->fork_one->fork_lock);
	if (philo->fork_two)
		pthread_mutex_unlock(&philo->fork_two->fork_lock);
}

static void	have_meal(t_philo *philo) // philo->data->meals_num == 0
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->data->is_dead == false)
	{
		write_msg("is eating\n", philo);
		ft_usleep(philo->data->time_eat);
		philo->time_last_meal = get_current_time();
		philo->meals_eaten++;
		philo->is_fool = true;
	}
	pthread_mutex_unlock(&philo->philo_lock);
	release_forks(philo);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->data->ph_num == 1)
	{
		write_msg("is thinking\n", philo);
		ft_usleep(philo->data->time_die);
		write_msg("died\n", philo);
		return (NULL);
	}
	if (!(philo->id % 2))
		ft_usleep(50);
	while (philo->data->is_dead == false)
	{
		write_msg("is thinking\n", philo);
		if (philo->is_fool == false && philo->data->is_dead == false)
			have_meal(philo);
		if (philo->is_fool == true && philo->data->is_dead == false)
		{
			write_msg("is sleeping\n", philo);
			ft_usleep(philo->data->time_sleep);
			philo->is_fool = false;
		}
	}
	return (NULL);
}

/*
1 800 200 200	| one should die					+
4 310 200 100	| one should die					+
5 600 150 150	| no one should die					+
5 800 200 200	| no one should die					+
4 410 200 200 	| no one should die					+
100 800 200 200	| no one should die					+
105 800 200 200	| no one should die					+
200 800 200 200	| no one should die					+
4 800 200 200	| no one should die					+

4 410 200 200 12 |no one should die stop 12 meals	+
5 800 200 200 7	 | no one should die stop 7 meals	+
4 410 200 200 10 |no one should die stop 12 meals	+
4 410 200 200 15 |no one should die stop 12 meals	+
*/