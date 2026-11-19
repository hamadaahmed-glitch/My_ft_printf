/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hait-h-m <hait-h-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by hait-h-m          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by hait-h-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_print_str_bonus(char *str, t_flags flags)
{
	int	count;
	int	len;

	count = 0;
	if (!str)
	{
		if (flags.dot && flags.precision < 6)
			str = "";
		else
			str = "(null)";
	}
	len = ft_strlen(str);
	if (flags.dot && flags.precision < len)
		len = flags.precision;
	if (!flags.minus && flags.width > len)
		count += ft_print_padding(flags.width - len, ' ');
	count += ft_putstr_len(str, len);
	if (flags.minus && flags.width > len)
		count += ft_print_padding(flags.width - len, ' ');
	return (count);
}