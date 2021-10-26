/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:07:35 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/26 23:49:54 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	fork_locking_last(t_philo *ph, int i)
{
	if (i == LOCK)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->back->fork_lock[ph->nbr - 1] = 1;
		ph->back->fork_lock[0] = 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		message(ph, TAKEN_FORK, get_time(ph->time));
		message(ph, TAKEN_FORK, get_time(ph->time));
	}
	else if (i == UNLOCK)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->back->fork_lock[ph->nbr - 1] = 0;
		ph->back->fork_lock[0] = 0;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
}

void	fork_locking(t_philo *ph, int i)
{
	if (i == LOCK)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->back->fork_lock[ph->nbr - 1] = 1;
		ph->back->fork_lock[ph->nbr] = 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		message(ph, TAKEN_FORK, get_time(ph->time));
		message(ph, TAKEN_FORK, get_time(ph->time));
	}
	else if (i == UNLOCK)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->back->fork_lock[ph->nbr - 1] = 1;
		ph->back->fork_lock[ph->nbr] = 1;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
}

void	eating(t_philo *ph)
{
	if (ph->nbr == ph->back->num_of_philo)
	{
		while (ph->back->fork_lock[ph->nbr - 1] != 1 && ph->back->fork_lock[0] != 1)
			if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
				kill(ph, get_time(ph->time));
		fork_locking_last(ph, LOCK);
	}
	else
	{
		while (ph->back->fork_lock[ph->nbr - 1] != 1 && ph->back->fork_lock[ph->nbr] != 1)
			if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
			{
				kill(ph, get_time(ph->time));
			}
		fork_locking(ph, LOCK);
	}
	ph->last_ate = get_time(ph->time);
	message(ph, EATING, get_time(ph->time));
	while (get_time(ph->time) - ph->last_ate < ph->back->time_to_eat)
	//WRONG CONDITIONS	if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate < ph->back->time_to_die)
			kill(ph, get_time(ph->time));
	if (ph->nbr == ph->back->num_of_philo)
		fork_locking_last(ph, UNLOCK);
	else
		fork_locking(ph, UNLOCK);
}

void	sleep_think(t_philo *ph)
{
	long int started_sleeping;

	started_sleeping = get_time(ph->time);
	message(ph, SLEEPING, started_sleeping);
	while(get_time(ph->time) - started_sleeping < ph->back->time_to_sleep)
		if (get_time(ph->time) - ph->last_ate > ph->back->time_to_die)
			kill(ph, get_time(ph->time));
	message(ph, THINKING, get_time(ph->time));
}
