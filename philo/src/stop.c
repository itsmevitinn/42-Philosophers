/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:09 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/03 17:42:22 by vsergio          ###   ########.fr       */
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
		pthread_mutex_destroy(&data->print);
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
	if (data->ph_thread)
		free(data->ph_thread);
	if (data->ph_data)
		free(data->ph_data);
	if (data->meals)
		free(data->meals);
}

void	print_status(t_data *data, char type, int pos)
{
	pthread_mutex_lock(&data->print);
	if (type == 't')
		printf("%lims: %i is thinking\n", get_current_time(), data->id);
	else if (type == 'f')
		printf("%lims: %i has taken a fork\n", get_current_time(), data->id);
	else if (type == 'e')
		printf("%lims: %i is eating\n", get_current_time(), data->id);
	else if (type == 's')
		printf("%lims: %i is sleeping\n", get_current_time(), data->id);
	else if (type == 'd')
		printf("%lims: %i died\n", get_current_time(), pos);
	pthread_mutex_unlock(&data->print);
}
