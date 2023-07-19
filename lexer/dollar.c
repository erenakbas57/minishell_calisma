/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:55:44 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:23:03 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon "c" değişkeninin geçerli bir operatör olarak kullanılıp 
kullanılamayacağını kontrol etmek için kullanılır. Fonksiyon, "c" 
değişkeninin a-z, A-Z, 0-9, _ veya ? içermesi durumunda 1, aksi durumda 0 döndürür.
*/
int	valid_op(char c)
{
	return ((c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z') || \
			(c >= '0' && c <= '9') || \
			(c == '_') || (c == '?'));
}

/*
Bu fonksiyon bir verilen string (`str`) içindeki `$` işaretinin doğru kullanılıp 
kullanılmadığını kontrol eder. Fonksiyon, string içinde gezinerek tek tırnak ve 
çift tırnak kullanımını takip eder. Eğer `$` işareti ile takip eden karakter 
geçerli bir operatör değilse veya `$` işareti tek tırnak içindeyse fonksiyon 
`FALSE` döndürür. Aksi durumda fonksiyon `TRUE` döndürür.
*/
int	check_dollar(char *str)
{
	int		i;
	int		single_quote;
	int		double_quote;

	i = 0;
	single_quote = TRUE;
	double_quote = FALSE;
	while (str[i] && str[i] != DOLLAR_OP)
	{
		if (str[i] == SINGLE_QUOTE)
			single_quote = double_quote;
		if (str[i] == DOUBLE_QUOTE)
			double_quote = !double_quote;
		i++;
	}
	if (!valid_op(*(ft_strchr(str, DOLLAR_OP) + 1)))
		return (FALSE);
	return (single_quote);
}

/*
Bu fonksiyon, verilen string (`str`) içindeki bir karakter dizisini (`type`) bulur 
ve bu diziyi sınırlandıran ilk pozisyon (`first`) ile son pozisyon (`*pos`) arasındaki 
kısmı, `ft_substr` fonksiyonu ile ayıklar. Döndürülen kısım, `data` değişkenine atanır 
ve `*pos` değişkeni, karakter dizisinin son pozisyonunu belirtir.
*/
static char	*get_str(char *str, int	*pos, int type)
{
	int		first;
	char	*data;

	first = *pos;
	while (str[*pos] != type)
		(*pos)++;
	data = ft_substr(str, first, *pos - first);
	(*pos)++;
	return (data);
}

/*
Bu fonksiyon, verilen string (`str`) içindeki `$` işareti ve bu işareti takip eden 
operatörü (örneğin, `$PATH`) kullanılarak bir ortam değişkenini (environment variable) 
çözmeyi amaçlar. İlk olarak `get_str` fonksiyonu ile `str` içindeki `$` işareti bulunur 
ve `result` değişkenine atanır. Eğer `$` işareti takip eden karakter `?` ise, `errno` 
değişkeninin değeri `ft_itoa` fonksiyonu ile string olarak alınır ve `result` değişkenine 
eklenir. Aksi durumda, `valid_op` fonksiyonu ile belirlenen geçerli bir operatör bulunur 
ve bu operatör ile ilişkili ortam değişkeni `get_env` fonksiyonu ile alınır. Son olarak, 
`get_str` fonksiyonu ile stringin geri kalan kısmı `result` değişkenine eklenir ve `result` 
değişkeni döndürülür.
*/
char	*parse_dollar_op(char *str)
{
	int		i;
	int		first;
	char	*env;
	char	*result;
	char	*data;

	i = 0;
	result = NULL;
	data = get_str(str, &i, DOLLAR_OP);
	push_new_str(&result, data);
	first = i;
	if (str[i] == '?' && ++i)
		push_new_str(&result, ft_itoa(errno));
	else
	{
		while (valid_op(str[i]))
			(i)++;
		data = ft_substr(str, first, i - first);
		env = get_env(data);
		push_new_str(&result, env);
		free(data);
	}
	data = get_str(str, &i, 0);
	push_new_str(&result, data);
	return (result);
}

/*
Bu fonksiyon, verilen string (`str`) içindeki `$` işaretlerini ve bu 
işaretleri takip eden operatörleri (örneğin, `$PATH`) çözmek için `parse_dollar_op` 
fonksiyonunu kullanır. `check_dollar` fonksiyonu ile `$` işaretinin geçerli bir 
operatör ile ilişkili olup olmadığı kontrol edilir. Eğer `$` işareti geçerli bir 
operatör ile ilişkiliyse, `parse_dollar_op` fonksiyonu ile bu operatör çözülür ve 
`new_str` değişkenine atanır. Bu işlem tekrar edilir ve eğer `$` işareti yoksa 
veya `$` işareti geçerli bir operatör ile ilişkili değilse, `new_str` değişkeni 
döndürülür.
*/
char	*dollar(char *str)
{
	char	*tmp;
	char	*new_str;

	new_str = ft_strdup(str);
	while (ft_strchr(new_str, DOLLAR_OP) && check_dollar(new_str))
	{
		tmp = new_str;
		new_str = parse_dollar_op(new_str);
		free(tmp);
	}
	return (new_str);
}
