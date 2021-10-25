/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:06:48 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/26 00:06:23 by malmeida         ###   ########.fr       */
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
	int				nbr;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_t		th;
	struct s_env	*back;
	struct timeval	time;
}				t_philo;

typedef struct s_env {
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	int				deaths;

	struct timeval	start;
	long int		start_time;
	
	t_philo			philo[200];
	pthread_mutex_t	fork[200];
}				t_env;

/*		Initialization and Cleanup	*/
void		var_attribution(t_env *args, int argc, char **argv);
void		init_philo(t_env *args);
void		init_threads(t_env *args);
void		destroy_threads_mutex(t_env *args);

/*		Utils		*/
int			ft_atoi(const char *nptr);
long int	get_time(struct timeval time);

void*		routine(void* arg);

#endif
