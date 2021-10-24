/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:06:48 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/24 13:31:48 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo {
	long int		last_ate;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_t		th;
}				t_philo;

typedef struct s_env {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;

	struct timeval	time;
	long int		start_time;
	
	t_philo			philo[999];
	pthread_mutex_t	fork[999];
}				t_env;


int		ft_atoi(const char *nptr);
void	var_attribution(t_env *args, int argc, char **argv);
void	create_threads_mutex(t_env *args);
void	destroy_threads_mutex(t_env *args);
void*	routine(void* arg);

#endif
