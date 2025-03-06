/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/06 10:36:51 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_msg(char *msg, t_philo *philo)
{
	size_t	from_start;

	pthread_mutex_lock(&philo->data->print_lock);
	if (checker(philo->data))
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

static void	have_meal(t_philo *philo)
{
	take_forks(philo);
	if (checker(philo->data))
	{
		write_msg("is eating\n", philo);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->time_last_meal = get_current_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->dead_lock);
		philo->is_fool = true;
		long_dream(philo, 0);
	}
	release_forks(philo);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->data->meals_num == 0)
	{
		{
			write_msg("is thinking\n", philo);
			return (ft_usleep(philo->data->time_die), NULL);
		}
	}
	if (philo->id % 2)
		ft_usleep(10);
	while (checker(philo->data))
	{
		if (philo->is_fool == false && checker(philo->data))
			have_meal(philo);
		if (philo->is_fool == true && checker(philo->data))
		{
			write_msg("is sleeping\n", philo);
			long_dream(philo, 1);
			philo->is_fool = false;
			write_msg("is thinking\n", philo);
		}
	}
	return (NULL);
}
