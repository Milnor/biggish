# biggish

Big numbers library. I need to implement some of this functionality in `x86_64`
assembly at work, so first I want to wrap my head around it in C.

## Why only BIG-ish?

At this point, arbitrary size isn't needed. That could be a later enhancement,
but supporting types `uint256_t` and `uint512_t` will suffice for now.

## Building

This project uses CMake and is set up for out-of-source builds. That means
CMake puts all generated build files in a separate directory, usually `build/`,
instead of mixing them into the source tree.

Ubuntu 22.04 ships CMake 3.22, and this project only requires that version even
though newer versions such as 3.28.3 also work.

### Debug build

Use a debug build while developing:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/biggish
```

The `-S .` option tells CMake that the source tree is the current directory.
The `-B build` option tells CMake to put generated files in the `build/`
directory.

### Release build

Use a release build when you want compiler optimizations:

```sh
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
./build-release/biggish
```

Keeping debug and release builds in separate directories lets you switch between
them without reconfiguring the same build directory over and over.

### Choosing the limb size

The `LIMB_SIZE` CMake variable can be `32` or `64`. If you do not pass it,
CMake uses `32`.

For a 32-bit limb build:

```sh
cmake -S . -B build-32 -DCMAKE_BUILD_TYPE=Debug -DLIMB_SIZE=32
cmake --build build-32
./build-32/biggish
```

For a 64-bit limb build:

```sh
cmake -S . -B build-64 -DCMAKE_BUILD_TYPE=Debug -DLIMB_SIZE=64
cmake --build build-64
./build-64/biggish
```

If you change `LIMB_SIZE` for an existing build directory, run the `cmake -S ...
-B ...` configure command again before rebuilding.

## Design Plan

* [ ] Support "limb" sizes of 32-bit and 64-bit

* [ ] Implement `uint256_t` and `uint512_t` structs

* [ ] Write `add()` functions supporting these types

* [ ] Write `multiply()` functions supporting these types

* [ ] Write `division()` functions...

* [ ] Implement decimal string conversion to support printing big integers

### Sensible things that aren't needed yet

* [ ] A `subtract()` function

* [ ] Arbitrary sizes with automatic (re)-allocation

* [ ] Signed integers

* [ ] Floats

**Note to self:**

GMP does something kinda clever:

```C
typedef struct
{
  int _mp_alloc;                /* Number of *limbs* allocated and pointed
                                   to by the _mp_d field.  */
  int _mp_size;                 /* abs(_mp_size) is the number of limbs the
                                   last field points to.  If _mp_size is
                                   negative this is a negative number.  */
  mp_limb_t *_mp_d;             /* Pointer to the limbs.  */
} __mpz_struct;
```

Hint: `sudo apt install libgmp-dev` and pull up
`/usr/include/x86_64-linux-gnu/gmp.h`.

The `_mp_alloc` field lets you know in advance if reallocation will be needed
for a given operation and `_mp_size` lets you know the signedness of the
integer while simultaneously telling you the number of allocated limbs
actually in use.
