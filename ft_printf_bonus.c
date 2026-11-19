
#include "ft_printf_bonus.h"

static int	ft_dispatch(va_list args, t_flags flags)
{
	if (flags.spec == 'c')
		return (ft_print_char_bonus(va_arg(args, int), flags));
	if (flags.spec == 's')
		return (ft_print_str_bonus(va_arg(args, char *), flags));
	if (flags.spec == 'p')
		return (ft_print_ptr_bonus(va_arg(args, uintptr_t), flags));
	if (flags.spec == 'd' || flags.spec == 'i')
		return (ft_print_nbr_bonus(va_arg(args, int), flags));
	if (flags.spec == 'u')
		return (ft_print_unsigned_bonus(va_arg(args, unsigned int), flags));
	if (flags.spec == 'x' || flags.spec == 'X')
		return (ft_print_hex_bonus(va_arg(args, unsigned int), flags));
	if (flags.spec == '%')
		return (ft_print_percent_bonus(flags));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_flags	flags;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_parse(format, &i, &flags);
			count += ft_dispatch(args, flags);
		}
		else
			count += ft_putchar_len(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}