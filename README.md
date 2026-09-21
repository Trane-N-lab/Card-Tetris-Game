# Card Tetris

A modular C++17 console game inspired by Tetris and match-3 mechanics. Falling card-suit symbols can be moved horizontally and dropped faster with the arrow keys. When three or more identical symbols form a horizontal or vertical run, they are removed and the remaining symbols fall under gravity.

> **Platform:** Windows. The interactive console uses Windows-specific keyboard and timing APIs (`conio.h` and `windows.h`).

## Features

- 10×10 console game board
- Four Unicode card-suit symbols: ♥ ♦ ♣ ♠
- Random falling symbols
- Left/right movement
- Faster drop with the Down arrow
- Horizontal and vertical match detection for 3+ symbols
- Automatic clearing and gravity after matches
- Score tracking based on removed cells
- Game-over detection
- UTF-8 console setup for Unicode symbols
- Modular C++17 architecture
- Dependency-free unit tests for core board logic
- CMake build system
- GitHub Actions CI on Windows
- Compiler warning flags for maintainability

## Project Structure

```text
CardTetris/
├── .github/workflows/ci.yml
├── src/
│   ├── Board.cpp
│   ├── Board.hpp
│   ├── Console.cpp
│   ├── Console.hpp
│   ├── Game.cpp
│   ├── Game.hpp
│   └── main.cpp
├── tests/
│   └── BoardTests.cpp
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Architecture

**Board** owns the 2D game state and implements bounds validation, match detection, clearing, and gravity.

**Game** controls the gameplay loop, random symbol generation, falling pieces, movement, scoring, and game-over condition.

**Console** contains Windows-specific keyboard polling, UTF-8 configuration, screen clearing, rendering, and delays. Separating console I/O from board rules keeps the core logic easier to test.

## Controls

| Key | Action |
|---|---|
| ← | Move left |
| → | Move right |
| ↓ | Drop faster |
| Any key | Start the game |

## Requirements

- Windows 10/11
- C++17-compatible compiler
- CMake 3.20+
- Visual Studio 2022, Build Tools, or another C++17 compiler supported by CMake

## Build

From the repository root in PowerShell:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Run the game:

```powershell
.\build\Release\card_tetris.exe
```

If your CMake generator places executables directly under `build`, use the generated executable path shown by CMake.

## Run Tests

```powershell
ctest --test-dir build -C Release --output-on-failure
```

The tests cover horizontal matches, vertical matches, four-cell matches, gravity, and no-match behavior.

## Design Notes

The original implementation mixed global board state, rendering, keyboard input, random generation, gameplay, and match logic in a single source file. This version separates those responsibilities into focused classes and keeps deterministic board rules testable without launching the interactive console.

The match resolver detects complete runs of three or more equal non-empty symbols in both directions, clears all marked cells in one resolution step, and then applies gravity column by column.

## Quality Engineering

- C++17 standard enforcement
- CMake-based reproducible builds
- Automated unit tests
- GitHub Actions CI on Windows
- Strict compiler warnings
- `.clang-format` for consistent formatting
- `.gitignore` for build and IDE artifacts

## Roadmap

- Pause/restart controls
- Configurable board size and difficulty
- Combo and multiplier scoring
- Persistent high scores
- Richer piece mechanics
- Cross-platform terminal input abstraction
- Visual themes and sound effects

## License

MIT License. See `LICENSE` for details.
