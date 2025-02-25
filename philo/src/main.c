/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/25 10:28:28 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msg(char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len] != '\0')
		len++;
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
}

void	destroy(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	while (i < data->ph_num)
	{
		pthread_mutex_destroy(&data->philos[i].philo_lock);
		pthread_mutex_destroy(&data->philos[i].fork_one->fork_lock);
		pthread_mutex_destroy(&data->philos[i].fork_two->fork_lock);
		i++;
	}
	free(data->forks);
	free(data->philos);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (parce_args(data, argv))
		return (free(data), 1);
	data_init(data);
	simulation_start(data);
	destroy(data);
	printf("	¯\\_(ツ)_/¯			\n");
	return (0);
}
/*
	// printf("my data is: %d\n", data->ph_num);
	// printf("my data is: %zu\n", data->time_die);
	// printf("my data is: %zu\n", data->time_eat);
	// printf("my data is: %zu\n", data->time_sleep);
	// printf("my data is: %d\n", data->meals_num);
// Nice project! All the example cases in the eval sheet run well, 
// I couldn't find any problems with helgrind or valgrind. Unfortunately 
// there was a forbidden function, atomic_load that is cool, makes the 
// project nicer, but wasn't sanctioned by the subject. We also noticed 
// that when philosophers are given long times to eat, think and sleep 
// there is a bit of a delay to the end of the simulation, although 
// this wasn't a point in the subject. For cleanup when a thread fails 
// in the middle of the loop the already created threads weren't joined
//  back, creating sort of a leak, we prototyped a quick fix that closes 
//  them. Good luck on the next round!*/