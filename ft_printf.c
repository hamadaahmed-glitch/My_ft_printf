
#include "ft_printf.h"

static int	ft_format(va_list args, const char specifier)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (specifier == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (specifier == 'p')
		count += ft_print_ptr(va_arg(args, uintptr_t));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_print_nbr(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_print_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), specifier);
	else if (specifier == '%')
		count += ft_print_char('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
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
			count += ft_format(args, format[i]);
		}
		else
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}