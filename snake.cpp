#include <bits/stdc++.h>
#ifdef _WIN32
#include <conio.h>  // For Windows
#include <windows.h> // For Windows specific functions
#else
#include <ncurses.h> // For Linux
#include <unistd.h>  // For usleep in Linux
#endif
using namespace std;

#define MAX_LENGTH 1000

// Directions
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

void initScreen() {
    #ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
    getmaxyx(stdscr, consoleHeight, consoleWidth); // ncurses function to get screen size
    #endif
}

struct Point {
    int xCoord;
    int yCoord;
    Point() {}
    Point(int x, int y) : xCoord(x), yCoord(y) {}
};

class Snake {
    int length;
    char direction;
public:
    Point body[MAX_LENGTH];
    Snake(int x, int y) : length(1), direction(DIR_RIGHT) {
        body[0] = Point(x, y);
    }

    int getLength() {
        return length;
    }

    void changeDirection(char newDirection) {
        if ((newDirection == DIR_UP && direction != DIR_DOWN) ||
            (newDirection == DIR_DOWN && direction != DIR_UP) ||
            (newDirection == DIR_LEFT && direction != DIR_RIGHT) ||
            (newDirection == DIR_RIGHT && direction != DIR_LEFT)) {
            direction = newDirection;
        }
    }

    bool move(Point food) {
        for (int i = length - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }

        switch (direction) {
            case DIR_UP:    body[0].yCoord--; break;
            case DIR_DOWN:  body[0].yCoord++; break;
            case DIR_RIGHT: body[0].xCoord++; break;
            case DIR_LEFT:  body[0].xCoord--; break;
        }

        // Snake bites itself
        for (int i = 1; i < length; ++i) {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord) {
                return false;
            }
        }

        // Snake eats food
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord) {
            body[length++] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
        }

        return true;
    }
};

class Board {
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;
public:
    Board() : score(0) {
        spawnFood();
        snake = new Snake(10, 10);
    }

    ~Board() {
        delete snake;
    }

    int getScore() {
        return score;
    }

    void spawnFood() {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y);
    }

    void displayCurrentScore() {
        gotoxy(consoleWidth / 2, 0);
        printw("Current Score : %d", score);
    }

    void gotoxy(int x, int y) {
        #ifdef _WIN32
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        #else
        move(y, x); // ncurses move cursor for Linux (note the order: y, x)
        #endif
    }

    void clearScreen() {
        #ifdef _WIN32
        system("cls"); // Windows clear screen
        #else
        clear(); // ncurses clear screen for Linux
        #endif
    }

    void draw() {
        clearScreen();
        for (int i = 0; i < snake->getLength(); ++i) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            printw("%c", SNAKE_BODY);
        }

        gotoxy(food.xCoord, food.yCoord);
        printw("%c", FOOD);

        displayCurrentScore();
        refresh();
    }

    bool update() {
        bool isAlive = snake->move(food);
        if (!isAlive) return false;

        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord) {
            score++;
            spawnFood();
        }
        return true;
    }

    void getInput() {
        #ifdef _WIN32
        if (kbhit()) {
            int key = getch();
            if (key == 'w' || key == 'W') snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A') snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S') snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D') snake->changeDirection(DIR_RIGHT);
        }
        #else
        int key = getch();
        if (key != ERR) {
            if (key == 'w' || key == 'W' || key == KEY_UP) snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A' || key == KEY_LEFT) snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S' || key == KEY_DOWN) snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D' || key == KEY_RIGHT) snake->changeDirection(DIR_RIGHT);
        }
        #endif
    }
};

int main() {
    #ifndef _WIN32
    initscr();  // Start ncurses mode
    cbreak();   // Disable line buffering
    noecho();   // Don't echo input
    keypad(stdscr, TRUE); // Enable special keys
    nodelay(stdscr, TRUE); // Non-blocking input
    #endif

    srand(time(0));
    initScreen();
    Board *board = new Board();
    while (board->update()) {
        board->getInput();
        board->draw();
        #ifdef _WIN32
        Sleep(100); // Sleep for Windows
        #else
        usleep(100 * 1000); // usleep for Linux (microseconds)
        #endif
    }

    #ifndef _WIN32
    printw("Game over\n");
    printw("Final score is: %d\n", board->getScore());
    refresh(); // Refresh the screen to show the output
    endwin(); // End ncurses mode
    #else
    cout << "Game over" << endl;
    cout << "Final score is: " << board->getScore() << endl;
    #endif

    delete board;
    return 0;
}

