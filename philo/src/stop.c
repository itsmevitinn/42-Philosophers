/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:09 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/31 19:45:55 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	invalid_args(void)
{
	printf("Invalid arguments!\n");
	printf("Try: ./philo 2 200 100 100 || ./philo 2 300 100 100 2\n");
	return (0);
}

int	invalid_values(void)
{
	printf("Invalid values!\nOnly numbers above 0 are allowed.\n");
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->guests)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->meal_access[i]);
	}
}

void	free_all(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->meal_access)
		free(data->meal_access);
	if (data->lst_meal)
		free(data->lst_meal);
	if (data->philo_th)
		free(data->philo_th);
}
