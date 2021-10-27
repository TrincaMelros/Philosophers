/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:07:35 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/27 13:44:07 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"
/*
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
		ph->back->fork_lock[ph->nbr - 1] = 0;
		ph->back->fork_lock[ph->nbr] = 0;
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
	}
}

void	pickup_forks(t_philo *ph)
{
	if (ph->back->fork_lock[ph->nbr] == 0 && ph->back->fork_lock[ph->nbr - 1] == 0)
		fork_locking(ph, LOCK);
	else
	{
		while (ph->back->fork_lock[ph->nbr - 1] || ph->back->fork_lock[ph->nbr])
			if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
				kill(ph, get_time(ph->time));
		fork_locking(ph, LOCK);
	}
}

void	pickup_forks_last(t_philo *ph)
{
	if (ph->back->fork_lock[ph->nbr] == 0 && ph->back->fork_lock[ph->nbr - 1] == 0)
		fork_locking(ph, LOCK);
	else
	{
		while (ph->back->fork_lock[ph->nbr - 1] || ph->back->fork_lock[0])
			if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
				kill(ph, get_time(ph->time));
		fork_locking_last(ph, LOCK);
	}
}
*/

void	drop_forks(t_philo *ph)
{
	if (ph->back->fork_lock[ph->l_f] == 0 && ph->back->fork_lock[ph->r_f] == 0)
		pick_forks(ph);
	else
	{
		if (ph->back->fork_lock[ph->l_f] == 1)
		{
			pthread_mutex_lock(ph->left_fork);
			ph->back->fork_lock[ph->l_f] = 0;
			pthread_mutex_unlock(ph->left_fork);
		}
		if (ph->back->fork_lock[ph->r_f] == 1)
		{
			pthread_mutex_lock(ph->left_fork);
			ph->back->fork_lock[ph->l_f] = 0;
			pthread_mutex_unlock(ph->left_fork);
		}
	}
	message(ph, TAKEN_FORK, get_time(ph->time));
	message(ph, TAKEN_FORK, get_time(ph->time));
}

void	pick_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	if (ph->back->fork_lock[ph->l_f] == 0)
		ph->back->fork_lock[ph->l_f] = 1;
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	if (ph->back->fork_lock[ph->r_f] == 0)
		ph->back->fork_lock[ph->r_f] = 1;
	pthread_mutex_unlock(ph->right_fork);
	if (!(ph->back->fork_lock[ph->l_f] == 1 && ph->back->fork_lock[ph->r_f] == 1))
		drop_forks(ph);
}

void	eating(t_philo *ph)
{
	message(ph, TAKEN_FORK, get_time(ph->time));
	message(ph, TAKEN_FORK, get_time(ph->time));
	ph->last_ate = get_time(ph->time);
	message(ph, EATING, get_time(ph->time));
	while (get_time(ph->time) - ph->last_ate < ph->back->time_to_eat)
		if ((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
			kill(ph, get_time(ph->time));
	drop_forks(ph);
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
