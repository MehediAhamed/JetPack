#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int playJetPack();
void gotoxy(int x, int y);                // input coordinate
void setcursor(bool visible, DWORD size); // set bool visible = 0(invisible), bool visible = 1(visible)
int serialJP(int x, FILE *fpRB);
int deserialJP(int x, FILE *fpRB);
void instructionsJetPack();
void updatescoreJetPack(int *scoreJP);
void gameoverJetPack(int *scoreJP);

int main()
{
    setcursor(0, 0);
    do
    {
        system("cls");
        system("color 1E");
        gotoxy(43, 9);
        cout << " -------------------------- ";
        gotoxy(43, 10);
        cout << " |   >> JETPACK  RIDE <<  | ";
        gotoxy(43, 11);
        cout << " --------------------------";
        gotoxy(45, 13);
        cout << "1. START GAME";
        gotoxy(45, 15);
        cout << "2. INSTRUCTIONS";
        gotoxy(45, 17);
        cout << "3. QUIT";
        gotoxy(45, 19);
        cout << "Select an Option- ";
        char op = getch();

        if (op == '1')
        {
            Beep(1459,105);
            playJetPack();
        }

        else if (op == '2'){

            Beep(1459,105);
            instructionsJetPack();
        }

        else if (op == '3')
        {
            system("cls");
            system("color 1");

            Beep(1459,105);
            exit(0);
        }
    } while (1);
    return 0;
}

int playJetPack()
{
    system("cls");
    //system("color 1");
    srand(time(0));
    char mv;
    char repeat = 'y';
    int highscore = 0;
    while (repeat == 'y')
    {
        system("cls");
        system("color 9");
        gotoxy(45, 13);
        cout << "Press Any Key To Start...";
        getch();
        system("cls");
        setcursor(0,0);
        system("color 6");
        int scoreJP = 0;
        bool isBool = true;
        int x = 9;
        int scrnRow[3];
        int scrnCol[3];
        scrnCol[0] = 13;            //three initial positions for the bars
        scrnCol[1] = 26;
        scrnCol[2] = 38;
        for (int i = 0; i < 3; i++)
        {
            scrnRow[i] = (rand() % 12 ) + 2;        //used for determing the gap in bars
        }
        string grid[20][40];
        for (int i = 0; i < 20; i++)            //creates the outer border
        {
            for (int j = 0; j < 40; j++)
            {
                if (i == 0 || i == 19 || j == 39 || j == 0)
                    grid[i][j] = 219;
                else
                    grid[i][j] = " ";
            }
        }
        while (isBool == true)
        {
            for (int i = 0; i < 3; i++)         //remove the bars
            {
                for (int j = 1; j < 19; j++)
                {
                    grid[j][scrnCol[i]] = " ";
                }
            }
            for (int i = 0; i < 3; i++)         //changes the position of the bars closer
            {
                scrnCol[i]--;
            }
            for (int i = 0; i < 3; i++)
            {
                for (int j = 1; j < 19; j++)        //generates the bars
                {
                    grid[j][scrnCol[i]] = "|";
                }
            }
            for (int i = 0; i < 3; i++)         //generates gaps in the bars
            {
                grid[scrnRow[i]][scrnCol[i]] = " ";
                grid[scrnRow[i] + 1][scrnCol[i]] = " ";
                grid[scrnRow[i] + 2][scrnCol[i]] = " ";
                grid[scrnRow[i] + 3][scrnCol[i]] = "*";
                //grid[scrnRow[i] + 4][scrnCol[i]] = "*";
            }
            for (int i = 0; i < 3; i++)     //pushes back a bar at the end when its nearest
            {
                if (scrnCol[i] == 1)
                {
                    scrnCol[i] = 38;
                    scrnRow[i] = (rand() % 12 ) + 2;
                }
            }
            grid[x][2] = " ";
            grid[x][3] = " ";
            if (kbhit())            //makes jump
            {
                mv = getch();
                x = x - 3;
            }
            x++;
            if (x < 1)
                x = 1;
            for (int i = 0; i < 3; i++)         //points add
            {
                if (scrnCol[i] == 3)
                    if (grid[x][3] == "*" || grid[x][2] == "*" || grid[x+1][2] == "*" || grid[x+1][3] == "*")
                        scoreJP = scoreJP + 1;
                if (grid[x][2] == "|" || grid[x][3] == "|" || x>=19 || x <= 1)      //die conditions
                    isBool = false;
            }
            grid[x][2] = "C";               //jetpack player
            grid[x][3] = 2;
            for (int i = 1; i < 19; i++)        //removes the bar at nearest
            {
                grid[i][1] = " ";
            }
            for (int i = 0; i < 20; i++)        //prints the entire screen again
            {
                for (int j = 0; j < 40; j++)
                {
                    cout << grid[i][j];
                }
                cout << endl;
            }
            cout <<"\n\t\tScore = " << scoreJP;        //prints score
            Sleep(120);
            system("cls");
        }
        updatescoreJetPack(&scoreJP);
        gameoverJetPack(&scoreJP);
    }
    system("color 7");
    system("cls");
    return 0;
}



void instructionsJetPack()
{

    system("cls");
    gotoxy(43, 9);
    system("color 27");
    cout << "Instructions";
    gotoxy(41, 10);
    cout << "________________\n\n";
    gotoxy(41, 12);
    cout << ">> Avoid touching the border and the trees ";
    gotoxy(41, 13);
    cout << ">> Press 'SPACE' to thrust up";
    gotoxy(41, 14);
    cout << ">> Collect the coins to score points";
    gotoxy(41, 15);
    cout << ">> Press 'escape' to exit\n\n";
    gotoxy(41, 17);
    cout << "Press any key to go back to menu";
    getch();
}

void gotoxy(int x, int y) // input coordinate
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) // set bool visible = 0(invisible), bool visible = 1(visible)
{
    if (size == 0)
        size = 20; // size is 0 to 20
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void gameoverJetPack(int *scoreJP)
{
    Beep(6059, 80);
    system("cls");
    system("color 4F");
    char ch;
    cout << endl;
    gotoxy(44, 10);
    cout << "---->>>> Game Over <<<<----" << endl;
    gotoxy(44, 11);
    cout << "___________________________" ;

    FILE *fpRB = fopen("jetpack.txt", "r");
    int hs = deserialJP(*scoreJP, fpRB);

    gotoxy(45, 14);
    cout << "Your Score :" << *scoreJP << endl;
    gotoxy(45, 15);
    cout << "High Score :" << hs << endl;
    gotoxy(45, 18);
    cout << "RETRY? (y/n) = "; // if wannna play again
    cin >> ch;
    ch = tolower(ch);
    if (ch == 'y')
    {
        playJetPack();
    }
    else
    {
        system("color 7");
        system("cls");
        exit(0);
    }
    getch();
}

void updatescoreJetPack(int *scoreJP) // print score
{
    //Beep(700, 80);
    FILE *fpRB = fopen("jetpack.txt", "a+");
    serialJP(*scoreJP, fpRB);
}

int serialJP(int x, FILE *fpRB)
{
    fpRB = fopen("jetpack.txt", "a+");
    fprintf(fpRB, "%d ", x);
    fclose(fpRB);
}

int deserialJP(int x, FILE *fpRB)
{
    int i = 0;
    int num[10000];
    char ch;

    fpRB = fopen("jetpack.txt", "r");

    while (!feof(fpRB))
    {
        fscanf(fpRB, "%d ", &num[i]);
        i++;
    }
    remove("jetpack.txt");
    fclose(fpRB);

    for (int k = 0; k < i - 1; k++)
    {
        for (int j = 0; j < i - k - 1; j++)
        {
            if (num[j + 1] > num[j])
            {
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }

    FILE *fpRB1 = fopen("jetpack.txt", "w");
    for (int k = 0; k < i; k++)
    {
        fprintf(fpRB1, "%d ", num[k]);
    }

    fclose(fpRB1);
    return num[0];
}
