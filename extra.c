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
            if (board[i][j] == 1)
            {
                printf("\e[31m   ×2\e[0m");
            }
            else if (board[i][j] == 0)
            {
                printf("%5d", board[i][j]);
            }
            else if (board[i][j] <= 8)
            {
                printf("\e[32m%5d\e[0m", board[i][j]);
            }
            else if (board[i][j] <= 64)
            {
                printf("\e[36m%5d\e[0m", board[i][j]);
            }
            else if (board[i][j] <= 512)
            {
                printf("\e[34m%5d\e[0m", board[i][j]);
            }
            else
            {
                printf("\e[35m%5d\e[0m", board[i][j]);
            }
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
    int check = 0;
    int x_2, y_2;
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 1)
            {
                ++check;
                x_2 = x;
                y_2 = y;
                board[y_2][x_2] = 0;
            }
        }
    }
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
    if (check == 1)
    {
        if (board[y_2][x_2] == 0)
        {
            board[y_2][x_2] = 1;
        }
        else
        {
            board[y_2][x_2] = board[y_2][x_2] * 2;
        }
    }
}
void go_down(int board[4][4])
{
    int check = 0;
    int x_2, y_2;
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 1)
            {
                ++check;
                x_2 = x;
                y_2 = y;
                board[y_2][x_2] = 0;
            }
        }
    }
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
    if (check == 1)
    {
        if (board[y_2][x_2] == 0)
        {
            board[y_2][x_2] = 1;
        }
        else
        {
            board[y_2][x_2] = board[y_2][x_2] * 2;
        }
    }
}

void go_left(int board[4][4])
{
    int check = 0;
    int x_2, y_2;
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 1)
            {
                ++check;
                x_2 = x;
                y_2 = y;
                board[y_2][x_2] = 0;
            }
        }
    }
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
    if (check == 1)
    {
        if (board[y_2][x_2] == 0)
        {
            board[y_2][x_2] = 1;
        }
        else
        {
            board[y_2][x_2] = board[y_2][x_2] * 2;
        }
    }
}

void go_right(int board[4][4])
{
    int check = 0;
    int x_2, y_2;
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 1)
            {
                ++check;
                x_2 = x;
                y_2 = y;
                board[y_2][x_2] = 0;
            }
        }
    }
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
    if (check == 1)
    {
        if (board[y_2][x_2] == 0)
        {
            board[y_2][x_2] = 1;
        }
        else
        {
            board[y_2][x_2] = board[y_2][x_2] * 2;
        }
    }
}

void add_num1(int board[4][4])
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

void add_num2(int board[4][4])
{
    int x0 = rand() % 4;
    int y0 = rand() % 4;
    while (board[y0][x0] != 0)
    {
        x0 = rand() % 4;
        y0 = rand() % 4;
    }
    int check = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (board[i][j] == 1)
            {
                check = 1;
            }
        }
    }
    if (check == 0)
    {
        board[y0][x0] = 1;
    }
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

int checker(int board[4][4], int copy[4][4], int *turn)
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (copy[y][x] != board[y][x])
            {
                *turn = *turn + 1;
                return 0; // 変化があれば0
            }
        }
    }
    return 1;
}

int judge(int board[4][4])
{
    int count = 0; // 0のマスを数える
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 0)
            {
                ++count;
            }
        }
    }
    if (count == 1)
    {
        return 1;
    }
    else if (count > 1)
    {
        return 2;
    }
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 1)
            {
                return 0;
            }
        }
    }
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            if (board[y][x] == board[y][x + 1])
            {
                return 0; // 変化の余地があれば0
            }
        }
    }
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            if (board[y][x] == board[y + 1][x])
            {
                return 0;
            }
        }
    }
    return -1; // ゲームオーバーで-1
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    printf("Press any key to continue\n");
    int c;

    system("/bin/stty raw onlcr"); // enterを押さなくてもキー入力を受け付けるようになる
    int board[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int copy[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int turn = 1;
    int counter = 3;
    int b = 0;
    int x_break, y_break;
    add_num2(board);
    while ((c = getchar()) != '.')
    {
        if (b == 0)
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
            else if (c == 'b' && counter != 0)
            {
                b = 1;
                print_board(board);
                printf("select number\r\n左から＿番目\r\n");
                continue;
            }
            if (checker(board, copy, &turn) == 0)
            {
                if (judge(board) == 2)
                {
                    add_num2(board);
                }
                else if (judge(board) == 1)
                {
                    add_num1(board);
                }
                if (judge(board) == -1 && counter == 0)
                {
                    break;
                }
            }
            print_board(board);
            printf("Press:  u-->up    d-->down\r\n        l-->left  r-->right\r\n        b-->break number (残り:%d回)\r\n", counter);
            printf("Turn:%d  You pressed '%c'\r\n", turn, c);
        }
        else if (b == 1)
        {
            if (c == '1' || c == '2' || c == '3' || c == '4')
            {
                x_break = c - '0' - 1;
                b = 2;
                system("clear");
                printf("Press '.' to close\r\n\r\n");
                print_board(board);
                printf("select number\r\n上から＿番目\r\n");
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (c == '1' || c == '2' || c == '3' || c == '4')
            {
                y_break = c - '0' - 1;
                b = 0;
                --counter;
                board[y_break][x_break] = 0;
                system("clear");
                printf("Press '.' to close\r\n\r\n");
                print_board(board);
                printf("Press:  u-->up    d-->down\r\n        l-->left  r-->right\r\n        b-->break number (残り:%d回)\r\n", counter);
                printf("Turn:%d  You pressed '%c'\r\n", turn, c);
            }
            else
            {
                continue;
            }
        }
    }
    system("clear");
    printf("Game Over\r\n\r\n");
    print_board(board);
    printf("Thanks for playing\r\n");
    system("/bin/stty cooked"); // 後始末

    return 0;
}