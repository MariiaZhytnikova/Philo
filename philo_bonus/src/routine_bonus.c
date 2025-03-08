/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/07 19:01:32 by mzhitnik         ###   ########.fr       */
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
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
}

static void	have_meal(t_philo *philo)
{
	take_forks(philo);
	write_msg("is eating\n", philo);
	sem_wait(philo->data->dead_lock);
	philo->time_last_meal = get_current_time();
	philo->meals_eaten++;
	sem_post(philo->data->dead_lock);
	long_dream(philo, 0);
	philo->is_fool = 1;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	one_meal(t_philo *philo)
{
	write_msg("is thinking\n", philo);
	take_forks(philo);
	ft_usleep(philo->data->time_die);
	exit(1);
}

void	routine(t_philo *philo)
{
	if (philo->data->meals_num == 0)
		one_meal(philo);
	if (pthread_create(&philo->data->observer, NULL, monitoring, philo) != 0)
		return (error_msg("Observer thread creation failed\n"));
	pthread_detach(philo->data->observer);
	if (!(philo->id % 2))
		ft_usleep(50);
	while (1)
	{
		if (philo->is_fool == 0)
			have_meal(philo);
		if (philo->is_fool == 1)
		{
			write_msg("is sleeping\n", philo);
			long_dream(philo, 1);
			philo->is_fool = 0;
			write_msg("is thinking\n", philo);
		}
	}
}
