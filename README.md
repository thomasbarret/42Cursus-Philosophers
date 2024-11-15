# 42 Cursus - Philosophers

**Philosophers** is a classic synchronization problem where multiple philosophers sit around a table, and each philosopher thinks and eats using a fork. The goal of the project is to simulate this problem, while ensuring that the philosophers can eat without causing a deadlock, and without allowing more than one philosopher to pick up the same fork at the same time. This problem demonstrates the use of threads, mutexes, and other synchronization techniques in C.

---

## Table of Contents
- [Requirements](#requirements)
- [Compilation and Usage](#compilation-and-usage)
- [Problem Description](#problem-description)
- [File Structure](#file-structure)
- [Synchronization](#synchronization)
- [Libraries](#libraries)

---

## Requirements

- GCC (GNU Compiler Collection)
- Make
- A Unix-based system (Linux/macOS recommended)
- pthread library for thread management

---

## Compilation and Usage

To compile and run the project, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/your_username/philosophers.git
   cd philosophers
   ```

2. To compile the project:
   ```bash
   make
   ```

3. To run the program:
   ```bash
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
   ```

   Example:
   ```bash
   ./philosophers 5 800 200 200 5
   ```

   Where:
   - `number_of_philosophers` is the number of philosophers (and forks).
   - `time_to_die` is the time a philosopher will wait before dying if they haven't eaten.
   - `time_to_eat` is the time it takes for a philosopher to eat.
   - `time_to_sleep` is the time a philosopher will sleep between meals.
   - `number_of_meals` (optional) is the number of times each philosopher should eat.

---

## Problem Description

In this problem, **N philosophers** sit at a round table. Each philosopher thinks, and in order to eat, they must pick up two forks (one from their left and one from their right). The challenge is to simulate this process while avoiding deadlock and starvation. 

The conditions are:
- Philosophers can eat only if they hold two forks.
- Each philosopher alternates between thinking and eating.
- A philosopher dies if they are unable to eat for a certain period of time (e.g., due to starvation).
- Philosophers should not interfere with each other while eating.

---

## File Structure

```
.
├── Makefile                  # Makefile to compile the project
└── src
    ├── function              # Core functionality and algorithms
    │   ├── event.c           # Event handling logic (philosopher's actions)
    │   ├── monitoring.c      # Monitoring thread to check the state of philosophers
    │   ├── mutex.c           # Mutex handling for synchronization
    │   ├── philosophers.c    # Main philosopher logic and simulation
    │   ├── thread.c          # Thread handling for philosophers
    │   └── utils.c           # Utility functions for the project
    └── header                 # Header files for the project
        └── philosophers.h    # Project's header file
```

---

## Synchronization

The core challenge of this project is ensuring that the philosophers can eat without deadlock or race conditions. To do this, the project uses:
- **Mutexes**: To lock the forks and prevent multiple philosophers from accessing the same fork at the same time.
- **Threads**: Each philosopher is represented by a separate thread. The program uses `pthread_create` to spawn threads and `pthread_join` to wait for them to finish.
- **Condition variables**: To signal and wait for specific events, such as when a philosopher is done eating and can release their forks.

### Mutexes and Threads

- Each philosopher has a corresponding thread that alternates between thinking, eating, and sleeping.
- The forks are represented as mutexes, and philosophers need to lock both the left and right forks to eat.
- Proper synchronization ensures that no two philosophers can pick up the same fork simultaneously.

---

## Libraries

The project uses the following libraries:
- **pthread**: For managing threads and synchronization.
- **unistd.h**: For system calls such as `sleep`.
- **stdio.h** and **stdlib.h**: For input/output and memory allocation.
