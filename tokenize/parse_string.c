/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:13:04 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:09:22 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, verilen `str` değişkeninin içinde belirtilen 
`type` karakterini arar. Eğer `type` karakteri bulunursa, 
karakterin bulunduğu pozisyondan sonraki karakterin boşluk 
veya operator karakter olup olmadığı kontrol edilir. Eğer 
boşluk veya operator karakter değilse, o karakterden sonraki 
boşluk veya operator karakter bulunana kadar `str` değişkeni 
içindeki karakterler gezilir. Bu fonksiyon, bulunan `type` 
karakterine kadarki kısmın son pozisyonunu belirler ve geriye döndürür.
*/
void	find_end_pos(char **str, char type)
{
	(*str)++;
	while (**str)
	{
		if (**str == type)
		{
			(*str)++;
			if (is_whitespace(**str) || is_operator(*str))
				break ;
			else
				while (**str && !is_whitespace(**str) && !is_operator(*str))
					(*str)++;
			return ;
		}
		(*str)++;
	}
}

/*
Bu fonksiyon, verilen karakter dizisi içinde (`*str`) bir operatör veya 
boşluk bulana kadar karakterleri okuyup ilerletir. Eğer bir operatör veya 
boşluk bulunursa döngüden çıkar ve fonksiyon sonlanır.
*/
void	without_quote_parse(char **str)
{
	while (**str)
	{
		if (is_whitespace(**str))
			break ;
		if (is_operator(*str))
			break ;
		(*str)++;
	}
}

/*
`skip_whitespace` fonksiyonu, verilen bir karakter dizisi içinde, gösterici (`str`) 
pozisyonunu oluşan boşluk karakterlerine kadar hareket ettirir. Sonra, `head` göstericisi 
o pozisyonu gösterir. Yani, `str` ve `head` göstericileri, verilen karakter dizisindeki 
ilk boşluk karakteri dışındaki ilk karakteri gösterir.
*/
void	skip_whitespace(char **str, char **head)
{
	while (**str && is_whitespace(**str))
		(*str)++;
	*head = *str;
}

/*
Bu fonksiyon, bir metin dizesinde belirtilen bir token'ı parse etmeye yarar. İlk olarak, 
belirtilen dizinin başındaki boşluklar atlanır ve token'ın başlangıç noktası belirlenir. 
Daha sonra, eğer token, çift veya tek tırnak içinde ise, token'ın son noktası belirlenir 
ve belirtilen tırnak tipi arasındaki metin alınır. Aksi takdirde, boşluk veya operatör 
bulunana kadar metin taranır. Elde edilen metin, son olarak token olarak eklenir.
*/
void	parse_token_string(char **str)
{
	int		len;
	char	*head;
	char	*token_str;

	skip_whitespace(str, &head);
	if (**str && **str == DOUBLE_QUOTE)
		find_end_pos(str, DOUBLE_QUOTE);
	else if (**str && **str == SINGLE_QUOTE)
		find_end_pos(str, SINGLE_QUOTE);
	else
		without_quote_parse(str);
	len = *str - head;
	if (len > 0)
	{
		token_str = ft_substr(head, 0, len);
		token_addback(&g_ms.token, init_token(token_str, STRING), 0);
	}
}
