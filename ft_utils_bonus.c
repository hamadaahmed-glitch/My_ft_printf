/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-h-m <hait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by hait-h-m          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by hait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_putchar_len(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr_len(char *s, int len)
{
	return (write(1, s, len));
}

int	ft_print_padding(int len, char c)
{
	int	count;

	count = 0;
	while (len > 0)
	{
		count += ft_putchar_len(c);
		len--;
	}
	return (count);
}