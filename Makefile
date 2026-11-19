NAME        = libftprintf.a

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs
RM          = rm -f

SRCS        = ft_printf.c \
              ft_print_char.c \
              ft_print_str.c \
              ft_print_ptr.c \
              ft_print_nbr.c \
              ft_print_unsigned.c \
              ft_print_hex.c

SRCS_BONUS  = ft_printf_bonus.c \
              ft_parser_bonus.c \
              ft_utils_bonus.c \
              ft_print_char_bonus.c \
              ft_print_str_bonus.c \
              ft_print_nbr_bonus.c \
              ft_print_unsigned_bonus.c \
              ft_print_hex_bonus.c \
              ft_print_ptr_bonus.c

OBJS        = $(SRCS:.c=.o)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS_BONUS)
	@touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS) .bonus

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus