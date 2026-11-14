*This project has been created as part of the 42 curriculum by hait-h-m.*

# ft_printf

## Description
The **ft_printf** project is an essential milestone in the 42 curriculum. Its primary objective is to recode the standard C library function `printf()`. Through this project, we explore the mechanisms of variadic functions in C using macros provided by `<stdarg.h>`.

The function implements direct unbuffered output to stdout and handles the following format specifiers:
- `%c`: Prints a single character.
- `%s`: Prints a string of characters (prints `(null)` if pointer is `NULL`).
- `%p`: Prints a `void *` pointer memory address in hexadecimal format (prints `(nil)` if `NULL`).
- `%d`: Prints a signed decimal integer (base 10).
- `%i`: Prints a signed integer in base 10.
- `%u`: Prints an unsigned decimal integer (base 10).
- `%x`: Prints a number in lowercase hexadecimal (base 16).
- `%X`: Prints a number in uppercase hexadecimal (base 16).
- `%%`: Prints a literal percent sign.

The function returns the total number of characters successfully written to the standard output.

---

## Instructions

### Compilation
The project uses a standard `Makefile` compiling with `cc` and the `-Wall -Wextra -Werror` flags.

To build the static library `libftprintf.a`:
```bash
make
```

### Makefile Rules
- `make` or `make all`: Compiles the source files and creates the library `libftprintf.a`.
- `make clean`: Removes the intermediate object files (`*.o`).
- `make fclean`: Removes the object files and the generated `libftprintf.a` library.
- `make re`: Performs a complete rebuild (`fclean` followed by `all`).

### Usage Example
Create a `main.c` file to test the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	count;

	count = ft_printf("Hello, %s! Value: %d, Hex: %x, Pointer: %p\n", 
		"42", 42, 255, (void *)0);
	ft_printf("Printed characters: %d\n", count);
	return (0);
}
```

Compile and link against `libftprintf.a`:
```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o test_printf
./test_printf
```

---

## Algorithm and Data Structure Justification

### Data Structure: Linear Stream & Call Stack
- **Variadic Arguments (`va_list`)**: The arguments are sequentially read from the execution stack through the standard `va_start`, `va_arg`, and `va_end` macros.
- **No Dynamic Heap Allocation**: No linked lists, arrays, or heap allocations (`malloc`/`free`) are used. By utilizing the program's runtime call stack for recursive number conversions, heap memory leaks are completely prevented.

### Chosen Algorithm: Linear Scan with Recursive Conversion
1. **Dispatcher Pattern (Linear Scan - $O(N)$)**:
   The format string is traversed character by character. When a `%` character is encountered, the subsequent character determines the conversion type and dispatches to the corresponding modular helper function. This keeps code decoupled, maintainable, and compliant with 42 code length standards.
2. **Recursive Numeric Conversion ($O(\log_{base} N)$)**:
   For conversions involving bases (base 10 for `%d`, `%i`, `%u` and base 16 for `%x`, `%X`, `%p`), recursion is used to divide numbers until the most significant digit is reached, then digits are output sequentially as the call stack unwinds. 
   - **Stack Depth**: The maximum recursion depth is bounded to at most 10 frames for 32-bit integers and 16 frames for 64-bit pointers, which is negligible in terms of memory overhead and avoids reverse-string buffer management.
   - **Edge Cases**: Underflow issues like `INT_MIN` (`-2147483648`) are explicitly caught and output as literal strings to avoid undefined integer negation behaviors.

---

## Resources

### Classic References
- **Man Pages**:
  - `man 3 printf` — Description and conversion specifications of standard `printf`.
  - `man 3 stdarg` — Handling variable argument lists (`va_list`, `va_start`, `va_arg`, `va_end`).
  - `man 2 write` — Unix system call for unbuffered output to file descriptors.
- **Documentation**:
  - [C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language) - Chapter on Variadic Functions.

### AI Usage
AI tools were consulted during the project strictly for:
- Understanding the portability of `%p` output formatting between OS platforms (confirming `(nil)` behavior for Linux/glibc vs `0x0` on Darwin/macOS).
- Reviewing edge-case handling for integer minimum limits (`INT_MIN`) and `NULL` pointer protections for `%s` and `%p`.
- Validating Makefile syntax and non-relinking rules against the 42 Norm guidelines.