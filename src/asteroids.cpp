#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
My version of the game asteroids. Playable in the terminal.

Last Update: 9/23/2026
Written on 9/18/2026
Written by: AJ Utz
*/

const int ASTEROIDS_SCREEN_WIDTH = 160;
const int ASTEROIDS_SCREEN_HEIGHT = 40;

vector<string> asteroid_buffer(
    ASTEROIDS_SCREEN_HEIGHT,
    string(ASTEROIDS_SCREEN_WIDTH, ' ')
);

void asteroid_drawSprite(
    vector<string>& asteroid_buffer,
    const vector<string>& sprite,
    int x,
    int y)
{
    for(int row = 0; row < sprite.size(); row++){
        for(int col = 0; col < sprite[row].size(); col++){
            if(sprite[row][col] != ' '){
                int screenX = x + col;
                int screenY = y + row;

                if(screenX >= 0 && screenX < ASTEROIDS_SCREEN_WIDTH && screenY >= 0 && screenY < ASTEROIDS_SCREEN_HEIGHT){
                    asteroid_buffer[screenY][screenX] = sprite[row][col];
                }
            }
        }
    }
}

void asteroid_clearBuffer(vector<string>& asteroid_buffer){
    for(auto& row : asteroid_buffer){
        row.assign(ASTEROIDS_SCREEN_WIDTH, ' ');
    }
}

void asteroid_renderBuffer(const vector<string>& asteroid_buffer){
    system("cls");

    for(const auto& row : asteroid_buffer){
        cout << row << '\n';
    }
}

struct asteroid_Graphics
{
    /* data */
    vector<vector<string>> ship;
    vector<string> asteroidL;
    vector<string> asteroidS;
    vector<string> bulletN;
};

asteroid_Graphics asteroidgraphics(){
    //Here is the Graphics for the game
    asteroid_Graphics g;
    
    g.ship = {
        {
            "| |",
            "###"
        },
        {
            "#---",
            "#---"
        },
        {
            "###",
            "| |"
        },
        {
            "---#",
            "---#"
        }
    };
    g.asteroidL = {
        "   ###",
        " ##   ##",
        "#       #",
        "#       #",
        "#       #",
        " ##   ##",
        "   ###"
    };
    g.asteroidS = {
        "  ##",
        " #  #",
        "  ##"
    };
    g.bulletN = { "+" };

    return g;
}

bool asteroid_checkCollision(
    int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2)
{
    return(
        x1 < x2 + w2 &&
        x1 + w1 > x2 &&
        y1 < y2 + h2 &&
        y1 + h1 > y2
    );
}

struct SpriteBounds
{
    int offsetX;
    int offsetY;
    int width;
    int height;
};

struct Bullet
{
    int x;
    int y;
    int velocityX;
    int velocityY;
};

struct Asteroid
{
    int x;
    int y;
    int velocityX;
    int velocityY;
    bool large;
    int hitPoints;
};

SpriteBounds getSpriteBounds(const vector<string>& sprite)
{
    int left = ASTEROIDS_SCREEN_WIDTH;
    int top = ASTEROIDS_SCREEN_HEIGHT;
    int right = -1;
    int bottom = -1;

    for(int row = 0; row < sprite.size(); row++){
        for(int col = 0; col < sprite[row].size(); col++){
            if(sprite[row][col] != ' '){
                if(col < left)
                    left = col;
                if(col > right)
                    right = col;
                if(row < top)
                    top = row;
                if(row > bottom)
                    bottom = row;
            }
        }
    }

    if(right == -1)
        return { 0, 0, 0, 0 };

    return { left, top, right - left + 1, bottom - top + 1 };
}

Asteroid spawnLargeAsteroid(const SpriteBounds& asteroidBounds)
{
    Asteroid asteroid = {
        0,
        0,
        0,
        0,
        true,
        3
    };
    int edge = rand() % 4;
    int centerX = ASTEROIDS_SCREEN_WIDTH / 2;
    int centerY = ASTEROIDS_SCREEN_HEIGHT / 2;

    if(edge == 0){
        asteroid.x = rand() % ASTEROIDS_SCREEN_WIDTH;
        asteroid.y = -asteroidBounds.height;
        asteroid.velocityY = 1;
        asteroid.velocityX = asteroid.x < centerX ? 1 : -1;
    }
    else if(edge == 1){
        asteroid.x = ASTEROIDS_SCREEN_WIDTH;
        asteroid.y = rand() % ASTEROIDS_SCREEN_HEIGHT;
        asteroid.velocityX = -1;
        asteroid.velocityY = asteroid.y < centerY ? 1 : -1;
    }
    else if(edge == 2){
        asteroid.x = rand() % ASTEROIDS_SCREEN_WIDTH;
        asteroid.y = ASTEROIDS_SCREEN_HEIGHT;
        asteroid.velocityY = -1;
        asteroid.velocityX = asteroid.x < centerX ? 1 : -1;
    }
    else{
        asteroid.x = -asteroidBounds.width;
        asteroid.y = rand() % ASTEROIDS_SCREEN_HEIGHT;
        asteroid.velocityX = 1;
        asteroid.velocityY = asteroid.y < centerY ? 1 : -1;
    }

    return asteroid;
}


int asteroidsMain(){
    srand(time(nullptr));
    
    asteroid_Graphics gfx = asteroidgraphics();
    
    //ship info and movement velocity
    int shipX = (ASTEROIDS_SCREEN_WIDTH - 3) / 2;
    int shipY = (ASTEROIDS_SCREEN_HEIGHT - 2) / 2;
    int facing = 0;
    vector<Bullet> bullets;
    
    SpriteBounds largeAsteroidBounds = getSpriteBounds(gfx.asteroidL);
    SpriteBounds smallAsteroidBounds = getSpriteBounds(gfx.asteroidS);
    vector<Asteroid> asteroids = {
        spawnLargeAsteroid(largeAsteroidBounds)
    };
    
    const int PLAYER_LR_SPEED = 4;
    const int PLAYER_UD_SPEED = 2;
    const int ASTEROID_MOVE_DELAY = 5;
    const int SMALL_ASTEROID_HIT_POINTS = 1;
    int largeAsteroidSpawnTimer = 20;
    int asteroidMoveTimer = 0;
    
    int score = 0;
    
    while(true){
        if(_kbhit()){
            int key = _getch();
            //Arrow key movement
            if(key == 0 || key == 224){
                key = _getch();
                //up
                if(key == 72){
                    facing = 0;
                    shipY -= PLAYER_UD_SPEED;
                }
                //right
                else if(key == 77){
                    facing = 1;
                    shipX += PLAYER_LR_SPEED;
                }
                //down
                else if(key == 80){
                    facing = 2;
                    shipY += PLAYER_UD_SPEED;
                }
                //left
                else if(key == 75){
                    facing = 3;
                    shipX -= PLAYER_LR_SPEED;
                }
            }
            //WSAD Movement
            else if(key == 'w' || key == 'W'){
                facing = 0;
                shipY -= PLAYER_UD_SPEED;
            }
            else if(key == 'd' || key == 'D'){
                facing = 1;
                shipX += PLAYER_LR_SPEED;
            }
            else if(key == 's' || key == 'S'){
                facing = 2;
                shipY += PLAYER_UD_SPEED;
            }
            else if(key == 'a' || key == 'A'){
                facing = 3;
                shipX -= PLAYER_LR_SPEED;
            }
            //Bullet movement
            else if(key == ' '){
                Bullet bullet = { shipX, shipY, 0, 0 };
                
                if(facing == 0){
                    bullet.x += 1;
                    bullet.y -= 1;
                    bullet.velocityY = -1;
                }
                else if(facing == 1){
                    bullet.x += 4;
                    bullet.y += 1;
                    bullet.velocityX = 2;
                }
                else if(facing == 2){
                    bullet.x += 1;
                    bullet.y += 2;
                    bullet.velocityY = 1;
                }
                else{
                    bullet.x -= 1;
                    bullet.y += 1;
                    bullet.velocityX = -2;
                }
                
                bullets.push_back(bullet);
            }
            else if(key == 27){
                system("cls");
                cout << "GAME PAUSED\n";
                cout << "Quit game? (Y/N): ";
                
                while(true){
                    int pauseKey = _getch();
                    
                    if(pauseKey == 'y' || pauseKey == 'Y'){
                        system("cls");
                        cout << "GAME OVER\n";
                        printf("Score: %d\n", score);
                        return 0;
                    }
                    
                    if(pauseKey == 'n' || pauseKey == 'N')
                    break;
                }
                
                system("cls");
            }
        }
        
        const vector<string>& currentShip = gfx.ship[facing];
        SpriteBounds shipBounds = getSpriteBounds(currentShip);
        
        largeAsteroidSpawnTimer++;
        asteroidMoveTimer++;
        
        if(largeAsteroidSpawnTimer >= 35){
            int largeAsteroidCount = 0;
            
            for(const auto& asteroid : asteroids){
                if(asteroid.large)
                largeAsteroidCount++;
            }
            
            if(largeAsteroidCount < 3)
                asteroids.push_back(spawnLargeAsteroid(largeAsteroidBounds));
                
                largeAsteroidSpawnTimer = 0;
            }
            
            if(shipX + shipBounds.offsetX < 0)
            shipX = -shipBounds.offsetX;
            if(shipY + shipBounds.offsetY < 0)
            shipY = -shipBounds.offsetY;
            if(shipX + shipBounds.offsetX + shipBounds.width > ASTEROIDS_SCREEN_WIDTH)
            shipX = ASTEROIDS_SCREEN_WIDTH - shipBounds.offsetX - shipBounds.width;
            if(shipY + shipBounds.offsetY + shipBounds.height > ASTEROIDS_SCREEN_HEIGHT)
            shipY = ASTEROIDS_SCREEN_HEIGHT - shipBounds.offsetY - shipBounds.height;
            
            for(auto bullet = bullets.begin(); bullet != bullets.end();){
                bullet->x += bullet->velocityX;
                bullet->y += bullet->velocityY;
                
                bool outsideScreen = bullet->x < 0 || bullet->x >= ASTEROIDS_SCREEN_WIDTH ||
                bullet->y < 0 || bullet->y >= ASTEROIDS_SCREEN_HEIGHT;
                bool hitAsteroid = false;
                
                //Asteroid splitting mechanic
                for(auto asteroid = asteroids.begin(); asteroid != asteroids.end(); ++asteroid){
                    SpriteBounds& asteroidBounds = asteroid->large ?
                    largeAsteroidBounds : smallAsteroidBounds;
                    
                    if(!asteroid_checkCollision(
                        bullet->x,
                        bullet->y,
                        1,
                        1,
                        asteroid->x + asteroidBounds.offsetX,
                        asteroid->y + asteroidBounds.offsetY,
                        asteroidBounds.width,
                        asteroidBounds.height
                    )){
                        continue;
                    }
                    
                    hitAsteroid = true;
                    asteroid->hitPoints--;
                    
                    if(asteroid->hitPoints > 0)
                    break;
                    
                    if(asteroid->large){
                        score += 2;
                        int splitCount = 2 + rand() % 5;
                        int centerX = asteroid->x + largeAsteroidBounds.width / 2;
                        int centerY = asteroid->y + largeAsteroidBounds.height / 2;
                        
                        asteroids.erase(asteroid);
                        
                        for(int split = 0; split < splitCount; split++){
                            int velocityX = 0;
                            int velocityY = 0;
                            
                            while(velocityX == 0 && velocityY == 0){
                                velocityX = rand() % 3 - 1;
                                velocityY = rand() % 3 - 1;
                            }
                            
                            asteroids.push_back({
                                centerX - smallAsteroidBounds.width / 2,
                                centerY - smallAsteroidBounds.height / 2,
                                velocityX,
                                velocityY,
                                false,
                                SMALL_ASTEROID_HIT_POINTS
                            });
                        }
                    }
                    else{
                        score += 10;
                        asteroids.erase(asteroid);
                    }
                    break;
                }
                //Delete bullet if it hits the screen edge or a asteroid.
                if(outsideScreen || hitAsteroid)
                bullet = bullets.erase(bullet);
                else
                ++bullet;
            }
            
            asteroid_clearBuffer(asteroid_buffer);
            //Draw the ship
            asteroid_drawSprite(
                asteroid_buffer,
                currentShip,
                shipX,
                shipY
            );
            //Asteroid movement speed
            if(asteroidMoveTimer >= ASTEROID_MOVE_DELAY){
                for(auto& asteroid : asteroids){
                    asteroid.x += asteroid.velocityX;
                    asteroid.y += asteroid.velocityY;
                }
                
                asteroidMoveTimer = 0;
            }
            
            for(const auto& asteroid : asteroids){
                const vector<string>& asteroidSprite = asteroid.large ?
                gfx.asteroidL : gfx.asteroidS;
                
                asteroid_drawSprite(
                    asteroid_buffer,
                    asteroidSprite,
                    asteroid.x,
                    asteroid.y
                );
            }
            
            for(const auto& bullet : bullets){
                if(bullet.x >= 0 && bullet.x < ASTEROIDS_SCREEN_WIDTH &&
                    bullet.y >= 0 && bullet.y < ASTEROIDS_SCREEN_HEIGHT){
                        asteroid_buffer[bullet.y][bullet.x] = '*';
                    }
                }
                
                asteroid_renderBuffer(asteroid_buffer);
                
                //If the collision check activates show the game over screen.
                for(const auto& asteroid : asteroids){
                    const SpriteBounds& asteroidBounds = asteroid.large ?
                    largeAsteroidBounds : smallAsteroidBounds;
                    
                    if(asteroid_checkCollision(
                        shipX + shipBounds.offsetX,
                        shipY + shipBounds.offsetY,
                        shipBounds.width,
                        shipBounds.height,
                        asteroid.x + asteroidBounds.offsetX,
                        asteroid.y + asteroidBounds.offsetY,
                        asteroidBounds.width,
                        asteroidBounds.height
                    )){
                        system("cls");
                        cout << "GAME OVER\n";
                        printf("\rScore: %d", score);
                        return 0;
                    }
                }
                
                //Game speed
                this_thread::sleep_for(
                    chrono::milliseconds(50)
                );
            }
            
            return 0;
        }