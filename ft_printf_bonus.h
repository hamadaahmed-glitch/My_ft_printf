
#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_flags
{
	int		minus;
	int		zero;
	int		dot;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	char	spec;
}	t_flags;

int		ft_printf(const char *format, ...);
void	ft_init_flags(t_flags *flags);
int		ft_parse(const char *format, int *i, t_flags *flags);

int		ft_isdigit(int c);
int		ft_putchar_len(char c);
int		ft_putstr_len(char *s, int len);
int		ft_print_padding(int len, char c);

int		ft_print_char_bonus(char c, t_flags flags);
int		ft_print_percent_bonus(t_flags flags);
int		ft_print_str_bonus(char *str, t_flags flags);
int		ft_print_nbr_bonus(int n, t_flags flags);
int		ft_print_unsigned_bonus(unsigned int n, t_flags flags);
int		ft_print_hex_bonus(unsigned int n, t_flags flags);
int		ft_print_ptr_bonus(uintptr_t ptr, t_flags flags);

#endif