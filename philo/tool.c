/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blyu <blyu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:22:21 by blyu              #+#    #+#             */
/*   Updated: 2022/07/11 15:50:44 by blyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
int		is_numstr(char	*s);

int	set_uint(char	*s, unsigned int *u)
{
	if (!is_numstr(s))
		return (1);
	*u = 0;
	while (*s)
	{
		*u *= 10;
		*u += *s - '0';
		s++;
	}
	return (0);
}

int	is_numstr(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	if (i > 10)
		return (0);
	if (i == 10)
		return (ft_memcmp(s, "4294967295", 10) <= 0);
	return (1);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && *((char *)s1 + i) == *((char *)s2 + i))
		i++;
	if (i == n)
		return (0);
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}
