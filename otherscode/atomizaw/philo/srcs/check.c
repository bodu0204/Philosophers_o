/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:44:13 by atomizaw          #+#    #+#             */
/*   Updated: 2022/03/14 14:44:48 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

typedef enum e_arg
{
	number_philo,
	time_die,
	time_eat,
	time_sleep,
	must_eat_count
}	t_arg;

int	is_digit(int argc, char **argv)
{
	char	*arg;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j < argc)
	{
		arg = argv[j];
		i = 0;
		while (arg[i] != '\0')
		{
			if (arg[i] >= '0' && arg[i] <= '9')
				i++;
			else
				return (FALSE);
		}
		j++;
	}
	return (TRUE);
}

int	is_arg_ok(int argc, char **argv)
{
	int	arg_array[5];
	int	i;

	i = 0;
	if (!is_digit(argc, argv))
		return (FALSE);
	if (argc == 5 || argc == 6)
	{
		while (i++ < 4)
			arg_array[i - 1] = ft_atoi(argv[i]);
		i = 0;
		if (argc == 6)
			arg_array[must_eat_count] = ft_atoi(argv[5]);
		else
			arg_array[must_eat_count] = 0;
		if (arg_array[number_philo] <= 0 || arg_array[time_die] < 0
			|| arg_array[time_eat] < 0 || arg_array[time_sleep] < 0
			|| arg_array[must_eat_count] < 0)
			return (FALSE);
		else
			return (TRUE);
	}
	else
		return (FALSE);
}
