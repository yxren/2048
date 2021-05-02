#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iomanip>

using namespace std;

// game map
int MAP[4][4] = { {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}, };

typedef struct {
    int x;
    int y;
} Coordinate;
// 游戏结束标志
bool gameOver = false;
// 游戏得分
int score = 0;

void InitMap(void);
void RefreshMap(void);
void GenerateTwoNumber(void);
void GenerateOneNumber(void);
void MoveMap(char command);
void MoveUp(void);
void MoveDown(void);
void MoveLeft(void);
void MoveRight(void);
bool IsCommandLegal(char command);
bool IsGameOver(void);

int main()
{
    InitMap();
    RefreshMap();

    while (!gameOver) {
        char command;
        cin >> command;
        if (!IsCommandLegal(command)) {
            // Illegal keyword
            cout << "Illegal, please operate again!(W,A,S,D)" << endl;
            continue;
        }
        MoveMap(command);
//        GenerateTwoNumber();
        GenerateOneNumber();
        system("cls");
        if (IsGameOver()) {
            cout << "Game Over!!! " << "Your score: " << score << endl;
        } else {
            RefreshMap();
        }
    }

    return 0;
}

void InitMap(void)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            MAP[i][j] = 0;
        }
    }
    GenerateTwoNumber();

    return;
}

void RefreshMap(void)
{
    cout << "score: " << score << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (MAP[i][j] == 0) {
                cout << "    -" << "  ";
            } else {
                cout << setw(5) << MAP[i][j] << "  ";
            }
        }
        cout << endl << endl;
    }

    return;
}

void GenerateTwoNumber(void)
{
    srand(time(nullptr));
    int m = 0, n = 0;
    if (rand() % 2 == 0) {
        m = 2;
    } else {
        m = 4;
    }
    if (rand() % 2 == 0) {
        n = 2;
    } else {
        n = 4;
    }
    int index = 0;
    map<int, Coordinate> zeroMap;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (MAP[i][j] == 0) {
                Coordinate co;
                co.x = i;
                co.y = j;
                zeroMap.insert({index, co});
                index++;
            }
        }
    }
    int one = rand() % index;
    MAP[zeroMap[one].x][zeroMap[one].y] = m;
    zeroMap.clear();
    index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (MAP[i][j] == 0) {
                Coordinate co;
                co.x = i;
                co.y = j;
                zeroMap.insert({index, co});
                index++;
            }
        }
    }
    int two = rand() % index;
    MAP[zeroMap[two].x][zeroMap[two].y] = n;

    return;
}

void GenerateOneNumber(void)
{
    srand(time(nullptr));
    int m = 0;
    if (rand() % 2 == 0) {
        m = 2;
    } else {
        m = 4;
    }
    int index = 0;
    map<int, Coordinate> zeroMap;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (MAP[i][j] == 0) {
                Coordinate co;
                co.x = i;
                co.y = j;
                zeroMap.insert({index, co});
                index++;
            }
        }
    }
    int one = rand() % index;
    MAP[zeroMap[one].x][zeroMap[one].y] = m;

    return;
}

bool IsCommandLegal(char command)
{
    if (command == 'w' ||
        command == 'a' ||
        command == 's' ||
        command == 'd') {
        return true;
    }

    return false;
}

void MoveMap(char command)
{
    switch (command) {
        case 'w':
            MoveUp();
            break;
        case 'a':
            MoveLeft();
            break;
        case 's':
            MoveDown();
            break;
        case 'd':
            MoveRight();
            break;
        default:
            break;
    }

    return;
}

void MoveUp(void)
{
    for (int k = 0; k < 4; k++) {
        int arr[4] = { 0, 0, 0, 0 };
        int i = 0;
        // 将每一列数字读取到arr数组中，用于合并计算
        for (int l = 0; l < 4; l++) {
            if (MAP[l][k] != 0) {
                arr[i] = MAP[l][k];
                MAP[l][k] = 0;
                i++;
            }
        }
        // 合并计算arr数组
        for (int m = 0; m < 3; m++) {
            if (arr[m] == 0) {
                continue;
            }
            if (arr[m] == arr[m + 1]) {
                arr[m] *= 2;
                arr[m + 1] = 0;
                score += arr[m];
            }
        }
        for (int m = 0, n = 0; m < 4; m++) {
            if (arr[m] != 0) {
                int temp = arr[m];
                arr[m] = 0;
                arr[n] = temp;
                n++;
            }
        }
        for (int l = 0; l < 4; l++) {
            MAP[l][k] = 0;
        }
        // 将计算后的arr数组重新填入地图
        for (int l = 0; l < i; l++) {
            MAP[l][k] = arr[l];
        }
    }

    return;
}

void MoveDown(void)
{
    for (int k = 0; k < 4; k++) {
        int arr[4] = { 0, 0, 0, 0 };
        int i = 0;
        for (int l = 0; l < 4; l++) {
            if (MAP[l][k] != 0) {
                arr[i] = MAP[l][k];
                MAP[l][k] = 0;
                i++;
            }
        }
        for (int m = 3; m >= 1; m--) {
            if (arr[m] == 0) {
                continue;
            }
            if (arr[m] == arr[m - 1]) {
                arr[m] *= 2;
                arr[m - 1] = 0;
                score += arr[m];
            }
        }
        for (int m = 0, n = 0; m < 4; m++) {
            if (arr[m] != 0) {
                int temp = arr[m];
                arr[m] = 0;
                arr[n] = temp;
                n++;
            }
        }
        int j = 3;
        for (int l = 3; l >= 0; l--) {
            MAP[l][k] = 0;
        }
        for (int l = 3; l >= 0; l--) {
            if (arr[l] != 0) {
                MAP[j][k] = arr[l];
                j--;
            }
        }
    }

    return;
}

void MoveLeft(void)
{
    for (int k = 0; k < 4; k++) {
        int arr[4] = { 0, 0, 0, 0 };
        int i = 0;
        for (int l = 0; l < 4; l++) {
            if (MAP[k][l] != 0) {
                arr[i] = MAP[k][l];
                MAP[k][l] = 0;
                i++;
            }
        }
        for (int m = 0; m < 3; m++) {
            if (arr[m] == 0) {
                continue;
            }
            if (arr[m] == arr[m + 1]) {
                arr[m] *= 2;
                arr[m + 1] = 0;
                score += arr[m];
            }
        }
        for (int m = 0, n = 0; m < 4; m++) {
            if (arr[m] != 0) {
                int temp = arr[m];
                arr[m] = 0;
                arr[n] = temp;
                n++;
            }
        }
        for (int l = 0; l < 4; l++) {
            MAP[k][l] = 0;
        }
        for (int l = 0; l < i; l++) {
            MAP[k][l] = arr[l];
        }
    }

    return;
}

void MoveRight(void)
{
    for (int k = 0; k < 4; k++) {
        int arr[4] = { 0, 0, 0, 0 };
        int i = 0;
        for (int l = 0; l < 4; l++) {
            if (MAP[k][l] != 0) {
                arr[i] = MAP[k][l];
                MAP[k][l] = 0;
                i++;
            }
        }
        for (int m = 3; m >= 1; m--) {
            if (arr[m] == 0) {
                continue;
            }
            if (arr[m] == arr[m - 1]) {
                arr[m] *= 2;
                arr[m - 1] = 0;
                score += arr[m];
            }
        }
        for (int m = 0, n = 0; m < 4; m++) {
            if (arr[m] != 0) {
                int temp = arr[m];
                arr[m] = 0;
                arr[n] = temp;
                n++;
            }
        }
        for (int l = 3; l >= 0; l--) {
            MAP[k][l] = 0;
        }
        int j = 3;
        for (int l = 3; l >= 0; l--) {
            if (arr[l] != 0) {
                MAP[k][j] = arr[l];
                j--;
            }
        }
    }

    return;
}

bool IsGameOver(void)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (MAP[i][j] == 0) {
                return false;
            }
            if (MAP[i][j] == MAP[i][j+1]) {
                return false;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (MAP[i][j] == 0) {
                return false;
            }
            if (MAP[j][i] == MAP[j][i+1]) {
                return false;
            }
        }
    }

    return true;
}