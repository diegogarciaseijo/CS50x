# CS50 Speller

My solution to the CS50x Week 5 Speller problem.

## My work

`dictionary.c` contains my implementation of:

- `load`
- `hash`
- `size`
- `check`
- `unload`

The remaining source files were provided by CS50.

## Hash function

I implemented a custom hash function using the first four
characters of each word to reduce hash collisions.

## Performance

I optimized the hash function to reduce the number of collisions
and avoid unnecessary repeated calculations.

Using the same dictionary and text, my implementation achieved a
total execution time of **0.04 seconds**, compared to **0.05 seconds**
for the staff implementation provided by CS50.

These results may vary slightly between runs due to system and
measurement variability.
