/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:08:25 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:25:01 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon bir shell sözdizimi analizi sırasında, belirtilen `token` ve `process` 
değişkenlerine veri eklemek için kullanılır. `token` bir sözdizimi parçasıdır ve 
`process` ise bu parçayı işlemek için gerekli verileri saklayan bir yapıdır.


Eğer `token`in tipi `STRING` ise, fonksiyon `process->execute` dizisine bu tokenin 
içeriğini temizleyerek ekler.

Eğer `token`in tipi `STRING` değilse, fonksiyon `process->redirects` dizisine bu 
tokenin içeriğini temizleyerek ekler. Ardından, `token` pointer'ı bir sonraki 
`token`'a güncellenir. Eğer sonraki `token` `STRING` tipinde değilse, bir hata 
oluşur ve bu hatayı göstermek için `token_err` fonksiyonu çağrılır.

Fonksiyon sonunda, veri ekleme işlemi başarılı olduğu sürece `TRUE`, başarısız 
olduğunda `FALSE` değeri döndürür.
*/
int	append_arguments(t_token **token, t_process *process)
{
	char		*data;

	if ((*token)->type == STRING)
	{
		data = clean_quote((*token)->str);
		process->execute = push_array(process->execute, data);
	}
	else
	{
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
		*token = (*token)->next;
		if (!(*token) || (*token)->type != STRING)
		{
			if (!(*token))
				token_err(0);
			else
				token_err((*token)->type);
			free_token();
			return (FALSE);
		}
		data = clean_quote((*token)->str);
		process->redirects = push_array(process->redirects, data);
	}
	return (TRUE);
}

/*
Bu fonksiyon, bir komut satırındaki token'ları süzerek işlemleri ve yönlendirmeleri 
bir t_process yapısı içinde gruplandırır. Bu fonksiyon, token'ları gezerek, PIPE 
türündeki token'lardan sonra başka bir işlem başlatır ve token'ları (komutları ve yönlendirmeleri) 
bir t_process yapısına ekler. Her t_process yapısı bir komut satırındaki tek bir işlemi 
temsil eder. Fonksiyon, sonunda t_process yapılarını bir liste halinde saklar ve 
token'ları serbest bırakır.
*/
int	lexer(void)
{
	t_token		*token;
	t_process	*process;

	token = g_ms.token;
	while (token)
	{
		if (token->type == PIPE || token->prev == NULL)
		{
			if (token->type == PIPE)
				token = token->next;
			process = init_process();
			process_addback(&g_ms.process, process);
			g_ms.process_count++;
		}
		if (!token)
			break ;
		if (!append_arguments(&token, process))
			return (FALSE);
		if (token)
			token = token->next;
	}
	free_token();
	return (TRUE);
}
