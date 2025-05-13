/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/13 13:56:49 by mzhitnik         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->fork_one->fork_lock);
	write_msg("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->fork_two->fork_lock);
	write_msg("has taken a fork\n", philo);
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
		philo->time_next_meal = philo->time_last_meal
			+ philo->data->time_eat * 2 + 1;
		philo->is_fool = true;
		long_dream(philo, 0);
	}
	pthread_mutex_unlock(&philo->fork_one->fork_lock);
	pthread_mutex_unlock(&philo->fork_two->fork_lock);
}

static int	one(t_philo *philo)
{
	if (philo->data->ph_num == 1 || philo->data->meals_num == 0)
	{
		write_msg("is thinking\n", philo);
		ft_usleep(philo->data->time_die);
		return (1);
	}
	return (-1);
}

void	*routine(void *param)
{
	t_philo	*philo;
	int		delay;

	philo = (t_philo *)param;
	sim_start(philo->data->ps_start);
	if (one(philo) > 0)
		return (NULL);
	if (philo->id % 2 == 1)
		ft_usleep(10);
	while (checker(philo->data))
	{
		delay = philo->time_next_meal - get_current_time();
		if (delay > 0 && philo->id % 2 == 1)
			ft_usleep(1);
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
