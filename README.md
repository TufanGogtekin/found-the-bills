# 🧾 Found the Bills - C Terminal Game

**Found the Bills** is a two-player terminal-based game written in C. The objective is to collect randomly placed coins on the board and score more money than your opponent. Each player takes turns moving across the board, collecting coins by stepping on them. The player with the most money at the end of the game wins.

---

## 🎯 Game Rules

- The game board is square-shaped with a **minimum size of 5x5**.
- **Player 1 (`1`)** starts at the top-left corner `(0, 0)`.
- **Player 2 (`2`)** starts at the bottom-right corner `(size - 1, size - 1)`.
- There are **7 coins**, each with a different value:
  - `a` → 1
  - `b` → 2
  - `c` → 5
  - `d` → 10
  - `e` → 20
  - `f` → 50
  - `g` → 100
- Coins are placed randomly on the board at the start of the game.
- A player collects a coin by moving onto its position.
- Once all 7 coins are collected, the game ends.
- The player with the highest total coin value wins.
- If both players have the same amount, the game ends in a draw.

---

## 🕹️ Controls

- Players take turns moving using the following keys:
  - `U` → Up
  - `D` → Down
  - `L` → Left
  - `R` → Right
- Players cannot:
  - Move outside the boundaries of the board
  - Move into a space already occupied by the other player
  - Move onto a coin that has already been collected
- Players leave a trail (`','`) behind to mark where they have been.

---

## 🧩 Game Flow

1. The game starts by prompting the user to enter the board size (must be 5 or greater).
2. 7 coins with different values are randomly placed on the board.
3. Player 1 and Player 2 take alternating turns to move.
4. Players collect coins by landing on them.
5. The game ends once all 7 coins are collected.
6. The player with the highest score wins.

---

## 🛠️ Compilation

To compile the game, use a C compiler like `gcc`:

```bash
gcc -o found_the_bills found_the_bills.c
