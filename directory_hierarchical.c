#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct file
{
	char filename[100];
	struct directory *parent;
	struct file *link;
};

struct directory 
{
	char dirname[100];
	struct directory *nextdir;
	struct directory *subdir;
	struct directory *parentdir;
	struct file *files;
};

void pwd(struct directory **);
void insert_dir(struct directory **);
void insert_file(struct directory **);
void search_file(struct directory **, char []);
struct directory *search_dir(struct directory **, char []);
void display_dir(struct directory **);
void display_files(struct directory **);
void delete_dir(struct directory **, char []);
void delete_file(struct directory **, char []);

int main ()
{
	char maindirname[100];
	printf("Enter the name of the root directory\n");
	scanf("%s", maindirname);
	struct directory *p, *temp, *newdir;
	p = (struct directory *)malloc(sizeof(struct directory *));
	strcpy(p->dirname, maindirname);
	p->parentdir = NULL;
	p->subdir = NULL;
	p->nextdir = NULL;
	p->files = NULL;
	temp = p;
	char dirname[100], filename[100];
	printf("Present working directory presently set to the root directory\n");
	int choice;
	while (1)
	{
		printf("\n---------------------------------------------------------------------\n");
		printf("Enter 1 to display the current directory\n");
		printf("Enter 2 to change  into sub-directory\n");
		printf("Enter 3 to go the parent directory of the present directory\n");
		printf("Enter 4 to display all the files in the present directory\n");
		printf("Enter 5 to display all the subdirectories of the present directory\n");
		printf("Enter 6 to search for a directory\n");
		printf("Enter 7 to search for a file in the present directory\n");
		printf("Enter 8 to insert a file into the present directory\n");
		printf("Enter 9 to insert a sub-directory into the directory\n");
		printf("Enter 10 to delete a sub-directory\n");
		printf("Enter 11 to delete a file\n");
		printf("Enter 12 to exit\n");
		printf("Make your choice\n");
		scanf("%d", &choice);
		printf("------------------------------------------------------------------------\n\n");
		switch(choice)
		{
			case 1:
				pwd(&temp);
				break;
			case 2:
				printf("Enter the name of the directory\n");
				scanf("%s", dirname);
				newdir = search_dir(&temp, dirname);
				if (newdir == NULL)
				{
					printf("No directory found\n");
					break;
				}
				temp = newdir;
				printf("Directory changed\n");
				break;
			case 3:
				if (temp->parentdir == NULL)
				{
					printf("The current directory is the present directory\n");
					break;
				}
				temp = temp->parentdir;
				break;
			case 4:
				display_files(&temp);
				break;
			case 5:
				display_dir(&temp);
				break;
			case 6:
				printf("Enter the name of the directory to be searched for in the present directory\n");
				scanf("%s", dirname);
				newdir = search_dir(&temp, dirname);
				break;
			case 7:
				printf("Enter the name of the file to be searched for in the present directory\n");
				scanf("%s", filename);
				search_file(&temp, filename);
				break;
			case 8:
				insert_file(&temp);
				break;
			case 9:
				insert_dir(&temp);
				break;
			case 10:
				printf("Enter the name of the directory to be deleted\n");
				scanf("%s", dirname);
				delete_dir(&temp, dirname);
				break;
			case 11:
				printf("Enter the name of the file to be deleted\n");
				scanf("%s", filename);
				delete_file(&temp, filename);
				break;
			case 12:
				return 0;
			default:
				printf("Enter a valid choice\n");
		}
	}
	return 0;
}

void display_dir(struct directory **p)
{
	struct directory *temp;
	temp = (*p)->subdir;
	if (temp == NULL)
	{
		printf("No subdiectories in the directory\n");
		return;
	}
	printf("The subdirectories of the directory are -->\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->dirname);
		temp = temp->nextdir;
	}
	return;
}

void display_files(struct directory **p)
{
	struct file *temp;
	temp = (*p)->files;
	if (temp == NULL)
	{
		printf("No files present in the directory\n");
		return;
	}
	printf("The files present in the directory are -->\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->filename);
		temp = temp->link;
	}
	return;
}

struct directory *search_dir(struct directory **p, char a[])
{
	struct directory *temp;
	temp = (*p)->subdir;
	if (temp == NULL)
	{
		printf("No directories present in the directory\n");
		return NULL;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->dirname, a) == 0)
		{
			printf("Directory %s found\n", a);
			return temp;
		}
		temp = temp->nextdir;
	}
	printf("Directory named %s not found\n", a);
	return NULL;
}

void search_file(struct directory **p, char a[])
{
	struct file *temp;
	temp = (*p)->files;
	if (temp == NULL)
	{
		printf("No files present in the directory\n");
		return;
	}
	while (temp != NULL)
	{
		if (strcmp(temp->filename, a) == 0)
		{
			printf("File %s found\n", a);
			return;
		}
		temp = temp->link;
	}
	printf("File not found\n");
	return;
}

void pwd(struct directory **q)
{
	struct directory *temp;
	printf("Current Directory\n");
	temp = (*q)->parentdir;
	printf("%s -->", (*q)->dirname);
	while (temp != NULL)
	{
		printf("%s -->", temp->dirname);
		temp = temp->parentdir;
	}
	return;
}

void insert_dir(struct directory **p)
{
	struct directory *temp, *new_dir;
	new_dir = (struct directory *)malloc(sizeof(struct directory));
	char dname[100];
	printf("Enter the name of the new directory\n");
	scanf("%s", dname);
	temp = (*p)->subdir;
	strcpy(new_dir->dirname, dname);
	new_dir->parentdir = (*p);
	new_dir->nextdir = NULL;
	new_dir->subdir = NULL;
	new_dir->files = NULL;
	if (temp == NULL)
	{
		(*p)->subdir = new_dir;
		printf("New directory inserted\n");
		return;
	}
	while (temp->nextdir != NULL)
	{
		temp = temp->nextdir;
	}
	temp->nextdir = new_dir;
	printf("New Directory inserted\n");
	return;
}

void insert_file(struct directory **p)
{
	struct file *temp, *newfile;
	newfile = (struct file *)malloc(sizeof(struct file *));
	char fname[100];
	printf("Please enter the name of the new file\n");
	scanf("%s", fname);
	strcpy(newfile->filename, fname);
	newfile->link = NULL;
	newfile->parent = (*p);
	temp = (*p)->files;
	if (temp == NULL)
	{
		(*p)->files = newfile;
		printf("New file created\n");
		return;
	}
	while (temp->link != NULL)
	{
		temp = temp->link;
	}
	temp->link = newfile;
	printf("New file created\n");
	return;
}

void delete_dir(struct directory **p, char a[])
{
	struct directory *temp, *z;
	temp = (*p)->subdir;
	z = temp;
	if (temp == NULL)
	{
		printf("Empty directory\n");
		return;
	}
	if (strcmp(temp->dirname, a) == 0)
	{
		(*p)->subdir = temp->nextdir;
		free(temp);
		printf("Directory deleted\n");
		return;
	}
	temp = temp->nextdir;
	while (temp != NULL)
	{
		if (strcmp(temp->dirname, a) == 0)
		{
			z->nextdir = temp->nextdir;
			free(temp);
			printf("Directory deleted\n");
			return;
		}
		z = temp;
		temp = temp->nextdir;
	}
	printf("No directory found\n");
	return;
}

void delete_file(struct directory **p, char a[])
{
	struct file *temp, *z;
	temp = (*p)->files;
	z = temp;
	if (temp == NULL)
	{
		printf("Empty directory\n");
		return;
	}
	if (strcmp(temp->filename, a) == 0)
	{
		(*p)->files = temp->link;
		free(temp);
		printf("Directory deleted\n");
		return;
	}
	temp = temp->link;
	while (temp != NULL)
	{
		if (strcmp(temp->filename, a) == 0)
		{
			z->link = temp->link;
			free(temp);
			printf("Directory deleted\n");
			return;
		}
		z = temp;
		temp = temp->link;
	}
	printf("No directory found\n");
	return;
}