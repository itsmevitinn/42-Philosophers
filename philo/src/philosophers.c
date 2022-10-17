/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/17 15:09:35 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

// int kikos = 0;
pthread_mutex_t mutex;

void	*routine(void *value)
{
	int *rato = value; //vai castar pra int * e apontar pro msm valor na memoria dos threads
	int i = 0;

	pthread_mutex_lock(&mutex);
	printf("Running\n");
	while(i++ < 1000000000)
		++*rato;
	pthread_mutex_unlock(&mutex);
	printf("Valor: %i\n", *rato);
	printf("Ending\n");
	return (0);
}

int main(int argc, char **argv)
{
	//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosophers_must_eat
	t_philo *philo;
	pthread_t	t1;
	pthread_t	t2;
	int			number_of_philo;
	int i;
	int value;

	value = 0;
	i = 0;
	philo->number_of_philo = ft_atoi(argv[2]);
	philo = malloc(sizeof(pthread_t) * number_of_philo);
	if (!philo)
	{
		free(philo);
		return (0);
	}
	while(i < number_of_philo)
		if (pthread_create(&philo[i], NULL, &routine, &value) != 0)
			write(2, "Error\n", 6);
	pthread_mutex_init(&mutex, NULL);
	// if (pthread_create(&t1, NULL, &routine, &value) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
	// 	write(2, "Error\n", 6);
	// if (pthread_create(&t2, NULL, &routine, &value) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
	// 	write(2, "Error\n", 6);
	// if (pthread_join(t1, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
	// 	write(2, "Error\n", 6);
	// if (pthread_join(t2, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
	// 	write(2, "Error\n", 6);
	pthread_mutex_destroy(&mutex);
	return (0);
}
