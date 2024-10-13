This README was written in two languages:
- **Polski** [Polski](#polski)
- **English** [English](#english)

# Memory Game (English)

## Table of Contents
1. [Project Overview](#project-overview)
2. [Setup and Compilation](#setup-and-compilation)
3. [Game Instructions](#game-instructions)
4. [Key Features](#key-features)
5. [Good Practices and Code Design](#good-practices-and-code-design)

---

## Project Overview

This is a simple command-line memory game where players uncover pairs of cards on a grid, attempting to match symbols. The game can be played in two modes:
- **2-Player Mode**: Two human players alternate turns to match pairs of cards.
- **Vs. Computer Mode**: A single player competes against the computer.

The game includes optional features like **animations** for smooth card reveals and **extra turn rewards** for correct guesses.

---

## Setup and Compilation

### Prerequisites

To run this program, you need a C++ development environment. The game is compatible with most operating systems (Windows, Linux, macOS). The setup depends on your system, but generally, you will need:

- A **C++ compiler** (e.g., g++, clang, or Visual Studio).
- A terminal or command-line interface to compile and run the program.

### Compilation Instructions

1. **Download the code**:
   Clone or download the repository from GitHub to your local machine.
   
2. **Open terminal**:
   Navigate to the folder where the game code is stored.

3. **Compile the code**:
   Using a terminal, run the following command to compile the program (assuming `g++` is installed):

   ```
   g++ -o memory_game memory_game.cpp
   ```

   This will create an executable named `memory_game`.

4. **Run the game**:
   After compiling, run the game by typing:

   ```
   ./memory_game
   ```

   If you're on Windows, run it as:

   ```
   memory_game.exe
   ```

---

## Game Instructions

### Main Menu Options

When you launch the game, you will see the following main menu:

```
 _  _  ____  _  _ 
( \/ )(  __)( \/ )
/ \/ \ ) _) / \/ \
\_)(_/(____)\_)(_/ 

Welcome to Memory Game!

(1) 2-Players Mode
(2) Vs. Computer Mode
(3) Settings
(4) Exit

Input: 
```

### How to Play

- **Goal**: The objective is to uncover pairs of matching cards on the board. The player with the most matched pairs wins.
  
- **2-Player Mode**:
  1. Select "1" to play in 2-player mode.
  2. Choose the board size by entering the number of rows and columns.
  3. Players take turns selecting two cards, trying to match the symbols.
  4. If a match is found, the player gets a point, and (optionally) an extra turn.
  5. The game ends when all pairs are matched.

- **Vs. Computer Mode**:
  1. Select "2" to play against the computer.
  2. Choose the board size by entering the number of rows and columns.
  3. You take turns against the computer. The game ends when all pairs are matched.

### Settings Menu

- Select "3" from the main menu to adjust game settings:
  - Enable or disable **card reveal animations**.
  - Enable or disable **extra turn rewards** for correct matches.

---

## Key Features

1. **Smooth Card Reveal Animation**:
   - Each card can be revealed with a smooth animation showing different transition steps.
   - You can toggle this feature in the settings menu.

2. **Extra Turn Rewards**:
   - If a player finds a matching pair, they are rewarded with an extra turn (if enabled in settings).

3. **AI Opponent**:
   - In Vs. Computer mode, the computer uses a random algorithm to select cards.

4. **Win Animations**:
   - If a player wins, a trophy animation is displayed.
   - If the computer wins, a "losing face" animation is shown.

5. **Adjustable Board Size**:
   - Players can customize the number of rows and columns for the board.

---

## Good Practices and Code Design

1. **Code Modularity**: The game logic is divided into several functions, each handling a specific part of the game (e.g., board initialization, animations, card selection). This makes the code easier to maintain and extend.

2. **Use of Standard Libraries**:
   - Libraries like `<vector>`, `<algorithm>`, `<chrono>`, and `<thread>` are utilized to handle dynamic data structures, shuffling cards, and creating smooth animations.
   - These libraries improve code readability and efficiency.

3. **Cross-Platform Support**: The game includes conditional compilation to clear the screen on both Windows (`cls`) and Unix/Linux (`clear`) systems.

4. **Readability and Comments**: The code is well-commented, providing explanations for major functions and logic.

5. **User-Friendly Prompts**: Error handling is incorporated (e.g., preventing players from selecting already revealed cards or the same card twice).

---

# Gra w Memory (Polski)

## Spis treści
1. [Opis projektu](#opis-projektu)
2. [Konfiguracja i kompilacja](#konfiguracja-i-kompilacja)
3. [Instrukcje do gry](#instrukcje-do-gry)
4. [Kluczowe funkcje](#kluczowe-funkcje)
5. [Dobre praktyki i projekt kodu](#dobre-praktyki-i-projekt-kodu)

---

## Opis projektu

To prosta gra w pamięć działająca w konsoli, w której gracze odkrywają pary kart na planszy, próbując dopasować symbole. Gra może być rozgrywana w dwóch trybach:
- **Tryb 2-graczy**: Dwóch graczy na zmianę odkrywa karty, aby dopasować pary.
- **Tryb vs. komputer**: Jeden gracz rywalizuje z komputerem.

Gra zawiera opcjonalne funkcje, takie jak **animacje** dla płynnych odkryć kart oraz **nagrody za dodatkowe tury** za poprawne zgadywanie.

---

## Konfiguracja i kompilacja

### Wymagania wstępne

Aby uruchomić ten program, potrzebujesz środowiska programistycznego C++. Gra jest kompatybilna z większością systemów operacyjnych (Windows, Linux, macOS). Konfiguracja zależy od twojego systemu, ale generalnie będziesz potrzebować:

- **Kompilatora C++** (np. g++, clang lub Visual Studio).
- Terminala lub interfejsu wiersza poleceń do kompilacji i uruchamiania programu.

### Instrukcje kompilacji

1. **Pobierz kod**:
   Sklonuj lub pobierz repozytorium z GitHub na swój lokalny komputer.
   
2. **Otwórz terminal**:
   Przejdź do folderu, w którym znajduje się kod gry.

3. **Kompiluj kod**:
   W terminalu uruchom następujące polecenie, aby skompilować program (zakładając, że masz zainstalowany `g++`):

   ```
   g++ -o memory_game memory_game.cpp
   ```

   To stworzy plik wykonywalny o nazwie `memory_game`.

4. **Uruchom grę**:
   Po skompilowaniu uruchom grę, wpisując:

   ```
   ./memory_game
   ```

   Jeśli jesteś na systemie Windows, uruchom jako:

   ```
   memory_game.exe
   ```

---

## Instrukcje do gry

### Opcje głównego menu

Gdy uruchomisz grę, zobaczysz następujące główne menu:

```
 _  _  ____  _  _ 
( \/ )(  __)( \/ )
/ \/ \ ) _) / \/ \
\_)(_/(____)\_)(_/ 

Witaj w grze w pamięć!

(1) Tryb 2-graczy
(2) Tryb vs. komputer
(3) Ustawienia
(4) Wyjście

Wybór: 
```

### Jak grać

- **Cel**: Celem gry jest odkrycie par pasujących kart na planszy. Gracz z największą liczbą dopasowanych par wygrywa.
  
- **Tryb 2-graczy**:
  1. Wybierz "1", aby grać w trybie 2-graczy.
  2. Wybierz rozmiar planszy, wpisując liczbę wierszy i kolumn.
  3. Gracze na zmianę wybierają dwie karty, próbując dopasować symbole.
  4. Jeśli karta pasuje, gracz zdobywa punkt, a (opcjonalnie) dodatkową turę.
  5. Gra kończy się, gdy wszystkie pary zostaną dopasowane.

- **Tryb vs. komputer**:
  1. Wybierz "2", aby grać przeciwko komputerowi.
  2. Wybierz rozmiar planszy, wpisując liczbę

 wierszy i kolumn.
  3. Na przemian wykonujesz ruchy przeciwko komputerowi. Gra kończy się, gdy wszystkie pary zostaną dopasowane.

### Menu ustawień

- Wybierz "3" z głównego menu, aby dostosować ustawienia gry:
  - Włącz lub wyłącz **animacje odkrywania kart**.
  - Włącz lub wyłącz **nagrody za dodatkowe tury** za poprawne dopasowania.

---

## Kluczowe funkcje

1. **Płynna animacja odkrywania kart**:
   - Każda karta może być odkryta z płynna animacją pokazującą różne etapy przejścia.
   - Możesz przełączać tę funkcję w menu ustawień.

2. **Nagrody za dodatkowe tury**:
   - Jeśli gracz znajdzie dopasowaną parę, otrzymuje dodatkową turę (jeśli włączono w ustawieniach).

3. **Przeciwnik AI**:
   - W trybie vs. komputer komputer używa losowego algorytmu do wyboru kart.

4. **Animacje zwycięstwa**:
   - Jeśli gracz wygra, wyświetla się animacja trofeum.
   - Jeśli komputer wygra, wyświetla się animacja „przegranej twarzy”.

5. **Dostosowywany rozmiar planszy**:
   - Gracze mogą dostosować liczbę wierszy i kolumn planszy.

---

## Dobre praktyki i projekt kodu

1. **Modularność kodu**: Logika gry jest podzielona na kilka funkcji, z których każda obsługuje konkretną część gry (np. inicjalizacja planszy, animacje, wybór kart). Ułatwia to utrzymanie i rozwój kodu.

2. **Wykorzystanie standardowych bibliotek**:
   - Biblioteki takie jak `<vector>`, `<algorithm>`, `<chrono>` i `<thread>` są używane do obsługi dynamicznych struktur danych, tasowania kart i tworzenia płynnych animacji.
   - Te biblioteki poprawiają czytelność i efektywność kodu.

3. **Wsparcie dla wielu platform**: Gra zawiera kompilację warunkową do czyszczenia ekranu zarówno w systemie Windows (`cls`), jak i Unix/Linux (`clear`).

4. **Czytelność i komentarze**: Kod jest dobrze skomentowany, dostarczając wyjaśnień dla głównych funkcji i logiki.

5. **Przyjazne dla użytkownika komunikaty**: Zintegrowano obsługę błędów (np. uniemożliwiając graczom wybieranie już odkrytych kart lub tej samej karty dwukrotnie).

---
