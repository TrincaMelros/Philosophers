/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmeida <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:04:39 by malmeida          #+#    #+#             */
/*   Updated: 2021/10/28 14:09:22 by malmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	is_digit(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_negative(char **argv, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (ft_atoi(argv[i]) < 1)
			return (1);
	return (0);
}

int	error_message(int f, int time)
{
	if (f == NUM_ARGS)
		printf("[ERROR]: Wrong number of arguments, needs 4 or 5\n");
	else if (f == NOT_NUM)
		printf("[ERROR]: Arguments need to be digits\n");
	else if (f == NEG_NUM)
		printf("[ERROR]: Arguments need to be positive numbers\n");
	else if (f == NUM_PHILO)
		printf("[ERROR]: Only able to handle up to 200 Philosophers");
	else if (f == ONE_PHILO)
		printf("[%d]: 1 died\n", time);
	return (1);
}

int	arg_validation(int argc, char **argv)
{
	int	r;

	r = 0;
	if (argc < 5 || argc > 6)
		r = error_message(NUM_ARGS, 0);
	else if (is_digit(argv, argc))
		r = error_message(NOT_NUM, 0);
	else if (is_negative(argv, argc))
		r = error_message(NEG_NUM, 0);
	else if (ft_atoi(argv[1]) > 200)
		r = error_message(NUM_PHILO, 0);
	else if (ft_atoi(argv[1]) == 1)
		r = error_message(ONE_PHILO, ft_atoi(argv[2]));
	return (r);
}
