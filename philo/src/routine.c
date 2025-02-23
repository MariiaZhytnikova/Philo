/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/23 20:07:40 by mzhitnik         ###   ########.fr       */
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
		write_msg(" has taken a fork\n", philo);
	}
	if (philo->fork_two)
	{
		pthread_mutex_lock(&philo->fork_two->fork_lock);
		write_msg(" has taken a fork\n", philo);
	}
}

static void	release_forks(t_philo *philo)
{
	if (philo->fork_one)
	{
		pthread_mutex_unlock(&philo->fork_one->fork_lock);
		write_msg(" has taken a fork\n", philo);
	}
	if (philo->fork_two)
	{
		pthread_mutex_unlock(&philo->fork_two->fork_lock);
		write_msg(" has taken a fork\n", philo);
	}
}

static void	have_meal(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->ph_num == 1 || philo->data->meals_num == 0)
	{
		release_forks(philo);
		ft_usleep(philo->data->time_die);
		return ;
	}
	pthread_mutex_lock(&philo->philo_lock);
	if (philo->data->is_dead == false)
	{
		write_msg(" is eating\n", philo);
		ft_usleep(philo->data->time_eat);
		philo->time_last_meal = get_current_time();
		philo->meals_eaten++;
		philo->is_fool = true;
		release_forks(philo);
	}
	pthread_mutex_unlock(&philo->philo_lock);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	
	while (philo->data->is_dead == false)
	{
		write_msg(" is thinking\n", philo);
		have_meal(philo);
		if (philo->is_fool == true)
		{
			write_msg(" is sleeping\n", philo);
			ft_usleep(philo->data->time_sleep);
			philo->is_fool = false;
		}
	}
	return (NULL);
}
