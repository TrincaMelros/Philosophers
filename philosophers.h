/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:06:48 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/29 12:39:17 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define TAKEN_FORK 1
# define EATING		2
# define SLEEPING	3
# define THINKING	4
# define DIED		5
# define LEFT		6
# define RIGHT		7
# define BOTH		8
# define NUM_ARGS	9
# define NOT_NUM	10
# define NEG_NUM	11
# define NUM_PHILO	12
# define ONE_PHILO	13

typedef struct s_philo {
	long int		last_ate;
	int				nbr;
	int				times_ate;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				l_f;
	int				r_f;
	int				has_leftfork;
	int				has_rightfork;

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
	int				last_arg;
	int				death_print;

	struct timeval	start;
	long int		start_time;

	t_philo			philo[200];
	int				fork_lock[200];
	pthread_mutex_t	fork[200];
	pthread_mutex_t	message_lock;
	pthread_mutex_t	death;
}				t_env;

/*		Arg Validation		*/
int			is_digit(char **argv, int argc);
int			is_negative(char **argv, int argc);
int			error_message(int f, int time);
int			arg_validation(int argc, char **argv);

/*		Initialization and Cleanup	*/
void		var_attribution(t_env *args, int argc, char **argv);
void		init_philo(t_env *args);
void		init_threads(t_env *args);
void		wait_threads(t_env *args);
void		garbage_collector(t_env *args);

/*		Utils		*/
int			ft_atoi(const char *nptr);
long int	get_time(struct timeval time);
void		is_dead(t_philo *ph);
int			check_death(t_philo *ph);
int			all_philos_ate(t_env *args);

/*		Operations		*/
void		drop_forks(t_philo *ph, int i);
void		pick_forks(t_philo *ph);
void		eating(t_philo *ph);
void		sleep_think(t_philo *ph);
void		message(t_philo *ph, int i, long int timer);

void		*routine(void *arg);

#endif
