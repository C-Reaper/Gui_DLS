# Project README

## Overview
This project is a digital logic simulation GUI using C and various libraries. It allows users to interactively design, simulate, and analyze digital circuits.

## Features
- Basic circuit building blocks (AND, OR, NOT, etc.)
- Circuit simulation based on truth tables
- User-friendly interface for designing and viewing circuits
- Save and load circuit configurations

## Project Structure
```
Gui_DLS/
├── build/              # .exe files produced by Main.c
├── src/                # src code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration
├── Makefile.web        # Emscripten Build configuration
└── README.md           # This file
```

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- Libraries needed in specific projects:
  - Linux: X11 for GUI, PNG and JPEG for image handling.
  - Windows: WINAPI, User32, GDI32, Winmm for GUI and multimedia functionalities.
  - Wine: For cross-compiling to Windows on Linux.
  - Emscripten: For web assembly build.

## Build & Run
### Linux
To build the project on Linux:
```bash
cd Gui_DLS/
make -f Makefile.linux all
```

Run the executable:
```bash
make -f Makefile.linux exe
```

Clean and rebuild:
```bash
make -f Makefile.linux clean
make -f Makefile.linux all
```

### Windows
To build the project on Windows:
```bash
cd Gui_DLS/
make -f Makefile.windows all
```

Run the executable:
```bash
make -f Makefile.windows exe
```

Clean and rebuild:
```bash
make -f Makefile.windows clean
make -f Makefile.windows all
```

### Wine
To build for Windows on Linux using Wine:
```bash
cd Gui_DLS/
make -f Makefile.wine all
```

Run the executable:
```bash
make -f Makefile.wine exe
```

Clean and rebuild:
```bash
make -f Makefile.wine clean
make -f Makefile.wine all
```

### Web Assembly (Emscripten)
To build for web assembly:
```bash
cd Gui_DLS/
make -f Makefile.web all
```

Serve the output:
```bash
make -f Makefile.web exe
```

Clean and rebuild:
```bash
make -f Makefile.web clean
make -f Makefile.web all
```