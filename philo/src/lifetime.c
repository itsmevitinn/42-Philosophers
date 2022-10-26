/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/26 11:49:04 by vsergio          ###   ########.fr       */
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
	while (++i < data->guests)
	{
		if (data->lst_meal[i] != 0)
		{
			if (data->times_must_eat)
			{
				pthread_mutex_lock(&data->meal_access[i]);
				if (data->meals[i] >= data->times_must_eat)
					data->all_eaten++;
				else
					data->all_eaten = 0;
				if (data->all_eaten == data->guests)
				{
					printf("%lims: everyone ate\n", get_current_time());
					return (0);
				}
				pthread_mutex_unlock(&data->meal_access[i]);
			}
			if (death_time(data, i))
				return (0);
		}
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
	if (starving_time > data->time_to_die)
	{
		printf("%lims: %i died\n", current_time, i + 1);
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
