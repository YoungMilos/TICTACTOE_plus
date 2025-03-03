#include "Game.h"
#include <vector>

bool Game::init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;
        success = false;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        cout << "IMG_Init HAS FAILED. SDL_ERROR: " << IMG_GetError() << endl;
        success = false;
    }
    if (!(IMG_Init(IMG_INIT_JPG))) {
        cout << "IMG_Init HAS FAILED. SDL_ERROR: " << IMG_GetError << endl;
        success = false;
    }
    if (success == true) commonFunc::renderWindow(TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

    return success;
}

void Game::createBoard()
{
    cell_empty = commonFunc::loadTexture("IMG\\cell_empty.png");
    cell_o = commonFunc::loadTexture("IMG\\cell_o.png");
    cell_x = commonFunc::loadTexture("IMG\\cell_x.png");
    win_up = commonFunc::loadTexture("IMG\\win_up.png");
    win_down = commonFunc::loadTexture("IMG\\win_down.png");
    win_horizontal = commonFunc::loadTexture("IMG\\win_horizontal.png");
    win_vertical = commonFunc::loadTexture("IMG\\win_vertical.png");
    
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            gameBoard[i][j] = EMPTY_CELL;
        }
    }
}

void Game::renderBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)   {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            int x, y;
            x = 10 + 35 * i;
            y = 10 + 35 * j;
            switch (gameBoard[i][j]) {
            case EMPTY_CELL:
                commonFunc::renderTexture(cell_empty, x, y, 35, 35);
                break;
            case X_CELL:
                commonFunc::renderTexture(cell_x, x, y, 35, 35);
                break;
            case O_CELL:
                commonFunc::renderTexture(cell_o, x, y, 35, 35);
                break;
            };
        }
    }
    commonFunc::renderPresent();
}

void Game::resetGame()
{

}

void Game::move(int col, int row)
{
    if (row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH && gameBoard[col][row] == EMPTY_CELL)
    {
        gameBoard[col][row] = nextMove;
        nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
    }
}

bool Game::isWin(int col, int row)
{
    int x, y,cnt;
    vector <pair<int, int>> moved;

    // kiểm tra chéo xuống
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && row + 1 < BOARD_HEIGHT && gameBoard[x + 1][y + 1] == gameBoard[col][row]) {
        x++;
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && row - 1 >= 0 && gameBoard[x - 1][y - 1] == gameBoard[col][row]) {
        x--;
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt == 5) {
        gameRunning = false;
        commonFunc::renderTexture(win_down, moved[moved.size() - 1].first*35 + BOARD_X, BOARD_Y + moved[moved.size() - 1].second*35, 175, 175);
        commonFunc::renderPresent();
        SDL_Delay(1000);

        return true;
    }

    // kiểm tra ngang
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && gameBoard[x + 1][y] == gameBoard[col][row]) {
        x++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && gameBoard[x - 1][y] == gameBoard[col][row]) {
        x--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt == 5) {
        gameRunning = false;
        commonFunc::renderTexture(win_horizontal, moved[moved.size() - 1].first * 35 + BOARD_X, BOARD_Y + moved[moved.size() - 1].second * 35 - 70, 175, 175);
        commonFunc::renderPresent();
        SDL_Delay(1000);

        return true;
    }

    // kiểm tra dọc
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (row + 1 < BOARD_HEIGHT && gameBoard[x][y + 1] == gameBoard[col][row]) {
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (row - 1 >= 0 && gameBoard[x][y - 1] == gameBoard[col][row]) {
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt == 5) {
        gameRunning = false;
        commonFunc::renderTexture(win_vertical, moved[moved.size() - 1].first * 35 + BOARD_X - 70, BOARD_Y + moved[moved.size() - 1].second * 35, 175, 175);
        commonFunc::renderPresent();
        SDL_Delay(1000);

        return true;
    }

    // kiểm tra chéo lên
    cnt = 1;
    moved.clear();
    x = col, y = row;
    cout << x << " " << y << endl;
    while (col + 1 < BOARD_WIDTH && row - 1 >= 0 && gameBoard[x + 1][y - 1] == gameBoard[col][row]) {
        x++;
        y--;
        cnt++;
        moved.push_back({ x,y });
    }
    moved.push_back({ col,row });
    x = col, y = row;
    while (col - 1 >= 0 && row + 1 < BOARD_HEIGHT && gameBoard[x - 1][y + 1] == gameBoard[col][row]) {
        x--;
        y++;
        cnt++;
        moved.push_back({ x,y });
    }
    if (cnt == 5) {
        gameRunning = false;
        commonFunc::renderTexture(win_up, moved[moved.size() - 1].first * 35 + BOARD_X, BOARD_Y + moved[moved.size() - 1].second * 35 - 140, 175, 175);
        commonFunc::renderPresent();
        SDL_Delay(1000);

        return true;
    }


    return false;
}

void Game::handleGameInput(SDL_Event& event)
{
    if (event.type == SDL_QUIT) gameRunning = false;
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y; 
        SDL_GetMouseState(&x, &y);

        int clickedCol = (x - BOARD_X) / CELL_SIZE;
        int clickedRow = (y - BOARD_Y) / CELL_SIZE;
        Game::move(clickedCol, clickedRow);
        Game::renderBoard();
        
        if (!Game::isWin(clickedCol, clickedRow))
        {

        }
    }
}