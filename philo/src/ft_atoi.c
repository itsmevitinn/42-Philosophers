/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 08:59:49 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/23 02:27:29 by Vitor            ###   ########.fr       */
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
			print_exit();
		str++;
	}
	if (!check_atoi_numbers(str))
		print_exit();
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res > 2147483647 || res < -2147483648)
			print_exit();
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

void	print_exit(void)
{
	printf("Invalid parameters!\nTry something like below\n./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}
