// failfish.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

//failfish list: circular doubly linked list
struct fish_struct {
	int no;
	struct fish_struct *next;
	struct fish_struct *prev;
};

typedef struct fish_struct failfish;

struct fish_list_struct {
	failfish *head;
	failfish *tail;
};

typedef struct fish_list_struct failfish_queue;

//create a failfish
failfish *create_failfish(int no) {
	failfish *m = (failfish*)malloc(sizeof(failfish));
	m->no = no;
	m->next = NULL;
	m->prev = NULL;
	return m;
}

//free failfish
void dispose_fish(failfish *m) {
	free(m);
}

//print failfish number
void print_fish(failfish *m, FILE* fp_out) {
	fprintf(fp_out, "%d", m->no);
	printf("%d", m->no);
}

//Create failfish queue
failfish_queue *create_failfish_queue() {
	failfish_queue *ml = (failfish_queue*)malloc(sizeof(failfish_queue));

	ml->head = NULL;
	ml->tail = NULL;

	return ml;
}

//free failfish queue
void dispose_fish_list(failfish_queue *ml) {
	free(ml);
}

//free failfish queue and all the nodes
void dispose_fish_list_all(failfish_queue *ml) {

}

//add one failfish into the circular doubly linked list
void fish_list_add(failfish_queue *ml, failfish *m) {

}

/*
  Remove the fish from the list, don't free the memory
*/
void fish_list_remove(failfish_queue *ml, failfish *m) {

}

/* dequeue(): Removes the front item from the queue, and returns it.  
   Returns NULL if the queue is empty. */
failfish* fish_list_dequeue(failfish_queue *ml)
{
	failfish* p = ml->head;

	if ( p == NULL )
	{
		return NULL;
	}

	fish_list_remove(ml, p);
	return p;
}

/* enqueue(): Adds an item to the back of the queue.  The item must already be constructed.
  */
void fish_list_enqueue(failfish_queue *ml, failfish *m)
{
	fish_list_add(ml, m);
}

/* queue_peek(): Like dequeue except it doesn't remove the item from the queue.  
   Returns NULL if the queue is empty. */
failfish* fish_list_peek(failfish_queue *ml)
{
	return ml->head;
}

/* pond node
   All ponds are in one linked list
*/
struct pond_struct {
	char *name;
	int no;
	int fish_count;
	int e;
	int threshold;
	failfish_queue* fishs;
	struct pond_struct *next;
};

typedef struct pond_struct pond_node;

struct pond_list_struct {
	pond_node *head;
};

typedef struct pond_list_struct pond_list;

//Create one pond node
pond_node *new_pond_node(char *name, int no, int n, int e, int threshold)
{
	int i;
	pond_node* p = (pond_node*)malloc(sizeof(pond_node));

	p->fishs = create_failfish_queue();

	//initialize the fish list queue
  //...

	return p;
}

//free one pond and its the fish queues
void dispose_pond_node(pond_node *p)
{
	dispose_fish_list_all(p->fishs);
	free(p->name);
	free(p);
}

//output the information of failfish queue and the pond
void print_failfish_queue(pond_node *m, FILE* fp_out)
{
	failfish* p = m->fishs->head;
	fprintf(fp_out, "%d %s ", m->no, m->name);
	printf("%d %s ", m->no, m->name);
	while ( 1 )
	{
		print_fish(p, fp_out);
		fprintf(fp_out, " ");
		printf(" ");
		if (p == m->fishs->tail)
		{
			break;
		}
		p = p->next;
	}
	fprintf(fp_out, "\n");
	printf("\n");
}

//create the pond list
pond_list *new_pond_list()
{
	pond_list *ml = (pond_list *)malloc(sizeof(pond_list));

	ml->head = NULL;

	return ml;
}

//free the pond list
void dispose_pond_list(pond_list *ml)
{
	free(ml);
}

//free all the ponds and the fish queues
void dispose_pond_list_all(pond_list *ml) {
	pond_node *m = ml->head;
	pond_node *mnext;

	if (m == NULL) {
		dispose_pond_list(ml);
		return;
	}

	do {
		//...
	} while (m != NULL);

	dispose_pond_list(ml);
}

/* insert in a sorted linked list */
void pond_list_add(pond_list *ml, pond_node *m)
{
	pond_node* p = ml->head;

//...

	m->next = p->next;
	p->next = m;
}

//output the status for all the ponds
void output_pond_status(pond_list* ponds, FILE* fp_out)
{
	pond_node* p = ponds->head;
	while ( p!= NULL )
	{
		print_failfish_queue(p, fp_out);
		p = p->next;
	}
}

int main()
{
	FILE* fp_in = NULL;
	FILE* fp_out = NULL;
	int count = 0;
	int remainFishCount = 0; // counter to save how many fish in all the ponds
	int i = 0;
	int n, e, th;
	pond_list* ponds = NULL;
	pond_node* pond = NULL;
	char buf[64] = {0};


	//open the input file
	if ((fp_in = fopen("cop3502-as2-input.txt", "rt")) == NULL)
	{
		printf("Error: unable to read the file: cop3502-as2-input.txt");
		getchar();
		return 0;
	}

	//prepare the output file
	if ((fp_out = fopen("cop3502-as2-output-funfrock-florian.txt", "wb")) == NULL)
	{
		printf("Error: unable to open the output file");
		getchar();
		return 0;
	}

	//read the data from the input file
	ponds = new_pond_list();

	fscanf(fp_in, "%d\n", &count);
	
	for ( i = 0; i < count; i++ )
	{
		int pond_no = 0;
		fscanf(fp_in, "%d %s %d %d %d\n", &pond_no, buf, &n, &e, &th);
		pond_list_add(ponds, new_pond_node(buf, pond_no, n, e, th));
		remainFishCount += n;
	}

	fclose(fp_in);

	fprintf(fp_out, "Initial Pond Status\n");
	printf( "Initial Pond Status\n");
	output_pond_status(ponds, fp_out);

	//First Course
	fprintf(fp_out, "\nFirst Course\n\n");
	printf( "\nFirst Course\n\n");

	pond = ponds->head;
	while (pond)
	{
		//...
		pond = pond->next;
		fprintf(fp_out, "\n");
		printf("\n");
	}

	fprintf(fp_out, "\nEnd of course Pond Status\n");
	printf("\nEnd of course Pond Status\n");
	output_pond_status(ponds, fp_out);

	//Second Course
	fprintf(fp_out, "\nSecond Course\n\n");
	printf("\nSecond Course\n\n");

	do 
	{
//...
	} while (1);

	dispose_pond_list_all(ponds);
	report_mem_leak();
	fclose(fp_out);

	//pause to have the chance to check the result
	getchar(); 
    return 0;
}

