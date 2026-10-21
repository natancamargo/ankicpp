[![](https://img.shields.io/badge/c++-black?logo=c++&style=for-the-badge)](https://learnxinyminutes.com/c++/)

# Anki cpp
Small library to create anki notes.

### Usage
---
#### Basic usage
```c++
  #include "ankicpp/ankicpp.h"

  using namespace ankicpp;

  std::shared_ptr<Deck> deck = std::make_shared<Deck>("deck-name");
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(basicNoteType);
  note->addField("Front", "<Front Content>"); // required
  note->addField("Back", "<Back Content>"); // required
  note->addTag("tag1"); // optional
  note->addTag("tag2"); // optional

  deck->addNote(note);

  exportDeck(deck, "./basic/ankicpp.apkg");
```
#### Basic and Reversed usage
```c++
  #include "ankicpp/ankicpp.h"
 
  using namespace ankicpp;

  std::shared_ptr<Deck> deck = std::make_shared<Deck>("deck-namme");
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(basicAndReversedNoteType);
  note->addField("Front", "<Front Content>");
  note->addField("Back", "<Back Content>");

  deck->addNote(note);

  exportDeck(deck, "./basic-and-reversed/ankicpp.apkg");
```
#### Cloze usage
```c++
  #include "ankicpp/ankicpp.h"
 
  using namespace ankicpp;

  std::shared_ptr<Deck> deck = std::make_shared<Deck>("deck-name");
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(clozeNoteType);
  note->addField("Text", "Canberra was founded in {{c1::1913}}.");
  note->addField("Back Extra", "<Some Extra Content>");

  deck->addNote(note);

  exportDeck(deck, "./cloze/ankicpp.apkg");
```
#### Nested decks usage
```c++
  #include "ankicpp/ankicpp.h"
 
  using namespace ankicpp;

  std::shared_ptr<Deck> deck1 = std::make_shared<Deck>("nested-deck");
  std::shared_ptr<Deck> deck2 = std::make_shared<Deck>("child-deck");
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(basicNoteType);
  note->addField("Front", "<Front Content>");
  note->addField("Back", "<Back Content>");

  deck2->addNote(note);
  deck1->addDeck(deck2);
    
  exportDeck(deck, "./nested/ankicpp.apkg");
```
#### Deck with media usage
```c++
  #include "ankicpp/ankicpp.h"

  using namespace ankicpp;

  std::shared_ptr<Deck> deck = std::make_shared<Deck>("media-deck");
  std::shared_ptr<Note> note = std::make_shared<Note>();

  note->setType(basicNoteType);
  note->addField("Front", R"(
&lt;Front Content&gt;<br>
<img src="flynn.jpeg">
)");
  note->addMedia("./images/flynn.jpeg");
  note->addField("Back", "<Back Content>");
  deck->addNote(note);

  exportDeck(deck, "./media/ankicpp.apkg");
```
### Build
---
#### Install VCPKG

Official Link: <https://vcpkg.io/en/index.html>

Export vcpkg to the path and export vcpkg root:
```cmd
export VCPKG_ROOT=/path/to/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```

Run bootstrap:
```cmd
cd $VCPKG_ROOT
.\vcpkg\bootstrap-vcpkg.bat # windows
./vcpkg/bootstrap-vcpkg.sh # Unix
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
