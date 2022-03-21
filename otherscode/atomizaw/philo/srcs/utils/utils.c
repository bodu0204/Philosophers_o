/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:18:51 by atomizaw          #+#    #+#             */
/*   Updated: 2022/02/19 14:55:45 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	ans;

	sign = 1;
	ans = 0;
	i = ft_isspace(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		ans = ans * 10 + str[i] - '0';
		if (ans > 2147483647 && sign == 1)
			return (-1);
		if (ans - 1 > 2147483647 && sign == -1)
			return (0);
		i++;
	}
	return ((int)ans * sign);
}

int	ft_isspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	return (i);
}
