# HW6 Part 1: Red-Black Tree

A red-black tree of `int`s in C++ for CS 222. It supports insert (with
rebalancing), contains, min, max, size, the three traversal strings, and deep
copying. `Remove()` comes in part 2.

## Files

- `RedBlackTree.h` / `RedBlackTree.cpp`: the `RBTNode` struct and the tree
- `RedBlackTreeTestsFirstStep.cpp`: the provided first-step tests
- `RedBlackTreeTests.cpp`: the provided tests plus my own, including a call to
  `PrivateTests()` for the private helpers (rotations, copying, and a checker
  for the red-black rules)

## Build and run

```
make
./test     # full test suite
./first    # first-step tests
make clean # remove the executables
```

To check for memory problems:

```
valgrind --leak-check=full ./test        # Linux
leaks --atExit -- ./test                 # macOS
```

## Colors

Colors are stored as integers using `#define COLOR_BLACK 0` and
`#define COLOR_RED 1` in `RedBlackTree.h`. Traversal strings print them as
`B` and `R`, for example ` B30  R15 `.

## Sources

- Claude (Anthropic, via Claude Code) reviewed my code throughout and wrote
  the insert fix-up, rotations, the remaining tree methods, and many of the
  added tests. Each file's header lists exactly what.
