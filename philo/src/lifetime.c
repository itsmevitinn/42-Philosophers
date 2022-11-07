/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/07 18:29:36 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*lifetime(void *data)
{
	t_data		*cast;
	int			i;

	cast = data;
	while (42)
	{
		pthread_mutex_lock(&cast->global->finish);
		if (cast->global->end)
		{
			pthread_mutex_unlock(&cast->global->finish);
			return (NULL);
		}
		pthread_mutex_unlock(&cast->global->finish);
		i = -1;
		monitor(cast, i);
	}
	return (NULL);
}

void	monitor(t_data *data, int i)
{
	int	all_eaten;

	all_eaten = 0;
	while (++i < data->global->guests)
	{
		if (data->times_must_eat)
		{
			pthread_mutex_lock(&data->global->meal_access[i]);
			if (data->global->meals[i] == data->times_must_eat)
				all_eaten++;
			else
				all_eaten = 0;
			if (all_eaten >= data->global->guests)
			{
				pthread_mutex_lock(&data->global->finish);
				data->global->end = 1;
				pthread_mutex_unlock(&data->global->finish);
			}
			pthread_mutex_unlock(&data->global->meal_access[i]);
		}
		death_time(data, i);
	}
}

void	death_time(t_data *data, int i)
{
	long int	starving_time;

	pthread_mutex_lock(&data->global->meal_access[i]);
	starving_time = get_current_time() - data->global->lst_meal[i];
	if (starving_time >= data->time_to_die && data->global->lst_meal[i] != 0)
	{
		print_status(data, 'd', i);
		pthread_mutex_lock(&data->global->finish);
		data->global->end = 1;
		pthread_mutex_unlock(&data->global->finish);
	}
	pthread_mutex_unlock(&data->global->meal_access[i]);
}

long int	get_current_time(void)
{
	struct timeval	time;
	long int		miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = ((time.tv_sec * 1000) + time.tv_usec / 1000);
	return (miliseconds);
}
