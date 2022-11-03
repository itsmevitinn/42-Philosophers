/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:41 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/02 21:00:28 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*dinner(void *cast)
{
	t_data	*data;

	data = cast;
	pthread_mutex_lock(&data->meal_access[data->pos - 1]);
	data->lst_meal[data->pos - 1] = get_current_time();
	pthread_mutex_unlock(&data->meal_access[data->pos - 1]);
	while (42)
	{
		take_forks(data);
		eat(data);
		return_forks(data);
		sleep_time(data);
		print_status(data, 't', 0);
	}
	return (NULL);
}

void	take_forks(t_data *data)
{
	if (data->pos == data->guests)
	{
		pthread_mutex_lock(&data->forks[0]);
		print_status(data, 'f', 0);
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		print_status(data, 'f', 0);
	}
	else
	{
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		print_status(data, 'f', 0);
		pthread_mutex_lock(&data->forks[data->pos]);
		print_status(data, 'f', 0);
	}
}

void	sleep_time(t_data *data)
{
	print_status(data, 's', 0);
	usleep(data->time_to_sleep * 1000);
}

void	return_forks(t_data *data)
{
	pthread_mutex_unlock(&data->forks[data->pos - 1]);
	if (data->pos == data->guests)
		pthread_mutex_unlock(&data->forks[0]);
	else
		pthread_mutex_unlock(&data->forks[data->pos]);
}

void	eat(t_data *data)
{
	print_status(data, 'e', 0);
	pthread_mutex_lock(&data->meal_access[data->pos - 1]);
	data->lst_meal[data->pos - 1] = get_current_time();
	pthread_mutex_unlock(&data->meal_access[data->pos - 1]);
	usleep(data->time_to_eat * 1000);
	if (data->times_must_eat)
	{
		pthread_mutex_lock(&data->meal_access[data->pos - 1]);
		data->meals[data->pos - 1]++;
		pthread_mutex_unlock(&data->meal_access[data->pos - 1]);
	}
}
