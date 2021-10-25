/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/25 12:22:00 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int mails = 0;



void*	routine(void* arg)
{
	t_philo	*ph;
	int i;

	ph = (t_philo *)arg;
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&ph->envi->fork[0]);
		mails++;
		pthread_mutex_unlock(&ph->envi->fork[0]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env	*args;
	
	if (argc < 5 || argc > 6)
		return (1);
	args = malloc(sizeof(t_env));
	var_attribution(args, argc, argv);
	init_philo_forks(args);
	destroy_threads_mutex(args);
	printf("mails: %d\nstart_time: %ld\n", mails, args->start_time);
	free(args);
	return (0);
}
