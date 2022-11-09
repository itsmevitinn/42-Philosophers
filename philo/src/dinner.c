/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:04:41 by vsergio           #+#    #+#             */
/*   Updated: 2022/11/09 12:36:15 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*dinner(void *cast)
{
	t_data	*data;

	//wait a little before threads start
	// usleep(1000); 
	data = cast;
	pthread_mutex_lock(&data->global->meal_access[data->id]);
	data->global->lst_meal[data->id] = get_current_time();
	pthread_mutex_unlock(&data->global->meal_access[data->id]);
	while (42)
	{
		print_status(data, 't', data->id);
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end == 1)
		{
			pthread_mutex_unlock(&data->global->finish);
			return (NULL);
		}
		pthread_mutex_unlock(&data->global->finish);
		if (!take_forks(data))
			return (0);
		if (!eat(data))
			return (0);
		return_forks(data);
		if (!sleep_time(data))
			return (0);
	}
	return (NULL);
}

int	take_forks(t_data *data)
{
	int	handled;

	handled = 0;
	while (handled < 2)
	{
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end)
		{
			pthread_mutex_unlock(&data->global->finish);
			return (0);
		}
		pthread_mutex_unlock(&data->global->finish);
		if (data->id + 1 == data->global->guests)
		{
			pthread_mutex_lock(&data->global->m_forks[0]);
			if (!data->global->forks[0])
			{
				print_status(data, 'f', data->id);
				handled++;
				data->global->forks[0] = 1;
			}
			pthread_mutex_unlock(&data->global->m_forks[0]);
			pthread_mutex_lock(&data->global->m_forks[data->id]);
			if (!data->global->forks[data->id])
			{
				print_status(data, 'f', data->id);
				handled++;
				data->global->forks[data->id] = 1;
			}
			pthread_mutex_unlock(&data->global->m_forks[data->id]);
		}
		else
		{
			pthread_mutex_lock(&data->global->m_forks[data->id]);
			if (!data->global->forks[data->id])
			{
				print_status(data, 'f', data->id);
				handled++;
				data->global->forks[data->id] = 1;
			}
			pthread_mutex_unlock(&data->global->m_forks[data->id]);
			pthread_mutex_lock(&data->global->m_forks[data->id + 1]);
			if (!data->global->forks[data->id + 1])
			{
				print_status(data, 'f', data->id);
				handled++;
				data->global->forks[data->id + 1] = 1;
			}
			pthread_mutex_unlock(&data->global->m_forks[data->id + 1]);
		}
	}
	return (1);
}

int	sleep_time(t_data *data)
{
	print_status(data, 's', data->id);
	if (!smart_usleep(data->time_to_eat, data))
		return (0);
	return (1);
}

void	return_forks(t_data *data)
{
	pthread_mutex_lock(&data->global->m_forks[data->id]);
	data->global->forks[data->id] = 0;
	pthread_mutex_unlock(&data->global->m_forks[data->id]);
	if (data->id + 1 == data->global->guests)
	{
		pthread_mutex_lock(&data->global->m_forks[0]);
		data->global->forks[0] = 0;
		pthread_mutex_unlock(&data->global->m_forks[0]);
	}
	else
	{
		pthread_mutex_lock(&data->global->m_forks[data->id + 1]);
		data->global->forks[data->id + 1] = 0;
		pthread_mutex_unlock(&data->global->m_forks[data->id + 1]);
	}
}

int	eat(t_data *data)
{
	print_status(data, 'e', data->id);
	pthread_mutex_lock(&data->global->meal_access[data->id]);
	data->global->lst_meal[data->id] = get_current_time();
	if (data->times_must_eat)
		data->global->meals[data->id]++;
	pthread_mutex_unlock(&data->global->meal_access[data->id]);
	if (!smart_usleep(data->time_to_eat, data))
		return (0);
	return (1);
}

int	smart_usleep(long int timer, t_data *data)
{
	long int	start;
	long int	end;

	start = get_current_time();
	end = start + timer;
	while (end >= get_current_time())
	{
		pthread_mutex_lock(&data->global->finish);
		if (data->global->end)
		{
			pthread_mutex_unlock(&data->global->finish);
			return (0);
		}
		pthread_mutex_unlock(&data->global->finish);
		usleep(100);
	}
	return (1);
}
