
#include "ft_printf_bonus.h"

int	ft_print_char_bonus(char c, t_flags flags)
{
	int	count;

	count = 0;
	if (!flags.minus && flags.width > 1)
		count += ft_print_padding(flags.width - 1, ' ');
	count += ft_putchar_len(c);
	if (flags.minus && flags.width > 1)
		count += ft_print_padding(flags.width - 1, ' ');
	return (count);
}

int	ft_print_percent_bonus(t_flags flags)
{
	int		count;
	char	pad;

	count = 0;
	pad = ' ';
	if (flags.zero && !flags.minus)
		pad = '0';
	if (!flags.minus && flags.width > 1)
		count += ft_print_padding(flags.width - 1, pad);
	count += ft_putchar_len('%');
	if (flags.minus && flags.width > 1)
		count += ft_print_padding(flags.width - 1, ' ');
	return (count);
}