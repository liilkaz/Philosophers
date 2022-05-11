/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 10:46:35 by tacarlen          #+#    #+#             */
/*   Updated: 2021/08/20 16:45:14 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_safe(int i)
{
	if (i != 0)
		ft_error("Mutex error!\n");
}

long long	ft_atoi(const char *str)
{
	int				i;
	int				m;
	long long int	res;

	i = 0;
	m = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32))
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		m = -m;
		i++;
	}
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			res = res * 10 + str[i] - 48;
		else
			break ;
		i++;
	}
	return (res * m);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}
