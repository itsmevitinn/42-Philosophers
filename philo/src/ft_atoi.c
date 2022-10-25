/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 08:59:49 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/25 18:28:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

long int	ft_atoi(char *str)
{
	long int	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
			str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (exit_atoi());
		str++;
	}
	if (!check_atoi_numbers(str))
		return (exit_atoi());
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 2147483647 || res < -2147483648)
			return (exit_atoi());
		str++;
	}
	return (sign * res);
}

int	check_atoi_numbers(char *string)
{
	char	*temp;

	temp = string;
	if (*temp == 0 || *temp == '0')
		return (0);
	while (*temp)
	{
		if (*temp >= '0' && *temp <= '9')
			temp++;
		else
			return (0);
	}
	return (1);
}

long int	exit_atoi(void)
{
	return (2147483650);
}
