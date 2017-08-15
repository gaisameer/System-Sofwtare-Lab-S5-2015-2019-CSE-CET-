#include<stdio.h>
#include<string.h>
#include<math.h>

int n, m;

void generate_need(int max[n][m], int allocation[n][m], int need[n][m]);
int check_state(int max[n][m], int allocate[n][m], int need[n][m], int available[]);
int check_need_state(int need[], int work[]);
void update_work(int work[], int allocate[]);
void allocate_resources(int request[n][m], int need[n][m], int available[], int allocate[n][m], int max[n][m], int i);


int main ()
{
	printf("Enter number of processes\n");
	scanf("%d", &n);
	printf("Enter number of resources\n");
	scanf("%d", &m);
	int i, j;
	int max[n][m], allocation[n][m], need[n][m], available[m], request[n][m];
	int x, y, z;
	int pr, w;
	for(i=0; i<m; i++)
	{
		printf("Enter available units of Resource %d\n", i+1);
		scanf("%d", &available[i]);
	}
	for(i=0; i<n; i++)
	{
		printf("\n");
		printf("-------------------------------------------------\n");
		printf("Enter maximum requirements of Process %d\n-------------------------------------------------\n", i+1);
		for(j=0; j<m; j++)
		{
			printf("Enter maximum need of Resource %d\n", j+1);
			scanf("%d", &max[i][j]);
		}
		printf("-------------------------------------------------\n");
		printf("Enter allocation details of Process %d\n-------------------------------------------------\n", i+1);
		for(j=0; j<m; j++)
		{
			printf("Enter allocation details of Resource %d\n", j+1);
			scanf("%d", &allocation[i][j]);
		}
		printf("-------------------------------------------------\n");
		printf("Enter resources required for Process %d\n-------------------------------------------------\n", i+1);
		for(j=0; j<m; j++)
		{
			printf("Enter resource required details of Resource%d\n", j+1);
			scanf("%d", &request[i][j]);
		}
		printf("\n");
	}

	generate_need(max, allocation, need);

	while (1)
	{
		printf("\n--------------------------------------------------------------------\n");
		printf("1 to check for the state of the system using Banker's algorithm\n");
		printf("2 to proceed with an existing resource allocation from a process\n");
		printf("3 to initiate a new resource allocation request from a process\n");
		printf("4 to EXIT\n");
		printf("Make your choice\n");
		scanf("%d", &x);
		printf("--------------------------------------------------------------------\n\n");
		switch(x)
		{
			case 1:
				pr = check_state(max, allocation, need, available);
				if (pr == 1)
				{
					printf(" \n-------------Safe State-------------\n");
				}
				else
				{
					printf("\n-------------Deadlock may occur-------------\n");
				}
				break;
			case 2:
				printf("Enter the Process number for which the resources are to be allocated\n");
				scanf("%d", &y);
				pr = 0;
				for(z=0; z<m; z++)
				{
					if (request[y-1][z] != 0)
					{
						pr = 1;
						break;
					}
				}
				if (pr == 0)
				{
					printf("No resource allocation request from the process\n");
					break;
				}
				else
				{
					allocate_resources(request, need, available, allocation, max, y);
					break;
				}
			case 3:
				printf("Enter the Process number which is making the resource allocation request\n");
				scanf("%d", &y);
				pr = 0;
				for(z=0; z<m; z++)
				{
					printf("Enter amount of Resource %d requested by Process %d\n", z+1, y);
					scanf("%d", &w);
					if (w != 0)
						pr = 1;
					request[y-1][z] = w;
				}
				if (pr == 0)
				{
					printf("No resource allocation request from the process\n");
					break;
				}
				else
				{
					allocate_resources(request, need, available, allocation, max, y);
					break;
				}
			case 4:
				return 0;
			default:
				printf("Please enter a valid choice\n");
		}
	}
	return 0;
}

void allocate_resources(int request[n][m], int need[n][m], int available[], int allocate[n][m], int max[n][m], int i)
{
	int p=0, j=0;
	i = i - 1;
	for(j=0; j<m; j++)
	{
		if (request[i][j] > need[i][j])
		{
			p = 1;
			break;
		}
	}
	if ( p == 1)
	{
		printf("Invalid resource allocation request from the process\n");
		return;
	}
	for(j=0; j<m; j++)
	{
		if (request[i][j] > available[j])
		{
			p = 1;
			break;
		}
	}
	if (p == 1)
	{
		printf("Process %d will have to wait since the rqeuired amount of resources are not qavailable\n", i+1);
		return;
	}
	for(j=0; j<m; j++)
	{
		available[j] = available[j] - request[i][j];
		allocate[i][j] = allocate[i][j] + request[i][j];
		need[i][j] = need[i][j] - request[i][j];
	}
	p = check_state(max, allocate, need, available);
	if (p == 1)
	{
		printf("Required resources allocated\n");
		return;
	}
	else
	{
		for(j=0; j<m; j++)
		{
			available[j] = available[j] + request[i][j];
			allocate[i][j] = allocate[i][j] - request[i][j];
			need[i][j] = need[i][j] + request[i][j];
			printf("Resources can't be allocate since the system is not in safe state after resource allocation\n");
			return;
		}
	}
}

void generate_need(int max[n][m], int allocation[n][m], int need[n][m])
{
	int i, j;
	for (i=0; i<n; i++)
	{
		for(j=0; j<m; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	return;
}

int check_state(int max[n][m], int allocate[n][m], int need[n][m], int available[m])
{
	int work[m], finish[n];
	int i, j;

	for(i=0; i<n; i++)
	{
		finish[i] = 0;
	}

	for(i=0; i<m; i++)
	{
		work[i] = available[i];
	}

	int p = 0;
	i = 0;

	while (1)
	{
		if (p == n)
			break;

		if (finish[i] == 0 && check_need_state(need[i], work) == 0)
		{
			update_work(work, allocate[i]);
			finish[i] = 1;
			p = 0;
		}
		else
		{
			p++;
			i = (i+1)%n;
		}
	}

	for(i=0; i<n; i++)
	{
		if (finish[i] == 0)
		{
			return 0;
		}
	}

	return 1;
}

int check_need_state(int need[], int work[])
{
	int k=0, i;
	for (i=0; i<m; i++)
	{
		if (need[i] > work[i])
		{
			k = 1;
			break;
		}
	}
	return k;
}

void update_work(int work[], int allocate[])
{
	int i;
	for(i=0; i<m; i++)
	{
		work[i] = work[i] + allocate[i];
	}
	return;
}