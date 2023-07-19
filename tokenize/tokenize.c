/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:13:13 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 17:49:39 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"init_token" fonksiyonu belirli bir string ve token tipi ile bir token nesnesi oluşturmak 
için kullanılır. Fonksiyon, token nesnesi için bellek alanı ayırarak oluşturulan nesnenin 
değerlerini ayarlar ve döndürür. "str" parametresi token nesnesinin string değerini belirler, 
"type" parametresi ise token nesnesinin tipini belirler.
*/
t_token	*init_token(char *str, enum e_ttype type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	token->type = type;
	token->str = str;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

/*
Bu fonksiyon, belirtilen token dizisinin sonuna, belirtilen yeni token nesnesini ekler. 
Fonksiyon, eklenen token'ın sayısını (önceki token sayısı + 1) geri döndürür.
*/
int	token_addback(t_token **token, t_token *new_token, int plus)
{
	t_token	*i_token;

	i_token = *token;
	if (!i_token)
		*token = new_token;
	else
	{
		while (i_token->next)
			i_token = i_token->next;
		i_token->next = new_token;
		new_token->prev = i_token;
	}
	return (plus);
}

/*
Bu fonksiyon "tokenize" verilen bir metin dizesini belirli işaretler ve operatörler bazında ayrıştırır. 
İşaret ve operatörler belirlenerek "t_token" tipinde bir yapı içinde saklanır. Bu yapıdaki veriler 
sonrasında işlem yapmak için kullanılabilir.
*/
void	tokenize(char *str)
{
	while (*str)
	{
		if (is_operator(str) == RED_APPEND)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">>"), RED_APPEND), 2);
		else if (is_operator(str) == HERE_DOC)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<<"), HERE_DOC), 2);
		else if (is_operator(str) == PIPE)
			str += token_addback(&g_ms.token, init_token(ft_strdup("|"), PIPE), 1);
		else if (is_operator(str) == RED_INPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup("<"), RED_INPUT), 1);
		else if (is_operator(str) == RED_OUTPUT)
			str += token_addback(&g_ms.token, init_token(ft_strdup(">"), RED_OUTPUT), 1);
		else
			parse_token_string(&str);
	}
}
