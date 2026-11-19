
#include "ft_printf_bonus.h"

static int	ft_ptr_len(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr > 0)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

static void	ft_putptr_rec(uintptr_t ptr)
{
	if (ptr >= 16)
		ft_putptr_rec(ptr / 16);
	ft_putchar_len("0123456789abcdef"[ptr % 16]);
}

int	ft_print_ptr_bonus(uintptr_t ptr, t_flags flags)
{
	int	len;
	int	count;

	count = 0;
	if (!ptr)
	{
		if (!flags.minus && flags.width > 5)
			count += ft_print_padding(flags.width - 5, ' ');
		count += write(1, "(nil)", 5);
		if (flags.minus && flags.width > 5)
			count += ft_print_padding(flags.width - 5, ' ');
		return (count);
	}
	len = ft_ptr_len(ptr) + 2;
	if (!flags.minus && flags.width > len)
		count += ft_print_padding(flags.width - len, ' ');
	count += write(1, "0x", 2);
	ft_putptr_rec(ptr);
	if (flags.minus && flags.width > len)
		count += ft_print_padding(flags.width - len, ' ');
	return (count + len - 2);
}