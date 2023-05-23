#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9; 


struct SudokuGrid {
    int cells[SIZE][SIZE];
};

void displayBoard(const SudokuGrid& grid) {
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0 && i != 0) {
            cout << "\t------------------------------------------------------------------" << endl;
        }
        for (int j = 0; j < SIZE; ++j) {
            if (j % 3 == 0 && j != 0) {
                cout << "  | ";
            }
            if (grid.cells[i][j] == 0) {
                cout << "\t\033[1;31m" << grid.cells[i][j] << "\033[0m ";
            }
            else {
                cout << "\t\033[1;32m" << grid.cells[i][j] << "\033[0m ";
            }
        }
        cout << endl;
    }
}

void enterValue(SudokuGrid& grid, int row, int col, int value) {
    grid.cells[row][col] = value;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

bool isValidValue(const SudokuGrid& grid, int row, int col, int value) {
    for (int i = 0; i < SIZE; ++i) {
        if (grid.cells[row][i] == value || grid.cells[i][col] == value) {
            return false;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (grid.cells[i][j] == value) {
                return false;
            }
        }
    }

    return true;
}

void getPlayerInput(SudokuGrid& grid) {
    int row, col, value;
    cout << "\n\tВведите номер строки (от 1 до 9): ";
    while (!(cin >> row) || row < 1 || row > 9) {
        cout << "\n\t\033[1;31mОшибка ввода! Введите номер строки от 1 до 9: \033[0m";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\n\tВведите номер столбца (от 1 до 9): ";
    while (!(cin >> col) || col < 1 || col > 9) {
        cout << "\t\t\n\033[1;31mОшибка ввода! Введите номер столбца от 1 до 9: \033[0m";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (grid.cells[row - 1][col - 1] != 0) {
        cout << "\n\t\033[1;31mОшибка ввода! Указанная позиция уже содержит значение. Введите новую строку и столбец.\033[0m" << endl;
        return;
    }

    cout << "\n\tВведите значение (от 1 до 9): \033[0m";
    while (!(cin >> value) || value < 1 || value > 9 || !isValidValue(grid, row - 1, col - 1, value)) {
        if (!isValidValue(grid, row - 1, col - 1, value)) {
            cout << "\n\t\033[1;31mОшибка ввода! Данное число не может быть размещено в указанной позиции. Попробуйте снова: \033[0m";
        }
        else {
            cout << "\n\t\033[1;31mОшибка ввода! Введите значение от 1 до 9: \033[0m";
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    enterValue(grid, row - 1, col - 1, value);
}

void generateGrid(SudokuGrid& grid) {
    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grid.cells[i][j] = 0;
        }
    }

    
    srand(static_cast<unsigned int>(time(0))); 
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (rand() % 10 < 6) {
                int value = getRandomNumber(1, 9);
                if (isValidValue(grid, i, j, value)) {
                    grid.cells[i][j] = value;
                }
            }
        }
    }
}

bool isBoardFull(const SudokuGrid& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (grid.cells[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "RUS");
    SudokuGrid grid;
    generateGrid(grid);
    displayBoard(grid);

    int choice;
    bool exit = false;

    while (!exit) {
        cout << "\n\n\n";
        cout << "\t\033[1;32m######   ##   ##    ######     #####   ##  ####  ##   ##\033[0m\n";
        cout << "\t\033[1;32m#    ##   #   ##   ##    ##   ##   ##  #  ##      #   ##  \033[0m\n";
        cout << "\t\033[1;32m#          #####   ##    ##   ##   ##  ###         #####\033[0m\n";
        cout << "\t\033[1;32m#    ##       ##  ##########  ##   ##  #  ##          ##\033[0m\n";
        cout << "\t\033[1;32m######    ######  ##      ##   #####   ##  ####   ###### \033[0m\n";

        cout << "\n\n\t\033[1;34m1.Начало игры\033[0m";
        cout << "\n\t\033[1;31m2.Выход\n\033[0m";
        cout << "\t\033[1;32mСделай выбор (1-2): \033[0m";

        while (!(cin >> choice) || choice < 1 || choice > 2) {
            cout << "\n\t\t\033[1;31mНекорректный ввод! Сделай выбор 1 или 2: \033[0m\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
        case 1:
            while (!isBoardFull(grid)) {
                getPlayerInput(grid);
                displayBoard(grid);
            }
            cout << "\n\t\t\033[1;32mИгра завершена!\033[0m" << endl;
            break;
        case 2:
            exit = true;
            break;
        }
    }

    return 0;
}

