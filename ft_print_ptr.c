
#include "ft_printf.h"

static int	ft_put_ptr(uintptr_t ptr)
{
	int	count;

	count = 0;
	if (ptr >= 16)
		count += ft_put_ptr(ptr / 16);
	count += ft_print_char("0123456789abcdef"[ptr % 16]);
	return (count);
}

int	ft_print_ptr(uintptr_t ptr)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_put_ptr(ptr);
	return (count);
}