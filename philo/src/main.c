/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:53:36 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/22 12:37:36 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Avoiding Deadlocks:

//  In the philosophers' problem, a deadlock can occur if every philosopher picks 
// up one fork at the same time and then waits indefinitely for the other fork. To 
// avoid this, you would need to use additional logic, such as ensuring that a 
// philosopher can only pick up both forks (if both are available) or giving up a 
// fork if they can't get both

// Ensure that critical sections (the parts where philosophers pick up and put down 
// forks) are properly synchronized. This means that when a philosopher is eating, 
// no other philosopher can access their forks, and this must be done in a way that 
// prevents race conditions.

// pthread_mutex_t forks[NUM_PHILOSOPHERS];  // Mutexes for forks

// void* philosopher(void* arg) {
//     int philosopher_id = *((int*)arg);
//     while (1) {
//         // Thinking
//         think();

//         // Picking up left and right forks (mutexes)
//         pthread_mutex_lock(&forks[philosopher_id]);  // Lock left fork
//         pthread_mutex_lock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Lock right fork

//         // Eating
//         eat();

//         // Putting down left and right forks
//         pthread_mutex_unlock(&forks[philosopher_id]);  // Unlock left fork
//         pthread_mutex_unlock(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Unlock right fork
//     }
// }

// Compile with the -pthread flag to link the pthread library.

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (parce_args(data, argc, argv))
		return (free(data), 1);
	// printf("number_of_philosophers is                    %d\n", data->ph_num);
	// printf("time_to_die is                               %zu\n", data->time_die);
	// printf("time_to_eat is                               %zu\n", data->time_eat);
	// printf("time_to_sleep is                             %zu\n", data->time_sleep);
	// printf("number_of_times_each_philosopher_must_eat is %d\n", data->meals_num);

	data_init(data);
	simulation_start(data);
	printf("All done!\n");
	//Need to clean up
	free(data);
	return (0);
}
