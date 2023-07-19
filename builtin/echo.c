/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:23:12 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 14:14:07 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon girdi olarak aldığı karakter dizisini çıktı olarak yazdırır. İşlevi, 
her bir karakteri tek tek yazdırarak, girdi olarak verilen diziyi çıktıya yazmaktır.
*/
void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

/*
`skip_flag` fonksiyonu, bir argüman dizisinin "-n" içerip içermediğini kontrol eder ve 
"-n" var ise kaç tane "-n" olduğunu sayar. Eğer "-n" var ise, fonksiyon dizinin "-n"'den 
sonraki elemanına gösterilen indeksi döndürür.
*/
int	skip_flag(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_strcmp(str[i], "-n"))
			i++;
		else
			break ;
	}
	return (i);
}

/*
Bu fonksiyon `echo` komutunun işlemesini yapar. `input` parametresi `echo` komutu ile birlikte 
verilen argümanları içerir. Fonksiyon, argümanları yazdırır ve `-n` flag'inin bulunup bulunmadığına 
göre yazdırılan metnin sonunda bir satır başı karakteri ekler veya eklemez. `is_parent()` 
fonksiyonunun çıktısına göre çalışma durumu değerlendirilir ve uygun olduğu durumlarda program 
`exit` fonksiyonu ile sonlanır.
*/
void	builtin_echo(char **input)
{
	int	i;
	int	flag;

	i = 1;
	flag = TRUE;
	i = skip_flag(input);
	if (i > 1)
		flag = FALSE;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	if (!is_parent())
		exit(EXIT_SUCCESS);
}
