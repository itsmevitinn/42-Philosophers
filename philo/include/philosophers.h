/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/07 18:07:32 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_global
{
	pthread_mutex_t		*m_forks;
	pthread_mutex_t		*meal_access;
	pthread_mutex_t		print;
	pthread_mutex_t		finish;
	long int			guests;
	int					*forks;
	long int			*lst_meal;
	int					*meals;
	int					end;
}						t_global;

typedef struct s_data
{
	int					id;
	t_global			*global;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			times_must_eat;
}						t_data;

typedef struct s_philo
{
	pthread_t	*threads;
	t_data		*data;
}				t_philo;

long int	get_current_time(void);
long int	ft_atoi(char *str);
long int	exit_atoi(void);
int			invalid_args(void);
int			invalid_values(void);
int			check_values(t_data *data);
int			check_atoi_numbers(char *string);
void		print_status(t_data *data, char type, int id);
void		global_data(t_global *global, int argc, char **argv);
int			private_data(t_data *data, int argc, char **argv, t_global *global);
void		init_mutexes(t_data *data);
void		start_philos(t_philo *philos, t_data *data);
void		join_philos(t_philo *philos, t_data *data);
void		*lifetime(void *philo);
void		monitor(t_data *data, int i);
void		death_time(t_data *data, int i);
void		*dinner(void *data);
int			take_forks(t_data *data);
int			eat(t_data *data);
void		return_forks(t_data *data);
int			sleep_time(t_data *data);
int			smart_usleep(long int timer, t_data *data);
void		free_all(t_philo *philos, t_data *data);
void		destroy_mutexes(t_data *data);

#endif
