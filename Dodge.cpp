#include <iostream>
#include "Dodge.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdlib> 
#include <ctime>   
#include <conio.h>

using namespace std;

bool Dodge::enemyCollided = true;

void Dodge::setCursorPosition(int x, int y) 
{

    COORD cursorpos;

    cursorpos.X = x;
    cursorpos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorpos);

}

int Dodge::getRandomColumn() 
{
    return rand() % (cols - 2) + 1;
}

bool Dodge::isCollision(int x, int y) {
    return (x == 0 || x == rows - 1 || y == 0 || y == cols - 1);
}

bool Dodge::checkCollision(int playerX, int playerY, int obstacleX, int obstacleY) 
{
    return (playerX == obstacleX && playerY == obstacleY);
}

bool Dodge::clearScreen() 
{
    setCursorPosition(0, 0);

    return 0;
}

void Dodge::moveProjectiles(std::vector<Projectile>& projectiles) 
{
    for (Projectile& projectile : projectiles) {
        
        projectile.x++;
    }
}

void Dodge::moveObstacles(std::vector<Obstacle>& obstacles) 
{
    for (Obstacle& obstacle : obstacles) {
       
        obstacle.x++;
    }
}

void Dodge::moveSpikes(std::vector<Spike>& spikes) 
{
    for (Spike& spike : spikes) {

        spike.y--;
    }
}

void Dodge::printGrid(char grid[rows][cols], int playerX, int playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes)
{
    for (int i = 0; i < 13; i++)
    {
        cout << endl;
    }
    for (int i = 0; i < rows; i++) {
        cout << "                                   ";

        for (int j = 0; j < cols; j++) {
            bool isPlayer = (i == playerX && j == playerY);
            bool isProjectile = false;
            bool isObstacle = false;



            for (const Projectile& projectile : projectiles) {
                if (projectile.x == i && projectile.y == j) {
                    isProjectile = true;
                    break;
                }
            }

            for (const Obstacle& obstacle : obstacles) {
                if (obstacle.x == i && obstacle.y == j) {
                    isObstacle = true;
                    break;
                }
            }

            bool isSpike = false;
            for (const Spike& spike : spikes) {
                if (i >= spike.x && i < spike.x + spike.height && j == spike.y) {
                    isSpike = true;
                    break;
                }
            }


            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                cout << "+ "; // Boundary
            }
            else if (isPlayer) {
                cout << "\033[1;32mP\033[0m "; // Player position
            }
            else if (isProjectile)
            {
                cout << "X "; // Projectile position
            }
            else if (isObstacle)
            {
                cout << "\033[31mO\033[0m ";
            }
            else if (isSpike)
            {
                cout << "\033[31m|\033[0m "; // Red spike position
            }
            else if (grid[i][j] == countdownValue + '0')
            {
                cout << "\033[31m!\033[0m ";
            }
            else if (grid[i][j] == 'E')
            {
                std::cout << "\033[1;31mE\033[0m ";  // Red 'E' for enemy
            }
            else {
                cout << "  "; // Empty space
            }
        }
        cout << endl;
    }
}

void Dodge::fallingGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes)
{
    

    clearScreen();

  /*  std::cout << "\033[2K";*/

    setCursorPosition(100,0);

    std::cout << "Dodge the falling objects!" << endl;

    printGrid(grid, playerX, playerY, projectiles, obstacles, spikes);

    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    if (startDelay && duration >= 2.0)
    {
        startDelay = false;
    }


    for (int i = 0; i < obstacles.size(); i++) {
        if (checkCollision(playerX, playerY, obstacles[i].x, obstacles[i].y)) {

            enemyDamage = true;
            obstacles.erase(obstacles.begin() + i);
            i--; // Adjust index after erasing
        }
    }

    for (int i = 0; i < spikes.size(); i++) {
        for (int j = 0; j < spikes[i].height; j++) {
            if (checkCollision(playerX, playerY, spikes[i].x + j, spikes[i].y)) {

                break;
                
            }
        }
    }

    if (_kbhit()) {
        char input = _getch(); // Read user input

        int newX = playerX;
        int newY = playerY;

        // Update player position based on input
        switch (input) {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        default:
            break;
        }

        // Check if the new position is valid and doesn't collide with boundaries
        if (!isCollision(newX, newY)) {
            playerX = newX;
            playerY = newY;
        }
    }

    if (!startDelay)
    {
        moveProjectiles(projectiles);
        moveObstacles(obstacles);

        // Randomly spawn red obstacles at the top row
        if (rand() % 3 == 0) {
            int spawnY = rand() % (cols - 2) + 1; // Exclude boundaries 
            obstacles.push_back(Obstacle(1, spawnY));
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
}

void Dodge::wallGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes) 
{
    clearScreen();



    /*std::cout << "\033[2K";*/

    setCursorPosition(100, 0);

    std::cout << "Manoeuvre around the incoming walls!" << endl;


    printGrid(grid, playerX, playerY, projectiles, obstacles, spikes);

    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    if (startDelay && duration >= 1.5)
    {
        startDelay = false;
    }


    for (int i = 0; i < spikes.size(); i++) {
        for (int j = 0; j < spikes[i].height; j++) {
            if (checkCollision(playerX, playerY, spikes[i].x + j, spikes[i].y)) {

                enemyDamage = true;
                break; // No need to check further, player is hit
            }
        }
    }

    if (_kbhit()) {
        char input = _getch(); // Read user input

        int newX = playerX;
        int newY = playerY;

        // Update player position based on input
        switch (input)
        {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        default:
            break;
        }

        // Check if the new position is valid and doesn't collide with boundaries
        if (!isCollision(newX, newY)) {
            playerX = newX;
            playerY = newY;
        }
    }

    if (!startDelay)
    {
        moveProjectiles(projectiles);
        moveSpikes(spikes);


        //Spawn walls
        if (rand() % 10 == 0) {
            int spawnXbot = rows - 1 - rand() % 4;
            int spawnHeight = 3 + rand() % 4;
            spikes.push_back(Spike(spawnXbot, cols - 1, spawnHeight));
        }



        if (rand() % 10 == 0) {
            int spawnXtop = rand() % 3;
            int spawnHeight = 2 + rand() % 3;
            spikes.push_back(Spike(spawnXtop, cols - 1, spawnHeight));
        }
    }


    std::this_thread::sleep_for(std::chrono::milliseconds(75));
}

void Dodge::explosionGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes) 
{
    clearScreen();
    /*std::cout << "\033[2K";*/
  


    setCursorPosition(100, 0);

    std::cout << "Dodge the incoming explosions!" << endl;

    printGrid(grid, playerX, playerY, projectiles, obstacles, spikes);

    bosstimer++;
    secondtimer++;

   

    if (_kbhit()) {
        char input = _getch(); // Read user input

        int newX = playerX;
        int newY = playerY;

        // Update player position based on input
        switch (input) {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        default:
            break;
        }

        // Check if the new position is valid and doesn't collide with boundaries
        if (!isCollision(newX, newY)) {
            playerX = newX;
            playerY = newY;
        }
    }





    countdownValue--;
    if (countdownValue == 0) {
        countdownValue = 3;
    }

    int kSpawnCount = 0; // Counter for K spawns
    const int maxKSpawns = 3;



    //COLLSION DETECTION
    for (int i = playerX - 1; i <= playerX + 1; i++) {
        for (int j = playerY - 1; j <= playerY + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols) {
                if (grid[i][j] == 'E' && i == playerX && j == playerY) {
                    enemyDamage = true;
                    grid[i][j] = ' ';
                }
            }
        }
    }

    if (bosstimer == 10) {
        kX = rand() % (rows - 2) + 1;
        kY = rand() % (cols - 2) + 1;
        grid[kX][kY] = countdownValue + '0';

    }
    else if (bosstimer >= 20 && bosstimer < 30)
    {
        for (int i = kX - 1; i <= kX + 1; i++) {
            for (int j = kY - 1; j <= kY + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = 'E';
                }
            }
        }

    }
    else if (bosstimer >= 40)
    {
        for (int i = kX - 1; i <= kX + 1; i++) {
            for (int j = kY - 1; j <= kY + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = ' ';
                }
            }
        }
        bosstimer = 0;

    }


    if (secondtimer == 25) {
        kXs = rand() % (rows - 2) + 1;
        kYs = rand() % (cols - 2) + 1;
        grid[kXs][kYs] = countdownValue + '0';

    }
    else if (secondtimer >= 35 && secondtimer < 45)
    {
        for (int i = kXs - 1; i <= kXs + 1; i++) {
            for (int j = kYs - 1; j <= kYs + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = 'E';
                }
            }
        }

    }
    else if (secondtimer >= 45)
    {
        for (int i = kXs - 1; i <= kXs + 1; i++) {
            for (int j = kYs - 1; j <= kYs + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = ' ';
                }
            }
        }
        secondtimer = 0;

    }


    if (thirdtimer == 15) {
        kXt = rand() % (rows - 2) + 1;
        kYt = rand() % (cols - 2) + 1;
        grid[kXt][kYt] = countdownValue + '0';

    }
    else if (thirdtimer >= 15 && thirdtimer < 25)
    {
        for (int i = kXt - 1; i <= kXt + 1; i++) {
            for (int j = kYt - 1; j <= kYt + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = 'E';
                }
            }
        }

    }
    else if (thirdtimer >= 25)
    {
        for (int i = kXt - 1; i <= kXt + 1; i++) {
            for (int j = kYt - 1; j <= kYt + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {
                    grid[i][j] = ' ';
                }
            }
        }
        thirdtimer = 0;

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(40));
}

void Dodge::startGame()
{
   

    char grid[rows][cols];
    srand(time(0));

    int randomNum = rand() % 3;

    
    if (randomNum == 0)
    {
         Falling = true;

    }
    else if (randomNum == 1)
    {
       wall = true;


    }
    else
    {
        BossAttack = true;
    }


    // Initialize the grid with empty spaces
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = ' ';
        }
    }



    int playerX = 5; // Initial player row (excluding boundary)
    int playerY = 5; // Initial player column (excluding boundary)

    std::vector<Projectile> projectiles;
    std::vector<Obstacle> obstacles;
    std::vector<Spike> spikes;


    // Seed the random number generator
    srand(time(NULL));
    /*std::cout << "                                      " << std::endl;
    std::cout << " _____   ____  _____   _____ ______ " << std::endl;
    std::cout << "|  __ \\ / __ \\|  __ \\ / ____|  ____|" << std::endl;
    std::cout << "| |  | | |  | | |  | | |  __| |__   " << std::endl;
    std::cout << "| |  | | |  | | |  | | | |_ |  __|  " << std::endl;
    std::cout << "| |__| | |__| | |__| | |__| | |____ " << std::endl;
    std::cout << "|_____/ \\____/|_____/ \\_____|______|" << std::endl;*/



   

    
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    const int maxDurationInSeconds = 10;

    while (Falling == true && continuegame == false)
    {
        
        
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedDuration = currentTime - startTime;
        fallingGame(grid, playerX, playerY, projectiles, obstacles, spikes);
        int pos;
        int barwidth = 30;

        pos = barwidth * elapsedDuration.count() / maxDurationInSeconds;

        setCursorPosition(105, 5);
        for (int i = 0; i < barwidth; ++i) 
        {

            std::cout << "=";

            
            if (i < pos) std::cout << "\033[1;32m=\033[0m";
            else if (i == pos) std::cout << "\033[1;32m>\033[0m";
            else std::cout << " ";

            


    
        }
        setCursorPosition(0, 20);

        if (elapsedDuration.count() >= maxDurationInSeconds) {
            Dodge::enemyCollided = false;
            continuegame = true; // Exit the loop after 10 seconds
            break;
            
            
        }

        if (enemyDamage == true) 
        {
            Dodge::enemyCollided = true;
            enemyDamage = false;
            continuegame = false;
            break;


        }


    }




    while (wall == true && continuegame == false)
    {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedDuration = currentTime - startTime;

        wallGame(grid, playerX, playerY, projectiles, obstacles, spikes);

        int pos;
        int barwidth = 30;

        pos = barwidth * elapsedDuration.count() / maxDurationInSeconds;

        setCursorPosition(105, 5);
        for (int i = 0; i < barwidth; ++i)
        {

            std::cout << "=";


            if (i < pos) std::cout << "\033[1;32m=\033[0m";
            else if (i == pos) std::cout << "\033[1;32m>\033[0m";
            else std::cout << " ";





        }
        setCursorPosition(0, 20);


        if (elapsedDuration.count() >= maxDurationInSeconds) {
            Dodge::enemyCollided = false;
            continuegame = true; // Exit the loop after 10 seconds
            break;


        }

        if (enemyDamage == true)
        {
            Dodge::enemyCollided = true;
            enemyDamage = false;
            continuegame = false;
            break;


        }
    }



    while (BossAttack == true && continuegame == false)
    {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedDuration = currentTime - startTime;

        explosionGame(grid, playerX, playerY, projectiles, obstacles, spikes);


        int pos;
        int barwidth = 30;

        pos = barwidth * elapsedDuration.count() / maxDurationInSeconds;

        setCursorPosition(105, 5);
        for (int i = 0; i < barwidth; ++i)
        {

            std::cout << "=";


            if (i < pos) std::cout << "\033[1;32m=\033[0m";
            else if (i == pos) std::cout << "\033[1;32m>\033[0m";
            else std::cout << " ";





        }
        setCursorPosition(0, 20);

        if (elapsedDuration.count() >= maxDurationInSeconds) {
            Dodge::enemyCollided = false;
            continuegame = false; // Exit the loop after 10 seconds
            break;
        }

        if (enemyDamage == true)
        {
            Dodge::enemyCollided = true;
            enemyDamage = false;
            continuegame = false;
            break;


        }
    }



}






