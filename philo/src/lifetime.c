/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:49:55 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/21 13:50:01 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*lifetime(void *data)
{
	t_data			*new_data;
	long long int	current_time;
	long long int	starving_time;
	int				i;

	new_data = data;
	while(42)
	{
		i = -1;
		while(++i < new_data->guests)
		{
			if (new_data->last_meal[i] != 0)
			{
				current_time = get_current_time(new_data);
				starving_time = current_time - new_data->last_meal[i];
				if (starving_time > new_data->time_to_eat)
				{
					printf("%lims: %i died\n", get_current_time(new_data), i + 1);
					printf("%lims: %i last meal\n", new_data->last_meal[i], i + 1);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
	return (NULL);
}

long int	get_current_time(t_data *data)
{
	long int	sec_to_micro;
	long int	miliseconds;

	data->time = malloc(sizeof(struct timeval));
	gettimeofday(data->time, NULL);
	sec_to_micro = data->time->tv_sec * 1000000;
	miliseconds = (sec_to_micro + data->time->tv_usec) / 1000;
	return (miliseconds);
}
