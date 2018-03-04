#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>

char canvas[25][80];
char in;
int asteroidPx, asteroidPy, shooterP, shotPx, shotPy = 0;

void initializeCanvas(char c[25][80]){
    for (int i=0; i<25; i++){
        for (int j=0; j<80; j++){
            canvas[i][j] = ' ';
            c[i][j] = canvas[i][j];
        }
    }
    canvas[24][0] = 'X'; 
    c[24][0] = canvas[24][0];
}


int createAsteroid(char c[25][80]){
    int n = rand() % 80;
    canvas[0][n] = 'o';
    c[0][n] = canvas[0][n];
    return n;
}

int moveAsteroid(char c[25][80], int pos){
    canvas[pos][asteroidPx] = ' ';
    canvas[pos][asteroidPx] = 'o';
    c[pos][asteroidPx] = canvas[pos-1][asteroidPx];
    c[pos][asteroidPx] = canvas[pos][asteroidPx];
    pos++;
    return pos;
}

int moveLeft(int pos, char c[24][80]){
    if (pos != 0){
        pos++;
        canvas[24][pos] = canvas[24][pos-1];
        canvas[24][pos-1] = ' ';
        c[24][pos] = canvas[24][pos];
        c[24][pos-1] = canvas[24][pos];
    }
    return pos;
}

int moveRight(int pos, char c[24][80]){
    if (pos != 0){
        pos--;
        canvas[24][pos] = canvas[24][pos-1];
        canvas[24][pos+1] = ' ';
        c[24][pos] = canvas[24][pos];
        c[24][pos+1] = canvas[24][pos];
    }
    return pos;
}

int newShot(char c[24][80], int pos){
    canvas[23][pos] = '*';
    c[23][pos] = canvas[23][pos];
    return pos;
}

void movePos(){
    switch (in){
        case 's':
            shooterP = moveRight(shooterP,canvas);
            break;
        case 'a':
            shooterP = moveLeft(shooterP,canvas);
            break;
        case ' ':
            shotPx = newShot(canvas, shooterP);
            break;
        default:
            initializeCanvas(canvas);
    }
}

int shoot(char c[24][80], int posy, int posx){
        canvas[posy][posx] = '*';
        if (posy != 23)
            canvas[posy-1][posx] = ' ';
        posy++;
        return posy;
}


int main()
{
    initializeCanvas(canvas);
    for (int i=0; i<100000; i++){
        asteroidPx = createAsteroid(canvas);
        scanf("%d", &in);
        movePos();
        asteroidPy = moveAsteroid(canvas, 0);
        shotPy = shoot(canvas, 23, shotPx);
        if ((shotPy == (asteroidPy+1)) && (shotPx == asteroidPx)){
            canvas[shotPy][shotPx] = ' ';
            canvas[asteroidPy][asteroidPx] = ' ';
        }
        for (int j=0; j<25; j++){
            for (int n=0; n<80; n++){
                printf("%c", canvas[j][n]);
            }
            printf("\n");
        }
        if ((asteroidPy+1) == 24)
            initializeCanvas(canvas);
        sleep(10);
    }
    return 0;
}
//By: Majd Zayyad
