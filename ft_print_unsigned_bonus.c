
#include "ft_printf_bonus.h"

static int	ft_unbr_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_putunbr_rec(unsigned int n)
{
	if (n >= 10)
		ft_putunbr_rec(n / 10);
	ft_putchar_len((n % 10) + '0');
}

int	ft_print_unsigned_bonus(unsigned int n, t_flags flags)
{
	int	len;
	int	zeros;
	int	count;

	count = 0;
	len = ft_unbr_len(n);
	if (n == 0 && flags.dot && flags.precision == 0)
		len = 0;
	zeros = 0;
	if (flags.precision > len)
		zeros = flags.precision - len;
	else if (flags.zero && flags.width > len)
		zeros = flags.width - len;
	if (!flags.minus && flags.width > len + zeros)
		count += ft_print_padding(flags.width - len - zeros, ' ');
	count += ft_print_padding(zeros, '0');
	if (len > 0)
		ft_putunbr_rec(n);
	if (flags.minus && flags.width > len + zeros)
		count += ft_print_padding(flags.width - len - zeros, ' ');
	return (count + len);
}