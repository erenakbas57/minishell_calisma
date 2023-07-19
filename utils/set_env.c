/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:18 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:06:56 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"set_env" fonksiyonu, bir ortam değişkeni dizisi 
olan "env" verilen bir programın ortam değişkenlerini 
"g_ms.env" isimli global bir değişkene atar. Bu değişken, 
programın çalışma sırasında kullanılabilecek ortam 
değişkenlerinin tutulmasını sağlar.
*/
void	set_env(char **env)
{
	size_t	i;
	size_t	len;
	char	**head;

	head = env;
	while (*head)
		head++;
	len = head - env;
	g_ms.env = ft_calloc(sizeof(char **), len + 1);
	i = -1;
	while (++i < len)
		g_ms.env[i] = ft_strdup(env[i]);
}
