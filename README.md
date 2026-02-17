# my_xxd

Just me trying to re-implement the classic `xxd` tool in C++ as a way to learn the language better.

`xxd` is that handy little utility that turns binary files into readable hex + ASCII dumps (the kind you see when reverse-engineering stuff or debugging binary formats).

This is **not** trying to be a 1:1 drop-in replacement i did not even implemented flags — it's mostly me practicing file I/O, formatting output nicely, and not going insane seeing my code is 4x slower than xxd which is not even that crazily optimized 😅.

## What it currently does

Reads a file (or stdin) and prints a hexdump with:

- address column
- hex bytes (usually 16 per line)
- ASCII representation on the right
- some basic spacing and alignment

Very similar output style to classic `xxd`.

## Building

You need CMake and a C++17 (or later) compiler.

```bash
# from the project root
mkdir build && cd build
cmake ..
make
```

The binary ends up as `build/my_xxd` (or `build/my_xxd.exe` on Windows).

## Usage

```bash
# Basic usage
./my_xxd example.bin
```
Right now it does not  not support flags.  
I'm adding things slowly as I learn.

## Planned / maybe someday

- Flags parsing
-  performance enhancements
- implentation of -r flag

## License

Unlicense / public domain / do-whatever-you-want — pick your favorite zero-clause license.

Feel free to steal code, ideas, or just point and laugh at my terrible C++ style. PRs welcome if you want to teach me something.

Happy hacking!  
SquiggleKernel

