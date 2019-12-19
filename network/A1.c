#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 9999
#define MAX 10
void dijkstra(int G[MAX][MAX],int n,int sourcenode);
int main()
{
	int G[MAX][MAX],i,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);

	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra(G,n,u);

	return 0;
}
void dijkstra(int G[MAX][MAX],int n,int sourcenode)
{
	int cost[MAX][MAX],distance[MAX],pred[MAX];          //// dcvp dc vada pav tintane
	int visited[MAX],count,mindistance,nextnode,i,j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)

				cost[i][j]=G[i][j];

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[sourcenode][i];
		pred[i]=sourcenode;
		visited[i]=0;
	}

	//distance[sourcenode]=0;
	visited[sourcenode]=1;
	pred[sourcenode]=sourcenode;
	count=1;

	printf("\nsending hello and echo packets :\n");
	for(i=0;i<n;i++)
	for(j=0;j<n;j++)
	{
		if(cost[i][j]!=0 && cost[i][j]!=INFINITY)
		{printf("\n sending hello packets from %d to %d node",i,j);
		printf("\nsending echo packets from %d to %d node",j,i);}
	}

	while(count<n-1)
	{
		mindistance=INFINITY;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance && visited[i]!=1)
			{
				mindistance=distance[i];
				nextnode=i;
			}
			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
	//print the path and distance of each node
	for(i=0;i<n;i++){


			printf("\n\ndbDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);

			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=sourcenode);

	printf("\n");}
}

/* OUTPUT

shree@dell-Inspiron-5559:~/network$ gcc A1.c
shree@dell-Inspiron-5559:~/network$ ./a.out
Enter no. of vertices:9

Enter the adjacency matrix:
0     4     999   999   999   999   999   8     999
4     0     8     999   999   999   999   11    999
999   8     0     7     999   4     999   999   2
999   999   7     0     9     14    999   999   999
999   999   999   9     0     10    999   999   999
999   999   4     14    10    0     2     999   999
999   999   999   999   999   2     0     1     6
8     11    999   999   999   999   1     0     7
999   999   2     999   999   999   6     7     0

Enter the starting node:0

sending hello packets :

 sending hello packets from 0 to 1 node
 sending hello packets from 0 to 2 node
 sending hello packets from 0 to 3 node
 sending hello packets from 0 to 4 node
 sending hello packets from 0 to 5 node
 sending hello packets from 0 to 6 node
 sending hello packets from 0 to 7 node
 sending hello packets from 0 to 8 node
 sending hello packets from 1 to 0 node
 sending hello packets from 1 to 2 node
 sending hello packets from 1 to 3 node
 sending hello packets from 1 to 4 node
 sending hello packets from 1 to 5 node
 sending hello packets from 1 to 6 node
 sending hello packets from 1 to 7 node
 sending hello packets from 1 to 8 node
 sending hello packets from 2 to 0 node
 sending hello packets from 2 to 1 node
 sending hello packets from 2 to 3 node
 sending hello packets from 2 to 4 node
 sending hello packets from 2 to 5 node
 sending hello packets from 2 to 6 node
 sending hello packets from 2 to 7 node
 sending hello packets from 2 to 8 node
 sending hello packets from 3 to 0 node
 sending hello packets from 3 to 1 node
 sending hello packets from 3 to 2 node
 sending hello packets from 3 to 4 node
 sending hello packets from 3 to 5 node
 sending hello packets from 3 to 6 node
 sending hello packets from 3 to 7 node
 sending hello packets from 3 to 8 node
 sending hello packets from 4 to 0 node
 sending hello packets from 4 to 1 node
 sending hello packets from 4 to 2 node
 sending hello packets from 4 to 3 node
 sending hello packets from 4 to 5 node
 sending hello packets from 4 to 6 node
 sending hello packets from 4 to 7 node
 sending hello packets from 4 to 8 node
 sending hello packets from 5 to 0 node
 sending hello packets from 5 to 1 node
 sending hello packets from 5 to 2 node
 sending hello packets from 5 to 3 node
 sending hello packets from 5 to 4 node
 sending hello packets from 5 to 6 node
 sending hello packets from 5 to 7 node
 sending hello packets from 5 to 8 node
 sending hello packets from 6 to 0 node
 sending hello packets from 6 to 1 node
 sending hello packets from 6 to 2 node
 sending hello packets from 6 to 3 node
 sending hello packets from 6 to 4 node
 sending hello packets from 6 to 5 node
 sending hello packets from 6 to 7 node
 sending hello packets from 6 to 8 node
 sending hello packets from 7 to 0 node
 sending hello packets from 7 to 1 node
 sending hello packets from 7 to 2 node
 sending hello packets from 7 to 3 node
 sending hello packets from 7 to 4 node
 sending hello packets from 7 to 5 node
 sending hello packets from 7 to 6 node
 sending hello packets from 7 to 8 node
 sending hello packets from 8 to 0 node
 sending hello packets from 8 to 1 node
 sending hello packets from 8 to 2 node
 sending hello packets from 8 to 3 node
 sending hello packets from 8 to 4 node
 sending hello packets from 8 to 5 node
 sending hello packets from 8 to 6 node
 sending hello packets from 8 to 7 node

sending echo packets :

sending echo packets from 1 to 0 node
sending echo packets from 2 to 0 node
sending echo packets from 3 to 0 node
sending echo packets from 4 to 0 node
sending echo packets from 5 to 0 node
sending echo packets from 6 to 0 node
sending echo packets from 7 to 0 node
sending echo packets from 8 to 0 node
sending echo packets from 0 to 1 node
sending echo packets from 2 to 1 node
sending echo packets from 3 to 1 node
sending echo packets from 4 to 1 node
sending echo packets from 5 to 1 node
sending echo packets from 6 to 1 node
sending echo packets from 7 to 1 node
sending echo packets from 8 to 1 node
sending echo packets from 0 to 2 node
sending echo packets from 1 to 2 node
sending echo packets from 3 to 2 node
sending echo packets from 4 to 2 node
sending echo packets from 5 to 2 node
sending echo packets from 6 to 2 node
sending echo packets from 7 to 2 node
sending echo packets from 8 to 2 node
sending echo packets from 0 to 3 node
sending echo packets from 1 to 3 node
sending echo packets from 2 to 3 node
sending echo packets from 4 to 3 node
sending echo packets from 5 to 3 node
sending echo packets from 6 to 3 node
sending echo packets from 7 to 3 node
sending echo packets from 8 to 3 node
sending echo packets from 0 to 4 node
sending echo packets from 1 to 4 node
sending echo packets from 2 to 4 node
sending echo packets from 3 to 4 node
sending echo packets from 5 to 4 node
sending echo packets from 6 to 4 node
sending echo packets from 7 to 4 node
sending echo packets from 8 to 4 node
sending echo packets from 0 to 5 node
sending echo packets from 1 to 5 node
sending echo packets from 2 to 5 node
sending echo packets from 3 to 5 node
sending echo packets from 4 to 5 node
sending echo packets from 6 to 5 node
sending echo packets from 7 to 5 node
sending echo packets from 8 to 5 node
sending echo packets from 0 to 6 node
sending echo packets from 1 to 6 node
sending echo packets from 2 to 6 node
sending echo packets from 3 to 6 node
sending echo packets from 4 to 6 node
sending echo packets from 5 to 6 node
sending echo packets from 7 to 6 node
sending echo packets from 8 to 6 node
sending echo packets from 0 to 7 node
sending echo packets from 1 to 7 node
sending echo packets from 2 to 7 node
sending echo packets from 3 to 7 node
sending echo packets from 4 to 7 node
sending echo packets from 5 to 7 node
sending echo packets from 6 to 7 node
sending echo packets from 8 to 7 node
sending echo packets from 0 to 8 node
sending echo packets from 1 to 8 node
sending echo packets from 2 to 8 node
sending echo packets from 3 to 8 node
sending echo packets from 4 to 8 node
sending echo packets from 5 to 8 node
sending echo packets from 6 to 8 node
sending echo packets from 7 to 8 node

Distance of node1=4
Path=1<-0

Distance of node2=12
Path=2<-1<-0

Distance of node3=19
Path=3<-2<-1<-0

Distance of node4=21
Path=4<-5<-6<-7<-0

Distance of node5=11
Path=5<-6<-7<-0

Distance of node6=9
Path=6<-7<-0

Distance of node7=8
Path=7<-0

Distance of node8=14
Path=8<-2<-1<-0
shree@dell-Inspiron-5559:~/network$  */

