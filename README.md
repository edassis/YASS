# SDL engine

Provides some abstraction over SDL2 API through classes and patterns that are commonly utilized in game development.

> This project is part of the TAC discipline offered by UnB.

## Build

- Creates GNU Makefile for the project:
```bash
$ cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

- Generates the executable:
```bash
$ make
```

## Dependencies
- SDL2, SDL2_image, SDL2_mixer, SDL2_ttf;
- cmake (3.10 or greater);
- GNU make;
- GCC compiler (4.8.1 or greater).