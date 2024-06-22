#include <stdio.h>
#include <stdlib.h>
int AiMove;
unsigned int seed=12345;
void ShowPlayGround(char playGround[6][7], int row, int colum);
int EnemyTurn(char playGround[6][7], int row, int colum);
int PlayerTurn(char playGround[6][7], int row, int colum);
int GetColumCapacityAvailable(char playGround[6][7], int colum);
int CheckWin(char playGround[6][7],int n);
void ComputerTurn(char playGround[6][7], int row, int colum);
int CheckNextMoveWin(char playGround[6][7],char Symbol,int turns);
int getRandomNumber(int min,int max);
int main()
{
    srand(seed);
    int row = 6,colum = 7;
    char playGround[row][colum];
    for(int i = 0; i < row; i++)
    {

        for(int j=0; j < colum; j++)
        {
            playGround[i][j] = '_';
        }
    }
    int finish = 0;
    int playerWon=0;
    int plays=0;
    while(finish != 1)
    {
        if(plays<(6*7))
        {
            system("cls");
            ShowPlayGround(playGround, row, colum);
            printf("Player's Turn\n\n");
            int n = PlayerTurn(playGround, row, colum);
            plays++;
            finish = CheckWin(playGround,n);
            if(finish == 1)
            {
                playerWon=1;
                break;
            }
        }
        else
        {
            playerWon=-1;
            break;
        }
        if(plays<(6*7))
        {
            system("cls");
            ComputerTurn(playGround,row,colum);
            plays++;
            ShowPlayGround(playGround,row,colum);
            finish = CheckWin(playGround,AiMove+1);
        }
        else
        {
            playerWon=-1;
            break;
        }
    }
    if(playerWon==-1)
    {
        system("cls");
        ShowPlayGround(playGround, row, colum);
        printf("TIE");
    }
    else
    {
        system("cls");
        ShowPlayGround(playGround, row, colum);
        printf("%s",playerWon==1?"WINNER WINNER CHICKEN DINNER!":"YOU LOST!");
    }
    return 0;


}
void ShowPlayGround(char playGround[6][7], int row, int colum)
{
    for(int j = 0; j < colum; j++)
    {
        printf("|%d", j+1);
    }
    printf("|\n");
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < colum; j++)
        {
            printf("|%c",playGround[i][j]);
        }
        printf("|\n");
    }
    for(int j = 0; j < colum; j++)
    {
        printf("|%d", j+1);
    }
    printf("|\n");
}
int EnemyTurn(char playGround[6][7], int row, int colum)
{
    while(1 != 0)
    {
        int n = 0;
        printf("Enter The Colum To Play in (1-7): ");
        scanf("%d", &n);
        if(!(n <= 7 && n > 0))
        {
            system("cls");
            ShowPlayGround(playGround, row, colum);
            printf("\nTry Again!\n\n");
            continue;
        }
        if(GetColumCapacityAvailable(playGround, n-1)> 0)
        {
            playGround[GetColumCapacityAvailable(playGround, n-1)-1][n-1] = 'O';
            return n;
        }
        else
        {
            system("cls");
            ShowPlayGround(playGround, row, colum);
            printf("\nTry Again!\n\n");
            continue;
        }
    }

}
int PlayerTurn(char playGround[6][7], int row, int colum)
{
    while(1 != 0)
    {
        int n = 0;
        printf("Enter The Colum To Play in (1-7): ");
        scanf("%d", &n);
        if(!(n <= 7 && n > 0))
        {
            system("cls");
            ShowPlayGround(playGround, row, colum);
            printf("\nTry Again!\n\n");
            continue;
        }
        if(GetColumCapacityAvailable(playGround, n-1) > 0)
        {
            playGround[GetColumCapacityAvailable(playGround, n-1)-1][n-1] = 'X';
            return n;
        }
        else
        {
            system("cls");
            ShowPlayGround(playGround, row, colum);
            printf("\nTry Again!\n\n");
            continue;
        }
    }
}
int GetColumCapacityAvailable(char playGround[6][7], int colum)
{

    int Counter = 0;
    for(int i = 0; i < 6; i++)
    {
        if(playGround[i][colum] == '_')
        {
            Counter++;
        }
        else
        {
            return Counter;
        }
    }
    return Counter;
}
int CheckWin(char playGround[6][7],int n)
{
    char Symbol=playGround[GetColumCapacityAvailable(playGround, n-1)][n-1] == 'X' ? 'X' : 'O';
    int RLline[7];
    for(int i = 0; i < 7; i++)RLline[i] = 0 ;
    RLline[3] = 1;
    int curRow=GetColumCapacityAvailable(playGround, n-1);
    int maxRight = 7-n > 3 ? 3 : 7-n, maxLeft = n > 3 ? 3 : n-1 ;
    for(int i = 0; i < maxLeft; i++)
    {
        RLline[3-maxLeft+i]=playGround[curRow][n-1-maxLeft+i] == Symbol ? 1 : 0;
    }
    for(int i = 4; i < 4+maxRight; i++)
    {
        RLline[i]=playGround[curRow][n-1+i-3] == Symbol ? 1 : 0;
    }
    int Counter = 0;
    for(int i = 0; i < 7; i++)
    {
        Counter = RLline[i] == 1 ? Counter+1 : 0 ;
        if(Counter==4)return 1;
    }
    Counter = 0;
    for(int i = 0; i < 6; i++)
    {
        Counter = playGround[i][n-1] == Symbol ? Counter+1 : 0 ;
        if(Counter == 4)return 1;
    }
    Counter=0;
    int maxColum=7,maxRow=6;
    int Current_Row = curRow + 1, Current_Column = n;
    int upright =maxColum-Current_Column<Current_Row-1?maxColum-Current_Column:Current_Row-1;
    int downright = maxColum-Current_Column<maxRow-Current_Row?maxColum-Current_Column:maxRow-Current_Row;
    int upleft = Current_Column-1<Current_Row-1?Current_Column-1:Current_Row-1;
    int downleft = Current_Column-1<maxRow-Current_Row?Current_Column-1:maxRow-Current_Row;
    Current_Column--;
    Current_Row--;
    for(int i=upright; i>=0; i--)
        if(playGround[Current_Row-i][Current_Column+i]==Symbol)
        {
            Counter++;
            if(Counter==4)return 1;
        }
        else Counter=0;
    Counter--;
    for(int i=0; i<=downleft; i++)
        if(playGround[Current_Row+i][Current_Column-i]==Symbol)
        {
            Counter++;
            if(Counter==4)return 1;
        }
        else Counter=0;
    Counter=0;
    for(int i=upleft; i>=0; i--)
        if(playGround[Current_Row-i][Current_Column-i]==Symbol)
        {
            Counter++;
            if(Counter==4)return 1;
        }
        else Counter=0;
    Counter--;
    for(int i=0; i<=downright; i++)
        if(playGround[Current_Row+i][Current_Column+i]==Symbol)
        {
            Counter++;
            if(Counter==4)return 1;
        }
        else Counter=0;
    return 0;
}
void ComputerTurn(char playGround[6][7], int row, int colum)
{

    if(CheckNextMoveWin(playGround,'O',1)==1)
    {
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }
    else if(CheckNextMoveWin(playGround,'X',1)==1)
    {
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }
    else if(CheckNextMoveWin(playGround,'O',2)==1)
    {
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }
    else if(CheckNextMoveWin(playGround,'X',2)==1)
    {
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }
    else if(CheckNextMoveWin(playGround,'O',3)==1)
    {
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }

    else
    {
        while(1>0)
        {
            AiMove= getRandomNumber(0,6);
            if(GetColumCapacityAvailable(playGround, AiMove) > 0)break;
        }
        playGround[GetColumCapacityAvailable(playGround,AiMove)-1][AiMove] = 'O';
    }
}
int getRandomNumber(int min,int max)
{
    return (rand() % (max - min + 1)) + min;
}
int CheckNextMoveWin(char playGround[6][7],char Symbol,int turns)
{
    int Counter=0,EmptyCounter=0;
    int Line[4]= {2,2,2,2};
    int LinePos[4]= {0,0,0,0};
    for(int s=0; s<6; s++)
    {
        for(int j=0; j<4; j++)Line[j]= 2;
        for(int i=0; i<7; i++)
        {
            char played=playGround[s][i];
            int canPlay=1;
            if(s<5)canPlay=playGround[s+1][i]!='_'?1:0;
            Line[i%4]= played == Symbol ? 1 :( (played == '_'&&canPlay==1) ? 0 : 2);
            LinePos[i%4]=i;
            Counter=0;
            EmptyCounter=0;
            for(int j=0; j<4; j++)
                if(Line[j]==1)Counter++;
                else if(Line[j]==2)
                {
                    Counter=0;
                    break;
                }
                else if(Line[j]==0)EmptyCounter++;
            if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));
        }
    }
    for(int s=0; s<7; s++)
    {
        for(int j=0; j<4; j++)Line[j]=2;
        for(int i=0; i<6; i++)
        {
            char played=playGround[i][s];
            Line[i%4]= played == Symbol ? 1 :( (played == '_') ? 0 : 2);
            LinePos[i%4]=s;
            Counter=0;
            EmptyCounter=0;
            for(int j=0; j<4; j++)
                if(Line[j]==1)Counter++;
                else if(Line[j]==2)
                {
                    Counter=0;
                    break;
                }
                else if(Line[j]==0)EmptyCounter++;
            if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));
        }
    }
    for(int j=0; j<4; j++)Line[j]=2;
    int Current_Row;
    int Current_Column;
    Counter=0,EmptyCounter=0;
    for(int i=0; i<=5; i++)
    {
                for(int j=0; j<4; j++)Line[j]=2;
        int LineCounter=0;
        for(int j=0; j<=6; j++)
        {
            Current_Row=i+1;
            Current_Column=j+1;
            int maxColum=7,maxRow=6;
            int upright =maxColum-Current_Column<Current_Row-1?maxColum-Current_Column:Current_Row-1;
            int downright = maxColum-Current_Column<maxRow-Current_Row?maxColum-Current_Column:maxRow-Current_Row;
            int upleft = Current_Column-1<Current_Row-1?Current_Column-1:Current_Row-1;
            int downleft = Current_Column-1<maxRow-Current_Row?Current_Column-1:maxRow-Current_Row;
            Current_Column--;
            Current_Row--;
            for(int i=upright; i>=0; i--)
            {
                if(playGround[Current_Row-i][Current_Column+i]==Symbol)
                {
                    Counter++;
                    Line[LineCounter%4]=1;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }
                else if(playGround[Current_Row-i][Current_Column+i]=='_'&&playGround[Current_Row-i+1][Current_Column+i]!='_')
                {
                    EmptyCounter++;
                    Line[LineCounter%4]=0;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }
                else
                {
                    Counter=0;
                    EmptyCounter=0;
                    Line[LineCounter%4]=2;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }

                if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));

            }
            for(int i=1; i<=downleft; i++)
            {
                if(playGround[Current_Row+i][Current_Column-i]==Symbol)
                {
                    Counter++;
                    Line[LineCounter%4]=1;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }
                else if(playGround[Current_Row+i][Current_Column-i]=='_'&&((Current_Row+i)>5)?playGround[Current_Row+i+1][Current_Column-i]!='_':0)
                {
                    EmptyCounter++;
                    Line[LineCounter%4]=0;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }
                else
                {
                    Counter=0;
                    EmptyCounter=0;
                    Line[LineCounter%4]=2;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }

                if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));
            }
            LineCounter=0;
            for(int x=0; x<4; x++)Line[x]=2;
            EmptyCounter=0,Counter=0;
            for(int i=upleft; i>=0; i--)
            {
                if(playGround[Current_Row-i][Current_Column-i]==Symbol)
                {
                    Counter++;
                    Line[LineCounter%4]=1;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }
                else if(playGround[Current_Row-i][Current_Column-i]=='_'&&playGround[Current_Row-i+1][Current_Column-i]!='_')
                {
                    EmptyCounter++;
                    Line[LineCounter%4]=0;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }
                else
                {
                    Counter=0;
                    EmptyCounter=0;
                    Line[LineCounter%4]=2;
                    LinePos[LineCounter%4]=Current_Column-i;
                    LineCounter++;
                }


                if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));
            }
            for(int i=1; i<=downright; i++)
            {
                if(playGround[Current_Row+i][Current_Column+i]==Symbol)
                {
                    Counter++;
                    Line[LineCounter%4]=1;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }
                else if(playGround[Current_Row+i][Current_Column+i]=='_'&&((Current_Row+i)<5)?playGround[Current_Row+i+1][Current_Column+i]!='_':0)
                {
                    EmptyCounter++;
                    Line[LineCounter%4]=0;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }
                else
                {
                    Counter=0;
                    EmptyCounter=0;
                    Line[LineCounter%4]=2;
                    LinePos[LineCounter%4]=Current_Column+i;
                    LineCounter++;
                }
                if(EmptyCounter==turns&&Counter==(4-turns))for(int j=0; j<4; j++)if(Line[j]==0)return 1+(0/(AiMove=LinePos[j]));
            }
        }
    }
    return 0;
}
