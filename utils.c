/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:20:21 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/25 16:05:24 by malmeida         ###   ########.fr       */
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
	args->deaths = 0;

}

/*
**			# Init Philosophers and Forks #
**
**			Iterates number_of_philo times and assigns 3 things. The
**			connection to the main structure from each philo struct.
**			It initializes the mutexs, represented as the forks. The creation
**			of the threads. And finally assigns right and left fork pointers
**			to each philosopher.
*/

void	init_philo_forks(t_env *args)
{
	int			i;
	int			num;
	
	num = args->num_of_philo;
	args->deaths = 1;
	i = -1;
	while (++i < num)
	{
		args->philo[i].nbr = i + 1;
		args->philo[i].back = args;
		pthread_mutex_init(&(args->fork[i]), NULL);
		args->philo[i].left_fork = &(args->fork[i]);
		if (i == (num - 1))
			args->philo[i].right_fork = &(args->fork[0]);
		else
			args->philo[i].right_fork = &(args->fork[i + 1]);
	}
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
		pthread_mutex_destroy(&(args->fork[i]));
	}
}

long int	get_time(struct timeval time)
{
	long int f;

	gettimeofday(&time, NULL);
	f = time.tv_sec * 1000000 + time.tv_usec;
	return (f);
}
