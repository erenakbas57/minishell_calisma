/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:47:57 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:26:14 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
"free_token" adlı fonksiyon, bellekte tutulan "g_ms.token" nesnesinde saklanan 
metin dizilerini (char *str) ve token nesnelerini (t_token) serbest bırakmaya 
yarar. Bu fonksiyon, bellekte ayrılan alanların boşa harcanmamasını ve sistem 
kaynaklarının verimli kullanılmasını sağlar.
*/
void	free_token(void)
{
	t_token		*tmp;
	t_token		*token;

	token = g_ms.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = g_ms.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}
