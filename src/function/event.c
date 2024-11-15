/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:44:21 by tbarret           #+#    #+#             */
/*   Updated: 2024/03/08 12:51:54 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	eating(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->l_fork);
		ft_print(p, "has taken a fork\n");
		pthread_mutex_lock(p->r_fork);
	}
	else
	{
		pthread_mutex_lock(p->r_fork);
		ft_print(p, "has taken a fork\n");
		pthread_mutex_lock(p->l_fork);
	}
	ft_print(p, "has taken a fork\n");
	pthread_mutex_lock(&p->prop->m_eat);
	p->eating = 1;
	p->l_eat = ft_date();
	pthread_mutex_unlock(&p->prop->m_eat);
	ft_print(p, "is eating\n");
	ft_usleep(p->prop->t_eat);
	pthread_mutex_lock(&p->prop->m_eat);
	p->eaten++;
	p->eating = 0;
	pthread_mutex_unlock(&p->prop->m_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	sleeping(t_philo *p)
{
	ft_print(p, "is sleeping\n");
	ft_usleep(p->prop->t_sleep);
}

void	thinking(t_philo *p)
{
	ft_print(p, "is thinking\n");
	if ((p->prop->total % 2) != 0)
		usleep(1);
}

int	dead_exit(t_philo *p)
{
	pthread_mutex_lock(&p->prop->m_dead);
	if (p->prop->dead)
	{
		pthread_mutex_unlock(&p->prop->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&p->prop->m_dead);
	if (p->prop->max_eat != -1 && p->eaten >= p->prop->max_eat)
		return (1);
	return (0);
}
