/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/26 10:01:15 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int main(int argc, char **argv)
{
	t_data		content;
	pthread_t	killer;

	if (argc != 5 && argc != 6)
		if (!invalid_args())
			return (0);
	if (!create_content(&content, argv, argc))
		return (0);
	create_killer(&killer, &content);
	init_mutexes(&content);
	create_philo_threads(&content);
	if (check_killer(&killer, &content) == 1)
	{
		destroy_mutexes(&content);
		free_all(&content);
		return (0);
	}
	destroy_mutexes(&content);
	free_all(&content);
	return (0);
}

int	create_content(t_data *content, char **argv, int argc)
{
	content->guests = ft_atoi(argv[1]);
	content->time_to_die = ft_atoi(argv[2]);
	content->time_to_eat = ft_atoi(argv[3]);
	content->time_to_sleep = ft_atoi(argv[4]);
	if (!check_values(content))
		return (0);
	content->forks = malloc(sizeof(pthread_mutex_t) * content->guests);
	content->meal_access = malloc(sizeof(pthread_mutex_t) * content->guests);
	content->last_meal = malloc(sizeof(long int) * content->guests);
	content->last_meal = memset(content->last_meal, 0, sizeof(long int) * content->guests);
	content->times_must_eat = 0;
	content->pos = 1;
	content->killer_ret = 0;
	content->philo_th = malloc(sizeof(pthread_t) * content->guests);
	if (argc == 6)
	{
		content->times_must_eat = ft_atoi(argv[5]);
		if (!check_values(content))
			return (0);
		content->meals_eaten = malloc(sizeof(int) * content->guests);
		content->meals_eaten = memset(content->meals_eaten, 0, sizeof(int) * content->guests);
		content->all_eaten = 0;
	}
	return (1);
}

int	check_values(t_data *data)
{
	if (data->guests == 2147483650)
		return (invalid_values());
	else if (data->time_to_die == 2147483650)
		return (invalid_values());
	else if (data->time_to_eat == 2147483650)
		return (invalid_values());
	else if (data->time_to_sleep == 2147483650)
		return (invalid_values());
	else if (data->times_must_eat == 2147483650)
		return (invalid_values());
	return (1);
}

void	create_killer(pthread_t *killer, t_data *content)
{
	if (pthread_create(killer, NULL, &lifetime, content) != 0)
		write(2, "Error2\n", 7);
}

void	init_mutexes(t_data *content)
{
	int i;

	i = -1;
	while(++i < content->guests)
		pthread_mutex_init(&content->forks[i], NULL);
}

void	create_philo_threads(t_data *content)
{
	t_philo		*philo;
	int i;

	philo = malloc(sizeof(t_philo) * content->guests);
	i = -1;
	while(++i < content->guests)
	{
		philo[i].data = *content;
		if (pthread_create(&content->philo_th[i], NULL, &dinner, &philo[i].data) != 0)
			write(2, "Error1\n", 7);
		content->pos++;
	}
}

int	check_killer(pthread_t *killer, t_data *content)
{
	if (pthread_join(*killer, (void *)content->killer_ret) != 0)
		write(2, "Error1\n", 7);
	return(*content->killer_ret);
}
