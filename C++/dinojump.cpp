#include <iostream>
#include <conio.h>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>


using namespace std;

//My version of the 2D Dino Jump game in the command line, or terminal.
const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 30;

vector<string> buffer(
    SCREEN_HEIGHT,
    string(SCREEN_WIDTH, ' ')
);

void drawSprite(
    vector<string>& buffer,
    const vector<string>& sprite,
    int x, 
    int y)
{
    for(int row = 0; row < sprite.size(); row++){
        for(int col = 0; col < sprite[row].size(); col++){
            if(sprite[row][col] != ' '){
                int screenX = x + col;
                int screenY = y + row;

                if(screenX >= 0 && screenX < SCREEN_WIDTH && screenY >= 0 && screenY < SCREEN_HEIGHT){
                    buffer[screenY][screenX] = sprite[row][col];
                }
            }
        }
    }
}

void drawGround(
    vector<string>& buffer,
    const string& ground,
    int offset,
    int y)
{
    for(int x = 0; x < SCREEN_WIDTH; x++){
        buffer[y][x] = ground[(x + offset) % ground.size()];
    }
}

void clearBuffer(vector<string>& buffer){
    for(auto& row : buffer){
        row.assign(SCREEN_WIDTH, ' ');
    }
}

void renderBuffer(const vector<string>& buffer){
    system("cls");

    for(const auto& row : buffer){
        cout << row << '\n';
    }
}

struct Graphics
{
    /* data */
    vector<string> dino;
    string ground;
    vector<string> smallCactus;
    vector<string> cactus;
};

Graphics graphics(){
    //Here is the Graphics for the game
    Graphics g;
    
    g.dino = {
        "          __",
        "         / *)",
        "        |   |",
        " _      |   |",
        "| |____/    |",
        " |          |",
        "  |_________|",
        "    \\_    \\_"
    };
    g.cactus = {
        "__ __",
        "| || |",
        "| || |__",
        "|__   _|",
        "   | |",
        "   |_|"
    };
    g.ground = "_________/\\____________________/\\_________/|\\___________________________________________/||\\_____________________";
    g.smallCactus = {
        "__",
        "| |_____",
        "|___  _|",
        "    |_|"
    };

    return g;
}

bool checkCollision(
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

int dinoMain() {  
    srand(time(nullptr));
    //Start by opening a terminal.
    Graphics gfx = graphics();

    int dinoX = 5;
    int dinoY = 15;
    bool jumping = false;
    float velocityY = -1;
    const float JUMP_FORCE = -2.5f;
    const float GRAVITY = 0.45f;
    const int GROUND_Y = 15;

    bool printSmallCactus = false;
    int groundSpeed = 2;
    int cactusSpeed = 2;
    int cactusX = 100;
    int groundOffset = 0;

    while(true){
        if(_kbhit()){
            char ch = _getch();

            if (ch == ' ' && !jumping){
                jumping = true;
                velocityY = JUMP_FORCE;
            }
        }

        if(jumping){
            dinoY += velocityY;
            velocityY += GRAVITY;

            if(dinoY >= GROUND_Y){
                dinoY = GROUND_Y;
                velocityY = 0;
                jumping = false;
            }
        }

        clearBuffer(buffer);

        drawSprite(
            buffer,
            gfx.dino,
            dinoX,
            dinoY
        );
        
        int cactusY;
        int cactusWidth;
        int cactusHeight;

        if (printSmallCactus){
            cactusY = 19;
            cactusWidth = gfx.smallCactus[0].size();
            cactusHeight = gfx.smallCactus.size();
        }else{
            cactusY = 17;
            cactusWidth = gfx.cactus[0].size();
            cactusHeight = gfx.cactus.size();
        }

        int dinoWidth = 0;

        for(const auto& row : gfx.dino){
            if(row.size() > dinoWidth)
                dinoWidth = row.size();
        }
        int dinoHeight = gfx.dino.size();

        if(printSmallCactus){
            drawSprite(
                buffer,
                gfx.smallCactus,
                cactusX,
                19
            );
        }else{
            drawSprite(
                buffer,
                gfx.cactus,
                cactusX,
                17
            );
        }

        drawGround(
            buffer,
            gfx.ground,
            groundOffset,
            25
        );

        renderBuffer(buffer);

        groundOffset += groundSpeed;
        groundOffset %= gfx.ground.size();
        
        cactusX -= cactusSpeed;
        if(cactusX < -10){
            cactusX = SCREEN_WIDTH + 20 + (rand() % 60);
            printSmallCactus = rand() % 2;
            if(cactusSpeed < 10){
                cactusSpeed++;
            }

            if(groundSpeed < 10){
                groundSpeed++;
            }
        }

        if(
            checkCollision(
                dinoX + 2,
                dinoY + 1,
                dinoWidth - 4,
                dinoHeight - 1,
                cactusX + 1,
                cactusY,
                cactusWidth - 2,
                cactusHeight
            )
        ){
            system("cls");
            cout << "GAME OVER\n";
            break;
        }

        this_thread::sleep_for(
            chrono::milliseconds(50)
        );
    }

    return 0;
}