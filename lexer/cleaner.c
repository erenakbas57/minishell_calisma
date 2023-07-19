/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:51:54 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 15:58:17 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
belirtilen bir dizgiyi (str) bir diğer dizgine (new_str) ekleme işlevini 
yerine getirir. İlk olarak, new_str boşsa, str'nin kopyası olarak ayarlanır. 
Eğer new_str daha önce tanımlanmışsa, str new_str ile birleştirilir ve sonuç 
yeniden new_str'nin değerine atanır. Böylece, belirtilen dizgi, bir kez daha 
kullanılabilir olarak korunur.
*/
void	push_new_str(char **new_str, char *str)
{
	char	*tmp;

	if (!(*new_str))
	{
		*new_str = ft_strdup(str);
		free(str);
		return ;
	}
	tmp = *new_str;
	*new_str = ft_strjoin(*new_str, str);
	free(tmp);
	free(str);
}

/*
Bu fonksiyon, belirtilen karakter (type) ile çevrili olan metin dizisindeki 
metin parçalarını temizler ve temizlenen parçaları yeni bir metin dizisi olarak 
döndürür. Fonksiyonun girdisi olarak verilen "str" değişkenindeki metin içinde, 
belirtilen tip karakteri ile çevrili olan metin parçaları bulunur ve bu parçalar 
"new_str" adında yeni bir metin dizisi olarak oluşturulur. Aynı zamanda, işlenen 
metnin pozisyonu "pos" değişkeni ile güncellenir.
*/
char	*clean_quote_with_type(char *str, int *pos, char type)
{
	int		first;
	char	*new_str;

	(*pos)++;
	first = *pos;
	while (str[*pos] && str[*pos] != type)
		(*pos)++;
	new_str = ft_substr(str, first, *pos - first);
	if (str[*pos])
		(*pos)++;
	return (new_str);
}

/*
"get_str" isimli fonksiyon, belirtilen pozisyondan başlayarak metindeki en fazla 
tek tırnaklı veya çift tırnaklı metin bloğunu bulmaya çalışır. Bulduğu bu metin 
bloğunu döndürür ve "pos" parametresi ile verilen pozisyon değişkenini de günceller.
*/
static char	*get_str(char *str, int	*pos)
{
	int	first;

	first = *pos;
	while (str[*pos] && str[*pos] != DOUBLE_QUOTE && str[*pos] != SINGLE_QUOTE)
		(*pos)++;
	return (ft_substr(str, first, *pos - first));
}

/*
Bu fonksiyon, verilen bir dize içindeki çift veya tek tırnak karakterlerini temizlemek 
için kullanılır. Fonksiyon, metin içindeki tırnak karakterlerini algılar ve tırnakların 
içindeki metnin dışındaki herhangi bir şeyi temizler. Sonuç olarak, fonksiyon, tırnak 
karakterleri içindeki metin dışındaki her şeyin atılmasıyla oluşan temiz bir metin dizesi oluşturur.
*/
char	*clean_quote(char *str)
{
	int		i;
	char	*data;
	char	*result;

	i = 0;
	result = NULL;
	str = dollar(str);
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTE)
			data = clean_quote_with_type(str, &i, DOUBLE_QUOTE);
		else if (str[i] == SINGLE_QUOTE)
			data = clean_quote_with_type(str, &i, SINGLE_QUOTE);
		else
			data = get_str(str, &i);
		push_new_str(&result, data);
	}
	free(str);
	return (result);
}