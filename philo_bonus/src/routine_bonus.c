/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:46:05 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/05 16:55:07 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_msg(char *msg, t_philo *philo)
{
	size_t	from_start;

	sem_wait(philo->data->print_lock);
	from_start = get_current_time() - philo->data->ps_start;
	printf("%zu %d %s", from_start, philo->id, msg);
	sem_post(philo->data->print_lock);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
	checker(philo);
	sem_wait(philo->data->forks);
	write_msg("has taken a fork\n", philo);
}

void	release_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

static void	have_meal(t_philo *philo)
{
	take_forks(philo);
	write_msg("is eating\n", philo);
	philo->time_last_meal = get_current_time();
	philo->meals_eaten++;
	long_dream(philo, 0);
	philo->is_fool = true;
	release_forks(philo);
}

void	routine(t_philo *philo)
{
	if (philo->data->meals_num == 0)
	{
		{
			write_msg("is thinking\n", philo);
			ft_usleep(philo->data->time_die);
			exit(1);
		}
	}
	if (!(philo->id % 2))
		ft_usleep(50);
	while (1)
	{
		checker(philo);
		if (philo->is_fool == false)
			have_meal(philo);
		checker(philo);
		if (philo->is_fool == true)
		{
			write_msg("is sleeping\n", philo);
			long_dream(philo, 1);
			philo->is_fool = false;
			checker(philo);
			write_msg("is thinking\n", philo);
		}
	}
}
