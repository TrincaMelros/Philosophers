/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:07:35 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/29 12:26:57 by malmeida         ###   ########.fr       */
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
	ph->has_leftfork = 0;
	ph->has_rightfork = 0;
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
	is_dead(ph);
}

void	eating(t_philo *ph)
{
	if (!check_death(ph))
	{
		message(ph, TAKEN_FORK, get_time(ph->time));
		message(ph, TAKEN_FORK, get_time(ph->time));
		ph->last_ate = get_time(ph->time) - ph->back->start_time;
		message(ph, EATING, get_time(ph->time));
		while ((get_time(ph->time) - ph->back->start_time) - ph->last_ate < \
				ph->back->time_to_eat);
		drop_forks(ph, BOTH);
		ph->times_ate++;
	}
}

void	sleep_think(t_philo *ph)
{
	long int	started_sleeping;

	started_sleeping = get_time(ph->time);
	message(ph, SLEEPING, started_sleeping);
	while(get_time(ph->time) - started_sleeping < ph->back->time_to_sleep)
		is_dead(ph);
	if(!check_death(ph))
		message(ph, THINKING, get_time(ph->time));
}

void	message(t_philo *ph, int i, long int timer)
{
	long int	og_time;

	og_time = ph->back->start_time;
	pthread_mutex_lock(&ph->back->message_lock);
	if (i == 1)
		printf("[%ld]: %d has taken a fork\n", timer - og_time, ph->nbr);
	else if (i == 2)
		printf("[%ld]: %d is eating\n", timer - og_time, ph->nbr);
	else if (i == 3)
		printf("[%ld]: %d is sleeping\n", timer - og_time, ph->nbr);
	else if (i == 4)
		printf("[%ld]: %d is thinking\n", timer - og_time, ph->nbr);
	else if (i == 5)
		if (ph->back->death_print == 0)
		{
			printf("[%ld]: %d died\n", timer - og_time, ph->nbr);
			ph->back->death_print++;
		}
	pthread_mutex_unlock(&ph->back->message_lock);
}
