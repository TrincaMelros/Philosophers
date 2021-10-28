/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/28 14:48:59 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

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
	
	if (arg_validation(argc, argv))
		return (1);
	args = malloc(sizeof(t_env));
	var_attribution(args, argc, argv);
	init_philo(args);
	init_threads(args);
	destroy_threads_mutex(args);
	free(args);
	return (0);
}
