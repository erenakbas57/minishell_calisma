/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:47:38 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:59:31 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Bu fonksiyon, belirtilen komutun bulunamadığı durumlar için bir hata mesajı oluşturmak 
için kullanılır. Eğer belirtilen komut bulunamazsa, `"minishell: [komut]: command not 
found"` şeklinde bir hata mesajı yazdırılır ve hata kodu 127 olarak atanır.
*/
void	command_err(char *str)
{
	errno = 127;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	if (!is_parent())
		exit(errno);
}

/*
Bu fonksiyon, belirtilen işlem tipine (redirection, pipe, here document gibi) göre syntax 
hatası olduğunu belirten bir hata mesajı yazdırır. Hata mesajı, standard hata çıkışına (STDERR, 
file descriptor #2) yazılır ve sonunda programın sonlandırılmasına neden olabilir.
*/
void	token_err(int type)
{
	char	*red;

	if (type == HERE_DOC)
		red = "<<";
	else if (type == RED_INPUT)
		red = "<";
	else if (type == RED_OUTPUT)
		red = ">";
	else if (type == RED_APPEND)
		red = ">>";
	else if (type == PIPE)
		red = "|";
	else
		red = "newline";
	errno = 258;
	write(2, "minishell: syntax error near unexpected token '", 47);
	write(2, red, ft_strlen(red));
	write(2, "'\n", 2);
}

/*
`directory_err` fonksiyonu, belirtilen dizinin bir dizin olduğunu ve bu nedenle çalıştırılamayacağı 
durumunda bir hata mesajı yazdırır. Eğer çalışan işlem bir child işlem değilse (parent process), 
`errno` değişkenini 126 olarak ayarlar ve çıkış yapar.
*/
void	directory_err(char *str)
{
	errno = 126;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": is a directory\n", 17);
	if (!is_parent())
		exit(errno);
}

/*
Bu fonksiyon, verilen dosya adı için "No such file or directory" hatasını raporlar. Eğer verilen dosya adı 
'/' içeriyorsa, 'errno' değişkenine 127 değeri atanır, değilse 1 değeri atanır. Daha sonra, hatayı "minishell:" 
ve dosya adıyla birlikte standard hata akışına (stderr) yazdırır. Eğer fonksiyonun çalıştığı işlem annesi değilse, 
program errno değerine göre çıkar.
*/
void	no_file_err(char *str)
{
	if (ft_strchr(str, '/'))
		errno = 127;
	else
		errno = 1;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
	if (!is_parent())
		exit(errno);
}
