/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/23 02:42:43 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*lifetime(void *data)
{
	t_data		*cast;
	long int	current_time;
	long int	starving_time;
	int			i;

	cast = data;
	while(42)
	{
		i = -1;
		while(++i < cast->guests)
		{
			if (cast->times_must_eat)
			{
				if (cast->meals_eaten[i] >= cast->times_must_eat)
				{
					pthread_mutex_lock(&cast->meal_access[i]);
					cast->all_eaten++;
					pthread_mutex_unlock(&cast->meal_access[i]);
				}
				if (cast->all_eaten == cast->guests)
				{
					usleep(cast->time_to_eat);
					printf("%lims: everyone ate\n", get_current_time());
					exit(1);
					// destroy_mutexes(data);
					// free_all(data);
				}
			}
			if (cast->last_meal[i] != 0 && cast->times_must_eat == 0)
			{
				pthread_mutex_lock(&cast->meal_access[i]);
				current_time = get_current_time();
				starving_time = current_time - cast->last_meal[i];
				if (starving_time > cast->time_to_die)
				{
					printf("%lims: %i died\n", current_time, i + 1);
					destroy_mutexes(data);
					free_all(data);
					exit(EXIT_FAILURE);
				}
				pthread_mutex_unlock(&cast->meal_access[i]);
			}
		}
	}
	return (NULL);
}

void	free_all(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->meal_access)
		free(data->meal_access);
	if (data->last_meal)
		free(data->last_meal);
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

long int	get_current_time()
{
	struct timeval time;
	long int	miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = ((time.tv_sec * 1000) + time.tv_usec / 1000);
	return (miliseconds);
}
