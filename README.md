# biggish

Big numbers library. I need to implement some of this functionality in `x86_64`
assembly at work, so first I want to wrap my head around it in C.

## Why only BIG-ish?

At this point, arbitrary size isn't needed. That could be a later enhancement,
but supporting types `uint256_t` and `uint512_t` will suffice for now.

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
