/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:13:11 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/05 16:51:31 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	long_dream(t_philo *philo, int action)
{
	int	sleep_time;
	int	rest;

	sleep_time = 5;
	if (action == 0)
		rest = philo->data->time_eat;
	else
		rest = philo->data->time_sleep;
	while (rest > 0)
	{
		checker(philo);
		ft_usleep(sleep_time);
		rest -= sleep_time;
		if (rest < sleep_time)
			sleep_time = rest;
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_msg("gettimeofday() error");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(200);
}

int	meals_eaten(t_philo *philo)
{
	if (philo->meals_eaten - 1 < philo->data->meals_num)
		return (1);
	return (0);
}

void	checker(t_philo *philo)
{
	size_t	elapse;
	int		i;

	i = 0;
	while (i < philo->data->ph_num)
	{
		sem_wait(philo->data->dead_lock);
		elapse = get_current_time() - philo->time_last_meal;
		if (elapse > philo->data->time_die)
			exit (1);
		if (philo->data->meals_num > 0 && !meals_eaten(philo))
			exit (0);
		sem_post(philo->data->dead_lock);
		i++;
	}
}
