
#include "ft_printf_bonus.h"

static int	ft_nbr_len(long long n)
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

static void	ft_putnbr_rec(long long n)
{
	if (n >= 10)
		ft_putnbr_rec(n / 10);
	ft_putchar_len((n % 10) + '0');
}

static int	ft_get_sign(long long *nb, t_flags flags, char *sign)
{
	*sign = 0;
	if (*nb < 0)
	{
		*sign = '-';
		*nb = -(*nb);
	}
	else if (flags.plus)
		*sign = '+';
	else if (flags.space)
		*sign = ' ';
	return (*sign != 0);
}

int	ft_print_nbr_bonus(int n, t_flags flags)
{
	long long	nb;
	char		sign;
	int			len;
	int			zeros;
	int			count;

	nb = n;
	count = 0;
	ft_get_sign(&nb, flags, &sign);
	len = ft_nbr_len(nb);
	if (nb == 0 && flags.dot && flags.precision == 0)
		len = 0;
	zeros = 0;
	if (flags.precision > len)
		zeros = flags.precision - len;
	else if (flags.zero && flags.width > len + (sign != 0))
		zeros = flags.width - len - (sign != 0);
	if (!flags.minus && flags.width > len + zeros + (sign != 0))
		count += ft_print_padding(flags.width - len - zeros - (sign != 0), ' ');
	if (sign)
		count += ft_putchar_len(sign);
	count += ft_print_padding(zeros, '0');
	if (len > 0)
		ft_putnbr_rec(nb);
	if (flags.minus && flags.width > len + zeros + (sign != 0))
		count += ft_print_padding(flags.width - len - zeros - (sign != 0), ' ');
	return (count + len);
}