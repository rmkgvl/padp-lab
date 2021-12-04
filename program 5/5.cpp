#include <stdio.h>
#include <string.h>
#include <mpi.h>
#define BUFSIZE 32 
char m[5][20]={"\nHello","\nRVCE","\nCSE","\n7th Sem","\nHPC"};
int main(int argc,char **argv)
{
	char mess[32];
	int root=0,tag =0,myRank,numProcs,temp=1;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);
	MPI_Comm_size(MPI_COMM_WORLD,&numProcs);
	if(myRank!=0)
	{
		strcpy(mess,m[myRank-1]);
		MPI_Send(&mess,BUFSIZE,MPI_CHAR,root,tag,MPI_COMM_WORLD);
		}	
	else
	{
		int i=0;
		for(i=1;i<numProcs;i++)
		{
			MPI_Recv(&mess,BUFSIZE,MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
			printf("%s is message from %d",mess,i);
		}
	}
	MPI_Finalize();
	return 0;
}