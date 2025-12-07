#include <stdio.h>
#include <conio.h> // for khbit() and getch()
#include <windows.h> // needed for windows functions like cursor positionning
#include <stdbool.h> // just true false
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// defines
#define SCREEN_W 80 // we use width & height values from here, so we can easily modify them later
#define SCREEN_H 25
#define GROUND_Y 22 // grounds position at 22th row (as default console window is 0-24, leaving 2 row space below)
#define DINO_X 5 // horizontal position of the dino
//#define DINO_WIDTH 16

// physics
#define JUMP_VEL 15 // dinos jumping velocity at start
#define GRAVITY 2
#define CACTUS_MOVE_STEP 3
#define FPS 25

// colors
#define C_BLACK           0
#define C_BLUE            1
#define C_GREEN           2
#define C_CYAN            3
#define C_RED             4
#define C_MAGENTA         5
#define C_YELLOW          6
#define C_WHITE           7

#define C_GRAY            8
#define C_BRIGHT_BLUE     9
#define C_BRIGHT_GREEN    10
#define C_BRIGHT_CYAN     11
#define C_BRIGHT_RED      12
#define C_BRIGHT_MAGENTA  13
#define C_BRIGHT_YELLOW   14
#define C_BRIGHT_WHITE    15



// [delay=1000/fps]
int gameDelay = 1000/FPS;

// global variables
int dinoY = 0; // dinos current vertical position
int dinoVel = 0; // current jump speed
int cactusX;
int score =0;
int highscore = 0;
bool gameover;
bool jumping;
int legAnimation = 0;

// utility function to set color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

// Start background music (loop)
void startBGM(const char* filename) {
    char cmd[512];

    // Close any existing bgm alias
    mciSendString("stop bgm", NULL, 0, NULL);
    mciSendString("close bgm", NULL, 0, NULL);

    // Open new music file
    sprintf(cmd, "open \"%s\" type mpegvideo alias bgm", filename);
    mciSendString(cmd, NULL, 0, NULL);

    // Play in loop
    mciSendString("play bgm repeat", NULL, 0, NULL);
}

// Stop background music
void stopBGM() {
    mciSendString("stop bgm", NULL, 0, NULL);
    mciSendString("close bgm", NULL, 0, NULL);
}

// initialization
void init() {
    gameDelay = 1000/FPS;
    dinoY = 0;
    dinoVel = 0;
    cactusX = SCREEN_W - 1;
    score = 0;
    gameover = false;
    jumping = false;
    legAnimation = 0;
}


// utility functions
void gotoxy (int x, int y){ // go to x, y (cursor position)
    COORD coord={x,y}; // COORD is a struct defined in windows.h
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showCursor(bool status){ // hide cursor
    CONSOLE_CURSOR_INFO info= {100, status}; // {cursor_size, true/false} defined in windows.h
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // main function, info is passed as pointer.
}


// input functions
void input(){
    if(kbhit()) { // if key pressed
        int key = getch(); // get the key
        if (key == 0 || key == 224) key = getch(); // take input again for special keys (copied from gpt older dos style)
        if ((key == ' ' || key == 'w') && !jumping) {
            jumping = true;
            dinoVel = JUMP_VEL;
            PlaySound(TEXT("jump.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
            //PlaySound(TEXT("jump.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
//             mciSendString("open \"jump.wav\" alias jumpSound", NULL, 0, NULL);
// mciSendString("play jumpSound", NULL, 0, NULL);

        }
    }
}

// draw functions
void clear(){ // clearing entire screen with white spaces
    gotoxy(0,0);
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
    printf("                                                                                \n");
}

void drawGround() {
    gotoxy(0, GROUND_Y + 1);

    // ANSI true-color (RGB: 235, 201, 201)
    printf("\x1b[38;2;183;157;157m");
    printf("≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤‹≤\n");
    printf("\x1b[0m");

}



void drawDino(int dinoY, int legAnimation){
    setColor(C_MAGENTA);
    int y = GROUND_Y - dinoY; // dinos vertical position relative to ground (dinoy is traditional x,y)
    int x = DINO_X;
    
    gotoxy(x, y - 8); printf("         ‹€ﬂ€€€€‹");
    gotoxy(x, y - 7); printf("         €€€€€€€€");
    gotoxy(x, y - 6); printf("         €€€€€ﬂﬂﬂ");
    gotoxy(x, y - 5); printf(" €      ‹€€€€ﬂﬂﬂ ");
    gotoxy(x, y - 4); printf(" €€‹  ‹€€€€€€‹‹‹ ");
    gotoxy(x, y - 3); printf(" ﬂ€€€€€€€€€€€  ﬂ ");
    gotoxy(x, y - 2); printf("   ﬂ€€€€€€€ﬂ     ");
    
    // printing the full sprite at each vertical point of dino
    if (dinoY > 0) {
        gotoxy(x, y - 1); printf("    €€ﬂ ﬂ€       "); // if dino jumping no leg animation
        gotoxy(x, y);     printf("    €‹   €‹      ");
    } else if (legAnimation == 0) {
        gotoxy(x, y - 1); printf("    ﬂ€€ﬂ  ﬂﬂﬂ    "); // else dinorunning leganimation frame 1
        gotoxy(x, y);     printf("      €‹         ");
    } else {
        gotoxy(x, y - 1); printf("     ﬂ€‹ ﬂ€      "); // else dinorunning leg animation frame 2
        gotoxy(x, y);     printf("          €‹     ");
    }
    setColor(C_BRIGHT_WHITE);

}

// Draw cactus with clipping
void drawCactus(int x) {
    setColor(C_BRIGHT_GREEN);
    if (x<-5 || x >= SCREEN_W) return;

    char *sprite[6] = { //array of 6 strings (c style)
        "€   €",
        "€   €",
        "€   €",
        "€‹‹‹€",
        "  €  ",
        "  €  "
    };

    int start, offset;

    if (x<0) {
        start = 0;
        offset = -x;
    } else {
        start = x;
        offset = 0;
    }
    // clipping (complicated af used chatgpt)
    // as computers cant draw outside of console visible area, so we need to skip characters outside (clipping)

    // loop through the cactus sprite and draw it row by row
    for (int i = 0; i<6; i++) {
        int len = 5 - offset; // number of characters to print for this row

        // making sure we don't go past the screen width
        if (start + len > SCREEN_W) {
            len = 5 - start; // if the cactus is too wide for the screen, trim its width to fit
        }

        if (len > 0) { // if there's anything to print on this row
            gotoxy(start, GROUND_Y -5 + i); // move cursor to the correct position
            for (int j = 0; j<len; j++) { // print row
                putchar(sprite[i][j + offset]);
            }
        }
    }
    setColor(C_BRIGHT_WHITE);
}



// game Screen
void gameScreen() {

    startBGM("music.wav");

    //PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    clear();
    system("cls");

    // Title
    setColor(C_MAGENTA);
    printf("\n\n\n\n\n");
    printf("        €€€€€€€€ª€€€€€€ª €€€€€€€ª€€ª  €€ª\n");
    printf("        »ÕÕ€€…ÕÕº€€…ÕÕ€€ª€€…ÕÕÕÕº»€€ª€€…º\n");
    printf("           €€∫   €€€€€€…º€€€€€ª   »€€€…º \n");
    printf("           €€∫   €€…ÕÕ€€ª€€…ÕÕº   €€…€€ª \n");
    printf("           €€∫   €€∫  €€∫€€€€€€€ª€€…º €€ª\n");
    printf("           »Õº   »Õº  »Õº»ÕÕÕÕÕÕº»Õº  »Õº\n");

    setColor(C_RED);
    printf("\n                CONSOLE RUNNER >_<\n");

    // setColor(C_BRIGHT_WHITE);
    // printf("        =====================================\n");

    // Controls
    setColor(C_BRIGHT_CYAN);
    printf("\n              [SPACE] or [W]  --> Jump\n");

    setColor(C_BRIGHT_GREEN);
    printf("                  [ENTER]     --> Start\n");

    setColor(C_BRIGHT_MAGENTA);
    printf("                    [Q]       --> Exit\n");

    // setColor(C_BRIGHT_WHITE);
    // printf("        =====================================\n");

    // Prompt
    setColor(C_BRIGHT_YELLOW);
    printf("\n           Press a key to continue...\n");

    int key;
    do {
        key = getch();
        if (key == 0 || key == 224) getch(); // ignore arrow keys
        if (key == 'q' || key == 'Q') {
            clear();
            system("cls");

            setColor(C_BRIGHT_MAGENTA);
            printf("\n\n      Shafin Loves You, mwahhh >_<\n\n");

            gameover = true;
            setColor(C_WHITE);
            return;
        }
    } while (key != 32 && key != 13); // Space or Enter

    system("cls");
    setColor(C_BRIGHT_WHITE);
}




// physics
void update(){

    //jumping logic
    if(jumping){ // working with traditional x,y coord here as dinoY is actually dinoY passing to drawDino.
        dinoY += dinoVel / 5; // updates position relative to velocity (/5 is just a balancer so we can put larger/precise values on JUMP_VEL as we are working with floats)
        dinoVel -= GRAVITY; //velocity + (dino goes up) veclocity - (dino comes down)

        if(dinoY<=0){ // landed
            dinoY=0;
            dinoVel = 0;
            jumping = false;
        }
    }


    srand(time(NULL));
    int r = rand() % 61 -10; // -10 to 30 random number;

    // cactus moving logic
    cactusX -= CACTUS_MOVE_STEP; // moving the cactus horizontallyy
    if (cactusX<-6) { // reset when offscreen left
        cactusX = SCREEN_W + r; // to screens rightmost
        score++;

        // game level/spedup logic (every 5 score)
        if (score%5 == 0 && gameDelay>30) gameDelay *= 0.9;
    }

    // leganimation logic
    legAnimation = !legAnimation; // toggling leg animation, gives the animation effect

    // collision logic
    int DINO_HIT_X_START = DINO_X + 5; // dinos hitbox horizontal
    int DINO_HIT_X_END = DINO_X + 13;
    int CACTUS_HIT_X_START = cactusX + 1; // cactus hitbox horizontal
    int CACTUS_HIT_X_END = cactusX + 4;

    bool xOverlap = (DINO_HIT_X_END > CACTUS_HIT_X_START ) && (DINO_HIT_X_START<CACTUS_HIT_X_END); // checking both edge cases (first is overlap, second is after cactus goes past through dino)
    bool yOverlap = (dinoY<6);
    if (xOverlap && yOverlap){
        PlaySound(TEXT("collide.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
        stopBGM();
        //PlaySound(NULL, 0, 0); // stop background music
        gameover = true;
    }

    // if(score%10==0 && score!=0 && gameSpeed>12){
    //     gameSpeed-=1;
    // }
}

// Main Loop
int main() {
    showCursor(false);
    PlaySound(TEXT("freshgame.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);

    while(1) {
        init();
        gameScreen();
        if(gameover) return 0;
        
        while(!gameover) {
            clear();
            input();
            update();


            gotoxy(0, 1);
            setColor(C_BRIGHT_BLUE);
            printf("SCORE: %d  |  HIGH SCORE: %d", score, highscore);
            setColor(C_BRIGHT_WHITE);
            drawCactus(cactusX);
            drawDino(dinoY, legAnimation);
            drawGround();


            Sleep(gameDelay);
            //delay(gameDelay);
        }

        // after game over (END Screen)
        if (score > highscore) highscore = score;

        setColor(C_BRIGHT_RED);
        gotoxy(30, 8);  printf("…ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕª");
        gotoxy(30, 9);  printf("∫         GAME OVER         ∫");
        gotoxy(30, 10); printf("»ÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕÕº");

        // setColor(C_BRIGHT_WHITE);
        // gotoxy(30, 12); printf("=============================");

        setColor(C_BRIGHT_GREEN);
        gotoxy(30, 13); printf("      FINAL SCORE : %d", score);

        setColor(C_BRIGHT_CYAN);
        gotoxy(30, 15); printf(" [SPACE / Enter] --> Restart");

        setColor(C_BRIGHT_MAGENTA);
        gotoxy(30, 16); printf("      [ Q ]      --> Exit");

        // setColor(C_BRIGHT_WHITE);
        // gotoxy(30, 17); printf("=============================");

        setColor(C_BRIGHT_WHITE);

        int key;
        do {
            key = getch();
            if (key == 0 || key == 224) key = getch(); // special keys

            if (key == 'q' || key == 'Q') {
                clear();
                system("cls");

                setColor(C_BRIGHT_MAGENTA);
                printf("\n\n   Shafin Loves You, mwahhh >_<\n\n");

                setColor(C_WHITE);
                return 0;
            }
        } while (key != 32 && key != 13);
        
        // Play new game sound
        PlaySound(TEXT("restart.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);


        system("cls");
    }

    return 0;
}
