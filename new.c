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

int cnt_que[10000];
int px_que[10000];
int py_que[10000];
int tx_que[10000];
int ty_que[10000];//값들의 큐
int qi = 0, qj = 1; //qi:빼내야할 값이 있는 번호, qj: 값을 넣어야하는 위치

void que_output(int *cnt, int *px, int *py, int *tx, int *ty)
{
    /*
        큐에서 값을 빼내어 변수에 대입 시켜줌
    */

    if (cnt_que[qi] == -1) return;
    *cnt = cnt_que[qi];
    cnt_que[qi] = -1;//-1인 이유는 0도 좌표가 가능하기 때문에 이것을 설정해준다.
    *px = px_que[qi];
    px_que[qi] = -1;
    *py = py_que[qi];
    py_que[qi] = -1;
    *tx = tx_que[qi];
    tx_que[qi] = -1;
    *ty = ty_que[qi];
    qi = (qi + 1) % 10000;
}

void que_input(int cnt, int px, int py, int tx, int ty)
{
    /*
        큐에 값을 넣어줌
    */

    if (cnt_que[qj] != -1)
    {
        printf("오류\n");
        return;
    }//큐가 가득 찼을 경우 오류(Only for debug)
    
    cnt_que[qj] = cnt;
    px_que[qj] = px;
    py_que[qj] = py;
    tx_que[qj] = tx;
    ty_que[qj] = ty;
    qj = (qj + 1) % 10000;
}

int checking(int px, int py, int tx, int ty)
{
    /* 반환의 종류
        1. 경찰과 도둑 모두 이상 없음
        0. 둘 다 이상 있음
        -1. 경찰만 이상 있음
        -2. 도둑만 이상 있음
    */
    /* 반환의 경우
        1. 도둑이나 경찰이 범위를 벗어나는 경우(이 경우는 무조건 거짓을 반환한다.)
        2. 도둑이나 경찰 둘 중 하나라도 현재 위치에 이미 방문한 경우(이 경우는 무조건 거짓을 반환한다.)
        3. 도둑이나 경찰이 장애물을 만나는 경우(한명이라도 이동 가능하면 참을 반환한다.)
        4. 경찰이 집에 도착했을 경우(이 경우는 무조건 거짓을 반환한다.)
        5. 도둑이 집에 도착했을 경우(이 경우는 무조건 참을 반환한다.)
    */
}

int BFS(int cnt, int px, int py, int tx, int ty)
{
    int mx[4] = {-1,1,0,0};
    int my[4] = {0,0,-1,1};//이동 좌표(상하좌우)

  
    for (int i = 0 ; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (checking(px+mx[i], py+my[i], tx+mx[j], ty+my[j]) == 0) continue;
            else return cnt+1;//집에 한번이라도 도착할 수 있는 경우가 최단거리이다.

            //여기까지 오면 가볼만한 구간이다(이 코드는 조건부를 수정 할 경우 checking if문 안으로 경우에 맞춰 넣어줘야한다.)
            que_input(cnt+1, px+mx[i], py+my[i], tx+mx[j], ty+my[j]);
        }
    }  

    pvisit[px][py] = 0;
    tvisit[tx][ty] = 0;//방문 여부 초기화
    int ncnt, npx, npy, ntx, nty;//다음 값들
    que_output(ncnt, npx, npy, ntx, nty);//값 대입
    return BFS(ncnt, npx, npy, ntx, nty);//다음 값으로 반복

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
    return 0;
}