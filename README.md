[![](https://img.shields.io/badge/c++-black?logo=c++&style=for-the-badge)](https://learnxinyminutes.com/c++/)

# Anki cpp
Small library to create anki notes.

### Usage
---
#### Basic usage
```c++
  #include "ankicpp"

  using namespace ankicpp;

  Deck deck{"deck-name"};
  Note note;

  note.setType(NoteType.BASIC);
  note.setField("Front", "...");
  note.setField("Back", "...");

  note.addTag("tag1");

  deck.addNote(note);
  exportDeck(deck, "./ankicpp.apkg");
```
### Cloze usage
```c++
  #include "ankicpp"
 
  using namespace ankicpp;

  Deck deck{"deck-name"};
  Note note;

  note.setType(NotesType.Cloze);
  note.setField("Text", "{{c1::text1}} {{c2::text2}}");

  deck.addNote(&note);
  deck.export("./path");
```
### With a new template usage
```c++
  #include "ankicpp"

  using namespace ankicpp;

  Deck deck{"deck-name"};
  Note note;

  note.setType(NotesType.BASIC);
  note.setField("Front", "...");
  note.setField("Back", "...");

  Template templatee{"Card 1"};
  templatee.setFrontTemplate("{{Front}}");
  templatee.setBackTemplate(R"(
  {{FrontSide}}

  <hr id=answer>

  {{Back}}
          )");
  note.setStyle(R"(
   .card {
     font-family: arial;
     font-size: 20px;
     line-height: 1.5;
     text-align: center;
     color: black;
     background-color: white;
   }
  )");
  note.addTemplate(newType);

  deck.addNote(note);
  exportDeck(deck, "./ankicpp.apkg");
```

### Build
---
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

### Watch with nodemon
```shell
npx nodemon --exec "cmake -S . -B build && cmake --build build && ./build/ankicpp/exe" --watch src -e cpp,hpp,txt
```
