# my\_xxd 

A fast C++ rewrite of the classic `xxd` utility - it is not 1 to 1 replica port to cpp it is learning project.

## The backstory

This started as a simple exercise to get comfortable with C++ file I/O. Then I noticed it was slow. Then I started reading about and checking that my programme spending all its time either doing std-out or formatting. 

The core idea: instead of relying on either of `printf`, `std::cout`, `std::format` or `iomanip library` to build each line, I write hex and ASCII characters directly into a pre-allocated buffer using lookup tables and bitshifts. Turns out, it results in 20-35x performance improvement when compared to `std::format_to`.

## How fast is it?

Benchmarked on a 10 GiB file (CachyOS, Ryzen 7):

| Tool               | Time (10 GiB) | Speedup | IPC |
|--------------------|--------------|---------|-----|
| Original vim `xxd` | ~97.2s | 1.0x | 2.9 |
| `my_xxd`           | ~16.7s | **5.8x** | 4.9 |

Before starting this project I would never even known the names of tools like `perf`, `hyperfine`, `strace`. It helped me a lot in figuring out where my code losing time.

The IPC number (Instructions Per Cycle) is the part I'm most proud of. Getting to 4.9 means the CPU pipeline is almost never sitting idle.

> Things to note that my_xxd currently do not support 64 bit offset. Currently limited to 32bits. If you go above it overflows. So, max file size currently supported is `4GiB`.

## What's actually making it fast

**Zero-copy formatting** — no `printf`, no `std::format`, no temporary strings. Bytes go straight into the output buffer as hex characters and finally written using `std::cout.write()`.

**Pre-allocated buffers** — memory is allocated once upfront, not per-line or per-chunk.

## Current limitation — file size

Right now, `my_xxd` uses **32-bit offsets**, which means it works correctly on files **up to ~4 GiB**. Feeding it anything larger will produce wrong offset values in the output (the hex dump itself will be fine, but the address column will wrap around).

64-bit offset support is actively being worked on — it's on the roadmap and will land soon. For now, just be aware of that.

## Building

You'll need CMake and a C++20-compatible compiler.

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

For maximum performance, also add `-O3 -march=native` to your CMake config — this lets the compiler take full advantage of your specific CPU's instruction set.

## Usage

```bash
# Hex dump a file
./my_xxd example.bin

# Benchmark against the original
hyperfine './my_xxd big_file.bin > /dev/null' 'xxd big_file.bin > /dev/null'
```

## Roadmap

- [x] Direct-write buffer formatting
- [x] Hex conversion via LUT and bitshifts
- [ ] 64-bit offset support *(in progress — 4 GiB limit for now)*
- [ ] `mmap` support *(to push past the 16s barrier)*
- [ ] Flag parsing (`-c` for column count, `-p` for plain hex)
- [ ] Reverse mode (`-r`)

## License

The Unlicense — public domain, do whatever you want with it.

Happy hacking! — SquiggleKernel