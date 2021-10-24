/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:51:01 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/24 13:31:46 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int mails = 0;

void*	routine(void* arg)
{
	t_env	*bros;
	int i;

	bros = (t_env *)arg;
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&bros->fork[0]);
		mails++;
		pthread_mutex_unlock(&bros->fork[0]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_env	args;
	
	if (argc < 5 || argc > 6)
		return (1);
	var_attribution(&args, argc, argv);
	create_threads_mutex(&args);
	destroy_threads_mutex(&args);
	printf("mails: %d\nstart_time: %ld\n", mails, args.start_time);
	return (0);
}
