#pragma once

#include <vector>
#include <ctime>


class Dodge
{
private:
    int countdownValue = 3;
    bool startDelay = true;
    bool continuegame = false;
    
    int health = 100;

    int kX = -1;
    int kY = -1;

    int kXs = -1;
    int kYs = -1;

    int kYt = -1;
    int kXt = -1;

    int bosstimer = 0;
    int secondtimer = 0;
    int thirdtimer = 0;

    bool BossAttack = false;
    bool wall = false;
    bool Falling = false;

    bool isDodgeActive = false;

    int GameTotalTimer = 10;


    clock_t start = std::clock();


    struct Obstacle 
    {
        int x, y;

        Obstacle(int startX, int startY) : x(startX), y(startY) {}
    };

    struct Projectile
    {
        int x, y;

        Projectile(int startX, int startY) : x(startX), y(startY) {}
    };

    struct Spike
    {
        int x, y;
        int height;

        Spike(int startX, int startY, int h) : x(startX), y(startY), height(h) {}
    };

    struct ObstacleWarning 
    {
        int x, y;
        bool active;;

        ObstacleWarning(int startX, int startY, int h) : x(startX), y(startY), active(true) {}
    };
	

public:

   
    static const int rows = 10;
    static const int cols = 10;

    bool enemyDamage = false;
    static bool enemyCollided;

    // Forward declarations

    void setCursorPosition(int x, int y);
    int getRandomColumn();
    bool isCollision(int x, int y);
    bool checkCollision(int playerX, int playerY, int obstacleX, int obstacleY);
    bool clearScreen();

    void moveProjectiles(std::vector<Projectile>& projectiles);
    void moveObstacles(std::vector<Obstacle>& obstacles);
    void moveSpikes(std::vector<Spike>& spikes);

    void printGrid(char grid[rows][cols], int playerX, int playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes);
    void fallingGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes);
    void wallGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes);
    void explosionGame(char grid[rows][cols], int& playerX, int& playerY, std::vector<Projectile>& projectiles, std::vector<Obstacle>& obstacles, std::vector<Spike>& spikes);
	
	
    void startGame();



};

