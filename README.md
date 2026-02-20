[![](https://img.shields.io/badge/c++-black?logo=c++&style=for-the-badge)](https://learnxinyminutes.com/c++/)

## Anki cpp
Small api to create anki notes.

### Build
```shell
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
cmake -S . -B ./build -G "Ninja"
cmake --build build
```

### Run
```shell
./build/ankicpp/exe
```

### Debug
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
gdb ./build/ankicpp/exe
```

### Tests
```shell
cmake -S . -B build
cmake --build build --target unit-tests
./build/tests/unit-tests
```

### Watch with nodemon
```shell
npx nodemon --exec "cmake -S . -B build && cmake --build build && ./build/ankicpp/exe" --watch src -e cpp,hpp,txt
```
