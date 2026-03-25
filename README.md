# C++ Projects

Collection of C++ coursework projects from the University of Illinois Urbana-Champaign, covering data structures, algorithms, image processing, and problem-specific software design.

## Overview

This repository brings together several self-contained machine problems implemented in modern C++. Each project focuses on a different concept, such as traversals, disjoint sets, scheduling, image composition, and maze generation/solving. Most folders include their own `CMakeLists.txt`, making the repository easy to explore one assignment at a time.

## Repository Layout

```text
Cpp-Projects/
├── mp_stickers/    # Image layering and sticker composition
├── mp_traversals/  # Flood fill and traversal abstractions
├── mp_mosaics/     # KD-tree and image mosaic generation
├── mp_schedule/    # Scheduling/problem-solving assignment
├── mp_mazes/       # Maze generation/solving and disjoint sets
└── src/            # Shared list implementation coursework
```

## Topics Covered

- Object-oriented design in C++
- Templates and reusable abstractions
- Image and graphics-oriented data transformations
- Graph/traversal-style logic
- Disjoint-set data structures
- CMake-based project organization

## Building Projects

The repository is organized as multiple independent subprojects rather than one monolithic build.

Typical workflow:

```bash
cd mp_mazes
cmake -S . -B build
cmake --build build
```

Repeat that pattern from whichever project directory you want to explore. Some folders may rely on course-provided support code or assignment-specific test harnesses that are not bundled here.

## Notes

- File and folder names match the original coursework conventions.
- The code is preserved as a portfolio/archive of individual assignments.
- The repository is useful as a reference for the progression of C++ problem solving across multiple topics instead of as a single application.

## Key Skills Gained

- Writing reusable C++ code around classes, templates, and clean interfaces
- Implementing core data structures and algorithms in project-oriented settings
- Organizing independent projects with CMake-based build flows
- Solving visual and traversal-heavy problems through modular abstractions
- Strengthening object-oriented design and codebase navigation skills
