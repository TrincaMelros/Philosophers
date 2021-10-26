/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/26 13:01:32 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	death(t_philo *ph)
{
	printf("[%ld]: %d died\n", \
			(get_time(ph->time) - ph->back->start_time), ph->nbr);
	exit(0);
}

void	thinking(t_philo *ph)
{
	if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
			exit(0);

}

void	pick_forks(t_philo *ph)
{
	if (ph->nbr != ph->back->num_of_philo)
	{
		while (fork_lock[ph->nbr - 1] && fork_lock[ph->nbr])
			if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
				/* DIEEEEE */;
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		fork_lock[ph->nbr - 1] = 1;
		fork_lock[ph->nbr] = 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
	else
	{
		while (fork_lock[ph->nbr] && fork_lock[0])
			if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
				/* DIEEEEE */;
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		fork_lock[ph->nbr - 1] = 1;
		fork_lock[0] = 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
	message(ph, TAKEN_FORK, get_time(ph->time);
}

void	eating(t_philo *ph)
{
/*
	pthread_mutex_lock(ph->left_fork);
	printf("[%ld]: Philo %d has taken a fork\n", \
			(get_time(ph->time) - ph->back->start_time), ph->nbr);
	pthread_mutex_lock(ph->right_fork);
	printf("[%ld]: Philo %d has taken a fork\n", \
	(get_time(ph->time) - ph->back->start_time), ph->nbr);
*/
	pick_forks(ph);
	ph->last_ate = get_time(ph->time);
	printf("[%ld]: Philo %d is eating\n", \
			(get_time(ph->time) - ph->back->start_time), ph->nbr);
	while (get_time(ph->time) - ph->last_ate < ph->back->time_to_eat)
		if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
			exit(0);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void*	routine(void* arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!ph->back->deaths)
	{
		if (ph->nbr % 2)
			usleep(ph->back->time_to_eat * 1000);
		eating(ph);
		printf("[%ld]: Philo %d has started sleeping\n", \
				(get_time(ph->time) - ph->back->start_time), ph->nbr);
		while (get_time(ph->time) - (ph->last_ate + ph->back->time_to_eat) \
				< ph->back->time_to_sleep)
			if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
				return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env	*args;
	
	if (argc < 5 || argc > 6)
		return (1);
	args = malloc(sizeof(t_env));
	var_attribution(args, argc, argv);
	init_philo(args);
	init_threads(args);
	destroy_threads_mutex(args);
	free(args);
	return (0);
}
