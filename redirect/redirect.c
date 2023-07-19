/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:11:59 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:16:50 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, belirtilen işlemde yönlendirilmiş girdi kaynaklarını almak için kullanılır. 
İşlemdeki tüm yönlendirme işaretçleri taranır ve eğer RED_INPUT veya HERE_DOC gibi yönlendirme 
operatörleri bulunursa, ilgili fonksiyonlar çağrılır ve girdi kaynağı belirlenir.
*/
void	get_all_inputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_INPUT)
			input(redirects[i + 1]);
		else if (is_operator(redirects[i]) == HERE_DOC)
			dup2(process->heredoc_fd[0], 0);
		i += 2;
	}
}

/*
`get_all_inputs` ve `set_all_outputs` fonksiyonları, `process` verilerini yönlendirme işlemlerini 
yapmak için kullanılan fonksiyonlardır. `get_all_inputs` fonksiyonu verilen `process` verilerine 
göre girdi dosyalarını okumak için gerekli olan fonksiyonları çağırır. `set_all_outputs` fonksiyonu 
verilen `process` verilerine göre çıktı dosyalarını yazmak için gerekli olan fonksiyonları çağırır.
*/
void	set_all_outputs(t_process *process)
{
	int		i;
	char	**redirects;

	i = 0;
	redirects = process->redirects;
	while (redirects[i])
	{
		if (is_operator(redirects[i]) == RED_OUTPUT)
			output(redirects[i + 1], REPLACE);
		else if (is_operator(redirects[i]) == RED_APPEND)
			output(redirects[i + 1], APPEND);
		i += 2;
	}
}

/*
Bu fonksiyon, bir shell uygulamasında "here document" (heredoc) yönlendirmesini desteklemek için tasarlandı. 
Her process için, process'in "redirects" dizisindeki her bir "here document" yönlendirmesini işler ve o yönlendirmenin 
bitiş satırına kadar okunan kullanıcı girdilerini bir pipe üzerinden saklar. "heredoc_fd" dizisi, pipe'ın okuma ve yazma 
uçlarını tutar. "heredoc()" fonksiyonu, kullanıcı girdilerini okur ve yazdığı pipe üzerinde saklar. "fill_all_heredoc()" 
fonksiyonu ise tüm processler için "heredoc()" fonksiyonunu çağırır ve tüm "here document" yönlendirmelerinin doldurulmasını sağlar.
*/
void	fill_all_heredoc(void)
{
	int			i;
	char		**redirects;
	t_process	*process;

	process = g_ms.process;
	while (process)
	{
		i = 0;
		redirects = process->redirects;
		while (redirects[i] && !(g_ms.ignore))
		{
			if (is_operator(redirects[i]) == HERE_DOC)
				heredoc(process->heredoc_fd, redirects[i + 1]);
			i += 2;
		}
		process = process->next;
	}
}
