#include <iostream>
#include <vector>
#include <string>
#include <limits> 

void printField(const std::vector<char>& field) {
    for (int i = 0; i < 9; i += 3) {
        std::cout << " " << field[i] << " | " << field[i + 1] << " | " << field[i + 2] << "\n";
        if (i < 6) std::cout << "---+---+---\n";
    }
    std::cout << std::endl;
}

bool checkWin(const std::vector<char>& field, char player) {
    const int winCombos[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6}            
    };

    for (const auto& combo : winCombos) {
        if (field[combo[0]] == player && field[combo[1]] == player && field[combo[2]] == player) {
            return true;
        }
    }
    return false;
}


int getValidInput(const std::vector<char>& field) {
    int choice;
    while (true) {
        std::cout << "Введите номер клетки (1-9): ";
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 9 || field[choice - 1] == 'X' || field[choice - 1] == 'O') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
        } else {
            break;
        }
    }
    return choice - 1;
}

int main() {
    char playAgain;
    do {
        std::vector<char> field = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char currentPlayer = 'X';
        int moves = 0;

        while (true) {
            system("clear"); 
            printField(field);

            std::cout << "Ход игрока " << currentPlayer << ".\n";
            int move = getValidInput(field);
            field[move] = currentPlayer;
            moves++;

            if (checkWin(field, currentPlayer)) {
                system("clear");
                printField(field);
                std::cout << "Игрок " << currentPlayer << " выиграл!\n";
                break;
            } else if (moves == 9) {
                system("clear");
                printField(field);
                std::cout << "Ничья!\n";
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        std::cout << "Хотите сыграть ещё раз? (Y/N): ";
        std::cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    return 0;
}
