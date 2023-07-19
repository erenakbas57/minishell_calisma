/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:56:52 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:09:00 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu C dilinde bir fonksiyondur ve "Heredoc" denilen bir özelliğin işlem dosyasını kapatır. 
Bu fonksiyon, verilen t_process tipindeki işlem nesnesinde "Heredoc" içeriğinin bulunup 
bulunmadığını kontrol eder ve eğer bulunuyorsa ve işlem dosyası 2'den büyükse, dosyayı 
kapatır (close(process->heredoc_fd[0])).
*/
void	close_heredoc_fd(t_process *process)
{
	if (contain_heredoc(process) && process->heredoc_fd[0] > 2)
		close(process->heredoc_fd[0]);
}

/*
Bu C dilinde bir fonksiyondur ve tüm açık işlem dosyalarını kapatır. Bu fonksiyon, g_ms.process 
değişkeni tarafından tanımlanan tüm t_process tipindeki işlem nesnelerinin bulunduğu bağlı listede 
dolaşır ve her bir işlem nesnesi için close_heredoc_fd(process) fonksiyonunu çağırarak dosyaları 
kapatır. Eğer işlem dosyası 2'den büyükse, dosyayı kapatır (close(process->fd[0/1])).
*/
void	close_all_fd(void)
{
	t_process	*process;

	process = g_ms.process;
	while (process)
	{
		close_heredoc_fd(process);
		if (process->fd[0] > 2)
			close(process->fd[0]);
		if (process->fd[1] > 2)
			close(process->fd[1]);
		process = process->next;
	}
}
