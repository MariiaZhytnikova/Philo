/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:51:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/08 13:50:35 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	long_dream(t_philo *philo, int action)
{
	int	sleep_time;
	int	rest;

	if (philo->data->time_die >= 60)
		sleep_time = philo->data->time_die / 10;
	else
		sleep_time = philo->data->time_die;
	if (action == 0)
		rest = philo->data->time_eat;
	else
		rest = philo->data->time_sleep;
	while (checker(philo->data) && rest > 0)
	{
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
