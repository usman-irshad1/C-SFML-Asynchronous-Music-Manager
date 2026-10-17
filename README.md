# Intelligent iPod Music Management System (C++ / SFML)

[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square)]()
[![Library: SFML](https://img.shields.io/badge/Library-SFML-green?style=flat-square)]()
[![License: MIT](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)](LICENSE)

A high-performance digital audio playback engine in C++ that leverages custom-built data structures, multithreaded background processing, and real-time audio manipulation using the SFML library.

This project emulates a classic iPod-style interface, focusing on efficient playlist management, seamless playback, and optimized memory usage.

- **UML & Class Documentation**: [Live Doxygen Documentation](https://usman-irshad1.github.io/C-SFML-Asynchronous-Music-Manager/)

---

## Overview

The system is designed to handle music libraries efficiently by combining:
- **Fast Navigation**: Constant-time $O(1)$ track transitions.
- **Memory Efficiency**: Custom template-based data structures.
- **Continuous Playback**: Background worker thread automation.

---

## Core Features

### 1. Custom Doubly Linked List Architecture
- Bidirectional traversal using a template-based `DoublyLinkedList<T>`
- $O(1)$ transitions between next and previous tracks
- Deep copy constructor for safe playlist duplication
- Dynamic insertion and deletion without full reallocation

### 2. Multithreaded Playback Engine
- Background monitoring using `std::thread`
- Thread-safe control via `std::atomic<bool>`
- Automatic transition to the next track upon completion
- Clean shutdown without race conditions

### 3. Persistent Storage System
- CSV-based file storage (`songs.csv`) for playlists
- Serialization of metadata (title, artist, duration, file path)
- Persistent state across program executions

### 4. Real-Time Audio Control (SFML)
- Fine-grained seeking using `setPlayingOffset`
- Audio streaming directly from disk with low memory footprint
- Circular playlist navigation and shuffle playback modes

---

## Performance Analysis

| Operation | Complexity | Description |
| :--- | :--- | :--- |
| **Next / Previous** | $O(1)$ | Direct pointer manipulation |
| **Add Song** | $O(1)$ | Insert at head or tail |
| **Search by Title** | $O(n)$ | Linear traversal |
| **Auto-Play Response** | $< 1\text{ s}$ | Controlled via thread polling |

---

## Project Structure

```text
├── DoublyLinkedList.h   # Template-based Doubly Linked List implementation
├── IPOD_Manager.cpp     # Core logic and multithreaded playback engine
├── songs.csv            # Persistent CSV storage for tracks
└── LICENSE              # MIT License
```

---

## License

This project is licensed under the [MIT License](LICENSE).
