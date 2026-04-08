\*\*Intelligent IPOD Music Management System (C++)\*\*



!\[C++](https://img.shields.io/badge/Language-C%2B%2B-blue)

!\[SFML](https://img.shields.io/badge/Library-SFML-green)

!\[Status](https://img.shields.io/badge/Project-Completed-success)

!\[License](https://img.shields.io/badge/License-MIT-lightgrey)



A high-performance digital audio playback simulation that leverages custom-built data structures, multithreaded background processing, and real-time audio manipulation using the SFML library.



This project emulates a classic iPod-style interface, focusing on efficient playlist management, seamless playback, and optimized memory usage.



\---



\*\*Overview\*\*



The system is designed to handle large music libraries efficiently by combining:



\- Fast Navigation — Constant time O(1) track transitions  

\- Memory Efficiency — Custom template-based data structures  

\- Continuous Playback — Background thread automation  



\---



\*\*Objectives\*\*



\- Provide constant-time navigation between tracks  

\- Ensure memory safety through custom data structures  

\- Maintain uninterrupted playback using concurrent execution  



\---



\*\*Core Features\*\*



\*\*Custom Doubly Linked List Architecture\*\*



\- Bidirectional traversal using a template-based DoublyLinkedList<t>  

\- O(1) transitions between next and previous tracks  

\- Deep copy constructor for safe playlist duplication  

\- Dynamic insertion and deletion without full reallocation  



\*\*Multithreaded Playback Engine\*\*



\- Background monitoring using std::thread  

\- Thread-safe control via std::atomic<bool>  

\- Automatic transition to the next track upon completion  

\- Clean shutdown without race conditions  



\*\*Persistent Storage System\*\*



\- CSV-based file storage for playlists  

\- Efficient serialization of metadata (title, artist, duration, file path)  

\- Persistent state across program executions  



\*\*Real-Time Audio Control (SFML)\*\*



\- Fine-grained seeking using setPlayingOffset  

\- Efficient audio streaming directly from disk  

\- Reduced memory consumption compared to full buffering  



\*\*Playback Modes\*\*



\- Random shuffle using indexed traversal (O(n))  

\- Circular playlist navigation (tail to head and vice versa)  

\- Continuous playback without interruption  



\---



\*\*Technical Design\*\*



\*\*Metadata Model\*\*



Each track is represented using a MetaData class with operator overloading:



\- == for title-based comparisons  

\- < and > for duration-based ordering  

\- << for formatted console output  



\---



\*\*Performance Analysis\*\*



Operation            | Complexity | Description

\-------------------- | ---------- | --------------------------------

Next / Previous      | O(1)       | Direct pointer manipulation

Add Song             | O(1)       | Insert at head or tail

Search by Title      | O(n)       | Linear traversal

Auto-Play Response   | < 1 second | Controlled via thread polling



\---



\*\*Project Structure\*\*



```text

DoublyLinkedList.h   # Template-based DLL implementation

IPOD\_Manager.cpp     # Core logic and playback engine

songs.csv            # Persistent storage for tracks



**Technologies Used**

C++

SFML (Simple and Fast Multimedia Library)

Standard Template Library (STL)

Multithreading (<thread>, <atomic>)

