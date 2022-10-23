/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/23 02:01:57 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

void	*routine(void *data)
{
	t_data	*cast;

	cast = data;
	while(42)
	{
		printf("%lims: %i is thinking\n", get_current_time(), cast->pos);
		if (cast->pos == cast->guests) //ultimo filosofo
		{
			pthread_mutex_lock(&cast->forks[0]); //garfo a direita do ultimo filosofo eh o garfo do primeiro, e tambem deve rodar primeiro pra ficar na fila e evitar deadlock
			printf("%lims: %i has taken a fork\n", get_current_time(), cast->pos);
			pthread_mutex_lock(&cast->forks[cast->pos - 1]);
			printf("%lims: %i has taken a fork\n", get_current_time(), cast->pos);
		}
		else
		{
			pthread_mutex_lock(&cast->forks[cast->pos - 1]);
			printf("%lims: %i has taken a fork\n", get_current_time(), cast->pos);
			pthread_mutex_lock(&cast->forks[cast->pos]); //garfo a direita do filosofo
			printf("%lims: %i has taken a fork\n", get_current_time(), cast->pos);
		}

		printf("%lims: %i is eating\n", get_current_time(), cast->pos);
		usleep(cast->time_to_eat); //tempo para comer
		
		pthread_mutex_lock(&cast->meal_access[cast->pos - 1]);
		cast->last_meal[cast->pos - 1] = get_current_time(); //mutex p/ evitar data race c/ funcao lifetime
		if (cast->times_must_eat)
			cast->meals_eaten[cast->pos - 1]++;
		pthread_mutex_unlock(&cast->meal_access[cast->pos - 1]);
		
		pthread_mutex_unlock(&cast->forks[cast->pos - 1]); //libera o garfo a esquerda
		
		if (cast->pos == cast->guests)
			pthread_mutex_unlock(&cast->forks[0]); //libera o garfo a direita
		else
			pthread_mutex_unlock(&cast->forks[cast->pos]); //libera o garfo a direita
		printf("%lims: %i is sleeping\n", get_current_time(), cast->pos);
		usleep(cast->time_to_sleep);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		killer;
	t_data			data;
	int				i;
	
	if (argc != 5 && argc != 6)
		perror("Error\n");
	create_data(&data, argv, argc);
	philo = malloc(sizeof(t_philo) * data.guests);
	

	if (pthread_create(&killer, NULL, &lifetime, &data) != 0)
		write(2, "Error2\n", 7);
	
	i = -1;
	while(++i < data.guests)
		pthread_mutex_init(&data.forks[i], NULL);

	i = -1;
	while(++i < data.guests)
	{
		philo[i].data_control = data;
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i].data_control) != 0)
			write(2, "Error1\n", 7);
		data.pos++;
	}

	i = -1;
	while(++i < data.guests)
		if (pthread_join(philo[i].philo_th, NULL) != 0)
			write(2, "Error2\n", 7);
	
	i = -1;
	while(++i < data.guests)
		pthread_mutex_destroy(&data.forks[i]);
	
	return (0);
}

void	create_data(t_data *data, char **argv, int argc)
{
	data->guests = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->guests);
	data->meal_access = malloc(sizeof(pthread_mutex_t) * data->guests);
	data->last_meal = malloc(sizeof(long int) * data->guests);
	data->last_meal = memset(data->last_meal, 0, sizeof(long int) * data->guests);
	data->times_must_eat = 0;
	data->all_eaten = 0;
	data->pos = 1;
	if (argc == 6)
	{
		data->times_must_eat = ft_atoi(argv[5]);
		data->meals_eaten = malloc(sizeof(int) * data->guests);
	}
}
