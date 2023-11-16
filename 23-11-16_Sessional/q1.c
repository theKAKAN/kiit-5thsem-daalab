#include <stdio.h>
#include <stdlib.h>

int stack[100];
int cur = 0;

void push( int element ){
    stack[cur] = element;
    cur++;
}

int pop(){
    if( cur <= 0 )
        return -1;
    cur--;
    return stack[cur];
}

void DFS( int m[][6], int idx, int o[]){
    int c = 0;
    int visited[6] = { 0 };
    visited[idx] = 1;
    push(idx);
    int x = pop();
    while( c < 6 ){
        for( int i = 5; i >= 0; i-- ){
            if( m[x][i] != 0 && visited[i] == 0 )
                push(i);
        }
        o[c] = x;
        c++;
        visited[x] = 1;
        x = pop();
    }
    o[--c] = 3;
}

int main(){
    int m[][6] = {
        {0,1,1,1,0,0},
        {1,0,0,0,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0}
    };
    char e[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    printf("Enter starting index: ");
    int i;
    scanf("%d", &i);

    int o[6];
    DFS(m, i, o);

    printf("DFS Traversal: ");
    for( int i = 0; i < 6; i++ ){
        printf("%c", e[o[i]]);
    }

}