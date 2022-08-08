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

본 코드에서 경찰을 정수로 표현하면 1이다.
본 코드에서 도둑을` 정수로 표현하면 -1이다.
*/

int n, m;
char arr[10000][10000];//배열 

int visited[10000][10000];//방문했는지 체크

int hx,hy;//집의 위치

int cnt_que[10000]={-1},px_que[10000]={-1},py_que[10000]={-1},tx_que[10000]={-1},ty_que[10000] = {-1};//값들의 큐
int qi = 0, qj = 1; //qi:빼내야할 값이 있는 번호, qj: 값을 넣어야하는 위치

void que_output(int *cnt, int *px, int *py, int *tx, int *ty)
{
    /*
        큐에서 값을 빼내어 변수에 대입 시켜줌
    */
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

    if (cnt_que[qj] == -1)
    {
        printf("x\n");
        return;
    }//큐가 가득 찼을 경우 오류(Only for debug)
    
    cnt_que[qj] = cnt;
    px_que[qj] = px;
    py_que[qj] = py;
    tx_que[qj] = tx;
    ty_que[qj] = ty;
    qj = (qj + 1) % 10000;
}

int objchecking(int x, int y)
{
    /*
        검사항목
        1. 좌표의 유효성
        2. 방문의 유효성
        3. 장애물의 유효성
        4. 다른 객체와의 충돌 유효성(얘는 for에서 하는 걸로)
    */
    if (x < 0 || x > n-1 || y < 0 || y > m-1)
        return 0;
    if (visited[x][y] == 1)
        return 0;
    if (arr[x][y] == '#')
        return 0;
    return 1;
    
}

int nodechecking(int px, int py, int tx, int ty)
{
    
}

int BFS(int cnt, int px, int py, int tx, int ty)
{
    int mx[4] = {-1,1,0,0};
    int my[4] = {0,0,-1,1};//이동 좌표(상하좌우)

    int ppl[5] = {0};//경찰의 이동 가능 좌표(상하좌우)
    int ptl[5] = {0};//도둑의 이동 가능 좌표(상하좌우)
    for (int i = 0 ; i < 4; i++)
    {
        int pc = checking(px + mx[i], py + my[i]);
        int tc = checking(tx + mx[i], ty + my[i]);
        ppl[i] = pc, ppl[4] += pc;
        ptl[i] = tc, ptl[4] += tc;//이동 가능한 곳이 하나라도 있는가
    }  

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (ppl[4] && ptl[4] == 0)//경찰이 이동 가능하고 도둑은 불가능할 때
            {
                if (ppl[i])//경찰이 이동가능한 경우
                {
                    que_input(cnt, px + mx[i], py + my[i], tx, ty);
                    visited[px + mx[i]][py + my[i]] = 1;
                }
            }
            else if (ppl[4] == 0 && ptl[4])//경찰이 이동이 불가능하고 도둑은 가능할 때
            {
                if (ptl[i])//도둑이 이동가능한 경우
                {
                    que_input(cnt, px, py, tx + mx[i], ty + my[i]);
                    visited[tx + mx[i]][ty + my[i]] = 1;
                }
            }
            else if (ppl[4] && ptl[4])//둘 다 이동 가능한 경우가 있을 때
            {
                if (ppl[i] && ptl[i])//둘 다 이동 가능할 때
                {
                    que_input(cnt, px + mx[i], py + my[i], tx + mx[i], ty + my[i]);
                    visited[px + mx[i]][py + my[i]] = 1;
                    visited[tx + mx[i]][ty + my[i]] = 1;
                }
            }
            else continue;
        }
    }
    


    int ncnt = 0, npx = 0, npy = 0, ntx = 0, nty = 0;//다음 값들
    que_output(&ncnt, &npx, &npy, &ntx, &nty);//값 대입
    if (ncnt == -1) return -1;//다음에 실행할 값이 없을 경우 종료
    else return BFS(ncnt, npx, npy, ntx, nty);//다음 값들을 넣어준다.
}

int main()
{
    int px,py;//경찰의 x,y;
    int tx,ty;//도둑의 X,y;

    for (int i = 0; i < 10000; i++)
    {
        cnt_que[i] = -1, px_que[i] = -1, py_que[i] = -1, tx_que[i] = -1, ty_que[i] = -1;
    }

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
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
    if (val == -1)
    {
        printf("-1");
    }
    else
    {
        printf("%d",val);
    }
    return 0;
}