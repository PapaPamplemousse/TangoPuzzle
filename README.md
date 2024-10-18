
# Puzzle Game

This is a console-based puzzle game written in C using the `ncurses` library. The game involves filling a grid with symbols while adhering to specific rules.

## How to Play

The goal of the game is to fill a grid with symbols, either a sun ("*") or a moon (")"). Follow these rules:

1. No more than two "*" or ")" symbols can be placed next to each other, either vertically or horizontally.
2. Each row and each column must contain an equal number of "*" and ")" symbols.
3. Cells separated by an "=" sign must have the same symbol.
4. Cells separated by an "X" must have different symbols.
5. The puzzle has only one correct solution, and it can be solved by deduction alone (you should never need to guess).

## Project Structure

```
.
├── CODE/
│   ├── inc/
│   │   ├── game_state.h
│   │   ├── solver.h
│   │   ├── ui.h
│   │   └── utils.h
│   ├── src/
│   │   ├── game_state.c
│   │   ├── main.c
│   │   ├── solver.c
│   │   ├── ui.c
│   │   └── utils.c
│   └── Makefile
├── run_game.sh
└── README.md
```

## Prerequisites

- GCC compiler
- `ncurses` library

### Installing `ncurses`

#### Debian/Ubuntu

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

#### CentOS/Red Hat

```bash
sudo yum install ncurses-devel
```

## Building and Running the Game

### Using the Script

A script `run_game.sh` is provided for convenience.

#### Build the Game

```bash
./run_game.sh build
```

#### Clean Build Files

```bash
./run_game.sh clean
```

#### Rebuild the Game

```bash
./run_game.sh rebuild
```

#### Run the Game

```bash
./run_game.sh run
```

## How to Play

- Use the arrow keys to move the cursor around the grid.
- Press `Enter` or `Space` to change the symbol in the selected cell.
- The symbols cycle through empty -> sun (`*`) -> moon (`)`) -> empty.
- The goal is to fill the entire grid while following the game rules.

### Controls

- **Arrow Keys**: Move the cursor.
- **Enter** or **Space**: Change the symbol in the selected cell.
- **r**: Reset the game with a new puzzle.
- **s**: Show the solution.
- **q**: Quit the game.

## Generating Documentation

If you have Doxygen installed, you can generate HTML documentation.

```bash
doxygen Doxyfile
```

## License

This project is open-source and available for modification and distribution.
```