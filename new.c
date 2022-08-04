#include<stdio.h>

/*
문제 설명: 헉헉! 도둑인 성민이는 감옥에서 겨우 탈출했다.
         그러나 곧 경찰의 추적이 따라 붙을 것을 안 성민이는 자신의 집에 있는
         돈과 함께 경찰의 추적을 피하고자 한다. 성민이가 경찰의 추적을 피할 수 있는지 알아보자.

입력 조건: 첫번째 줄에는 배열의 크기 n, m이 주어진다.
        2번째 줄부터 n번째 줄까지는 성민이와 성민이와 집, 경찰의 위치가 각각 t, h, p로 주어진다.
        빈 공간은 . 이며 장애물은 x 이다.
        성민이와 성민이와 집은 서로 다른 위치를 가진다.

기타 조건: 성민이와 경찰은 상하좌우로만 움직일 수 있으며 성민이가 한번 움직이면 동시에 경찰도 한칸 움직일 수 있다.(단 장애물에 가로막인 객체는 움직이지 못한다.)
        만약 집에 도착하기 전에 경찰이 집에 도착하면 성민이는 경찰을 피할 수 없다.
        만약 집에 이미 도착한 상태에서 경찰이 집에 도착하면 성민이는 경찰을 피할 수 없다.

출력 조건: 성민이가 집에 도착할 수 있는지의 여부와 집에 도착하기 위한 최소 이동횟수를 구하라.
        성민이가 집에 도착할 수 없을 경우에는 -1을 출력하면 된다.
        성민이가 집에 도착할 수 있을 경우에는 집에 도착하기 위한 최소 이동횟수를 출력하면 된다.
*/

int n, m;
char arr[10000][10000];//배열 

int pvisit[10000][10000];//경찰의 위치 방문 여부
int tvisit[10000][10000];//도둑의 위치 방문 여부

int hx,hy;//집의 위치


int tmin_move = 9999999;
int ptmin_move = 9999999;

int cnt_que[10000];
int px_que[10000];
int py_que[10000];
int tx_que[10000];
int ty_que[10000];//값들의 큐(근데 이거 함수 포인터 쓰면 되는지 알아봐)
int qi = 0, qj = 1; //qi:빼내야할 값이 있는 번호

void que_output(int *cnt, int *px, int *py, int *tx, int *ty)
{
    cnt = cnt_que[qi];
    
}

void que_input(int cnt, int px, int py, int tx, int ty)
{

}

int checking(int px, int py, int tx, int ty)
{

}

int BFS(int cnt, int px, int py, int tx, int ty)
{
    if (checking(px, py, tx, ty)) return 0;

    int mx[4] = {-1,1,0,0};
    int my[4] = {0,0,-1,1};//이동 좌표(상하좌우)

    pvisit[px][py] = 1;
    tvisit[tx][ty] = 1;
    for (int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int ncnt, npx, npy, ntx, nty;//다음 값들
            que_output(ncnt, npx, ntx, nty);//값 대입
        }

    }
}

int main()
{
    int px,py;//경찰의 x,y;
    int tx,ty;//도둑의 X,y;

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf(" %c", &arr[i][j]);
            if (arr[i][j] == 't')
            {
                tx = i;
                ty = j;
            }
            else if (arr[i][j] == 'h')
            {
                hx = i;
                hy = j;
            }
            else if (arr[i][j] == 'p')
            {
                px = i;
                py = j;
            }
        }
    }

    int val = BFS(0, px, py, tx, ty);
    if (val == 0)
    {
        printf("-1");
    }
    else
    {
        printf("%d",val);
    }
}