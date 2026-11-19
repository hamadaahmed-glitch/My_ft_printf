
#include "ft_printf_bonus.h"

static int	ft_hex_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

static void	ft_puthex_rec(unsigned int n, char spec)
{
	char	*base;

	if (spec == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		ft_puthex_rec(n / 16, spec);
	ft_putchar_len(base[n % 16]);
}

static int	ft_print_prefix(unsigned int n, t_flags flags)
{
	if (flags.hash && n != 0)
	{
		if (flags.spec == 'X')
			return (write(1, "0X", 2));
		return (write(1, "0x", 2));
	}
	return (0);
}

int	ft_print_hex_bonus(unsigned int n, t_flags flags)
{
	int	len;
	int	p_len;
	int	zeros;
	int	count;

	count = 0;
	len = ft_hex_len(n);
	if (n == 0 && flags.dot && flags.precision == 0)
		len = 0;
	p_len = (flags.hash && n != 0) * 2;
	zeros = 0;
	if (flags.precision > len)
		zeros = flags.precision - len;
	else if (flags.zero && flags.width > len + p_len)
		zeros = flags.width - len - p_len;
	if (!flags.minus && flags.width > len + zeros + p_len)
		count += ft_print_padding(flags.width - len - zeros - p_len, ' ');
	count += ft_print_prefix(n, flags);
	count += ft_print_padding(zeros, '0');
	if (len > 0)
		ft_puthex_rec(n, flags.spec);
	if (flags.minus && flags.width > len + zeros + p_len)
		count += ft_print_padding(flags.width - len - zeros - p_len, ' ');
	return (count + len);
}