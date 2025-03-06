/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:54:47 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/05 16:55:35 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/time.h>
# include <signal.h>

# define USAGE "./philo philo_number time_to_die time_to_eat time_to\
_sleep [number_of_meals]"

typedef struct s_data	t_data;

typedef struct s_philo
{
	pid_t		pid;
	int			id;
	int			meals_eaten;
	size_t		time_last_meal;
	bool		is_fool;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int			ph_num;
	size_t		time_die;
	size_t		time_eat;
	size_t		time_sleep;
	int			meals_num;
	size_t		ps_start;
	t_philo		*philos;
	sem_t		*forks;
	bool		is_dead;
	sem_t		*dead_lock;
	sem_t		*print_lock;
}	t_data;

// Parce args
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	word_count(char *str);
void	split_args(char **res, char *args, int k);
void	error_msg(char *msg);
void	free_arr(char **arr);
int		parce_args(t_data *data, char **argv);

// Simulation utls
void	long_dream(t_philo *philo, int action);
size_t	get_current_time(void);
void	ft_usleep(size_t milliseconds);

//Threads
void	data_init(t_data *data);
void	simulation(t_data *data);

void	checker(t_philo *philo);
void	write_msg(char *msg, t_philo *philo);
void	routine(t_philo *philo);
void	destroy(t_data *data);

#endif
