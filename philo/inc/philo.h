/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:47 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/02/23 18:46:11 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define USAGE "./philo philo_number time_to_die time_to_eat time_to\
_sleep [number_of_meals]"

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
	int				fork_id;
}	t_fork;

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	t_fork			*fork_one;
	t_fork			*fork_two;
	int				meals_eaten;
	size_t			time_last_meal;
	bool			is_fool;
	pthread_mutex_t	philo_lock;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				ph_num;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	int				meals_num;
	size_t			ps_start;
	t_philo			*philos;
	t_fork			*forks;
	bool			is_dead;
	pthread_t		observer;
	pthread_mutex_t	print_lock;
}	t_data;


// Utils
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	word_count(char *str);
void	split_args(char **res, char *args, int k);

//Errors and frees
void	error_msg(char *msg);
void	free_arr(char **arr);


// Parce args
int		parce_args(t_data *data, int argc, char **argv);

// Simulation utls
size_t	get_current_time(void);
int	ft_usleep(size_t milliseconds);

//Threads
void	data_init(t_data *data);
void	write_msg(char *msg, t_philo *philo);
void	*routine(void *param);
void	simulation_start(t_data *data);

#endif
