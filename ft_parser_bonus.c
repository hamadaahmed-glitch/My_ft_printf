
#include "ft_printf_bonus.h"

void	ft_init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->dot = 0;
	flags->hash = 0;
	flags->space = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->spec = 0;
}

static void	ft_parse_flags(const char *format, int *i, t_flags *flags)
{
	while (format[*i] == '-' || format[*i] == '0' || format[*i] == '#'
		|| format[*i] == ' ' || format[*i] == '+')
	{
		if (format[*i] == '-')
			flags->minus = 1;
		else if (format[*i] == '0')
			flags->zero = 1;
		else if (format[*i] == '#')
			flags->hash = 1;
		else if (format[*i] == ' ')
			flags->space = 1;
		else if (format[*i] == '+')
			flags->plus = 1;
		(*i)++;
	}
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
}

static void	ft_parse_width_prec(const char *format, int *i, t_flags *flags)
{
	while (ft_isdigit(format[*i]))
	{
		flags->width = flags->width * 10 + (format[*i] - '0');
		(*i)++;
	}
	if (format[*i] == '.')
	{
		flags->dot = 1;
		(*i)++;
		while (ft_isdigit(format[*i]))
		{
			flags->precision = flags->precision * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
}

int	ft_parse(const char *format, int *i, t_flags *flags)
{
	ft_init_flags(flags);
	ft_parse_flags(format, i, flags);
	ft_parse_width_prec(format, i, flags);
	flags->spec = format[*i];
	if (flags->dot && (flags->spec == 'd' || flags->spec == 'i'
			|| flags->spec == 'u' || flags->spec == 'x' || flags->spec == 'X'))
		flags->zero = 0;
	return (1);
}