#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct cell
{
    int value;
    bool isShowed;
};
cell table[8][8];
int inputRow, inputCol, difficulty, totalBomb, roundWin, countRound = 1;
bool inGame;

void placeBomb()
{
    if (difficulty == 1)
    {
        totalBomb = 3;
        roundWin = 65 - totalBomb;
    }
    else if (difficulty == 2)
    {
        totalBomb = 6;
        roundWin = 65 - totalBomb;
    }
    else if (difficulty == 3)
    {
        totalBomb = 9;
        roundWin = 65 - totalBomb;
    }
    else
    {
        cout << "\nINPUT INVALID, SILAHKAN MASUKAN ANGKA 1-3";
        inGame = false;
        return;
    }
    srand(static_cast<unsigned int>(time(nullptr)));
    int bombsPlaced = 0;
    while (bombsPlaced < totalBomb)
    {
        int randomRow = rand() % 8;
        int randomColumn = rand() % 8;
        if (table[randomRow][randomColumn].value == -1)
        {
            table[randomRow][randomColumn].value = 0;
            bombsPlaced++;
        }
    }
}

int check(int row, int col)
{
    int countBomb = 0;
    for (int i = max(0, row - 1); i <= min(row + 1, 7); i++)
    {
        for (int j = max(0, col - 1); j <= min(col + 1, 7); j++)
        {
            if (!(i == row && j == col) && table[i][j].value == 0)
            {
                countBomb++;
            }
        }
    }
    return countBomb;
}

void placeHint()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (table[i][j].value != 0)
            {
                int cellValue = check(i, j);
                if (cellValue > 0)
                {
                    table[i][j].value = cellValue;
                }
            }
        }
    }
}

void printTable()
{
    for (int i = 0; i < 8; i++)
    {
        if (i == 0)
        {
            cout << "    1   2   3   4   5   6   7   8  \n";
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }
        for (int j = 0; j < 8; j++)
        {
            if (j == 0)
            {
                cout << i + 1 << " | ";
            }
            else
            {
                cout << "| ";
            }
            if (table[i][j].isShowed == true)
            {
                if (table[i][j].value != -1)
                {
                    cout << table[i][j].value << " ";
                }
                else if (table[i][j].value == -1)
                {
                    cout << "  ";
                }
            }
            else if (table[i][j].isShowed == false)
            {
                cout << "X ";
            }
            if (j == 7)
            {
                cout << "|";
            }
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
}

void round()
{
    if (inGame == true)
    {
        if (countRound == roundWin)
        {
            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    table[i][j].isShowed = true;
                }
            }
            printTable();
            cout << "\nSelamat Anda Menang!! Telah Menyelesaikan " << roundWin << " Babak Beruntun Tanpa Menginjak Bom";
            inGame = false;
            return;
        }
        printTable();
        cout << "\nTebak Lokasi (Babak " << countRound << ")\n";
        cout << "Baris ke: ";
        cin >> inputRow;
        cout << "Kolom ke: ";
        cin >> inputCol;
        cout << "\n";

        if (inputRow < 1 || inputRow > 8 || inputCol < 1 || inputCol > 8)
        {
            cout << "INPUT TIDAK VALID, TOLONG MASUKKAN ANGKA 1-8\n";
            cout << "_______________________________________________\n\n";
            round();
            return;
        }

        if (table[inputRow - 1][inputCol - 1].isShowed == true)
        {
            cout << "KOTAK TELAH DITEBAK SEBELUMNYA\n";
            cout << "_______________________________________________\n\n";
            round();
            return;
        }

        if (table[inputRow - 1][inputCol - 1].value != 0)
        {
            cout << "ANDA AMAN, BABAK SELANJUTNYA\n";
            cout << "_______________________________________________\n\n";
            table[inputRow - 1][inputCol - 1].isShowed = true;
            countRound++;
            round();
        }
        else
        {
            table[inputRow - 1][inputCol - 1].isShowed = true;
            cout << "_______________________________________________\n\n";
            printTable();
            cout << "\nANDA KALAH DI BABAK " << countRound << "\n\n";
            inGame = false;
            return;
        }
    }
}

int main()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            table[i][j].value = -1;
            table[i][j].isShowed = false;
        }
    }

    cout << "\nMine Sweeper\n\n";
    cout << "1. Easy (3 bom)\n";
    cout << "2. Medium (6 bom)\n";
    cout << "3. Hard (9 bom)\n";
    cout << "Pilih Tingkat Kesulitan: ";
    cin >> difficulty;
    cout << "\n";

    inGame = true;

    placeBomb();

    placeHint();

    round();

    return 0;
}
