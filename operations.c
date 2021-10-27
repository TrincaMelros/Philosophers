/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:07:35 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/27 19:20:32 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	drop_forks(t_philo *ph, int i)
{
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	if (i == LEFT || i == BOTH)
		ph->back->fork_lock[ph->l_f] = 0;
	if (i == RIGHT || i == BOTH)
		ph->back->fork_lock[ph->r_f] = 0;
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	pick_forks(t_philo *ph)
{
	ph->has_leftfork = 0;
	ph->has_rightfork = 0;
	pthread_mutex_lock(ph->left_fork);
	if (ph->back->fork_lock[ph->l_f] == 0)
	{
		ph->back->fork_lock[ph->l_f] = 1;
		ph->has_leftfork++;
	}
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	if (ph->back->fork_lock[ph->r_f] == 0)
	{
		ph->back->fork_lock[ph->r_f] = 1;
		ph->has_rightfork++;
	}
	pthread_mutex_unlock(ph->right_fork);
	if (ph->has_rightfork && !ph->has_leftfork)
		drop_forks(ph, RIGHT);
	else if (!ph->has_rightfork && ph->has_leftfork)
		drop_forks(ph, LEFT);
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
	drop_forks(ph, BOTH);
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
