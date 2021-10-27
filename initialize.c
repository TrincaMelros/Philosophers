/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 22:20:48 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/27 19:20:33 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

/*
**					# Var Attribution #
**
**		Fills up the main t_env struct with the main arguments, as well as
**		initializing some of its variables.
*/

void	var_attribution(t_env *args, int argc, char **argv)
{
	int	i;

	args->num_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->num_times_to_eat = ft_atoi(argv[5]);
	else
		args->num_times_to_eat = -1;
	args->deaths = 0;
	pthread_mutex_init(&(args->message_lock), NULL);
	i = -1;
	while (++i < args->num_of_philo)
		args->fork_lock[i] = 0;

}

/*
**					# Init Philo #
**
**		Iterates number_of_philo times and fills up the structs t_philo.
**		Each of the structs represents one philosopher. It assigns a number
**		i + 1 to each of them, so the first philosopher is 1 instead of 0.
**		It then links each struct back to the main t_env struct to have an
**		easier time accessing variables inside the threads. Finally, it
**		initializes the mutexes(forks) and assigns left and right fork
**		pointers to each philosopher for easier access.
*/

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

/*
**					# Init Threads #
**
**		Iterates num_of_philo times and initializes the threads. It passes each
**		thread the corresponding t_philo struct. It also initializes the
**		start_time variable, to keep the time the programs started running.
*/

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

/*
**					# Destroy #
**
**		Joins the threads as they finish and destroy the mutexes that have
**		been allocated.
*/

void	destroy_threads_mutex(t_env *args)
{
	int	i;
	int	num;

	num = args->num_of_philo;
	i = -1;
	while (++i < num)
	{
		pthread_join(args->philo[i].th, NULL);
		pthread_mutex_destroy(&(args->fork[i]));
	}
	pthread_mutex_destroy(&(args->message_lock));
}
