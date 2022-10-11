/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsergio <vsergio@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:17:36 by vsergio           #+#    #+#             */
/*   Updated: 2022/10/11 17:47:42 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int kikos = 5;

#include "../include/philosophers.h"
void	*test()
{
	int i = 0;
	while (i++ < 100000) //exemplo de data race, o valor sera instavel
		kikos++;
	return (0);
}

// void	*test(void *value)
// {
// 	int *rato = value; //vai castar pra int * e apontar pro msm valor na memoria dos threads
// 	printf("Valor: %i\n", ++*rato);
// 	printf("Running\n");
// 	//sleep(2);
// 	printf("Ending\n");
// 	return (0);
// }

int main(void)
{
	pthread_t t1;
	pthread_t t2;
	// int value = 3;

	if (pthread_create(&t1, NULL, &test, NULL) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
		write(2, "Error\n", 6);
	if (pthread_create(&t2, NULL, &test, NULL) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
		write(2, "Error\n", 6);
	// if (pthread_create(&t1, NULL, &test, &value) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
	// 	write(2, "Error\n", 6);
	// if (pthread_create(&t2, NULL, &test, &value) != 0) //criamos a thread, passamos ponteiro da variavel e a funcao p/ ser chamada
	// 	write(2, "Error\n", 6);
	if (pthread_join(t1, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
		write(2, "Error\n", 6);
	if (pthread_join(t2, NULL) != 0) // basicamente um wait para threads, p/ processo n acabar antes da thread
		write(2, "Error\n", 6);
	printf("Valor: %i\n", kikos);
}
