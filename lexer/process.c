/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:10:01 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:25:40 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
`init_process()` fonksiyonu bir `t_process` yapısı oluşturur ve bu yapının tüm 
elemanlarını başlangıç değerlerine atar. Özellikle, `pipe` fonksiyonu ile bir 
pipe oluşturur ve fd değişkenine kaydeder, pid değişkenini -1 olarak atar, execute 
ve redirects dizilerini bellekte yer açar ve bu dizilerin içeriklerini sıfırlar. 
Son olarak, bu yapının prev ve next işaretçilerini NULL yapar.
*/
t_process	*init_process(void)
{
	t_process	*process;

	process = ft_calloc(sizeof(t_process), 1);
	pipe(process->fd);
	process->pid = -1;
	process->execute = ft_calloc(sizeof(char *), 1);
	process->redirects = ft_calloc(sizeof(char *), 1);
	process->prev = NULL;
	process->next = NULL;
	return (process);
}

/*
"process_addback" fonksiyonu, bir süreç verilen bir bağlı listesine eklemek için kullanılır. 
Eğer verilen bağlı liste boş ise, verilen yeni süreç bağlı listenin tek öğesi olarak atanır. 
Aksi takdirde, bağlı listedeki son süreç bulunur ve yeni süreç bu son sürecin "next" öğesine 
atanır. Ayrıca, yeni sürecin "prev" öğesi de bulunan son sürecin kendisi olarak ayarlanır.
*/
void	process_addback(t_process **process, t_process *new_process)
{
	t_process	*i_process;

	i_process = *process;
	if (!(i_process))
		*process = new_process;
	else
	{
		while (i_process->next)
			i_process = i_process->next;
		i_process->next = new_process;
		new_process->prev = i_process;
	}
}
