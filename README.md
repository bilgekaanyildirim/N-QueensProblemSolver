# N-Queens Problem Solver

This project is a **C++ implementation** of the **N-Queens problem**, solved using a **stack-based backtracking approach**. The goal is to place `N` queens on an `N×N` chessboard so that no two queens attack each other. Instead of traditional recursion, this solution uses a **custom stack class** to track and backtrack queen placements.

## Features
- Implements **backtracking** with a **custom stack** to efficiently explore valid placements.
- Uses a **safe matrix** to quickly check available positions.
- Outputs all valid solutions to a text file.
- Supports **any board size (N ≤ 13)** for finding solutions.

## Files
- `main.cpp` → Main program implementing the N-Queens solution.
- `stack.h` → Header file defining the **template-based stack class**.
- `stack.cpp` → Implementation of the **stack operations**.
