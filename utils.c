/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:20:21 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/27 19:20:35 by malmeida         ###   ########.fr       */
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
		printf("[%ld]: %d died\n", timer - og_time, ph->nbr);
	pthread_mutex_unlock(&ph->back->message_lock);
}

void	kill(t_philo *ph, long int timer)
{
	ph->back->deaths = 1;
	message(ph, DIED, timer);
	exit(0);
}
