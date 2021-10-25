/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/25 16:05:22 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void*	routine(void* arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	ph->last_ate = get_time(ph->back->time);
	while (ph->back->deaths)
	{
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		usleep(200);
		printf("Philo %d has finished eating\n", ph->nbr);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		usleep(2000000);
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
	free(args);
	return (0);
}
