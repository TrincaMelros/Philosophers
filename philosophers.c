/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/27 19:11:05 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	is_dead(t_philo *ph)
{
	if((get_time(ph->time) - ph->back->start_time) - ph->last_ate > ph->back->time_to_die)
		kill(ph, get_time(ph->time));
}

void*	routine(void* arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	while (1)
	{
		while (!(ph->has_leftfork && ph->has_rightfork))
		{
			pick_forks(ph);
			is_dead(ph);
		}
		eating(ph);
		sleep_think(ph);
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
	init_philo(args);
	init_threads(args);
	destroy_threads_mutex(args);
	free(args);
	return (0);
}
