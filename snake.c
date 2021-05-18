// Snake game in C for using Windows
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

int gameover = 0, sn_y = 10, sn_x = 20, score = 0, start = 0, fruit_posX = 10, fruit_posY = 10, lastX, lastY, Xdir = 0, Ydir = 0;
int tailX[100], tailY[100];

void boundaries(char field[20][40]){
    for(int i = 0; i<20; i++){
        for(int j = 0; j<40; j++){
            if(i == 0 || j == 0 || i == 19 || j == 39)
                field[i][j] = '#';
            else
                field[i][j] = ' ';
        }
    }
}

void render(char field[20][40]){
    system("cls");
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 40; j++){
            if(field[i][j] == '#')
                printf("\033[35m%c", field[i][j]);
            else if(field[i][j] == '*')
                printf("\033[32m%c", field[i][j]);
            else
                printf("\033[33m%c", field[i][j]);
        }
        printf("\n");
    }
    Sleep(1);
}

void shift(int ar[]){
    for(int i = score; i >= 0; i--)
        ar[i] = ar[i-1];
}

void snake(char field[20][40], int len){
    char user_in;
    if(kbhit()){
        user_in = getch();
        if(user_in == 'f')
            score++;
        else if(user_in == 'w'){
            Ydir = -1;
            Xdir = 0;
            }
        else if(user_in == 's'){
            Xdir = 0;
            Ydir = 1;
            }
        else if(user_in == 'a'){
            Xdir = -1;
            Ydir = 0;
            }
        else if(user_in == 'd'){
            Xdir = 1;
            Ydir = 0;
        }
    }
    if(Ydir == -1){
        sn_y--;
        shift(tailY);
        tailY[0] = sn_y;
        shift(tailX);
        tailX[0] = sn_x;
        }
    else if(Ydir == 1){
        sn_y++;
        shift(tailY);
        tailY[0] = sn_y;
        shift(tailX);
        tailX[0] = sn_x;
        }
    else if(Xdir == -1){
        sn_x--;
        shift(tailX);
        tailX[0] = sn_x;
        shift(tailY);
        tailY[0] = sn_y;
        }
    else if(Xdir == 1){
        sn_x++;
        shift(tailX);
        tailX[0] = sn_x;
        shift(tailY);
        tailY[0] = sn_y;
        }

    if(field[sn_y][sn_x] == '#')
        gameover = 1;

    for(int k = 1; k < len; k++){
        if(sn_y == tailY[k] && sn_x == tailX[k])
            gameover = 1;
    }

    for(int i = 0; i <= len; i++){
        field[tailY[i]][tailX[i]] = 'O';
    }
}

void fruit(char field[20][40]){
    int maxI = 18, maxJ = 38;
    field[fruit_posY][fruit_posX] = '*';
    if(sn_x == fruit_posX && sn_y == fruit_posY){
        field[fruit_posY][fruit_posX] = ' ';
        srand(time(NULL));
        fruit_posX = rand() % (maxJ + 1 - 1) + 1;
        fruit_posY = rand() % (maxI + 1 - 1) + 1;
        score++;
    }
}

int main(){
    char field[20][40];
    while(gameover != 1){
        boundaries(field);
        fruit(field);
        snake(field, score);
        render(field);
    }
    printf("\033[0mGame Over\nYour score: %d", score);
    return 0;
}
