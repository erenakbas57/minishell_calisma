/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:51:00 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:26:47 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon "arr" adlı bir diziyi bellekte serbest bırakır. Her bir dizi elemanını 
tek tek serbest bırakır ve sonra diziyi kendisini serbest bırakır. Bu, bellekte 
boşluk açmak ve bellek sıkıntısı oluşmadan programın çalışmasını sağlamaya yardımcı olur.
*/
void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
Bu fonksiyon, `g_ms.process` adlı bir veri yapısındaki tüm işlemleri serbest bırakır. İşlemler,
 `t_process` tipindeki bir veri yapısında saklanır ve tek tek serbest bırakılır. Her bir işlemin 
 `execute` ve `redirects` alanlarındaki diziler de serbest bırakılır.
*/
void	free_process(void)
{
	t_process	*tmp;
	t_process	*process;

	process = g_ms.process;
	if (!process)
		return ;
	while (process)
	{
		free_array(process->execute);
		free_array(process->redirects);
		tmp = process;
		process = process->next;
		free(tmp);
	}
}
