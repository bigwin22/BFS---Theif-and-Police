#include <stdio.h>

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

char arr[10000][10000];//초기 위치 정보 및 대피소 정보를 담을 배열

int n, m;//배열의 크기

int pvisit[1000][1000] ={0};//경찰의 위치 방문 여부
int tvisit[1000][1000] = {0};//도둑의 위치 방문 여부

int hx, hy;//집의 위치

int tmin_move = 9999999;//도둑 최소 이동 횟수
int ptmin_move = 9999999;//경찰 최소 이동 횟수

int checking(int px, int py, int tx, int ty, int cnt)
{
    /* 
    다음 좌표의 유효성 검사: 
    리턴 값이 0일 경우 둘의 모두 좌표에 문제가
    리턴 값이 -1일 경우 도둑의 좌표에 문제가
    리턴 값이 -2일 경우 경찰의 좌표에 문제가
    리턴 값이 1일 경우 둘의 좌표는 유효하다
    */
    if ((px > m || py > n || px < 1 || py < 1))//좌표의 범위 유효성 검사(경찰) -> 불가의 경우
        return -2;
    if ((tx > m || ty > n || tx < 1 || ty < 1))//좌표의 범위 유효성 검사(도둑) -> 불가의 경우
        return -1;
    if (arr[px][py] == 'x' || arr[tx][ty] == 'x')//장애물이 있는 경우
        return;
    if (pvisit[px][py] || tvisit[tx][ty])//경찰이나 도둑이 한번이라도 방문 했을 경우
        return;


    if (tx == px && ty == py)//도둑이 경찰에 잡혔을 경우
        return;

    if (tx == hx && ty == hy)//도둑이 집에 도착했을 경우
    {
        if (cnt < tmin_move)//이동 횟수가 최소 이동 횟수보다 적을 경우
            tmin_move = cnt;
        return;
    }  
    else if (px == hx && py == hy)//경찰이 집에 도착했을 경우
    {
        if (cnt < ptmin_move)//이동 횟수가 최소 이동 횟수보다 적을 경우
            ptmin_move = cnt;
        return;
    }
}

void bfs(int px, int py, int tx, int ty, int cnt) //px, py : 경찰의 좌표, tx, ty : 도둑의 좌표, hx, hy: 집의 좌표
//1을 리턴하는 경우는 도둑이 무사히 집에 도착할 수 있는 경우이다.
//1은 정상적으로 도착을 한 경우이다.
//만약 진행도중 cnt가 최소 이동 횟수를 넘으면 그 함수는 진행하지 않는다.
//만약 경찰이 도둑의 집까지 도착하는 최소 이동 횟수보다 적거나 같으면 도둑은 집에 못 온다. -> 동시에 도착하면 도둑의 패배

//즉 이 문제는 도둑과 경찰의 최소를 겨루는 것이 쟁점이다.
{


    int mx[4] = {0, 1, -1, 0};// x 이동 좌표
    int my[4] = {1, 0, 0, -1};// y 이동 좌표
    


    pvisit[px][py] = 1;
    tvisit[tx][ty] = 1;
    for (int i = 1; i <= 4; i++)//재귀 함수 호출
    {
        int ntx, nty;//다음 좌표
        int npx, npy;

        for (int j = 1; j <= 4; j++)
        {
            bfs(px + mx[i - 1], py + my[i - 1], tx + mx[j - 1], ty + my[j - 1], cnt + 1);
        }
    }
    pvisit[px][py] = 0;
    tvisit[tx][ty] = 0;  
    return; 
}

int main()
{
    
    scanf("%d %d", &n, &m);

    int px, py, tx, ty;//경찰의 x, y 좌표, 도둑의 x, y 좌표

    
    for (int i = 1; i <= n; i++)//초기 위치 정보를 입력받는다.
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

    bfs(px, py, tx, ty, 0);//도둑이 집에 도착할 수 있는지 확인한다.
    printf("\n%d %d", ptmin_move, tmin_move);
    if (tmin_move >= ptmin_move)//도둑이 집에 도착할 수 없는 경우이거나 집에 도착할 수 없는 경우
        printf("-1");
    else//도둑이 집에 도착할 수 있는 경우
        printf("%d", tmin_move);
}