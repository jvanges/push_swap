*This project has been created as part of the 42 curriculum by jvan-ges.*

# Push_swap

## Description

Push_swap is an algorithmic project: sort a stack of integers using two
stacks (`a` and `b`) and a very limited set of operations (`sa`, `sb`,
`ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`), while keeping
the total number of operations as low as possible.

The program analyses the input before moving anything: it computes a
**disorder metric** (the fraction of inverted pairs in the initial
stack) and selects one of four embedded sorting strategies, each with a
different complexity class **measured in number of push_swap
operations**:

| Selector     | Strategy                         | Complexity (op model) |
|--------------|----------------------------------|-----------------------|
| `--simple`   | selection sort (min extraction)  | O(n²)                 |
| `--medium`   | chunk sort (√n chunks)           | O(n·√n)               |
| `--complex`  | radix sort LSD on ranks          | O(n log n)            |
| `--adaptive` | picks from the metric (default)  | per regime (below)    |

An optional `--bench` flag prints, on **stderr** (the operation stream
stays clean on stdout): the disorder (in %, two decimals), the strategy
used with its complexity class, the total number of operations and the
count of each operation type.

A `checker` program (bonus) verifies that an operation stream actually
sorts the stack.

## Instructions

```sh
make            # builds push_swap
make bonus      # builds checker
```

Usage:

```sh
./push_swap 3 2 1          # prints the operations that sort the stack
./push_swap "3 2 1"        # quoted strings work too
./push_swap --complex 4 67 3 87 23 | ./checker 4 67 3 87 23   # OK
./push_swap --bench 2 1 3  # operations on stdout, metrics on stderr
```

Errors (non integers, values outside int range, duplicates, unknown
flags) print `Error` on stderr. With no arguments the program prints
nothing.

## Algorithms and complexity

All complexities below count **push_swap operations**, as required by
the subject — not CPU operations on a classical array model. Stacks are
implemented as plain arrays with the top at index 0; rotating or
pushing costs a `memmove`, but that internal CPU cost is irrelevant to
the metric.

### Disorder metric

Computed **before any move**, on the raw values:

```
disorder = #(pairs i < j with a[i] > a[j]) / (n·(n-1)/2)
```

0 means already sorted, 1 means the worst possible arrangement.

### Simple — selection sort, O(n²)

While more than 3 elements remain in `a`, the minimum is located,
rotated to the top via `ra`/`rra` (whichever direction is shorter) and
pushed to `b`. The last 3 are sorted with a hardcoded decision tree,
then everything is popped back with `pa`. At iteration k the minimum is
at most k positions away, so the rotation cost is bounded by
n·(n-1)/2 = **O(n²)** operations; total upper bound is
n²/2 + 2n operations. Space: O(n) for the two stack arrays.

### Medium — chunk sort, O(n·√n)

Values are first compressed into ranks 0..n-1. The rank space is divided
into **√n chunks** of size ≈ √n. Elements of `a` are pushed to `b`
chunk by chunk: `a[0]` is pushed when its rank is below the current
chunk limit, otherwise `a` is rotated. Ranks from the lower half of a
chunk are sent to the bottom of `b` (`rb`) so large values stay near
the top. Then `b` is drained by always extracting its maximum with the
shortest rotation and `pa`.

- Push phase: √n chunk boundaries, each element of `a` is scanned at
  most once per chunk boundary → O(n·√n) `ra`, plus n `pb`.
- Pull-back phase: by construction, elements deeper than one chunk
  from the top of `b` belong to strictly lower chunks (they were
  rotated to the bottom), so the current maximum is always within
  O(√n) rotations → n extractions × O(√n) = **O(n·√n)** operations.
- Space: O(n) stacks + O(n) rank buffer.

### Complex — radix sort LSD, O(n log n)

Classic LSD radix on compressed ranks: for each bit i from 0 to
⌈log₂ n⌉ − 1, scan `a` once — `ra` if bit i is set, `pb` otherwise —
then `pa` everything back. Each pass costs between n and 2n operations
(n splits + one `pa` per pushed element) and there are ⌈log₂ n⌉ passes,
giving a tight upper bound of **2·n·⌈log₂ n⌉ = O(n log n)** operations
(≈ 6800 ops for 500 numbers). Space: O(n).

### Adaptive — default, driven by disorder

| Disorder          | Internal method          | Class     |
|-------------------|--------------------------|-----------|
| `< 0.2`           | insertion sort into `b`  | O(n²)     |
| `0.2 ≤ d < 0.5`   | chunk sort               | O(n·√n)   |
| `≥ 0.5`           | radix sort               | O(n log n)|

A stack is *also* routed to a hardcoded optimal sort when n ≤ 5
(constant-size input: O(1), at most 8 operations).

**Insertion sort** (`O(n²)`): `b` is maintained circularly sorted
(descending from its maximum). Each top of `a` is inserted at its exact
position with at most |b|/2 rotations, then `b` is popped back. Worst
case Σ k/2 = **O(n²)** operations, but on nearly-sorted inputs each
insertion lands at the stack boundary and the cost collapses to O(n).

**Why these thresholds.** For low disorder the number of inversions is
small, so insertion sort — whose rotation count tracks the distance
each element has to travel — needs far fewer operations than any
comparison-blind method; its O(n²) worst case never materialises there.
Between 0.2 and 0.5 the chunk strategy's √n grouping keeps rotations
local and beats radix's fixed 2n·log n cost. Above 0.5 (including all
random permutations, whose expected disorder is 0.5) input looks
uniformly shuffled, where the guaranteed O(n log n) of radix is the
safest and fastest choice in the operation model.

## Performance (measured on random inputs, default `--adaptive`)

| n   | Operations | Requirement                             |
|-----|------------|-----------------------------------------|
| 100 | ~950 avg   | < 2000 pass, < 1500 good, < 700 excellent |
| 500 | ~7000 avg  | < 12000 pass, < 8000 good, < 5500 excellent |

## Resources

- 42 subject *push_swap* (v1.2)
- T. H. Cormen et al., *Introduction to Algorithms* — radix sort,
  insertion sort, selection sort, inversion counting
- [https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a) — chunk strategy overview
- [https://push_swap.simple.ink](https://push_swap.simple.ink) — push_swap algorithm discussion

**AI usage.** Claude Code was used to bootstrap the project structure
(parsing, stack primitives, operation recording), to draft the four
sorting strategies and this README, and to generate the randomised test
scripts used during development. All generated code was reviewed line
by line, tested with the custom `checker` (hundreds of random
permutations per strategy) and with valgrind (no leaks), and several
bugs found during review (stack ordering when merging `b` back into
`a`, value clobbering in `pa`/`pb`) were fixed by hand. The algorithmic
choices (strategy per regime, thresholds) were validated empirically
against the benchmark targets.

## Contributors

- **jvan-ges** — architecture, parsing, the four sorting strategies,
  bench mode, checker, tests and documentation.
