#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
    char data[1023];
    int count;
    struct Node* next;
};

struct Package
{
	struct Node *head;
	char filename[25];
};

// Function to insert a given node in a sorted linked list
void sortedInsert(struct Node**, struct Node*);

void insertionSort(struct Node **head_ref)
{
    // Initialize sorted linked list
    struct Node *sorted = NULL;

    // Traverse the given linked list and insert every
    // node to sorted
    struct Node *current = *head_ref;
    while (current != NULL)
    {
        // Store next for next iteration
        struct Node *next = current->next;

        // insert current in sorted linked list
        sortedInsert(&sorted, current);

        // Update current
        current = next;
    }

    // Update head_ref to point to sorted linked list
    *head_ref = sorted;
}


void sortedInsert(struct Node** head_ref, struct Node* new_node)
{
    struct Node* current;
    if (*head_ref == NULL || strcmp((*head_ref)->data, new_node->data)>0)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next!=NULL &&
               strcmp(current->next->data, new_node->data)<0)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

int traverse(struct Node** head_ref, char newdata[1023]){

    if(*head_ref == NULL){
        return 0;
    }

    struct Node* current = *head_ref;

    do{
        if(strcmp(current->data,newdata)==0){
            current->count = current->count+1;
            return 1;
        }
    current = current->next;
    }while (current!=NULL);

    return 0;
}

void deleteNode(struct Node **head_ref, int position)
{
   // If linked list is empty
   if (*head_ref == NULL)
      return;

   // Store head node
   struct Node* temp = *head_ref;

    // If head needs to be removed
    if (position == 0)
    {
        *head_ref = temp->next;   // Change head
        free(temp);               // free old head
        return;
    }

    // Find previous node of the node to be deleted
    for (int i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;

    // If position is more than number of nodes
    if (temp == NULL || temp->next == NULL)
         return;

    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    struct Node *next = temp->next->next;

    // Unlink the node from linked list
    free(temp->next);  // Free memory

    temp->next = next;  // Unlink the deleted node from list
}

void printt(struct Node *node)
{
  while (node != NULL)
  {
     printf(node->data);
     printf(" %d ", node->count);
     node = node->next;
  }
}

void push(struct Node** head_ref, struct Node* new_node)
{
    /* link the old list off the new node */
    new_node->next = (*head_ref);

    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
// Let us create a global variable to change it in threads
int g = 0;



void* worker(void* arg) {


struct Package* arg_struct = arg;




   char str1[1023];
        FILE * fp;
        fp = fopen (arg_struct->filename, "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}

    struct Node* nodede = node1;
    while(nodede!=NULL){
        printf(nodede->data);
        nodede = nodede->next;
    }
    arg_struct->head = node1;


   pthread_exit(NULL);
}
int main (int argc, char *argv[]) {
printf("sa");
int strt;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("\nSTART of the code\nseconds : %ld\nmicro seconds : %ld\n", current_time.tv_sec, current_time.tv_usec);
    strt = current_time.tv_sec % 100 * 1000000 + current_time.tv_usec;
   pthread_t threads[argc-3];
    int n = argc-3;

   FILE *fpw;
fpw = fopen( argv[n+2], "w");

   int rc;
   struct Package args[argc-3];

   for(int i = 0; i < argc-3; i++ ) {
      strcpy(args[i].filename,argv[i + 2]);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		rc = pthread_create(&threads[i],&attr,worker,&args[i]);
      if (rc) {
         printf("Error:unable to create thread, %d\n", rc);
         exit(-1);
      }
   }

	for (int i = 0; i < argc-3; i++)
	{
	    pthread_join(threads[i], NULL);
	}

    int minpos=0;
int end =0;
char ak[1023] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
while(end==0){

    for(int i=0; i<argc-3; i++){
    if(args[i].head != NULL){
        if(strcmp(args[i].head->data,ak)<0){
            minpos = i;
        }
    }
}

    for(int i = 0; i<argc-3; i++){
    if(args[i].head != NULL){
        if(minpos != i){
            if(strcmp(ak,args[i].head->data)==0){
                args[minpos].head->count = args[minpos].head->count+args[i].head->count;
                args[i].head = args[i].head->next;
            }
        }
    }
}
        if(args[minpos].head !=NULL){
        fprintf(fpw, "%s\t", args[minpos].head->data);
        fprintf(fpw, "%i\n", args[minpos].head->count);
        }

        if(args[minpos].head !=NULL )
        args[minpos].head = args[minpos].head->next;
    if(args[0].head==NULL)
    break;

    if(n>1 && args[0].head==NULL &&args[1].head==NULL )
    break;

    if(n>2 &&args[0].head==NULL &&args[1].head==NULL &&args[2].head==NULL )
    break;

    if(n>3 &&args[0].head==NULL &&args[1].head==NULL &&args[2].head==NULL &&args[3].head==NULL )
    break;

    if(n>4 && args[0].head==NULL &&args[1].head==NULL &&args[2].head==NULL &&args[3].head==NULL &&args[4].head==NULL)
    break;

}


   pthread_exit(NULL);


     gettimeofday(&current_time, NULL);
    printf("END of the code\nseconds : %ld\nmicro seconds : %ld\n", current_time.tv_sec, current_time.tv_usec);
    printf("Time it take in micro seconds = %ld\n", current_time.tv_sec % 100 * 1000000 + current_time.tv_usec - strt);
    printf("\n");
   return 0;
}
