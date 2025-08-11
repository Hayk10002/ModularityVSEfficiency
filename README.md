# ModularityVSEfficiency

## Table of Contents
- [Introduction](#introduction)
- [Build and Run](#build-and-run)
- [Possible Output](#possible-output)
- [How does this work](#how-does-this-work)

The purpose of this project is to explore the trade-off between modularity and efficiency when processing large vectors. By comparing separate, modular loops with a fused, more efficient loop, the code demonstrates how increasing modularity can sometimes come at the cost of performance, particularly in terms of cache usage and execution time.

## Build and Run
To clone and run this project, you'll need [Git](https://git-scm.com) and [CMake](https://cmake.org/) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/Hayk10002/ModularityVSEfficiency

# Go into the repository
$ cd ModularityVSEfficiency

# We need to generate the executable in Release configuration to be able to observe the time difference between fused and non-fused loops

# Generate the build files
$ cmake -DCMAKE_BUILD_TYPE=Release -S . -B build

# Build the project
$ cmake --build build --config Release

# Then, run the executable generated in the `build` directory with two number arguments.
$ your/path/to/exe/main.exe {vector_size} {iteration_count}
# example - .../main.exe 10000 1000
```

## Possible Output

```
Time not fused:   652ms
Time     fused:   534ms
```

## How does this work
The program initializes three large vectors with random integers. It then measures the time taken to compute the result vector in two ways:
- **Not fused:** Performs multiplication and addition in separate loops (using separate functions).
- **Fused:** Performs both operations in a single loop (using a fused function).

By timing both approaches over multiple iterations, the program demonstrates the effect of loop fusion on cache efficiency and overall performance. Fusing loops can reduce memory traffic and improve cache locality, often resulting in faster execution times.

Note: The actual timing results will depend on your hardware and the input sizes you provide.
