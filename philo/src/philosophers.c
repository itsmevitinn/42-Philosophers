/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/20 01:47:28 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_mutex_t	mutex;
long long int	value = 0;

void	*routine(void *philo)
{
	t_philo *temp = philo; //vai castar pra int * e apontar pro msm valor na memoria dos threads
	int i = 0;

	printf("Running\n");
	// if (temp->pos + 1 == temp->counter_philos) //ultimo thread
	// {
	// 	if ((temp - 1)->eating == 0 && temp[0]->eating[0] == 0)
	// 		printf("Philo %i is eating", temp->pos);
	// }
	printf("pos do philo: %i\n", temp->pos);
	pthread_mutex_lock(&mutex);
	while(i++ < 100000000)
		value++;
	pthread_mutex_unlock(&mutex);
	printf("Valor: %lli\n", value);
	printf("Ending\n\n");
	return (0);
}

int main(int argc, char **argv)
{
	//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, number_of_times_each_philosophers_must_eat
	t_philo		*philo;
	int			i;
	int counter_philos;

	argc++;
	i = 0;
	
	philo = NULL;
	//criar array de status hungry e popular com -1, depois checar de acordo com a posicao do philo,
	//se o anterior e o proximo nao estao comendo, se nao estiverem, o thread edita com mutex o status no array de inteiros
	//que ele esta comendo..
	pthread_mutex_init(&mutex, NULL);
	counter_philos = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * counter_philos);

	if (!philo)
	{
		free(philo);
		return (0);
	}
	printf("Filosofos criados: %i\n", counter_philos);
	while(i < counter_philos)
	{
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0) //injeta ID da thread no 1o param
			write(2, "Error1\n", 7);
		philo[i].pos = i;
		philo[i].eating = 0;
		i++;
	}
	i = 0;
	while(i < counter_philos)
	{
		if (pthread_join(philo[i].philo_th, NULL) != 0)
			write(2, "Error2\n", 7);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
