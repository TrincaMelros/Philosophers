/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:20:21 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/29 12:21:24 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32)))
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	number = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		number *= 10;
		number += nptr[i] - '0';
		i++;
	}
	return (number * sign);
}

long int	get_time(struct timeval t)
{
	long int f;

	gettimeofday(&t, NULL);
	f = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (f);
}

void	is_dead(t_philo *ph)
{
	if((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
	{
		pthread_mutex_lock(&ph->back->death);
		ph->back->deaths = 1;
		message(ph, DIED, get_time(ph->time));
		pthread_mutex_unlock(&ph->back->death);
	}
}

int	all_philos_ate(t_env *args)
{
	int i;

	i = -1;
	while (++i < args->num_of_philo)
		if (args->philo[i].times_ate != args->num_times_to_eat)
			return (0);
	return (1);
}
