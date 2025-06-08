#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

// Constants
const int SIZE = 10;
const char PLAYER = 'P';
const char WALL = '#';
const char CRYSTAL = 'C';
const char TRAP = 'T';
const char EMPTY = '.';
const int MAX_ENERGY = 100;
const int MAX_UNDO = 5;

// Game state
struct State {
    int x, y;
    int energy;
    int crystals;
    vector<vector<char>> grid;
};

struct Game {
    vector<vector<char>> grid;
    int playerX, playerY;
    int energy;
    int crystals;
    int score;
    int highScore;
    bool gameOver;
    stack<State> history;
};

// Initialize game
void initGame(Game& game) {
    game.grid = vector<vector<char>>(SIZE, vector<char>(SIZE, EMPTY));
    game.playerX = 0;
    game.playerY = 0;
    game.energy = MAX_ENERGY;
    game.crystals = 0;
    game.score = 0;
    game.gameOver = false;
    game.history = stack<State>();

    // Place walls, crystals, and traps
    srand(time(0));
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == 0 && j == 0) continue;
            int r = rand() % 100;
            if (r < 20) game.grid[i][j] = WALL;
            else if (r < 25) game.grid[i][j] = CRYSTAL;
            else if (r < 30) game.grid[i][j] = TRAP;
        }
    }

    // Load high score
    ifstream file("chronovault_highscore.txt");
    if (file.is_open()) {
        file >> game.highScore;
        file.close();
    } else {
        game.highScore = 0;
    }
}

// Display game
void displayGame(const Game& game) {
    system("clear"); // Use "cls" on Windows
    cout << "=== Chrono Vault ===" << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == game.playerX && j == game.playerY) {
                cout << PLAYER << " ";
            } else {
                cout << game.grid[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << game.score << " | High Score: " << game.highScore 
         << " | Energy: " << game.energy << " | Crystals: " << game.crystals 
         << " | Rewinds Available: " << game.history.size() << "/" << MAX_UNDO << endl;
}

// Save state for rewind
void saveState(Game& game) {
    if (game.history.size() >= MAX_UNDO) {
        stack<State> temp;
        for (int i = 0; i < MAX_UNDO - 1; ++i) {
            temp.push(game.history.top());
            game.history.pop();
        }
        game.history = stack<State>();
        while (!temp.empty()) {
            game.history.push(temp.top());
            temp.pop();
        }
    }
    State state = {game.playerX, game.playerY, game.energy, game.crystals, game.grid};
    game.history.push(state);
}

// Move player
void movePlayer(Game& game, char direction) {
    int newX = game.playerX;
    int newY = game.playerY;

    if (direction == 'w' && newX > 0) newX--;
    else if (direction == 's' && newX < SIZE - 1) newX++;
    else if (direction == 'a' && newY > 0) newY--;
    else if (direction == 'd' && newY < SIZE - 1) newY++;

    if (game.grid[newX][newY] != WALL) {
        saveState(game);
        if (game.grid[newX][newY] == CRYSTAL) {
            game.crystals++;
            game.score += 50;
            game.energy = min(MAX_ENERGY, game.energy + 20);
            game.grid[newX][newY] = EMPTY;
        } else if (game.grid[newX][newY] == TRAP) {
            game.energy -= 30;
            cout << "Hit a trap! Energy -30" << endl;
            game.grid[newX][newY] = EMPTY;
        }
        game.playerX = newX;
        game.playerY = newY;
        game.energy = max(0, game.energy - 1); // Moving consumes energy
    } else {
        cout << "Blocked by wall!" << endl;
    }
}

// Rewind time
void rewindTime(Game& game) {
    if (game.history.empty()) {
        cout << "No moves to rewind!" << endl;
        return;
    }
    if (game.energy < 10) {
        cout << "Not enough energy to rewind!" << endl;
        return;
    }
    State prev = game.history.top();
    game.history.pop();
    game.playerX = prev.x;
    game.playerY = prev.y;
    game.energy = max(0, prev.energy - 10); // Rewind costs energy
    game.crystals = prev.crystals;
    game.grid = prev.grid;
    cout << "Time rewound!" << endl;
}

// Save high score
void saveHighScore(const Game& game) {
    ofstream file("chronovault_highscore.txt");
    if (file.is_open()) {
        file << game.highScore;
        file.close();
    }
}

// Main game loop
int main() {
    Game game;
    initGame(game);
    srand(time(0));

    cout << "Welcome to Chrono Vault! Use WASD to move, 'r' to rewind time, 'q' to quit.\n";
    cout << "Collect Crystals ('C'), avoid Traps ('T'), and navigate around Walls ('#').\n";

    while (!game.gameOver) {
        displayGame(game);
        cout << "Enter action: ";
        char action;
        cin >> action;

        if (action == 'q') {
            cout << "Game Over. Final Score: " << game.score << ". Thanks for playing!" << endl;
            break;
        } else if (action == 'r') {
            rewindTime(game);
        } else if (action == 'w' || action == 'a' || action == 's' || action == 'd') {
            movePlayer(game, action);
        } else {
            cout << "Invalid action!" << endl;
        }

        if (game.energy <= 0) {
            cout << "Out of energy! Game Over." << endl;
            game.gameOver = true;
        }

        if (game.score > game.highScore) {
            game.highScore = game.score;
            saveHighScore(game);
        }
    }

    if (game.gameOver) {
        cout << "Final Score: " << game.score << " | High Score: " << game.highScore << endl;
        saveHighScore(game);
    }

    return 0;
}
