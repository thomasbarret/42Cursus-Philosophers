/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:11:44 by tbarret           #+#    #+#             */
/*   Updated: 2024/02/29 12:43:30 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	init_philo(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->prop.total)
	{
		ctx->philo[i].id = i;
		ctx->philo[i].eating = 0;
		ctx->philo[i].eaten = 0;
		ctx->philo[i].l_eat = ft_date();
		ctx->philo[i].l_fork = &ctx->m_fork[i];
		if (i == 0)
			ctx->philo[i].r_fork = &ctx->m_fork[ctx->prop.total - 1];
		else
			ctx->philo[i].r_fork = &ctx->m_fork[i - 1];
		ctx->philo[i].prop = &ctx->prop;
		i++;
	}
}

static void	init_fork(t_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->prop.total)
	{
		pthread_mutex_init(&ctx->m_fork[i], NULL);
		i++;
	}
}

void	init_mutex(t_ctx *ctx)
{
	pthread_mutex_init(&ctx->prop.m_dead, NULL);
	pthread_mutex_init(&ctx->prop.m_eat, NULL);
	pthread_mutex_init(&ctx->prop.m_write, NULL);
	init_fork(ctx);
}
