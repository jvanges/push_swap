# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project context

42 school project (subject v1.2, group project). Goal: `push_swap` sorts
integers on two stacks with a limited op set (`sa sb ss pa pb ra rb rr rra
rrb rrr`) and prints the operation stream on stdout. **Global variables are
forbidden**; only `read/write/malloc/free/exit` plus libft are allowed
(no `printf`/`qsort` — formatting is hand-rolled with `write`). Code is
written to the 42 Norm (≤25 lines/function, ≤5 functions/file, ≤5 params,
declarations at the top of blocks, no comma operator); norminette is not
installed on this machine, so keep new code Norm-shaped by hand.

## Commands

```sh
make            # builds push_swap (builds libft first)
make bonus      # builds checker
make re / fclean
./push_swap --bench $(shuf -i 0-9999 -n 100 | tr '\n' ' ')   # ops on stdout, metrics on stderr
./push_swap --simple $ARG | ./checker $ARG   # correctness check loop
```

There is no test suite in the repo — test with random permutations piped
into `./checker` (example above) and `valgrind --leak-check=full`.
Benchmark targets (default adaptive mode): 100 numbers < 2000/1500/700
ops, 500 numbers < 12000/8000/5500 ops.

## Architecture

**Stacks are plain int arrays with the top at index 0.** `pa`/`pb`/`ra`/
`rra` shift memory with `ft_memmove` — when touching `do_pa`/`do_pb`
(srcs/ops.c), the pushed value must be saved *before* any shift or it
gets clobbered.

**All state lives in `t_ctx`** (includes/push_swap.h): both stacks, the
accumulated output buffer `ops` (grows by doubling in ops_record.c) and
per-op counters. Ops record into `ctx->ops` only when `ctx->record` is
set; the bonus `checker` runs the same `do_*` functions with `record = 0`
and no buffer.

**Parse is two-pass** (srcs/parse.c): `count_numbers` counts tokens across
argv (each argv is `ft_split` on spaces, so `"4 67 3"` works) to size the
arrays once, then `parse_args` validates (strict int syntax, INT_MIN/MAX
range, duplicates) and fills stack `a`. `--flags` may appear anywhere.

**Pipeline in main.c:** parse → `compute_disorder` (inversion ratio of
the *raw* input, stored in `t_flags`) → early-exit if already sorted →
`compress_ranks` (values become 0..n-1, required by chunk & radix) →
`dispatch` → write buffered ops → optional bench. Inputs of n ≤ 5 bypass
all strategies via `sort_small` (hardcoded optimal sorts).

**Strategies** (complexity measured in push_swap ops, per the subject —
see README.md for the full justification):
- `simple.c`: selection by repeated min-extraction, O(n²)
- `medium.c`: chunk sort in √n chunks; `push_chunks` rotates the lower
  half of each chunk to the bottom of `b`, then b is drained by
  max-extraction — O(n·√n)
- `complex.c`: LSD radix on ranks, O(n log n)
- `adaptive.c`: disorder < 0.2 → circular insertion into b (O(n²), cheap
  on nearly-sorted input); < 0.5 → chunk; ≥ 0.5 → radix. The insertion
  keeps `b` **circularly descending** (predecessor lookup, fallback to
  max) precisely so the final `pa` sweep rebuilds `a` ascending — flipping
  that ordering invariant silently breaks sorting.

Shared helpers: `rot_to_top` (shortest-direction rotate), `index_of_min/
max`, `is_sorted`, `i_sqrt` (srcs/utils.c).

**Bonus `checker`** (bonus/checker_bonus.c) reuses parse/stack/ops sources
(the Makefile compiles them into both binaries; only `main` differs) and
reads ops char-by-char from stdin; an unterminated trailing instruction or
an unknown op is an `Error`.

## Contribution constraints

The subject requires exactly 2 learners; README first line and
Contributors list only `jvan-ges`. If a partner joins, add their login in
both places before submission.
