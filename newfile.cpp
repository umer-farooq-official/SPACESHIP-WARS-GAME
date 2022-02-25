// SPACESHIP WARS
// PREPARED BY : UMER FAROOQ , SECTION : C , ROLL NO : 151
#include <iostream>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include <time.h>
#include <fstream>
// DEFINING CONSTANTS
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
#define WIN_WIDTH 90
#define MENU_WIDTH 30
#define GAP_SIZE 10
#define Enemy_DIF 50

using namespace std;
// CONSOLE HANDLING
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
// GLOBAL VARIABLES
int enemyY[3];
int enemyX[3];
int enemyFlag[3];
wchar_t ship[3][5] = {
    {L' ', L' ', L'±', L' ', L' '},
    {L'|', L'±', L'±', L'±', L'|'},
    {L'±', L'±', L'±', L'±', L'±'}};

// wchar_t enemy_ship[3][5] = {
//       {L'±', L'±', L'±', L'±', L'±'},
//       {L'|', L'±', L'±', L'±', L'|'},
//       {L' ', L' ', L'±', L' ', L' '}};

int space_ship = WIN_WIDTH / 2;
int score = 0;
int highscore = 0 ;
int bullets[20][4];
int bulletsLife[20];
int bindex = 0;
// END OF GLOBAL VARIABLES

// FUNCTIONS PROTOTYPES START
void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void MAKE_Border();
void generate_Enemy(int idx);
void make_Enemy(int idx);
void remove_enemy(int idx);
void reset_Enemy(int idx);
void generate_Bullet();
void move_Bullet();
void make_Bullets();
void erase_Bullets();
void erase_Bullet(int i);
void make_ship();
void remove_ship();
int collision();
int bulletHit();
void update_Score();
void user_guidance();
void gameover();
void start();
void high_score();
// FUNCTIONS PROTOTYPES END

// MAIN IMPLEMENTATION START
int main()
{
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    while(true)
    {
        system("cls");
        gotoxy(10, 2);
        cout << "                               _     _                                          " << endl;
        cout << "                              | |   (_)                                         " << endl;
        cout << " ___ _ __   __ _  ___ ___  ___| |__  _ _ __   __      ____ _ _ __ ___           " << endl;
        cout << "/ __| '_ \\ / _` |/ __/ _ \\/ __| '_ \\| | '_ \\  \\ \\ /\\ / / _` | _/ __|     " << endl;
        cout << "\\__ \\ |_) | (_| | (_|  __/\\__ \\ | | | | |_) |  \\ V  V / (_| | |  \\__ \\   " << endl;
        cout << "|___/ .__/ \\__,_|\\___\\___||___/_| |_|_| .__/    \\_/\\_/ \\__,_|_|  |___/    " << endl;
        cout << "    | |                               | |                                       " << endl;
        cout << "    |_|                               |_|                                       " << endl;
        gotoxy(10, 10 + 1);
        cout << "1. Start Game";
        gotoxy(10, 11 + 1);
        cout << "2. Instructions";
        gotoxy(10, 12 + 1);
        cout << "3. Quit";
        gotoxy(10, 14 + 1);
        cout << "Select option: ";
        char op = getche();

        if (op == '1'){
            start();
        }
        else if (op == '2')
            user_guidance();
        else if (op == '3')
            exit(0);

    }

    return 0;
}
// MAIN IMPLEMENTATION ENDS

// FUNCTION IMPLEMENTATIONS START

void gotoxy(int x, int y) // FOR THE POSITION OF PLAYER
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) // FOR THE SETTING OF CURSOR
{
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void MAKE_Border() // FOR THE IMPLEMENTATION OF BORDER
{
    gotoxy(0, 0);
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    for (int i = 0; i < SCREEN_WIDTH - 29; i++)
    {
        gotoxy(i, SCREEN_HEIGHT + 1);
        cout << "@@";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(0, i + 1);
        cout << "@@";
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(WIN_WIDTH, i + 1);
        cout << "@@";
    }
}

void generate_Enemy(int idx) //  GENERATING ENEMY
{
    enemyX[idx] = 3 + rand() % (WIN_WIDTH - 10);
}

void make_Enemy(int idx) // making the enemy
{
    if (enemyFlag[idx] == true)
    {
        gotoxy(enemyX[idx], enemyY[idx] + 1);
        cout << "****";
        gotoxy(enemyX[idx], enemyY[idx] + 2);
        cout << "***";
        gotoxy(enemyX[idx], enemyY[idx] + 3);
        cout << "***";
        gotoxy(enemyX[idx], enemyY[idx] + 4);
        cout << "****";
        // for (int i = 0; i < 3; i++)
        // {
        //     for (int j = 0; j < 5; j++)
        //     {
        //         gotoxy(enemyX[idx] , enemyY[idx] + 1);
        //         wcout << enemy_ship[i][j] << enemy_ship[i][j] << enemy_ship[i][j];
        //         gotoxy(enemyX[idx] , enemyY[idx] + 2);
        //         wcout << enemy_ship[i][j] << enemy_ship[i][j] << enemy_ship[i][j];
        //         gotoxy(enemyX[idx] , enemyY[idx] + 3);
        //         wcout << enemy_ship[i][j] << enemy_ship[i][j] << enemy_ship[i][j];
        //         gotoxy(enemyX[idx] , enemyY[idx] + 4);
        //         wcout << enemy_ship[i][j] << enemy_ship[i][j] << enemy_ship[i][j];

        //     }
        // }
    }
}

void remove_enemy(int idx) // ERASING ENEMY
{
    if (enemyFlag[idx] == true)
    {
        gotoxy(enemyX[idx], enemyY[idx] + 1);
        cout << "    ";
        gotoxy(enemyX[idx], enemyY[idx] + 2);
        cout << "    ";
        gotoxy(enemyX[idx], enemyY[idx] + 3);
        cout << "    ";
        gotoxy(enemyX[idx], enemyY[idx] + 4);
        cout << "    ";
    }
}

void reset_Enemy(int idx) // ENEMY RESETING
{
    remove_enemy(idx);
    enemyY[idx] = 4;
    generate_Enemy(idx);
}

void generate_Bullet() // GENERATING BULLET
{
    bullets[bindex][0] = 22;
    bullets[bindex][1] = space_ship;
    bullets[bindex][2] = 22;
    bullets[bindex][3] = space_ship + 4;
    bindex++;
    if (bindex == 20)
        bindex = 0;
}

void move_Bullet() // MOVING THE BULLET
{
    for (int i = 0; i < 20; i++)
    {
        if (bullets[i][0] > 2)
            bullets[i][0] = bullets[i][0] - 3;
        else
            bullets[i][0] = 0;

        if (bullets[i][2] > 2)
            bullets[i][2] = bullets[i][2] - 3;
        else
            bullets[i][2] = 0;
    }
}

void make_Bullets() // FOR MAKING THE BULLETS
{
    for (int i = 0; i < 20; i++)
    {
        if (bullets[i][0] > 1)
        {
            gotoxy(bullets[i][1], bullets[i][0] + 1);
            cout << "^";
            gotoxy(bullets[i][3], bullets[i][2] + 1);
            cout << "^";
        }
    }
}

void erase_Bullets() // ERASING THE BULLETS
{
    for (int i = 0; i < 20; i++)
    {
        if (bullets[i][0] >= 1)
        {
            gotoxy(bullets[i][1], bullets[i][0] + 1);
            cout << " ";
            gotoxy(bullets[i][3], bullets[i][2] + 1);
            cout << " ";
        }
    }
}

void erase_Bullet(int i) // ERASING A SINGLE BULLET
{
    gotoxy(bullets[i][1], bullets[i][0] + 1);
    cout << " ";
    gotoxy(bullets[i][3], bullets[i][2] + 1);
    cout << " ";
}

void make_ship() // MAKING THE SHIP
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            gotoxy(j + space_ship, i + 27);
            wcout << ship[i][j];
        }
    }
}

void remove_ship() // ERASING THE SHIP
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            gotoxy(j + space_ship, i + 1 + 27);
            cout << " ";
        }
    }
}

int collision() // WHEN THE SHIP AND ENEMY SHIP COLLIDE
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - space_ship >= 0 && enemyX[0] + 4 - space_ship < 8)
        {
            return 1;
        }
    }
    return 0;
}

int bulletHit() // WHEN THE BULLET HIT THE ENEMY SHIP
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j += 2)
        {
            if (bullets[i][j] != 0)
            {
                if (bullets[i][j] >= enemyY[0] && bullets[i][j] <= enemyY[0] + 4)
                {
                    if (bullets[i][j + 1] >= enemyX[0] && bullets[i][j + 1] <= enemyX[0] + 4)
                    {
                        erase_Bullet(i);
                        bullets[i][j] = 0;
                        reset_Enemy(0);
                        return 1;
                    }
                }
                if (bullets[i][j] >= enemyY[1] && bullets[i][j] <= enemyY[1] + 4)
                {
                    if (bullets[i][j + 1] >= enemyX[1] && bullets[i][j + 1] <= enemyX[1] + 4)
                    {
                        erase_Bullet(i);
                        reset_Enemy(1);
                        bullets[i][j] = 0;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void gameover() // GAMEOVER
{
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl
         << endl;
    cout << "\t\tPress any key to go back to menu.";
    getch();
}
void high_score()
{
    gotoxy(WIN_WIDTH + 7 , 7+1);
    cout << "HIGH SCORE " << highscore;

}

void update_Score() // UPDATING SCORE
{
    gotoxy(WIN_WIDTH + 7, 5 + 1);
    cout << "Score: " << score << endl;
    fstream newfile;
    newfile.open("score.txt" , ios::out);
    if (score > highscore)
    {
        highscore = score;
    }
    newfile << score ;
    newfile.close(); 
}

void user_guidance() // INSTRUCTIONS FOR PLAYERS
{

    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Press spacebar to make space ship fire ";
    cout << "\n Press left arrow key to make space ship move left ";
    cout << "\n Press right arrow key to make space ship move right ";
    cout << "\n Press any key to go back to menu";
    getch();
}

void start() // LETS START THE GAME
{
     int counter = 0;
     int counter1 = 0;
    space_ship = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 1;
    enemyY[0] = enemyY[1] = 4;

    for (int i = 0; i < 20; i++)
    {
        bullets[i][0] = bullets[i][1] = 0;
    }

    system("cls");
    MAKE_Border();
    generate_Enemy(0);
    generate_Enemy(1);

    update_Score();
    high_score();


    gotoxy(10, 5 + 1);
    cout << "Press any key to start";
    getch();
    gotoxy(10, 5 + 1);
    cout << "                      ";

    while (1)
    {
        if (GetAsyncKeyState(VK_LEFT))
        {
            if (space_ship > 2)
                space_ship -= 2;
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            if (space_ship < WIN_WIDTH - 7)
                space_ship += 2;
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generate_Bullet();
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        make_ship();
        
        make_Bullets();
        
        make_Enemy(0);
    
        make_Enemy(1);        
        if (collision() == 1)
        {
            gameover();
            return;
        }
        if (bulletHit() == 1)
        {
            score++;
            update_Score();
        }
        Sleep(200);
        remove_ship();
        remove_enemy(0);
        remove_enemy(1);
        erase_Bullets();
        move_Bullet();

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 5)
        {
            reset_Enemy(0);
        }
        if (enemyY[1] > SCREEN_HEIGHT - 5)
        {
            reset_Enemy(1);
        }
        counter++;
    counter1++;
    }
    
}
// FUNCTIONS IMPLEMENTATION ENDS

// PREPARED BY : UMER FAROOQ , SECTION : C , ROLL NO : 151