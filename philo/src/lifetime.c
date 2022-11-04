/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/03 22:49:07 by Vitor            ###   ########.fr       */
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
		i = -1;
		if (!monitor(cast, i))
			return (NULL);
	}
	return (NULL);
}

int	monitor(t_data *data, int i)
{
	while (++i < data->global->guests)
	{
		if (data->times_must_eat)
		{
			pthread_mutex_lock(&data->meal_access[i]);
			if (data->meals[i] >= data->times_must_eat)
				data->all_eaten++;
			else
				data->all_eaten = 0;
			if (data->all_eaten >= data->global->guests)
			{
				pthread_mutex_lock(&data->global->finish);
				data->global->end = 1;
				pthread_mutex_unlock(&data->global->finish);
				printf("Valor end killer: %i\n", data->global->end);
				return (0);
			}
			pthread_mutex_unlock(&data->meal_access[i]);
		}
		if (death_time(data, i))
			return (0);
	}
	return (1);
}

int	death_time(t_data *data, int i)
{
	long int	current_time;
	long int	starving_time;

	pthread_mutex_lock(&data->meal_access[i]);
	current_time = get_current_time();
	starving_time = current_time - data->lst_meal[i];
	if (starving_time >= data->time_to_die && data->lst_meal[i] != 0)
	{
		print_status(data, 'd', i);
		pthread_mutex_lock(&data->global->finish);
		data->global->end = 1;
		pthread_mutex_unlock(&data->global->finish);
		printf("Valor end: %i\n", data->global->end);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_access[i]);
	return (0);
}

long int	get_current_time(void)
{
	struct timeval	time;
	long int		miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = ((time.tv_sec * 1000) + time.tv_usec / 1000);
	return (miliseconds);
}
