[![](https://img.shields.io/badge/c++-black?logo=c++&style=for-the-badge)](https://learnxinyminutes.com/c++/)

# Anki cpp
Small library to create anki notes.

### Usage
---
#### Basic usage
```c++
  #include "ankicpp/ankicpp.h"

  using namespace ankicpp;

  ankicpp::Deck deck{"deck-name"};
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(basicNoteType);
  note->addField("Front", "<Front Content>");
  note->addField("Back", "<Bakc Content>");

  deck.addNote(note);

  exportDeck(deck, "./basic/ankicpp.apkg");
```
### Basic and Reversed usage
```c++
  #include "ankicpp/ankicpp.h"
 
  using namespace ankicpp;

  Deck deck{"deck-name"};
  std::shared_ptr<ankicpp::Note> note{};

  note.setType(basicAndReversedNoteType);
  note.addField("Front", "<Front Content>");
  note.addField("Back", "<Back Content>");

  deck.addNote(note);

  exportDeck(deck, "./basic-and-reversed/ankicpp.apkg");
```
### Cloze usage (not working, it's under development)
```c++
  #include "ankicpp/ankicpp.h"
 
  using namespace ankicpp;

  Deck deck{"deck-name"};
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note.setType(clozeNoteType);
  note.addField("Text", "{{c1::text1}} {{c2::text2}}");

  deck.addNote(note);

  exportDeck(deck, "./cloze/ankicpp.apkg");
```

### Build
---
#### Install VCPKG

Official Link: <https://vcpkg.io/en/index.html>

```cmd
cd external
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat # windows
./vcpkg/bootstrap-vcpkg.sh # Unix
```

Export vcpkg to the path if you have it not installed:
```cmd
# Go to repository root
cd ..
export VCPKG_ROOT=./external/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```

Then, build at repository root:
```shell
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
cmake -S . -B ./build -G "Ninja"
cmake --build build
```

### Run
---
```shell
./build/ankicpp/exe
```

### Debug
---
```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "Ninja"
cmake --build build
gdb ./build/ankicpp/exe
```

### Tests
---
```shell
cmake -S . -B build
cmake --build build --target unit-tests
./build/unit-tests
```

### Docs
---
```shell
cmake -S . -B build
cmake --build build --target docs
```
> Link:
> 
> https://natancamargo.github.io/ankicpp/html

### Watch with nodemon
```shell
npx nodemon --exec "cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G "Ninja"  && cmake --build build && ./build/ankicpp/unit-tests" --watch src -e cpp,hpp,txt
```
