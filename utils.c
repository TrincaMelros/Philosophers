/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:20:21 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/25 12:22:02 by malmeida         ###   ########.fr       */
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

void	var_attribution(t_env *args, int argc, char **argv)
{
	args->num_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_times_to_eat = ft_atoi(argv[5]);
	else
		args->num_times_to_eat = -1;
	args->start_time = get_time(args->time);

}

void	init_philo_forks(t_env *args)
{
	int			i;
	int			num;

	num = args->num_of_philo;
	i = -1;
	while (++i < num)
		args->philo[i].envi = args;
	i = -1;
	while (++i < num)
		pthread_mutex_init(&(args->fork[i]), NULL);
	i = -1;
	while (++i < num)
	{
		pthread_create(&(args->philo[i].th), NULL, &routine, \
				(void *)&(args->philo[i]));
		printf("Thread %d was created\n", i);
	}
}

void	destroy_threads_mutex(t_env *args)
{
	int	i;
	int	num;

	num = args->num_of_philo;
	i = -1;
	while (++i < num)
	{
		pthread_join(args->philo[i].th, NULL);
		printf("Thread %d has finished\n", i);
	}
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&(args->fork[i]));
}

long int	get_time(struct timeval time)
{
	long int f;

	gettimeofday(&time, NULL);
	f = time.tv_sec * 1000000 + time.tv_usec;
	return (f);
}
