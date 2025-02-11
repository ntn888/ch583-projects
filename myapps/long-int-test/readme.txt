Discrepancy of `long int` between llvm and gcc in riscv32

I do not know if this is a bug or intended (I'm missing a flag). But in gcc `unsigned long` expands to `uint32_t` while in llvm it doesn't.

```
#include <stdint.h>

void test (uint32_t i);

void test (unsigned long j);

int main (void) {}
```

`riscv64-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c` success compile

`clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c`:

```
main.c:5:6: error: conflicting types for 'test'
    5 | void test (unsigned long j);
      |      ^
main.c:3:6: note: previous declaration is here
    3 | void test (uint32_t i);
      |      ^
1 error generated.
```

I can see gcc is correct according to:

>In both RV32 and RV64 C compilers, the C type int is 32 bits wide. longs and pointers, on the other hand, are both as wide as a integer register, so in RV32, both are 32 bits wide, while in RV64, both are 64 bits wide.

Am I missing a flag? Thank you.

clangd version 19.1.7


--------------------------------------

After further experimentation I found it to be a discrepancy issue of `unsigned long` size between llvm and gcc in riscv32.

It states in the riscv spec

>In both RV32 and RV64 C compilers, the C type int is 32 bits wide. longs and pointers, on the other hand, are both as wide as a integer register, so in RV32, both are 32 bits wide, while in RV64, both are 64 bits wide.

So trying out the following code:

```
#include <stdint.h>

void test (uint32_t i);

void test (unsigned long j);

int main (void) {}
```

`riscv64-elf-gcc -march=rv32imac_zicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c` success compile

`clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c`:

```
main.c:5:6: error: conflicting types for 'test'
    5 | void test (unsigned long j);
      |      ^
main.c:3:6: note: previous declaration is here
    3 | void test (uint32_t i);
      |      ^
1 error generated.
```

I can see gcc is correct according to the spec. But why is clangd not?

I'm following this up here because it looks like a basic specification comparison.

Thank you.

=========================

clangd --query-driver=/usr/bin/riscv64-linux-gnu-gcc --clang-tidy --check=src/main.c

/StdPeriphDriver/inc/CH583SFR.h:57:#ifndef UINT32
./StdPeriphDriver/inc/CH583SFR.h:58:typedef unsigned long           UINT32;

=========================

clang -c --target=riscv32-esp-elf -march=rv32imc_zicsr_zifencei -mabi=ilp32 -o out main.c

clang -c -target riscv32imac-unknown-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c
clang -c -target riscv32imac-unknown-none-elf -o out main.c

clang -c -target riscv32-none-elf -march=rvi20u32_zicsr -mabi=ilp32 -msmall-data-limit=8 -o out main.c

===

--stdlib=/usr/riscv64-elf/include
-I/usr/riscv64-elf/include

clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -nostdinc -o out main.c

clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -nostdinc -I/usr/riscv64-elf/include -o out main.c
--

clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 --with-sysroot=/usr/riscv64-elf -o out main.c

--

clang -c -target riscv32-none-elf -march=rv32imaczicsr -mabi=ilp32 -msmall-data-limit=8 -nostdinc -I/usr/riscv64-elf/include -I/usr/riscv64-elf/include/machine -I/usr/riscv64-elf/include/newlib-nano -I/usr/riscv64-elf/include/ssp -I/usr/riscv64-elf/include/sys -o out main.c

-I/usr/riscv64-elf/include/machine -I/usr/riscv64-elf/include/newlib-nano -I/usr/riscv64-elf/include/ssp -I/usr/riscv64-elf/include/sys
