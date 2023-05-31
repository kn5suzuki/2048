#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_board(int board[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        printf(" ");
        for (int j = 0; j < 4; ++j)
        {
            printf("%5d", board[i][j]);
        }
        printf("\r\n\r\n");
    }
}
void change(int *a, int *b)
{ // aが下流
    if (*a == 0 && *b != 0)
    {
        *a = *b;
        *b = 0;
    }
}

void add(int *a, int *b)
{
    if (*a != 0 && *a == *b)
    {
        *a = 2 * (*a);
        *b = 0;
    }
}
void go_up(int board[4][4])
{
    for (int x = 0; x < 4; ++x)
    {
        for (int i = 0; i < 3; ++i)
        { // まず詰める
            for (int y = 0; y + i < 3; ++y)
            {
                change(&board[y][x], &board[y + 1][x]);
            }
        }
        for (int y = 0; y < 3; ++y)
        { // 足せるところを足す
            add(&board[y][x], &board[y + 1][x]);
        }
        for (int i = 0; i < 2; ++i)
        { // 詰める
            for (int y = 1; y + i < 3; ++y)
            {
                change(&board[y][x], &board[y + 1][x]);
            }
        }
    }
}
void go_down(int board[4][4])
{
    for (int x = 0; x < 4; ++x)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int y = 0; y + i < 3; ++y)
            {
                change(&board[3 - y][x], &board[2 - y][x]);
            }
        }
        for (int y = 0; y < 3; ++y)
        {
            add(&board[3 - y][x], &board[2 - y][x]);
        }
        for (int i = 0; i < 2; ++i)
        {
            for (int y = 1; y + i < 3; ++y)
            {
                change(&board[3 - y][x], &board[2 - y][x]);
            }
        }
    }
}

void go_left(int board[4][4])
{
    for (int y = 0; y < 4; ++y)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int x = 0; x + i < 3; ++x)
            {
                change(&board[y][x], &board[y][x + 1]);
            }
        }
        for (int x = 0; x < 3; ++x)
        {
            add(&board[y][x], &board[y][x + 1]);
        }
        for (int i = 0; i < 2; ++i)
        {
            for (int x = 1; x + i < 3; ++x)
            {
                change(&board[y][x], &board[y][x + 1]);
            }
        }
    }
}

void go_right(int board[4][4])
{
    for (int y = 0; y < 4; ++y)
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int x = 0; x + i < 3; ++x)
            {
                change(&board[y][3 - x], &board[y][2 - x]);
            }
        }
        for (int x = 0; x < 3; ++x)
        {
            add(&board[y][3 - x], &board[y][2 - x]);
        }
        for (int i = 0; i < 2; ++i)
        {
            for (int x = 1; x + i < 3; ++x)
            {
                change(&board[y][3 - x], &board[y][2 - x]);
            }
        }
    }
}

void new_num(int board[4][4])
{
    int x0 = rand() % 4;
    int y0 = rand() % 4;
    while (board[y0][x0] != 0)
    {
        x0 = rand() % 4;
        y0 = rand() % 4;
    }
    if (rand() % 10 == 0)
    {
        board[y0][x0] = 4;
    }
    else
    {
        board[y0][x0] = 2;
    }
}

int checker(int board[4][4], int copy[4][4])
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (copy[y][x] != board[y][x])
            {
                return 0; // 変化があれば0
            }
        }
    }
    return 1;
}

int judge(int board[4][4])
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 0)
            {
                return 0; // 盤上に0があれば0
            }
        }
    }
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            if (board[y][x] == board[y][x + 1])
            {
                return 1; // 変化の余地があれば1
            }
        }
    }
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (board[y][x] == board[y + 1][x])
            {
                return 1;
            }
        }
    }
    return 2; // ゲームオーバーで2
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    printf("Press any key to continue\n");
    int c;

    system("/bin/stty raw onlcr"); // enterを押さなくてもキー入力を受け付けるようになる
    int board[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int copy[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    new_num(board);
    while ((c = getchar()) != '.')
    {
        system("clear");
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                copy[y][x] = board[y][x];
            }
        }
        printf("Press '.' to close\r\n\r\n");
        if (c == 'u')
        {
            go_up(board);
        }
        else if (c == 'd')
        {
            go_down(board);
        }
        else if (c == 'l')
        {
            go_left(board);
        }
        else if (c == 'r')
        {
            go_right(board);
        }
        if (checker(board, copy) == 0)
        {
            if (judge(board) == 0)
            {
                new_num(board);
            }
            if (judge(board) == 2)
            {
                break;
            }
        }
        print_board(board);
        printf("Press  u-->up   d-->down\r\n       l-->left r-->right\r\n");
        printf("You pressed '%c'\r\n", c);
    }
    system("clear");
    printf("Game Over\r\n\r\n");
    print_board(board);
    printf("Thanks for playing\r\n");
    system("/bin/stty cooked"); // 後始末

    return 0;
}