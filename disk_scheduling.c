#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int n;
struct record
{
	int pos;
	struct record *right;
	struct record *left;
};

void append(struct record **, int);
void display(struct record **);
void clear_queue(struct record **);
void fcfs(struct record **);
void scan(struct record **);
void cscan(struct record **);

int main ()
{
	struct record *p;
	p = (struct record *)malloc(sizeof(struct record));
	p->pos = 0;
	p->right = NULL;
	p->left = NULL;
	int choice, x, y, z;
	printf("Enter the total number of tracks on the disk\n");
	scanf("%d", &n);
	while (1)
	{
		printf("\n---------------------------------------------------------\n");
		printf("Enter 1 to append a address position to be serviced\n");
		printf("Enter 2 to clear the disk service request positions\n");
		printf("Enter 3 to simulate FCFS Scheduling algorithm\n");
		printf("Enter 4 to simulate SCAN scheduling algorithm\n");
		printf("Enter 5 to simulate C-SCAN scheduling algorithm\n");
		printf("Enter 6 to display the request queue\n");
		printf("Enter 7 to exit\n");
		printf("Make your choice\n");
		scanf("%d", &choice);
		printf("---------------------------------------------------------\n\n");
		switch(choice)
		{
			case 1:
				while (1)
				{
					printf("Enter the track no to be appended to the request queue\n");
					scanf("%d", &x);
					if (x<0 || x>=n)
						printf("Please enter a valid track number\n");
					else
						break;
				}
				append(&p, x);
				break;
			case 2:
				clear_queue(&p);
				break;
			case 3:
				fcfs(&p);
				break;
			case 4:
				scan(&p);
				break;
			case 5:
				cscan(&p);
				break;
			case 6:
				display(&p);
				break;
			case 7:
				return 0;
			default:
				printf("Please enter a valid choice\n");
		}
	}
}

void append(struct record **a, int track)
{
	struct record *temp, *new;
	temp = (*a)->right;
	new = (struct record *)malloc(sizeof(struct record));
	new->pos = track;
	new->right = NULL;
	if (temp == NULL)
	{
		new->left = (*a);
		(*a)->right = new;
		printf("New Request Inserted\n");
		return;
	}
	while (temp->right != NULL)
	{
		temp = temp->right;
	}
	temp->right = new;
	new->left = temp;
	printf("New Request Inserted\n");
	return;
}

void display(struct record **a)
{
	struct record *temp;
	temp = (*a)->right;
	if (temp == NULL)
	{
		printf("Empty request queue\n");
		return;
	}
	printf("Printing the track numbers in the track queue\n");
	while (temp != NULL)
	{
		printf("Track No:- %d\n", temp->pos);
		temp = temp->right;
	}
	return;
}

void clear_queue(struct record **a)
{
	struct record *temp, *q;
	temp = (*a)->right;
	(*a)->right = NULL;
	while (temp != NULL)
	{
		q = temp;
		temp = temp->right;
		free(q);
	}
	printf("Cleared the contents of the ready queue\n");
	return;
}

void fcfs(struct record **a)
{
	struct record *temp;
	temp = (*a)->right;
	int start;
	int dist_travelled = 0;
	if (temp == NULL)
	{
		printf("Empty request queue\n");
		return;
	}
	while (1)
	{
		printf("Enter the disk head starting track\n");
		scanf("%d", &start);
		if (start < 0 || start >= n)
			printf("Please Enter valid disk head starting track\n");
		else
			break;
	}
	while (temp != NULL)
	{
		printf("Serviced Track No:- %d\n", temp->pos);
		printf("Distance traversed by disk head :- %d\n\n", dist_travelled + abs(start - temp->pos));
		dist_travelled += abs(start - temp->pos);
		start = temp->pos;
		temp = temp->right;
	}
	printf("FCFS Scheduling algorithm simulation completed\n");
	return;
}

void scan(struct record **a)
{
	struct record *temp;
	temp = (*a)->right;
	int p = 0;
	int i = 0;
	if (temp == NULL)
	{
		printf("Empty ready queue\n");
		return;
	}
	while (temp != NULL)
	{
		p++;
		temp = temp->right;
	}
	int l[p];
	temp = (*a)->right;
	while (temp != NULL)
	{
		l[i++] =temp->pos;
		temp = temp->right;
	}
	int j, k;
	for(i=0; i<p-1; i++)
	{
		for(j=i+1; j<p; j++)
		{
			if (l[i] > l[j])
			{
				k = l[i];
				l[i] = l[j];
				l[j] = k;
			}
		}
	}
	int start;
	while (1)
	{
		printf("Enter the starting track of the disk head\n");
		scanf("%d", &start);
		if (start < 0 || start >= n)
			printf("Please enter a valid disk head starting track\n");
		else
			break; 
	}
	int side = 0;
	if (n%2 == 0)
	{
		if (start >= n/2)
			side = 1;
	}
	else
	{
		if (start > n/2)
			side = 1;
	}
	int dist_travelled = 0, q;
	if (side == 0)
	{
		for(i=0; i<p; i++)
		{
			if (l[i] > start)
				break;
		}
		i--;
		j = i;
		for(q=i; q>=0; q--)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		if (j < p-1)
		{
			dist_travelled += (start);
			start = 0; 
		}
		for(q=j+1; q<p; q++)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		printf("SCAN Scheduling Algorithm simualtion completed\n");
		return;
	}
	else
	{
		for(i=0; i<p; i++)
		{
			if (l[i] >= start)
				break;
		}
		j = i;
		for(q=j; q<p; q++)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		if (j > 0)
		{
			dist_travelled += abs(n - 1 - start);
			start = n-1;
		}
		for(q=j-1; q>=0; q--)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		printf("SCAN Scheduling Algorithm simulation completed\n");
		return;
	}
}

void cscan(struct record **a)
{
	struct record *temp;
	temp = (*a)->right;
	int p = 0;
	int i = 0;
	if (temp == NULL)
	{
		printf("Empty ready queue\n");
		return;
	}
	while (temp != NULL)
	{
		p++;
		temp = temp->right;
	}
	int l[p];
	temp = (*a)->right;
	while (temp != NULL)
	{
		l[i++] =temp->pos;
		temp = temp->right;
	}
	int j, k;
	for(i=0; i<p-1; i++)
	{
		for(j=i+1; j<p; j++)
		{
			if (l[i] > l[j])
			{
				k = l[i];
				l[i] = l[j];
				l[j] = k;
			}
		}
	}
	int start;
	while (1)
	{
		printf("Enter the starting track of the disk head\n");
		scanf("%d", &start);
		if (start < 0 || start >= n)
			printf("Please enter a valid disk head starting track\n");
		else
			break; 
	}
	int side = 0;
	if (n%2 == 0)
	{
		if (start >= n/2)
			side = 1;
	}
	else
	{
		if (start > n/2)
			side = 1;
	}
	int dist_travelled = 0, q;
	if (side == 0)
	{
		for(i=0; i<p; i++)
		{
			if (l[i] > start)
				break;
		}
		i--;
		j = i;
		for(q=i; q>=0; q--)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		if (j < p-1)
		{
			dist_travelled += (start) + (n);
			start = n - 1; 
		}
		for(q=p-1; q>j; q--)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		printf("C-SCAN Scheduling Algorithm simualtion completed\n");
		return;
	}
	else
	{
		for(i=0; i<p; i++)
		{
			if (l[i] >= start)
				break;
		}
		j = i;
		for(q=j; q<p; q++)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		if (j > 0)
		{
			dist_travelled += abs(n - 1 - start) + (n);
			start = 0;
		}
		for(q=0; q<i; q++)
		{
			printf("Serviced Track No:- %d\n", l[q]);
			printf("Distance Travelled by Disk Head:- %d\n\n", dist_travelled + abs(start - l[q]));
			dist_travelled += abs(start - l[q]);
			start = l[q];
		}
		printf("C-SCAN Scheduling Algorithm simulation completed\n");
		return;
	}
}