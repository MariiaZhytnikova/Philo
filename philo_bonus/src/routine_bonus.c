/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/23 09:51:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_msg(char *msg, t_philo *philo)
{
	size_t	from_start;

	sem_wait(philo->data->dead_lock);
	from_start = get_current_time() - philo->data->ps_start;
	printf("%zu %d %s", from_start, philo->id, msg);
	sem_post(philo->data->dead_lock);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->fifo);
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
	sem_post(philo->data->fifo);
}

static void	have_meal(t_philo *philo)
{
	take_forks(philo);
	write_msg("is eating\n", philo);
	sem_wait(philo->data->dead_lock);
	philo->time_last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->data->dead_lock);
	ft_usleep(philo->data->time_eat);
	philo->is_fool = 1;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	routine(t_philo *philo)
{
	if (philo->data->ph_num == 1 || philo->data->meals_num == 0)
	{
		write_msg("is thinking\n", philo);
		ft_usleep(philo->data->time_die * 2);
	}
	while (1)
	{
		if (philo->is_fool == 0)
			have_meal(philo);
		if (philo->is_fool == 1)
		{
			write_msg("is sleeping\n", philo);
			ft_usleep(philo->data->time_sleep);
			philo->is_fool = 0;
			write_msg("is thinking\n", philo);
		}
	}
}

void	*monitoring(void *param)
{
	t_philo	*philo;
	size_t	elapse;

	philo = (t_philo *)param;
	while (1)
	{
		sem_wait(philo->data->dead_lock);
		elapse = get_current_time() - philo->time_last_meal;
		if (elapse > philo->data->time_die)
		{
			rip(philo);
			return (NULL);
		}
		if (philo->data->meals_num > 0 && !meals_eaten(philo))
		{
			sem_post(philo->data->done);
			return (NULL);
		}
		sem_post(philo->data->dead_lock);
		ft_usleep (5);
	}
	return (NULL);
}
