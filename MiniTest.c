#include <stdlib.h>
#include <stdio.h>

void printMenu()
{
    printf("---------Menu------------------\n");
    printf("1. Input the value of N.\n");
    printf("2. Initial status of game.\n");
    printf("3. Move\n");
    printf("4. Roll back\n");
    printf("5. Print your game's status.\n");
    printf("6. Exit.\n");
}
int **getN(int *n)
{
    printf("Hello, let 's input your N's value: ");
    scanf("%d", n);

    int **table = (int **)malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++)
    {
        int *row = (int *)malloc(*n * sizeof(int));
        table[i] = row;
    }
    return table;
}
int idX, idY;
void inputGrid(int **Grid, int n)
{
    printf("Please input cell's data. \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &Grid[i][j]);
            if (Grid[i][j] == 0)
            {
                idX = i;
                idY = j;
            }
        }
}

void printGrid(int **Grid, int n)
{
    printf("Here is your game's table!!!\n");
    printf("______________________________\n");
    for (int i = 0; i < n; i++, printf("||\n"))
        for (int j = 0; j < n; j++)
            printf("||%10d", Grid[i][j]);
    printf("______________________________\n");
}

int moveX[] = {0, 0, 1, -1};
int moveY[] = {-1, 1, 0, 0};

enum
{
    true,
    false
};
enum
{
    LEFT,
    RIGHT,
    DOWN,
    UP
};

char stack[1000];
int top = -1;
void push(char c)
{
    top += 1;
    stack[top] = c;
}
int isEmpty()
{
    if (top == -1)
        return true;
    else
        return false;     
}
void pop()
{
    top--;
}

void Swap(int **Grid, int x0, int y0, int x1, int y1)
{
    int tmp = Grid[x0][y0];
    Grid[x0][y0] = Grid[x1][y1];
    Grid[x1][y1] = tmp;
}

int move(int **grid, int n, char c)
{
    int x = idX, y = idY;
    switch (c)
    {
    case 'U':
        idX += moveX[UP];
        idY += moveY[UP];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
            push('D');
        }
        break;
    case 'D':
        idX += moveX[DOWN];
        idY += moveY[DOWN];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            push('U');
            Swap(grid, x, y, idX, idY);
        }
        break;
    case 'R':
        idX += moveX[RIGHT];
        idY += moveY[RIGHT];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
            push('L');
        }

        break;
    case 'L':
        idX += moveX[LEFT];
        idY += moveY[LEFT];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
            push('R');
        }
        break;
    }
}

int moveWithoutPush(int **grid, int n, char c)
{
    int x = idX, y = idY;
    switch (c)
    {
    case 'U':
        idX += moveX[UP];
        idY += moveY[UP];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
            
        }
        break;
    case 'D':
        idX += moveX[DOWN];
        idY += moveY[DOWN];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
        }
        break;
    case 'R':
        idX += moveX[RIGHT];
        idY += moveY[RIGHT];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
        }

        break;
    case 'L':
        idX += moveX[LEFT];
        idY += moveY[LEFT];
        if (idX >= n || idX < 0 || idY < 0 || idY >= n)
        {
            idX = x;
            idY = y;
            printf("Invalid move.\n");
        }
        else
        {
            Swap(grid, x, y, idX, idY);
        }
        break;
    }
}

void getPlayerSolution(int **grid, int n)
{
    printf("Please input your movement here: ");
    char c;
    fflush(stdin);
    scanf("%c", &c);
    move(grid, n, c);
}
void rollBack(int** Grid, int n)
{
    if (isEmpty() == true)
        {
            printf("Unable to roll back!!!\n");
            return;
        }
    char c = stack[top];
    pop();
    moveWithoutPush(Grid, n, c);
}
int main()
{

    int q;
    int N = 0;
    int **grid;
    do
    {
        printMenu();
        scanf("%d", &q);
        switch (q)
        {
        case 1:
            grid = getN(&N);
            break;
        case 2:
            inputGrid(grid, N);
            break;
        case 3:
            getPlayerSolution(grid, N);
            break;
        case 4:
            printf("How many times do you want to roll back? ");
            int t;
            scanf("%d", &t);
            while (t > 0)
            {
                rollBack(grid, N);
                t--;
            }
            break;

        case 5:
            printGrid(grid, N);
            break;

        case 6:
            printf("Good bye. See you again.\n");
            return 0;
            break;
            
        default:
            printf("Your input is invalid. Please input again.\n");
            break;
        }
    } while (q != 6);
}