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
    
    for (int i = 0; i < totalCards / 2; ++i) {
        symbols.push_back('A' + i); // Dodaje symbole dla par kart.
        symbols.push_back('A' + i);
    }
    
    random_device rd;
    mt19937 g(rd());
    shuffle(symbols.begin(), symbols.end(), g); // Tasuje symbole kart.

    int k = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            board[i][j] = symbols[k++]; // Rozmieszcza symbole na planszy.
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

// Funkcja przeprowadzająca rozgrywkę dla wybranego trybu.
void playGame(int rows, int cols, bool isVsComputer = false) {
    vector<vector<char>> board(rows, vector<char>(cols)); // Tworzy planszę.
    vector<vector<bool>> revealed(rows, vector<bool>(cols, false)); // Tworzy tablicę odkrytych kart.

    initializeBoard(board); // Inicjalizuje planszę z kartami.

    int currentPlayer = 1; // Ustawia aktualnego gracza.
    int pairsFound = 0; // Liczba znalezionych par.
    int totalPairs = (rows * cols) / 2; // Całkowita liczba par.

    int player1Pairs = 0; // Punkty gracza 1.
    int computerPairs = 0; // Punkty komputera.

    while (pairsFound < totalPairs) { // Dopóki nie znaleziono wszystkich par.
        bool extraTurn = false; // Czy gracz dostaje dodatkową rundę?

        do {
            displayBoard(board, revealed); // Wyświetla planszę.
            cout << "Player " << (currentPlayer == 1 ? "1" : (isVsComputer ? "Computer" : "2")) << "'s turn!" << endl;

            int r1, c1, r2, c2;

            if (currentPlayer == 2 && isVsComputer) {
                tie(r1, c1) = computerPickCard(revealed, rows, cols); // Wybiera kartę dla komputera.
                cout << "Computer selected: (" << r1 + 1 << ", " << c1 + 1 << ")" << endl;
                this_thread::sleep_for(chrono::milliseconds(1000)); // Opóźnia wybór.
            } else {
                do {
                    cout << "Enter row and column of first card: ";
                    cin >> r1 >> c1;
                    r1--; c1--;
                    if (revealed[r1][c1]) {
                        cout << "Card is already revealed! Choose a different one.\n"; // Sprawdza, czy karta nie jest już odkryta.
                    }
                } while (revealed[r1][c1]);
            }

            if (animationsEnabled) {
                smoothRevealAnimation(r1, c1, board, revealed); // Odkrywa kartę z animacją.
            } else {
                revealCard(r1, c1, board, revealed); // Odkrywa kartę bez animacji.
            }

            if (currentPlayer == 2 && isVsComputer) {
                tie(r2, c2) = computerPickCard(revealed, rows, cols); // Komputer wybiera drugą kartę.
                cout << "Computer selected: (" << r2 + 1 << ", " << c2 + 1 << ")" << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
            } else {
                do {
                    cout << "Enter row and column of second card: ";
                    cin >> r2 >> c2;
                    r2--; c2--;
                    if (r1 == r2 && c1 == c2) {
                        cout << "You cannot choose the same card twice! Choose a different card.\n"; // Gracz nie może wybrać tej samej karty dwa razy.
                    } else if (revealed[r2][c2]) {
                        cout << "Card is already revealed! Choose a different one.\n";
                    }
                } while ((r1 == r2 && c1 == c2) || revealed[r2][c2]);
            }

            if (animationsEnabled) {
                smoothRevealAnimation(r2, c2, board, revealed); // Odkrywa drugą kartę z animacją.
            } else {
                revealCard(r2, c2, board, revealed); // Odkrywa drugą kartę bez animacji.
            }

            if (board[r1][c1] == board[r2][c2]) { // Sprawdza, czy odkryte karty są takie same.
                cout << "It's a match!";
                pairsFound++; // Zwiększa liczbę znalezionych par.
                if (currentPlayer == 1) {
                    player1Pairs++; // Gracz 1 zdobywa punkt.
                } else if (isVsComputer) {
                    computerPairs++; // Komputer zdobywa punkt.
                }
                if (rewardsEnabled) { // Sprawdza, czy nagrody są włączone.
                    cout << " " << (currentPlayer == 1 ? "Player 1" : (isVsComputer ? "Computer" : "Player 2")) << " gets an extra turn!" << endl;
                    extraTurn = true; // Gracz dostaje dodatkową rundę.
                } else {
                    cout << endl;
                    extraTurn = false;
                }
            } else {
                cout << "Not a match." << endl; // Karty nie są takie same.
                revealed[r1][c1] = false; // Ukrywa karty.
                revealed[r2][c2] = false;
                extraTurn = false;
            }
            this_thread::sleep_for(chrono::milliseconds(500)); // Krótkie opóźnienie.

        } while (extraTurn && pairsFound < totalPairs); // Kontynuuje, jeśli gracz ma dodatkową rundę.

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Zmienia gracza.
    }

    cout << "Game over! "; // Koniec gry.
    if (isVsComputer) {
        if (player1Pairs > computerPairs) {
            cout << "Player 1 wins with " << player1Pairs << " pairs!" << endl; // Wyświetla wynik.
            displayTrophyAnimation("Player 1");
            
        } else if (computerPairs > player1Pairs) {
            cout << "Computer wins with " << computerPairs << " pairs!" << endl;
            displayLoseAnimation();
        } else {
            cout << "It's a tie!" << endl;
        }
    } else {
        displayTrophyAnimation("Player " + to_string((pairsFound % 2 == 0) ? 2 : 1));
    }
    
    this_thread::sleep_for(chrono::milliseconds(3000)); // Czeka 3 sekundy przed zakończeniem gry.
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
