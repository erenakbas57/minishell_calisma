/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makbas <makbas@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:14:16 by btekinli          #+#    #+#             */
/*   Updated: 2023/07/19 13:06:00 by makbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Bu fonksiyon, verilen bir karakterin boşluk veya sekme 
olup olmadığını kontrol eder ve eğer boşluk veya sekme 
ise 1, değilse 0 değerini döndürür.
*/
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}
