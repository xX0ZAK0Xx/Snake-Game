#include <iostream>
#include <conio.h>
#include<time.h>
#include<windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using  namespace std;
bool gameOver;
int width = 40;//default medium screen
int height = 20;//default medium screen
int x, y, fruitX, fruitY,score;
char head = '^';//default head direction
int *tailX, *tailY;//to store the tail position dynamically
int length;
int speed=0;//default snake speed

enum direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};
direction dir,prevDir;

void instruction(){
    system("cls");
    cout <<"See the instructions\n";
    cout <<"________________________\n";
    cout << "Press w to move up\n";
    cout << "Press a to move left\n";
    cout << "Press d to move right\n";
    cout << "Press s to move down\n";
    cout << "Just eat the \"X\"\n\n";
    cout <<"Chose snake speed\n";
    cout <<"1. Easy\n";
    cout <<"2. Medium\n";
    cout <<"3. Hard\n";
    if(!(_kbhit())){
        switch(_getch()){
            case '1':
                cout << "Easy\n";
                speed = 100;
                break;
            case '2':
                cout << "Medium\n";
                speed = 50;
                break;
            case '3':
                cout << "Hard\n";
                speed = 20;
                break;
            default:
                break;
        }
    }
    cout <<"\nChose Board size\n";
    cout <<"1. Small\n";
    cout <<"2. Medium\n";
    cout <<"3. Large\n";
    if(!(_kbhit())){
        switch(_getch()){
            case '1':
                cout << "Small\n";
                width = 20; height =10;
                break;
            case '2':
                cout << "Medium\n";
                width = 30; height = 15;
                break;
            case '3':
                cout << "Large\n";
                width = 40; height = 20;
                break;
            default:
                break;
        }
    }
    cout << "Press ENTER to start\n";
    cin.ignore();
    system("cls");
}

void setup(){
    instruction();
    tailX = new int [800];
    tailY = new int [800];
    length = 0;
    gameOver = false;
    dir = STOP;
    prevDir = STOP;
    x = width/2;
    y = height/2;
    score = 0;
    fruitX = 1+(rand() % (width-2));//1-18
    fruitY = (rand() % height);//0-19
}
void setFruit(){
    fruitX = 1+(rand() % (width-2));//1-18
    fruitY = (rand() % height);//0-19
}
void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case KEY_LEFT:
                dir = LEFT;
                break;
            case KEY_DOWN:
                dir = DOWN;
                break;
            case KEY_RIGHT:
                dir = RIGHT;
                break;
            case KEY_UP:
                dir = UP;
                break;
            case 'x':
                gameOver = true;
                break;
            default:
                break;
        }
    }
}
void draw(){
    // system("cls");

    cout <<"Score: "<<score<<endl;
    for(int i = 0; i <width+1 ; i++){
        cout <<"#";
    }cout<<endl;

    for (int i = 0; i < height ; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout <<"#";
            if(i==y && j==x)
                cout <<head;
            else if(i==fruitY && j==fruitX)
                cout <<"X";
            else{
                bool tail = false;
                for ( int k = 0; k < length; k++){
                    if(tailX[k]==j && tailY[k]==i){
                        cout <<"o";
                        tail = true;
                    }
                }
                if(!tail)
                    cout << " ";
            }
        }
        cout << "\n";

        

    }
    for(int i = 0; i <width+1 ; i++){
        cout <<"#";
    }cout<<endl;



}
void logic(){

    int prevX = tailX[0];//previous head position X
    int prevY = tailY[0];//previous head position Y
    int prev2X, prev2Y;//to swap 
    tailX[0] = x;//new head position X
    tailY[0] = y;//new head position Y
    for( int i=1 ; i<length; i++ ){
        prev2X = tailX[i];//storing the starting position of the body X
        prev2Y = tailY[i];//storing the starting position of the body Y
        tailX[i] = prevX;// Moving body to the previous head position X
        tailY[i] = prevY;// Moving body to the previous head position Y 
        prevX = prev2X;//
        prevY = prev2Y;
    }

    switch(dir){
        case LEFT:
            if(prevDir!=RIGHT){
                x--;
                prevDir = LEFT;
                head = '<';
            }
            else{
                dir=RIGHT;
                x++;
            }
            break;
        case RIGHT:
            if(prevDir!=LEFT){
                x++;
                prevDir = RIGHT;
                head = '>';
            }
            else{
                dir=LEFT;
                x--;
            }
            break;
        case UP:
            if(prevDir!=DOWN){
                y--;
                prevDir = UP;
                head = '^';
            }
            else{
                dir=DOWN;
                y++;
            }
            break;
        case DOWN:
            if(prevDir!=UP){
                y++;
                prevDir = DOWN;
                head = 'v';
            }
            else{
                dir=UP;
                y--;
            }
            break;
        default:
            break;        
    }
    if(x < 0)
        x= width-2;
    else if(x >= width-1)
        x= 0;
    else if(y < 0)
        y=height;
    else if(y>=height)
        y=0;

    for ( int i =0 ; i<length ; i++ )
        if(tailX[i]==x && tailY[i]==y)
            gameOver = true;
    if(x==fruitX && y==fruitY){
        score+=10;
        setFruit();
        for(int i= 0 ; i<length ; i++){
            if( fruitX==tailX[i] && fruitY==tailY[i] )
                setFruit();
        }
        length++;
    }
}

int main(){
    srand(time(0));
    setup();   

    while(!gameOver){
        draw();
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
        input();
        logic();
        Sleep(speed);
        if(gameOver){
            cout <<"Score: "<<score<<endl;
            cout <<"Oops! You ate yourself!" << endl;
            cout <<"Press 'a' if you want to play again or\n";
            cout <<"Press any other key to exit." << endl;
            if(!(_kbhit())){
                switch(_getch()){
                    case 'a':
                        delete tailX;
                        delete tailY;
                        main();
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return 0;
}