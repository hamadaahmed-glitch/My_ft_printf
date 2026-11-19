*This project has been created as part of the 42 curriculum by hait-h-m.*

# ft_printf (Mandatory + Bonus)

## Description
The **ft_printf** project is an essential milestone in the 42 curriculum. Its primary objective is to recode the standard C library function `printf()`. Through this project, we explore variadic functions in C using macros provided by `<stdarg.h>`, as well as formatted string parsing, flag precedence, and field width/precision mechanics.

### Conversions Handled
- `%c`: Prints a single character.
- `%s`: Prints a string of characters (outputs `(null)` if pointer is `NULL`).
- `%p`: Prints a `void *` pointer memory address in hexadecimal format (outputs `(nil)` if `NULL` on Linux).
- `%d`: Prints a signed decimal integer (base 10).
- `%i`: Prints a signed integer in base 10.
- `%u`: Prints an unsigned decimal integer (base 10).
- `%x`: Prints an unsigned number in lowercase hexadecimal (base 16).
- `%X`: Prints an unsigned number in uppercase hexadecimal (base 16).
- `%%`: Prints a literal percent sign.

### Bonus Features Handled
- **`-` (Left-align)**: Left-justifies the output within the given field width (pads with spaces to the right).
- **`0` (Zero-padding)**: Pads the field with leading zeros instead of spaces.
- **`.` (Precision)**:
  - For integers (`%d`, `%i`, `%u`, `%x`, `%X`): Sets minimum digit count; pads with leading zeros. (If precision is `0` and value is `0`, no digits are output).
  - For strings (`%s`): Sets maximum number of characters to display.
- **Minimum Field Width**: Ensures the conversion output occupies at least the specified number of columns.
- **`#` (Alternate form)**:
  - `%x`: Prefixes non-zero results with `0x`.
  - `%X`: Prefixes non-zero results with `0X`.
- **`+` (Force Sign)**: Prefixes positive signed conversions (`%d`, `%i`) with a `+`.
- **` ` (Space Flag)**: Prefixes positive signed conversions (`%d`, `%i`) with a space if no sign is written.

The function returns the total number of characters successfully written to standard output.

---

## Instructions

### Compilation
The project uses a standard `Makefile` compiling with `cc` and the flags `-Wall -Wextra -Werror`.

- To build the **mandatory** library:
  ```bash
  make
  ```
- To build the **bonus** library:
  ```bash
  make bonus
  ```

### Makefile Rules
- `make` / `make all`: Compiles mandatory files into `libftprintf.a`.
- `make bonus`: Compiles bonus files (`*_bonus.c`) and archives them into `libftprintf.a` without unnecessary relinking.
- `make clean`: Removes intermediate object files (`*.o`).
- `make fclean`: Removes object files and the static library `libftprintf.a`.
- `make re`: Rebuilds the library from scratch (`fclean` followed by `all`).

### Usage Example
Create a `main.c` file to test flags and bonus features:

```c
#include "ft_printf_bonus.h"

int	main(void)
{
	int	count;

	count = ft_printf("|%-10.5d| |%#8x| |%+d| |% 10s|\n", 42, 255, 42, "42");
	ft_printf("Characters printed: %d\n", count);
	return (0);
}
```

Compile and run:
```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
./test_printf
```

---

## Algorithm and Data Structure Justification

### Data Structures
1. **`va_list` (Call Stack Stream)**:
   Variadic arguments are extracted sequentially from the ABI argument registers and stack using `va_start`, `va_arg`, and `va_end`.
2. **Flag Container (`t_flags`)**:
   A dedicated structure aggregates parsed attributes for each conversion specifier:
   ```c
   typedef struct s_flags
   {
       int   minus;       // '-' flag
       int   zero;        // '0' flag
       int   dot;         // '.' presence
       int   hash;        // '#' flag
       int   space;       // ' ' flag
       int   plus;        // '+' flag
       int   width;       // Minimum field width
       int   precision;   // Value precision
       char  spec;        // Conversion specifier character
   }   t_flags;
   ```
   Passing this structure by value guarantees clean separation between tokenizer and formatters while strictly respecting 42's limit on function parameters (max 4 per function).

### Chosen Algorithm: Parsing State Resolution & Modular Dispatch

1. **Deterministic Flag Parsing ($O(K)$ per token)**:
   The format string is read linearly. Upon encountering `%`, a parser sub-loop extracts zero or more flags, the minimum width digits, and precision digits until a conversion specifier is reached.
2. **Precedence Resolution**:
   POSIX standard conflict rules are resolved immediately after parsing:
   - `-` overrides `0` (left alignment disables zero padding).
   - `+` overrides `' '` (explicit sign takes priority over leading blank).
   - Precision on numeric conversions (`%d`, `%i`, `%u`, `%x`, `%X`) disables `0` padding.
3. **Width and Padding Arithmetic**:
   Instead of dynamically allocating strings or using intermediate buffers, the print routines compute exact content length first (digits, signs, prefixes). Padding lengths (spaces vs. zeros) are determined beforehand, allowing direct unbuffered output to stdout in order:
   `[Leading Spaces] -> [Sign / Prefix] -> [Precision Zeros] -> [Value Digits] -> [Trailing Spaces]`
4. **Recursion for Base Conversion**:
   Numeric values are recursively converted base-by-base (`base 10` or `base 16`). This avoids reverse-buffer arrays and dynamic heap allocation (`malloc`/`free`), eliminating any risk of memory leaks. Maximum recursion depth is physically bounded by variable bit-width (at most 10 frames for 32-bit `int`, 16 frames for 64-bit pointers).

---

## Resources

### Classic References
- **Man Pages**:
  - `man 3 printf` — Complete POSIX specification for conversion flags, width, and precision.
  - `man 3 stdarg` — Variable argument lists macros.
  - `man 2 write` — Direct kernel system call for stdout output.
- **Literature**:
  - *The C Programming Language* (Kernighan & Ritchie) — Chapter on Variadic Functions and Formatted Output.

### AI Usage
AI tools were consulted during the project strictly for:
- Verifying POSIX specification precedence rules (e.g., interaction between `.`, `0`, and `-` on numeric conversions).
- Testing edge cases: zero value with zero precision (`%.0d` with `0`), pointer conversions (`%p`) printing `(nil)` on Linux glibc, and string precision truncations.
- Designing a Makefile structure using a hidden sentinel file (`.bonus`) to ensure `make bonus` satisfies the 42 requirement of preventing unnecessary relinks.
