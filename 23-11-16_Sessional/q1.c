#include <stdio.h>
#include <stdlib.h>

int stack89[100];
int cur89 = 0;

void push( int element ){
    stack89[cur89] = element;
    cur89++;
}

int pop(){
    if( cur89 <= 0 )
        return -1;
    cur89--;
    return stack89[cur89];
}

void DFS( int m89[][6], int idx89, int o89[]){
    int c89 = 0;
    int visited89[6] = { 0 };
    visited89[idx89] = 1;
    push(idx89);
    int x89 = pop();
    while( c89 < 6 ){
        for( int i = 5; i >= 0; i-- ){
            if( m89[x89][i] != 0 && visited89[i] == 0 )
                push(i);
        }
        o89[c89] = x89;
        c89++;
        visited89[x89] = 1;
        x89 = pop();
    }
    o89[--c89] = 3;
}

int main(){
    int m89[][6] = {
        {0,1,1,1,0,0},
        {1,0,0,0,1,1},
        {1,0,0,0,0,1},
        {1,0,0,0,0,0},
        {0,1,0,0,0,0},
        {0,1,1,0,0,0}
    };
    char e89[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    printf("Enter starting vertex: ");
    char c89;
    scanf("%c", &c89);

    int i89;
    for( int i = 0; i < 6; i++ ){
        if( c89 == e89[i] )
            i89 = i;
    }

    int o89[6];
    DFS(m89, i89, o89);

    printf("DFS Traversal: ");
    for( int i = 0; i < 6; i++ ){
        printf("%c", e89[o89[i]]);
    }

}