/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/28 17:45:56 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	check_death(t_philo *ph)
{
	int d;

	d = 0;
	pthread_mutex_lock(&ph->back->death);
	if (ph->back->deaths == 1)
		d = 1;
	pthread_mutex_unlock(&ph->back->death);
	return (d);
}

void*	routine(void* arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (!check_death(ph))
	{
		while (!(ph->has_leftfork && ph->has_rightfork) && !check_death(ph))
			pick_forks(ph);
		is_dead(ph);
		if (check_death(ph))
			break;
		eating(ph);
		if (check_death(ph))
			break;
		if (ph->back->last_arg && ph->times_ate == ph->back->num_times_to_eat)
			while(!all_philos_ate(ph->back));
		if (check_death(ph) || all_philos_ate(ph->back))
			break;
		sleep_think(ph);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env	*args;
	
	if (arg_validation(argc, argv))
		return (1);
	args = malloc(sizeof(t_env));
	var_attribution(args, argc, argv);
	init_philo(args);
	init_threads(args);
	wait_threads(args);
	garbage_collector(args);
	free(args);
	return (0);
}
