#include <iostream>
using namespace std;
/*ADJACENCY MATRIX*/
int source,X,Y,visited[20],Z[20][20];

void DFS(int p){
    int q;
    visited[p]=1;
    printf(" %d->",p+1);
    for(q=0;q<X;q++){
        if(Z[p][q]==1 && visited[q]==0)
        DFS(q);
    }
}
int main(){
    int p,q,x1,x2;
    printf("\t\t\tGraphs\n");
    printf("Enter the required number of edges:");
    scanf("%d",&Y);
    printf("Enter the required number of vertices:");
    scanf("%d",&X);
    for(p=0;p<X;p++){
        for(q=0;q<X;q++){
            Z[p][q]=0;
        }
    }
    /*creating edges : */
    for(p=0;p<Y;p++){
        printf("Enter the format of the edges (format: x1 x2) : ");
        scanf("%d%d",&x1,&x2);  
        Z[x1-1][x2-1]=1;
    }
    for(p=0;p<X;p++){
        for(q=0;q<X;q++){
            printf(" %d ",Z[p][q]);
        }
        printf("\n");
    }
    printf("Enter the source of the DFS: ");
    scanf("%d",&source);
    DFS(source-1);
    return 0;
}