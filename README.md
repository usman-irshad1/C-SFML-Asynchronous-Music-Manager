# Asynchronous Multithreaded Music Manager (C++ / SFML 3)

![Language: C++17](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=flat-square)
![Library: SFML 3.0](https://img.shields.io/badge/Library-SFML%203.0-green?style=flat-square)
[![Docs: Doxygen](https://img.shields.io/badge/Docs-Doxygen%20Live-2ea44f?style=flat-square)](https://usman-irshad1.github.io/C-SFML-Asynchronous-Music-Manager/)
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)](LICENSE)

A multithreaded C++ audio playback and playlist management system that combines a custom template-based **Doubly Linked List (`DoublyLinkedList<T>`)** with **SFML 3 (`sf::Music`)** disk streaming and a background worker thread (`std::thread` + `std::atomic<bool>`) for automated track transitions.

- **UML & Class Documentation**: [Live Doxygen Documentation](https://usman-irshad1.github.io/C-SFML-Asynchronous-Music-Manager/)

---

## Overview & Core Objectives

The system models an iPod-style playlist controller designed around three engineering goals:
- **Constant-Time Track Navigation ($O(1)$)**: Bidirectional `next`/`previous` pointer traversal via [`DoubleLinkedList.h`](DoubleLinkedList.h).
- **Non-Blocking Audio Playback**: Background worker thread polling playback state via `std::atomic<bool>` flags so the interactive console menu remains responsive while audio streams from disk.
- **Persistent Playlist State**: CSV-backed track metadata storage ([`songs.csv`](songs.csv)) preserving song titles, artists, durations, and file paths across runs.

---

## Core Features

### 1. Custom Doubly Linked List (`DoubleLinkedList.h`)
- Template-based `DoublyLinkedList<T>` and `node<T>` implementation.
- $O(1)$ transitions between next and previous tracks, plus circular wrap-around navigation.
- Deep copy constructor and destructor for leak-free playlist duplication and cleanup.

### 2. Multithreaded Playback Engine (`Assignment_1_DSA_ipod.cpp`)
- `IPOD` controller class managing an asynchronous `std::thread` worker that monitors `sf::Music::getStatus()`.
- Thread-safe signaling via `std::atomic<bool>` to trigger automatic transitions when a track finishes and ensure clean thread joining on shutdown.
- Real-time audio seeking via `sf::Music::setPlayingOffset`.

### 3. Metadata Model & Operator Overloading
- `MetaData` class encapsulating track attributes with overloaded operators (`==` for title matching, `<` and `>` for duration comparisons, and `<<` for formatted console output).

---

## Performance Complexity

| Operation | Time Complexity | Implementation Mechanism |
| :--- | :---: | :--- |
| **Next / Previous Track** | $O(1)$ | Direct `next` / `prev` pointer manipulation in `DoublyLinkedList<MetaData>` |
| **Insert Track (Head / Tail)** | $O(1)$ | Head/tail pointer update without array reallocation |
| **Search Track by Title** | $O(n)$ | Linear traversal using overloaded `MetaData::operator==` |
| **Shuffle Track Selection** | $O(n)$ | Indexed traversal to pseudo-random node offset |
| **Auto-Play Transition** | $< 1\text{ s}$ | Background `std::thread` status polling loop |

---

## Actual Repository File Structure

```text
C-SFML-Asynchronous-Music-Manager/
├── Assignment_1_DSA_ipod.cpp       # Main entry point, IPOD controller, MetaData class, and audio thread
├── DoubleLinkedList.h              # Custom template-based DoublyLinkedList<T> and node<T> implementation
├── songs.csv                       # Persistent CSV playlist storage (title, artist, duration, path)
├── Assignment_1_DSA_ipod.slnx      # Visual Studio 2022 solution file
├── Assignment_1_DSA_ipod.vcxproj   # Visual Studio 2022 C++ project file
├── sfml-audio-3.dll / sfml-*.dll   # Bundled SFML 3.0 Windows runtime DLLs (Release & Debug)
├── docs/                           # Generated Doxygen HTML & UML class diagrams
└── LICENSE                         # MIT License
```

---

## Prerequisites & Build / Run Instructions

### Prerequisites
- **C++17 Compiler**: MSVC (Visual Studio 2022) or MinGW-w64 / GCC.
- **SFML 3.0**: Simple and Fast Multimedia Library (`sfml-audio`, `sfml-system`). The Windows runtime DLLs (`sfml-audio-3.dll`, `sfml-system-3.dll`, etc.) are included in the repository root.
- **Audio Files**: Place valid audio files (`.ogg`, `.wav`, or `.mp3` supported by SFML 3) referenced by [`songs.csv`](songs.csv) in the working directory.

### Option 1: Visual Studio 2022 (Windows — Recommended)
1. Clone the repository:
   ```powershell
   git clone https://github.com/usman-irshad1/C-SFML-Asynchronous-Music-Manager.git
   cd C-SFML-Asynchronous-Music-Manager
   ```
2. Open `Assignment_1_DSA_ipod.slnx` (or `Assignment_1_DSA_ipod.vcxproj`) in **Visual Studio 2022**.
3. Ensure your SFML 3 `include/` and `lib/` paths are configured under *Project Properties $\rightarrow$ C/C++ $\rightarrow$ General* and *Linker $\rightarrow$ General* (the runtime `sfml-*-3.dll` files are already in the project root).
4. Build and run (`Ctrl + F5`).

### Option 2: Command-Line Compilation (`g++` with SFML 3)
```bash
g++ -std=c++17 -O2 Assignment_1_DSA_ipod.cpp -o MusicManager -lsfml-audio -lsfml-system -lpthread
./MusicManager
```

---

## License

This project is licensed under the [MIT License](LICENSE).
