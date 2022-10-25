/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/25 18:10:18 by vsergio          ###   ########.fr       */
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
	cast->killer_ret = malloc(sizeof(int));
	*cast->killer_ret = 1; //retorno quando morrer;
	while(42)
	{
		i = -1;
		while(++i < cast->guests)
		{
			if (cast->last_meal[i] != 0)
			{
				pthread_mutex_lock(&cast->meal_access[i]);
				current_time = get_current_time();
				starving_time = current_time - cast->last_meal[i];
				if (starving_time > cast->time_to_die)
				{
					printf("%lims: %i died\n", current_time, i + 1);
					return ((void *)cast->killer_ret);
				}
				pthread_mutex_unlock(&cast->meal_access[i]);
				if (cast->times_must_eat)
				{
					pthread_mutex_lock(&cast->meal_access[i]);
					if (cast->meals_eaten[i] >= cast->times_must_eat)
						cast->all_eaten++;
					else
					{
						cast->all_eaten = 0;		
						break;
					}
					if (cast->all_eaten == cast->guests)
					{
						printf("%lims: everyone ate\n", get_current_time());
						return ((void *)cast->killer_ret);
					}
					pthread_mutex_unlock(&cast->meal_access[i]);
				}
			}
		}
	}
	return (0);
}

long int	get_current_time()
{
	struct timeval time;
	long int	miliseconds;

	gettimeofday(&time, NULL);
	miliseconds = ((time.tv_sec * 1000) + time.tv_usec / 1000);
	return (miliseconds);
}
