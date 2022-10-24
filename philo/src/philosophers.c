/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/24 10:30:17 by vsergio          ###   ########.fr       */
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
		pthread_mutex_lock(&cast->meal_access[cast->pos - 1]);
		cast->last_meal[cast->pos - 1] = get_current_time(); //mutex p/ evitar content race c/ funcao lifetime
		if (cast->times_must_eat)
			cast->meals_eaten[cast->pos - 1]++;
		pthread_mutex_unlock(&cast->meal_access[cast->pos - 1]);
		usleep(cast->time_to_eat); //tempo para comer
		
		pthread_mutex_unlock(&cast->forks[cast->pos - 1]); //libera o garfo a esquerda
		if (cast->pos == cast->guests)
			pthread_mutex_unlock(&cast->forks[0]); //libera o garfo do primeiro
		else
			pthread_mutex_unlock(&cast->forks[cast->pos]); //libera o garfo a direita
		
		printf("%lims: %i is sleeping\n", get_current_time(), cast->pos);
		usleep(cast->time_to_sleep);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	t_data		content;
	pthread_t	killer;
	int			i;
	
	if (argc != 5 && argc != 6)
		print_exit();
	create_content(&content, argv, argc);
	philo = malloc(sizeof(t_philo) * content.guests);

	if (pthread_create(&killer, NULL, &lifetime, &content) != 0)
		write(2, "Error2\n", 7);
	
	i = -1;
	while(++i < content.guests)
		pthread_mutex_init(&content.forks[i], NULL);

	i = -1;
	while(++i < content.guests)
	{
		philo[i].data = content;
		if (pthread_create(&content.philo_th[i], NULL, &routine, &philo[i].data) != 0)
			write(2, "Error1\n", 7);
		content.pos++;
	}

	i = -1;
	while(++i < content.guests)
		if (pthread_join(content.philo_th[i], NULL) != 0)
			write(2, "Error2\n", 7);
	
	i = -1;
	while(++i < content.guests)
		pthread_mutex_destroy(&content.forks[i]);
	
	return (0);
}

void	create_content(t_data *content, char **argv, int argc)
{
	content->guests = ft_atoi(argv[1]);
	content->time_to_die = ft_atoi(argv[2]);
	content->time_to_eat = ft_atoi(argv[3]) * 1000;
	content->time_to_sleep = ft_atoi(argv[4]) * 1000;
	content->forks = malloc(sizeof(pthread_mutex_t) * content->guests);
	content->meal_access = malloc(sizeof(pthread_mutex_t) * content->guests);
	content->last_meal = malloc(sizeof(long int) * content->guests);
	content->last_meal = memset(content->last_meal, 0, sizeof(long int) * content->guests);
	content->times_must_eat = 0;
	content->pos = 1;
	content->philo_th = malloc(sizeof(pthread_t) * content->guests);
	if (argc == 6)
	{
		content->times_must_eat = ft_atoi(argv[5]);
		content->meals_eaten = malloc(sizeof(int) * content->guests);
		content->meals_eaten = memset(content->meals_eaten, 0, sizeof(int) * content->guests);
		content->all_eaten = 0;
	}
}
