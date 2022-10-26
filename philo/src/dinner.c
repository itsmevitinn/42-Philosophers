/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:41 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/26 11:48:38 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*dinner(void *cast)
{
	t_data	*data;

	data = cast;
	data->lst_meal[data->pos - 1] = get_current_time();
	while (42)
	{
		printf("%lims: %i is thinking\n", get_current_time(), data->pos);
		take_forks(data);
		eat(data);
		return_forks(data);
		sleep_time(data);
	}
	return (NULL);
}

void	take_forks(t_data *data)
{
	if (data->pos == data->guests)
	{
		pthread_mutex_lock(&data->forks[0]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
	}
	else
	{
		pthread_mutex_lock(&data->forks[data->pos - 1]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
		pthread_mutex_lock(&data->forks[data->pos]);
		printf("%lims: %i has taken a fork\n", get_current_time(), data->pos);
	}
}

void	sleep_time(t_data *data)
{
	printf("%lims: %i is sleeping\n", get_current_time(), data->pos);
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
	printf("%lims: %i is eating\n", get_current_time(), data->pos);
	pthread_mutex_lock(&data->meal_access[data->pos - 1]);
	data->lst_meal[data->pos - 1] = get_current_time();
	pthread_mutex_unlock(&data->meal_access[data->pos - 1]);
	usleep(data->time_to_eat * 1000);
	if (data->times_must_eat)
		data->meals[data->pos - 1]++;
}
