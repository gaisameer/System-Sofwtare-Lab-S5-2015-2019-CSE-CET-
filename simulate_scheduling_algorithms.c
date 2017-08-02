#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct process
{
	int pid;
	float burst_time;
	float execution_time;
	float waiting_time;
	int priority;
	float remaining_time;
	float considered_priority;
	struct process *link;
};

void append_process(struct process **, int, float, int);
void display_processes(struct process **);
void reset_process(struct process **);
void add_processes(struct process **);
void get_choice_and_execute(struct process **);
void simulate_fcfs(struct process **);
void simulate_sjf(struct process **);
void simulate_priority(struct process **);
void simulate_round_robin(struct process **, float);
void display_waiting_turnaround_time(struct process **);

int main ()
{
	struct process *main;
	main = NULL;
	printf("Please enter the number of processes to be inserted into the ready queue\n");
	int n;
	int i;
	scanf ("%d", &n);
	for (i=0; i<n; i++)
	{
		add_processes(&main);
	}

	display_processes(&main);
	
	get_choice_and_execute(&main);
	
	return 0;
}

void get_choice_and_execute(struct process **p)
{
	float quantum;
	int choice;
	while(1)
	{
		printf("--------------------------------------------------\n");
		printf("Enter 1 to append a process to the ready queue\n");
		printf("Enter 2 to simulate FCFS scheduling algorithm\n");
		printf("Enter 3 to simulate Shortest Job First (SJF) Algorithm\n");
		printf("Enter 4 to simulate Round Robin Algorithm\n");
		printf("Enter 5 to simulate Priority scheduling algorithm\n");
		printf("Enter 6 to exit\n");
		printf("Make your choice\n");
		printf("--------------------------------------------------\n");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1:
				add_processes(&(*p));
				break;
			case 2:
				simulate_fcfs(&(*p));
				display_waiting_turnaround_time(&(*p));
				reset_process(&(*p));
				break;
			case 3:
				simulate_sjf(&(*p));
				display_waiting_turnaround_time(&(*p));
				reset_process(&(*p));
				break;
			case 4:
				printf("Enter the time slice\n");
				scanf("%f", &quantum);
				simulate_round_robin(&(*p), quantum);
				display_waiting_turnaround_time(&(*p));
				reset_process(&(*p));
				break;
			case 5:
				simulate_priority(&(*p));
				display_waiting_turnaround_time(&(*p));
				reset_process(&(*p));
				break;
			case 6:
				exit(0);
			default:
				printf("Please make a valid choice\n");
				break;
		}
	}
}

void simulate_fcfs(struct process **p)
{
	struct process *temp;
	temp = (*p);
	float net = 0;
	if (temp == NULL)
	{
		return;
	}
	do
	{
		temp->waiting_time = net;
		net = net + temp->burst_time;
		temp = temp->link;
	}while (temp != (*p));
}

void simulate_sjf(struct process **p)
{
	if ((*p) == NULL)
		return;
	struct process *temp;
	struct process *newnode;
	float total_time = 0;
	while (1)
	{
		temp = NULL;
		newnode = (*p);
		do
		{
			if (temp == NULL)
			{
				if (newnode->remaining_time != 0)
					temp = newnode;
			}
			else if (temp->burst_time > newnode->burst_time)
			{
				if (newnode->remaining_time != 0)
					temp = newnode;
			}
			newnode = newnode->link;
		}while (newnode != (*p));
		if (temp == NULL)
			return;
		else
		{
			temp->remaining_time = 0;
			temp->waiting_time = total_time;
			total_time = total_time + temp->burst_time;
		}
	}
	return;
}

void simulate_priority(struct process **p)
{
	if ((*p) == NULL)
		return;
	struct process *temp;
	struct process *newnode;
	float total_time = 0;
	while (1)
	{
		temp = NULL;
		newnode = (*p);
		do
		{
			if (temp == NULL)
			{
				if (newnode->remaining_time != 0)
					temp = newnode;
			}
			else if (temp->priority > newnode->priority)
			{
				if (newnode->remaining_time != 0)
					temp = newnode;
			}
			newnode = newnode->link;
		}while (newnode != (*p));
		if (temp == NULL)
			return;
		else
		{
			temp->remaining_time = 0;
			temp->waiting_time = total_time;
			total_time = total_time + temp->burst_time;
		}
	}
	return;
}

void simulate_round_robin(struct process **p, float q)
{
	struct process *temp;
	struct process *newnode;
	int t;
	float total_time = 0;
	int z = 1;
	while (z == 1)
	{
		t = 0;
		temp = (*p);
		do
		{
			if (temp->remaining_time == 0)
			{
					temp = temp->link;
					continue;
			}
			if (temp->remaining_time > q)
			{
				t = 1;
				temp->remaining_time = temp->remaining_time - q;
				total_time += q;
			}
			else if (temp->remaining_time <= q && temp->remaining_time != 0)
			{
				t = 1;
				total_time = total_time + temp->remaining_time;
				temp->remaining_time = 0;
				temp->waiting_time = total_time;
			}
			temp = temp->link;
		}while (temp != (*p));
		if (t == 0)	
		{
			break;
		}
	}
	temp = (*p);
	do
	{
		temp->waiting_time = temp->waiting_time - temp->burst_time;
		temp = temp->link;
	}while(temp != (*p));
	return;
}

void add_processes(struct process **p)
{
	int proc_id;
	float burst_t;
	int prior;
	printf("Please enter the pid of the new process\n");
	scanf("%d", &proc_id);
	printf("Please enter the CPU burst time of the process\n");
	scanf("%f", &burst_t);
	printf("Please enter the priority of the process with PID --> %d\n", proc_id);
	scanf("%d", &prior);
	append_process(&(*p), proc_id, burst_t, prior);
	printf("\n");
	return;
}

void append_process(struct process **p, int p_id, float burst_t, int prior)
{
	struct process *temp;
	temp = (*p);
	struct process *new_node;
	new_node = (struct process *)malloc(sizeof(struct process));
	new_node->pid = p_id;
	new_node->burst_time = burst_t;
	new_node->priority = prior;
	new_node->waiting_time = 0;
	new_node->remaining_time = burst_t;
	if (temp == NULL)
	{
		(*p) = new_node;
		(*p)->link = (*p);
	}
	else
	{
		while (temp->link != (*p))
		{
			temp = temp->link;
		}
		temp->link = new_node;
		new_node->link = (*p);
	}
}

void display_processes(struct process **p)
{
	struct process *t;
	t = (*p);
	int i = 1;
	if (t == NULL)
	{
		printf("EMPTY READY QUEUE\n");
		return;
	}
	do
	{
		printf("Process id of the %dth process in the ready queue is %d\n", i, t->pid);
		t = t->link;
		i++;
	}while (t != (*p));
}

void reset_process(struct process **p)
{
	struct process *t;
	t = (*p);
	if (t == NULL)
	{
		return;
	}
	do
	{
		t->execution_time = 0;
		t->waiting_time = 0;
		t->remaining_time = t->burst_time;
		t = t->link;
	}while (t != (*p));
}

void display_waiting_turnaround_time(struct process **p)
{
	struct process *temp;
	temp = (*p);
	if (temp == NULL)
	{
		printf("EMPTY READY QUEUE\n");
		return;
	}
	do
	{
		printf("Process pid --> %d : Waiting time --> %f / Turnaround time --> %f\n", temp->pid, temp->waiting_time, temp->burst_time + temp->waiting_time);
		temp = temp->link;
	}while (temp != (*p));
}