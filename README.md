# SDL engine

Provides some abstraction over SDL2 API through classes and patterns that are commonly utilized in game development.

Use `--recurse-submodules` when cloning the repository to initialize and update the submodules automatacally:

```bash
$ git clone --recurse-submodules https://github.com/edassis/SDL_engine
```

> This project is part of the TAC discipline offered by UnB.

## Build

- Creates GNU Makefile for the project:
```bash
$ cmake -G "Unix Makefiles" -B build -DCMAKE_BUILD_TYPE=Debug -Wno-dev
```

- Generates the executable:
```bash
$ make -C build
```

## Dependencies
- SDL2, SDL2_image, SDL2_mixer, SDL2_ttf;
- Cmake (3.10 or above);
- GNU make;
- GCC compiler (4.8.1 or above);
- [SDL2 Cmake modules][sdl2_cmake].


[sdl2_cmake]: https://github.com/aminosbh/sdl2-cmake-modules