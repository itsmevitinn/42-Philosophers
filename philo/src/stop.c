/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:09 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/25 18:42:09 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	detach_threads(t_data *content)
{
	int i;
	
	i = -1;
	while(++i < content->guests)
		if (pthread_detach(content->philo_th[i]) != 0)
			write(2, "Error2\n", 7);
}

int	invalid_args(void)
{
	printf("Invalid parameters!\nTry something like below\n./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	invalid_values(void)
{
	printf("Invalid values!\nOnly numbers above 0 are allowed.\n");
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int i;

	i = -1;
	while(++i < data->guests)
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
	if (data->last_meal)
		free(data->last_meal);
	if (data->killer_ret)
		free(data->killer_ret);
}
