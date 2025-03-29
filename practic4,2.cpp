#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits> 

struct Character {
    std::string name;
    int health;
    int attackPower;
    int defense;

    void attackTarget(Character &target) {
        int damage = attackPower - target.defense;
        if (damage < 0) damage = 0;
        std::cout << name << " атакует " << target.name << " и наносит " << damage << " урона.\n";
        target.health -= damage;
    }
};


void printStatus(const Character &hero, const Character &monster) {
    std::cout << "\n--- Статус сражения ---\n";
    std::cout << hero.name << " (Здоровье: " << hero.health << ", Атака: " << hero.attackPower << ", Защита: " << hero.defense << ")\n";
    std::cout << monster.name << " (Здоровье: " << monster.health << ", Атака: " << monster.attackPower << ", Защита: " << monster.defense << ")\n";
    std::cout << "-------------------------\n";
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getValidInput() {
    int choice;
    while (true) {
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > 2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова: ";
        } else {
            return choice;
        }
    }
}

void battleGame() {

    Character hero = {"Герой", 100, 20, 5};
    Character monster = {"Монстр", 80, 15, 3};

    while (hero.health > 0 && monster.health > 0) {
        clearScreen();
        printStatus(hero, monster);

        std::cout << "Выберите действие:\n";
        std::cout << "1. Атаковать\n";
        std::cout << "2. Пропустить ход\n";
        std::cout << "Ваш выбор: ";
        int choice = getValidInput();

        if (choice == 1) {
            hero.attackTarget(monster);
        } else {
            std::cout << hero.name << " пропустил ход!\n";
        }

        if (monster.health > 0) {
            monster.attackTarget(hero);
        }
    }

    clearScreen();
    printStatus(hero, monster);

    if (hero.health > 0) {
        std::cout << hero.name << " победил монстра! Поздравляем!\n";
    } else {
        std::cout << monster.name << " победил героя. Удачи в следующей битве!\n";
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0))); 

    char playAgain;
    do {
        battleGame();
        std::cout << "Хотите сыграть снова? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Спасибо за игру!\n";
    return 0;
}
