/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:20:48 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/29 16:21:43 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	var_attribution(t_env *args, int argc, char **argv)
{
	int	i;

	args->num_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->num_times_to_eat = ft_atoi(argv[5]);
		args->last_arg = 1;
	}
	else
	{
		args->num_times_to_eat = 0;
		args->last_arg = 0;
	}
	args->deaths = 0;
	args->death_print = 0;
	pthread_mutex_init(&(args->message_lock), NULL);
	pthread_mutex_init(&(args->death), NULL);
	i = -1;
	while (++i < args->num_of_philo)
		args->fork_lock[i] = 0;
}

void	init_philo(t_env *args)
{
	int			i;

	i = -1;
	while (++i < args->num_of_philo)
	{
		args->philo[i].nbr = i + 1;
		args->philo[i].last_ate = 0;
		args->philo[i].times_ate = 0;
		args->philo[i].back = args;
		pthread_mutex_init(&(args->fork[i]), NULL);
		args->philo[i].left_fork = &(args->fork[i]);
		args->philo[i].l_f = i;
		if (i == (args->num_of_philo - 1))
		{
			args->philo[i].right_fork = &(args->fork[0]);
			args->philo[i].r_f = 0;
		}
		else
		{
			args->philo[i].right_fork = &(args->fork[i + 1]);
			args->philo[i].r_f = i + 1;
		}
	}
}

void	init_threads(t_env *args)
{
	int	i;

	args->start_time = get_time(args->start);
	i = -1;
	while (++i < args->num_of_philo)
	{
		pthread_create(&(args->philo[i].th), NULL, &routine, \
				(void *)&(args->philo[i]));
	}
}

void	wait_threads(t_env *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philo)
		pthread_join(args->philo[i].th, NULL);
}

void	garbage_collector(t_env *args)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philo)
		pthread_mutex_destroy(&(args->fork[i]));
	pthread_mutex_destroy(&(args->message_lock));
	pthread_mutex_destroy(&(args->death));
}
