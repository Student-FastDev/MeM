#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>

using namespace std;

bool rewardsEnabled = true; // Zmienna globalna określająca, czy włączone są nagrody.
bool animationsEnabled = true; // Zmienna globalna określająca, czy włączone są animacje.

// Funkcja czyszcząca ekran.
void clearScreen() {
#ifdef _WIN32
    system("cls"); // Dla systemu Windows.
#else
    system("clear"); // Dla systemu Unix/Linux.
#endif
}

// Trophy animation frames
void displayTrophyAnimation(string player) {
    string trophy1 = R"(
             ___________
            '._==_==_=_.'  
            .-/\:      /-.  
           | (|:.     |) |  
            '-|:.     |-'   
              \::.    /     
               '::. .'      
                 ) (        
               _.' '._      
              """"""""      
    )";

    
    string trophy2 = R"(
             ___________
            '._==_==_=_.'  
            .-\:      /-.  
           | (|:.     |) |  
            '-|:.     |-'   
              \::.    /     
               '::. .'      
                 ) (        
               _.' '._      
              """"""""      
    )";

    for (int i = 0; i < 6; ++i) {  // Loop to alternate the frames
        clearScreen();
        if (i % 2 == 0) {
            cout << "          " << player << " have won!" << endl;
            cout << trophy1 << endl;
        } else {
            cout << "          " << player << " have won!" << endl;
            cout << trophy2 << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Losing face animation for AI win
void displayLoseAnimation() {
    
    string loseFace = R"(
     .-""""""-.
   .'          '.
  /   O      O   \
 :      ______    :
 |     /      \   |  
 :    |        |  :
  \    \______/  /
   '.          .'
     '-......-'
    )";
    
    clearScreen();
    cout << "    You've lost!" << endl;
    
    cout << loseFace << endl;
}

// Funkcja wyświetlająca planszę gry wraz z odkrytymi kartami.
void displayBoard(const vector<vector<char>>& board, const vector<vector<bool>>& revealed, int animRow = -1, int animCol = -1, char animChar = '\0') {
    clearScreen(); // Czyści ekran.
    cout << "    ";
    for (int i = 0; i < board[0].size(); ++i)
        cout << setw(2) << i + 1 << " "; // Wyświetla numery kolumn.
    cout << endl;

    for (int i = 0; i < board.size(); ++i) {
        cout << setw(2) << i + 1 << " "; // Wyświetla numery wierszy.
        for (int j = 0; j < board[i].size(); ++j) {
            if (i == animRow && j == animCol) {
                cout << setw(2) << animChar << " "; // Wyświetla animację dla danego pola.
            } else if (revealed[i][j]) {
                cout << setw(2) << board[i][j] << " "; // Wyświetla odkryte karty.
            } else {
                cout << setw(2) << "#" << " "; // Ukryte karty.
            }
        }
        cout << endl;
    }
}

// Funkcja wyświetlająca animację odkrywania karty.
void smoothRevealAnimation(int row, int col, const vector<vector<char>>& board, vector<vector<bool>>& revealed) {
    char steps[] = {'#', '-', '/', '|', '\\', '?', board[row][col]}; // Kroki animacji odkrywania karty.
    int totalSteps = sizeof(steps) / sizeof(steps[0]);

    for (int i = 0; i < totalSteps; ++i) {
        revealed[row][col] = true; // Odkrywa kartę.
        int delay = 50 + (i * 100 / totalSteps); // Ustala opóźnienie animacji.
        displayBoard(board, revealed, row, col, steps[i]); // Wyświetla planszę z animacją.
        this_thread::sleep_for(chrono::milliseconds(delay)); // Czeka przez ustalony czas.
    }
}

// Funkcja odkrywająca kartę bez animacji.
void revealCard(int row, int col, vector<vector<bool>>& revealed) {
    revealed[row][col] = true; // Odkrywa kartę.
}

// Funkcja inicjalizująca planszę gry z kartami.
void initializeBoard(vector<vector<char>>& board) {
    vector<char> symbols;
    int totalCards = board.size() * board[0].size();
    
    // Użycie wielkich liter, małych liter oraz cyfr, aby mieć wystarczającą ilość symboli.
    for (char c = 'A'; c <= 'Z'; ++c) symbols.push_back(c);
    for (char c = 'a'; c <= 'z'; ++c) symbols.push_back(c);
    for (char c = '0'; c <= '9'; ++c) symbols.push_back(c);

    // Sprawdzenie, czy jest wystarczająca ilość symboli na planszę.
    if (totalCards / 2 > symbols.size()) {
        cerr << "Board is too big to generate unique symbols." << endl;
        exit(1); // Wyjście, jeśli plansza jest zbyt duża na dostępne symbole.
    }

    // Duplikowanie symboli, aby stworzyć pary.
    symbols.resize(totalCards / 2);
    symbols.insert(symbols.end(), symbols.begin(), symbols.end());

    // Tasowanie symboli.
    random_device rd;
    mt19937 g(rd());
    shuffle(symbols.begin(), symbols.end(), g);

    // Przypisanie symboli do planszy.
    int k = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            board[i][j] = symbols[k++];
        }
    }
}


// Funkcja wyświetlająca planszę po odkryciu karty.
void revealCard(int row, int col, const vector<vector<char>>& board, vector<vector<bool>>& revealed) {
    revealed[row][col] = true; // Odkrywa kartę.
    displayBoard(board, revealed); // Wyświetla planszę.
}

// Funkcja wyświetlająca menu ustawień gry.
void displaySettingsMenu() {
    clearScreen();
    cout << "+-------------------------+\n";
    cout << "| Animations  |  " << (animationsEnabled ? "Enabled " : "Disabled") << " |\n"; // Wyświetla stan animacji.
    cout << "+-------------------------+\n";
    cout << "| Rewards*    |  " << (rewardsEnabled ? "Enabled " : "Disabled") << " |\n"; // Wyświetla stan nagród.
    cout << "+-------------------------+\n";
    cout << "* - the person who got a match will get an extra round;\n\n"; // Informacja o dodatkowej rundzie.
}

// Funkcja wyświetlająca główne menu gry.
void displayMainMenu() {
    clearScreen();
    cout << " _  _  ____  _  _ \n";
    cout << "( \\/ )(  __)( \\/ )\n";
    cout << "/ \\/ \\ ) _) / \\/ \\\n";
    cout << "\\_)(_/(____)\\_)(_/ \n";
    cout << "\nWelcome to Memory Game!\n\n"; // Wyświetla tytuł gry.
    cout << "(1) 2-Players Mode\n";
    cout << "(2) Vs. Computer Mode\n";
    cout << "(3) Settings\n"; // Opcje menu.
    cout << "(4) Exit\n";
    cout << "\nInput: ";
}

// Funkcja wybierająca karty przez komputer.
pair<int, int> computerPickCard(const vector<vector<bool>>& revealed, int rows, int cols) {
    int r, c;
    do {
        r = rand() % rows;
        c = rand() % cols;
    } while (revealed[r][c]); // Losuje karty, które nie są jeszcze odkryte.
    return {r, c}; // Zwraca pozycję karty.
}

void playGame(int rows, int cols, bool isVsComputer = false) {
    vector<vector<char>> board(rows, vector<char>(cols)); // Tworzy planszę.
    vector<vector<bool>> revealed(rows, vector<bool>(cols, false)); // Tworzy tablicę odkrytych kart.

    initializeBoard(board); // Inicjalizuje planszę z kartami.

    int currentPlayer = 1; // Ustawia aktualnego gracza.
    int pairsFound = 0; // Liczba odkrytych par.
    int totalPairs = (rows * cols) / 2; // Całkowita liczba par do odkrycia.

    int player1Pairs = 0, player2Pairs = 0, computerPairs = 0; // Liczba par odkrytych przez każdego gracza.
    bool roundWon = false; // Czy gracz wygrał rundę.

    while (pairsFound < totalPairs) { // Główna pętla gry.
        displayBoard(board, revealed); // Wyświetla planszę.
        
        int row1, col1, row2, col2; // Wybór dwóch kart.

        // Wybór pierwszej karty
        if (isVsComputer && currentPlayer == 2) {
            do {
                tie(row1, col1) = computerPickCard(revealed, rows, cols); // Komputer wybiera kartę.
            } while (revealed[row1][col1]); // Sprawdzanie, czy karta nie została już odkryta.
        } else {
            do {
                cout << "Player " << currentPlayer << ", pick the first card (row and column): ";
                cin >> row1 >> col1;
                --row1; --col1; // Dopasowanie do indeksów tablicy.
            } while (row1 < 0 || row1 >= rows || col1 < 0 || col1 >= cols || revealed[row1][col1]); // Sprawdzanie poprawności wyboru.
        }

        if (animationsEnabled) smoothRevealAnimation(row1, col1, board, revealed); // Animacja odkrywania karty.
        else revealCard(row1, col1, board, revealed); // Odkrywa kartę bez animacji.

        // Wybór drugiej karty
        if (isVsComputer && currentPlayer == 2) {
            do {
                tie(row2, col2) = computerPickCard(revealed, rows, cols); // Komputer wybiera kartę.
            } while ((row1 == row2 && col1 == col2) || revealed[row2][col2]); // Sprawdzanie, czy karta nie została już odkryta.
        } else {
            do {
                cout << "Player " << currentPlayer << ", pick the second card (row and column): ";
                cin >> row2 >> col2;
                --row2; --col2; // Dopasowanie do indeksów tablicy.
            } while ((row1 == row2 && col1 == col2) || row2 < 0 || row2 >= rows || col2 < 0 || col2 >= cols || revealed[row2][col2]); // Sprawdzanie poprawności wyboru.
        }

        if (animationsEnabled) smoothRevealAnimation(row2, col2, board, revealed); // Animacja odkrywania karty.
        else revealCard(row2, col2, board, revealed); // Odkrywa kartę bez animacji.

        // Sprawdza, czy gracz odkrył parę.
        if (board[row1][col1] == board[row2][col2]) {
            cout << "It's a match!\n";
            pairsFound++; // Zwiększa liczbę odkrytych par.
            roundWon = true; // Gracz wygrał rundę.
            if (currentPlayer == 1) player1Pairs++; // Aktualizacja wyniku gracza 1.
            else if (isVsComputer) computerPairs++; // Aktualizacja wyniku komputera.
            else player2Pairs++; // Aktualizacja wyniku gracza 2.
        } else {
            cout << "Not a match.\n";
            this_thread::sleep_for(chrono::milliseconds(1000)); // Opóźnienie, aby gracze mogli zobaczyć wynik.
            revealed[row1][col1] = revealed[row2][col2] = false; // Ukrywa karty, jeśli nie są parą.
            roundWon = false; // Gracz nie wygrał rundy.
        }

        // Zmiana gracza, jeśli runda nie została wygrana lub jeśli nagrody są wyłączone.
        if (!(roundWon && rewardsEnabled)) {
            currentPlayer = (currentPlayer == 1) ? 2 : 1; // Zmienia aktualnego gracza.
        }
    }

    // Wyświetlanie wyników gry po zakończeniu.
    cout << "\nGame Over! Final Results:\n";
    cout << "Player 1 Pairs: " << player1Pairs << endl;
    
    if (isVsComputer) {
        cout << "Computer Pairs: " << computerPairs << endl;
    } else {
        cout << "Player 2 Pairs: " << player2Pairs << endl;
    }

    // Wyświetlanie zwycięzcy.
    if (player1Pairs > (isVsComputer ? computerPairs : player2Pairs)) {
        displayTrophyAnimation("Player 1");
    } else if (isVsComputer && computerPairs > player1Pairs) {
        displayLoseAnimation(); // Komputer wygrywa, wyświetla animację przegranej.
    } else if (!isVsComputer && player2Pairs > player1Pairs) {
        displayTrophyAnimation("Player 2");
    } else {
        cout << "It's a tie!" << endl; // Remis.
    }
}




// Funkcja obsługująca główne menu.
void mainMenu() {
    while (true) {
        displayMainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                clearScreen();
                int rows, cols;
                cout << "Please choose the board size." << endl;
                cout << "Enter number of rows: ";
                cin >> rows;
                cout << "Enter number of columns: ";
                cin >> cols;
                playGame(rows, cols); // Uruchamia tryb gry dla dwóch graczy.
                break; // Dodano break.
            }
            case 2: {
                clearScreen();
                int rows, cols;
                cout << "Please choose the board size." << endl;
                cout << "Enter number of rows: ";
                cin >> rows;
                cout << "Enter number of columns: ";
                cin >> cols;
                playGame(rows, cols, true); // Uruchamia tryb gry przeciwko komputerowi.
                break; // Dodano break.
            }
            case 3: {
                displaySettingsMenu();
                cout << "Enable animations during card reveals? (1 for Yes, 0 for No): ";
                cin >> animationsEnabled;
                cout << "Enable extra turn rewards for correct guesses? (1 for Yes, 0 for No): ";
                cin >> rewardsEnabled;
                break;
            }
            case 4: {
                return; // Kończy pętlę i opuszcza funkcję.
            }
            default: {
                cout << "Invalid choice." << endl; // Komunikat o błędnym wyborze.
                break; // Dodano break.
            }
        }
    }
}

// Funkcja główna programu.
int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicjalizuje generator losowy.
    mainMenu(); // Uruchamia główne menu gry.
    return 0; // Zakończenie programu.
}
