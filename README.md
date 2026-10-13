*This activity has been created as part of the 42 curriculum by aiwane, yuito.*

# push_swap

## Description

push_swap is a program that sorts a stack of integers — but instead of
printing the sorted numbers, it prints the **list of operations** needed to
sort them. Running `./push_swap 2 1 3` prints `sa`, meaning "one swap sorts
this input".

Two stacks are used: `a` holds the numbers, `b` starts empty. Only 11
operations are allowed:

| Operation | What it does |
| --- | --- |
| `sa` / `sb` / `ss` | swap the top 2 of a / b / both |
| `pa` / `pb` | move the top of b to a / of a to b |
| `ra` / `rb` / `rr` | rotate a / b / both up (top goes to bottom) |
| `rra` / `rrb` / `rrr` | rotate a / b / both down (bottom goes to top) |

## Instructions

```sh
make          # builds ./push_swap
make bonus    # builds ./checker
make clean / fclean / re
```

```sh
./push_swap 3 1 2                          # no flag = adaptive
./push_swap --simple 5 4 3 2 1             # force one strategy
./push_swap --bench --medium 5 4 3 2 1     # metrics go to stderr
./push_swap 3 2 1 0 | ./checker 3 2 1 0    # verify with the checker -> OK
```

Errors (non-integer, out of int range, duplicate, empty string, unknown
flag) print `Error` on stderr and exit 1. No arguments: prints nothing.
Sorted input: prints nothing (0 operations).

## File structure

```
push_swap/
├── Makefile                     # make / bonus / clean / fclean / re, no relink
├── include/push_swap.h          # structs, operation codes, prototypes
├── src/
│   ├── core/main.c              # main flow, strategy selection
│   ├── core/init.c              # init / malloc / free / Error handling
│   ├── core/parse.c             # split arguments into flags and numbers
│   ├── core/parse_tokens.c      # read numbers, int-range check, duplicates
│   ├── stack/stack.c            # swap / rotate / reverse rotate / is_sorted
│   ├── stack/ops.c              # push + ps_op (apply a move AND record it)
│   ├── stack/optimize.c         # delete useless pairs, merge ra+rb into rr
│   ├── sort/ranks.c             # disorder score, convert values to ranks
│   ├── sort/sort_simple.c       # selection sort O(n^2) + small-input sort
│   ├── sort/sort_medium.c       # chunk sort O(n*sqrt(n))
│   ├── sort/sort_medium_utils.c # helpers (find max, rotate b)
│   ├── sort/sort_complex.c      # binary radix sort O(n log n)
│   ├── utils/output.c           # print the recorded move list
│   ├── utils/bench.c            # --bench report (stderr)
│   └── utils/utils.c            # ft_strcmp / isdigit / putnbr etc.
└── bonus/checker_bonus.c        # checker: run moves from stdin, print OK/KO
```

## Program flow

1. Initialise.
2. Read the arguments (validate numbers, flags, duplicates). Stop here if
   there are no numbers.
3. Measure the disorder (before any move — required by the subject).
4. Replace each value by its rank (0, 1, 2, ...).
5. Run the strategy (move the internal stacks while recording each move).
6. Clean up the recorded list, then print it.
7. If `--bench` is set, print the metrics on stderr.
8. Free the memory and exit.

## Disorder and rank conversion

**Disorder** = number of pairs in the wrong order / total number of pairs.
0 = already sorted, 1 = fully reversed. A random shuffle is around 0.5.

**Rank conversion**: replace each value by "how many values are smaller".

```
original: [50, 10, 30, 20, 40]
ranks:    [ 4,  0,  2,  1,  3]
```

The order relation does not change, so sorting the ranks is the same as
sorting the original values. Ranks always fit in 0..n-1, which makes the
radix digit count exact and the chunk ranges easy to split.

## Algorithms and justification

### First, what "complexity" means here

It is a measure of **how fast the move count grows** as the number of
integers n grows. In this project we count printed operations, not CPU time.

| Class | When n becomes 10x, moves become | Rough figure at n=500 |
| --- | --- | --- |
| O(n^2) | about 100x | about 250,000 moves |
| O(n*sqrt(n)) | about 30x | about 11,000 moves |
| O(n log n) | about ten-something x | about 4,500 moves |

### simple (selection sort, O(n^2))

**How it works**
1. Find the smallest number in `a`.
2. Rotate it to the top (`ra`, or the shorter direction for small inputs).
3. `pb` it to `b`.
4. Repeat until 3 numbers remain, sort those directly, then `pa` all back.

**Why it sorts**: `b` receives the numbers smallest first, so inside `b` the
larger numbers sit on top. Bringing them back with `pa` puts the larger ones
on `a` first, and the smallest ends up on top — ascending order.

**Move count**: at most about n*n/2, which grows quickly. But on almost
sorted input the smallest number is already near the top, so the rotation in
step 2 costs almost nothing and the whole run finishes in about 2n moves.

**Why we chose it**: the subject lists insertion, selection, bubble and
simple min/max extraction. We chose selection sort because (1) it fits two
stacks naturally ("extract the minimum into b" is exactly `pb`), (2) bubble
sort needs a rotation for every adjacent swap, which inflates the move
count, (3) insertion sort's "insert at the right position" is awkward on a
stack, and (4) on nearly sorted input it drops to about 2n measured moves,
which makes it the right fit for the low-disorder regime.

- Time: O(n^2) — Space: O(n) — Used for: disorder < 0.2

### medium (chunk sort, O(n*sqrt(n)))

**How it works**
1. Define a window: a number may be pushed if its rank is below
   "already pushed + about 1.75*sqrt(remaining)".
2. Among the allowed numbers, push the one closest to the top (searching
   from both ends) with `pb`. Repeat until `a` is empty.
3. Find the largest number in `b`, rotate it to the top the shorter way,
   `pa`. Repeat until `b` is empty.

**Why it is faster**: simple's weakness is having to rotate a long way to
fetch one specific number. medium always has several acceptable candidates,
so one of them is nearly always close to the top. The pull side is cheap
too: larger values were pushed later, so the current maximum is always near
the top of `b`. Each side costs about sqrt(n) moves per element, so about
n*sqrt(n) in total.

**Why we chose it**: the subject lists chunk splitting, block partitioning,
buckets and range-based strategies. They all "move values in groups"; we
chose the chunk form because (1) values are already converted to ranks, so
splitting by rank range is the most natural, (2) it needs no extra container
— stack `b` alone is enough, and (3) making the window slide reduced the
measured move count further.

- Time: O(n*sqrt(n)) — Space: O(n) — Used for: disorder 0.2 to 0.5

### complex (LSD binary radix sort, O(n log n))

**How it works** (ranks are 0..n-1, so they fit in log2(n) binary digits —
9 digits for 500 numbers)
1. Go through `a` once. If the current digit of the top number is 0, `pb`
   it; if it is 1, `ra` it.
2. After the pass, `pa` everything back from `b`.
3. Move to the next digit and repeat. Stop early if `a` is already sorted.

**Why it sorts**: each pass keeps the relative order inside a group (the
0-group comes back in the order it left). So after pass 1 the stack is
ordered by the last digit, after pass 2 by the last two digits, and after
the final pass by all digits — fully sorted.

**Move count**: one pass is at most 2n moves and there are log2(n) passes,
so the total **never exceeds 2n*log2(n) for any input**. For 500 numbers
that is an upper bound of about 9,000; measured is about 6,700.

**Why we chose it**: the subject lists radix, merge, quicksort, heapsort and
Fenwick trees. Radix won because we can state with certainty that no input
exceeds 2n*log2(n). Quicksort can degrade to O(n^2) with bad pivots, which
breaks the claim. Merge and heap sort are complex to implement on two stacks
and the move count is hard to control. A Fenwick tree does not fit the
operation model. The subject requires the claimed complexity class to
actually hold, and radix is the one where that is easiest to show.

- Time: O(n log n) — Space: O(n) — Used for: disorder 0.5 and above

### adaptive (default)

It only measures the disorder and dispatches.

| Disorder | Method | Reason |
| --- | --- | --- |
| below 0.2 | simple | fastest in practice on nearly sorted input |
| 0.2 to 0.5 | medium | fewest moves on in-between input |
| 0.5 and up | complex | the move bound can be guaranteed |

The 0.2 / 0.5 cut-offs are the values fixed by the subject.

### Thresholds, per-regime techniques, and upper bounds

The three things the subject asks us to document — threshold rationale,
internal technique per regime, and time/space upper bounds in the Push_swap
model — in one table.

| Disorder regime | Technique | Threshold rationale | Time upper bound (moves) | Space |
| --- | --- | --- | --- | --- |
| d < 0.2 | selection sort | on nearly sorted input the minimum sits near the top and almost no rotation is needed; it drops to about 2n measured, so we deliberately use the plain O(n^2) method | n^2/2 + 2n + 3 <= O(n^2) | O(n) |
| 0.2 <= d < 0.5 | windowed chunk sort | partial order remains, so the "move values in groups" approach has the smallest constant here | push n*sqrt(n) + pull n*sqrt(n) <= O(n*sqrt(n)) | O(n) |
| d >= 0.5 | LSD binary radix | a random permutation has expected disorder exactly 0.5; beyond it we want a method whose bound does not depend on the input | 2n * ceil(log2 n) <= O(n log n) (holds for every input) | O(n) |

The 0.2 / 0.5 thresholds themselves are fixed by the subject; the table
shows that those values line up with where each method is strongest. Space
in every regime is the two stack arrays (n each) + one temporary rank array
(n) + the recorded move list (proportional to the move count) = O(n). No
global variables are used.

### Algorithms

**Q1. How does --simple work? (O(n^2))**
Find the minimum in `a`, rotate it up to the top with `ra`, `pb` it to `b`.
Repeat, then `pa` everything back: the numbers return smallest last, so `a`
ends up ascending. Each of the n elements costs up to about n moves, so
n*n — that is O(n^2).

**Q2. How does --medium work? (O(n*sqrt(n)))**
Define a window ("rank below pushed + about 1.75*sqrt(remaining) may go"),
and keep pushing whichever allowed number is closest to the top. Once `a` is
empty, pull back from `b` starting with the largest. There are always about
sqrt(n) acceptable candidates, so one element costs about sqrt(n) moves and
n elements cost n*sqrt(n) — that is O(n*sqrt(n)).

**Q3. How does --complex work? (O(n log n))**
Read the ranks in binary and, from the lowest digit up, sort one digit at a
time ("0 goes to `b`, 1 stays in `a`", then bring everything back). The
split preserves order, so after the last digit the stack is ascending. There
are log2(n) digits and each pass is at most 2n moves, so 2n*log2(n) — that
is O(n log n), and this bound holds for every input.

**Q4. How does --adaptive choose?**
Before any move it measures the disorder (share of inverted pairs, 0 to 1)
and uses simple below 0.2, medium from 0.2 to 0.5, and complex at 0.5 and
above. The thresholds come from the subject, and they match where each
method is strongest: nearly sorted = simple is fastest in practice,
in-between = medium has the fewest moves, random (about 0.5) or worse =
complex, whose bound is guaranteed.

## Contributions

| Login | Work |
| --- | --- |
| aiwane | parsing & error handling, simple & medium & adaptive strategies, bench mode　|
| yuito | simple & medium strategies, bonus checker, Makefile, tests, README |

Both members reviewed every file together and can explain any part of the
code.

## Resources

* https://en.wikipedia.org/wiki/Sorting_algorithm
* https://en.wikipedia.org/wiki/Selection_sort
* https://en.wikipedia.org/wiki/Radix_sort

## AI usage

AI (Anthropic Claude) was used for discussing and understanding the choice
of algorithms, writing test scripts, and proofreading this README. Every
generated piece of code or explanation was reviewed, tested and understood
by both members before it went into the project.
