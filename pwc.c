
#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <signal.h>
#include <mqueue.h>
#include <errno.h>
#define P4IPC_MSGSIZE 50
#define PMODE 0666
extern int errno;

#include <stdlib.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1


struct Node {
    char data[1023];
    int count;
    struct Node* next;
};

void sortedInsert(struct Node**, struct Node*);

void insertionSort(struct Node **head_ref)
{

    struct Node *sorted = NULL;

  
    struct Node *current = *head_ref;
    while (current != NULL)
    {
        struct Node *next = current->next;

        sortedInsert(&sorted, current);

        current = next;
    }

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
   if (*head_ref == NULL)
      return;

   struct Node* temp = *head_ref;

    if (position == 0)
    {
        *head_ref = temp->next;   
        free(temp);               
        return;
    }

    for (int i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;

    if (temp == NULL || temp->next == NULL)
         return;

    struct Node *next = temp->next->next;

    free(temp->next);  

    temp->next = next; 
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



    new_node->next = (*head_ref);

    (*head_ref)    = new_node;
}
int main(int argc, char *argv[])
{


int strt;
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("\nSTART of the code\nseconds : %ld\nmicro seconds : %ld\n", current_time.tv_sec, current_time.tv_usec);
    strt = current_time.tv_sec % 100 * 1000000 + current_time.tv_usec;


printf("sa");
int n = argc-3;
printf("= %i\n",n);

    int i;
mqd_t mqfd;
mqd_t mqfd2;
mqd_t mqfd3;
mqd_t mqfd4;
mqd_t mqfd5;
int endpos = -1;
struct mq_attr attr;
int open_flags = 0;
int num_bytes_to_send;
int priority_of_msg;
int num_bytes_received;
int num_bytes_received2;
int num_bytes_received3;
int num_bytes_received4;
int num_bytes_received5;
int min[n];
char minstr[1023];
int mincnt;
int minpos;
struct Node minnode;
strcpy(minnode.data,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");
minnode.count=0;
printf("START OF TEST_SEND \n");
int counter = 0;
/* Fill in attributes for message queue */
attr.mq_flags = 0;
attr.mq_maxmsg = 10;
attr.mq_msgsize = sizeof(struct Node);
attr.mq_curmsgs = 0;
for(int i=0; i<=n-1; i++){
    min[i]=0;
}
FILE *fpw;
fpw = fopen( argv[n+2], "w");
open_flags = O_RDWR|O_CREAT;

mqfd = mq_open("/c1",open_flags,PMODE,&attr);
mqfd2 = mq_open("/c2",open_flags,PMODE,&attr);
mqfd3 = mq_open("/c3",open_flags,PMODE,&attr);
mqfd4 = mq_open("/c4",open_flags,PMODE,&attr);
mqfd5 = mq_open("/c5",open_flags,PMODE,&attr);
    int p1 =1;
    int p2 =1;
    int p3 =1;
    int p4 =1;
    int p5 =1;
  	int p1end = 0;
	int p2end = 0;
	int p3end = 0;
	int pmainend = 0;
    char pdata1[1023];
    int pdata2;
	p1 = fork();
	if(p1!=0 && n>1){
	p2 = fork();
}
	if(p1!=0 && p2!=0 && n>2){
	p3 = fork();
}
    if(p1!=0 && p2!=0 && p3!=0 && n>3){
	p4 = fork();
}
    if(p1!=0 && p2!=0 && p3!=0 && p4!=0 && n>4){
	p5 = fork();
}

	if(p1==0 && p2==1 && p3==1){
        printf("hi from p1");
        char str1[1023];
        FILE * fp;
        fp = fopen (argv[2], "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}
    struct Node testo;
	while(node1!=NULL){
    num_bytes_to_send = 1023;
    priority_of_msg = 1;
    strcpy(testo.data,node1->data);
    testo.count = node1->count;
    int status = mq_send(mqfd,(const char *) &testo,sizeof(struct Node),0);
    if (status == -1){
        perror("mq_send failure on mqfd");
        break;
        }
    else{
    printf(node1->data);
        node1 = node1->next;
        }
	}
	struct Node testo2;
	testo2.count = -1;
	int status = mq_send(mqfd,(const char *) &testo2,sizeof(struct Node),0);
	printf("Node1 end");

    exit(0);
}
	else if(p2==0){
	printf("hi from p2");
	char str1[1023];

        FILE * fp;
        fp = fopen (argv[3], "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}
    struct Node testo3;
	while(node1!=NULL){
    strcpy(testo3.data,node1->data);
    testo3.count = node1->count;
    int status = mq_send(mqfd2,(const char *) &testo3,sizeof(struct Node),0);
    if (status == -1){
        perror("mq_send failure on mqfd2");
        break;
        }
    else{
        printf(node1->data);
        node1 = node1->next;
        }
	}
	struct Node testo2;
	testo2.count = -1;
	int status = mq_send(mqfd2,(const char *) &testo2,sizeof(struct Node),0);
	printf("Node2 end");
}
	else if(p3==0){
	printf("hi from p3");
	char str1[1023];

        FILE * fp;
        fp = fopen (argv[4], "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}
    struct Node testo3;
	while(node1!=NULL){
    strcpy(testo3.data,node1->data);
    testo3.count = node1->count;
    int status = mq_send(mqfd3,(const char *) &testo3,sizeof(struct Node),0);
    if (status == -1){
        perror("mq_send failure on mqfd2");
        break;
        }
    else{
        printf(node1->data);
        node1 = node1->next;
        }
	}
	struct Node testo2;
	testo2.count = -1;
	int status = mq_send(mqfd3,(const char *) &testo2,sizeof(struct Node),0);
	printf("Node3 end");
}

else if(p4==0){
	printf("hi from p4");
	char str1[1023];

        FILE * fp;
        fp = fopen (argv[5], "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}
    struct Node testo3;
	while(node1!=NULL){
    strcpy(testo3.data,node1->data);
    testo3.count = node1->count;
    int status = mq_send(mqfd4,(const char *) &testo3,sizeof(struct Node),0);
    if (status == -1){
        perror("mq_send failure on mqfd2");
        break;
        }
    else{
        printf(node1->data);
        node1 = node1->next;
        }
	}
	struct Node testo2;
	testo2.count = -1;
	int status = mq_send(mqfd4,(const char *) &testo2,sizeof(struct Node),0);
	printf("Node4 end");
}

else if(p5==0){
	printf("hi from p5");
	char str1[1023];

        FILE * fp;
        fp = fopen (argv[6], "r");
        struct Node* node1 = NULL;
        while(fscanf(fp, "%s", str1)==1){
        if(traverse(&node1, str1)==0){
            struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
            strcpy(node2->data, str1);
            node2->count = 1;
            sortedInsert(&node1,node2);
        }
}
    struct Node testo3;
	while(node1!=NULL){
    strcpy(testo3.data,node1->data);
    testo3.count = node1->count;
    int status = mq_send(mqfd5,(const char *) &testo3,sizeof(struct Node),0);
    if (status == -1){
        perror("mq_send failure on mqfd2");
        break;
        }
    else{
        printf(node1->data);
        node1 = node1->next;
        }
	}
	struct Node testo2;
	testo2.count = -1;
	int status = mq_send(mqfd5,(const char *) &testo2,sizeof(struct Node),0);
	printf("Node5 end");
}

	else if(p1!=0 && p2!=0 && p3!=0 && p4!=0 && p5!=0){
	sleep(1);
	printf("hi from parent");
    struct Node ntest[n];
	while(pmainend==0){


	if(min[0]==0 || min[0]==1){
    num_bytes_received = mq_receive(mqfd,(char *) &ntest[0],sizeof(struct Node),NULL);
    printf(minnode.data);
    if (num_bytes_received == -1)
        {
            perror("mq_receive failure on mqfdp");

            break;
        }
    else{
    }
}


    if((min[1]==0 || min[1]==1)&&n>1){
    num_bytes_received2 = mq_receive(mqfd2,(char *) &ntest[1],sizeof(struct Node),NULL);
    if (num_bytes_received2 == -1)
        {
            perror("mq_receive failure on mqfd2");

            break;
        }
    else{
    }
}

        if((min[2]==0 || min[2]==1)&&n>2){
    num_bytes_received3 = mq_receive(mqfd3,(char *) &ntest[2],sizeof(struct Node),NULL);
    if (num_bytes_received3 == -1)
        {
            perror("mq_receive failure on mqfd3");

            break;
        }
    else{
    }
}

    if((min[3]==0 || min[3]==1)&&n>3){
    num_bytes_received4 = mq_receive(mqfd4,(char *) &ntest[3],sizeof(struct Node),NULL);
    if (num_bytes_received4 == -1)
        {
            perror("mq_receive failure on mqfd4");

            break;
        }
    else{
    }
}


    if((min[4]==0 || min[4]==1)&&n>4){
    num_bytes_received5 = mq_receive(mqfd5,(char *) &ntest[4],sizeof(struct Node),NULL);
    if (num_bytes_received5 == -1)
        {
            perror("mq_receive failure on mqfd5");

            break;
        }
    else{
    }
}


    for(int i=0; i<=n-1; i++){
    if(ntest[i].count!=-1){
        for(int j=i+1; j<=n-1; j++){
        if(ntest[j].count!=-1){
            if(strcmp(ntest[i].data,ntest[j].data)<0){
                minpos = i;
            }
            else{

                minpos = j;
                i = j;
            }
            }
        }
        break;
        }
    }
    min[minpos] = 1;
    for(int i=0; i<=n-1; i++){
        if(i!=minpos){
            min[i] = 2;
        }
    }

    for(int i=0; i<=n-1; i++){
    if(ntest[i].count!=-1){
        if(minpos!=i){
            if(strcmp(ntest[minpos].data,ntest[i].data)==0){
                ntest[minpos].count = ntest[minpos].count+ntest[i].count;
                min[i] = 1;
            }
        }
        }
    }

    counter = counter +1;

        printf("data read for iteration = %s\n",ntest[minpos].data);
        printf("data read for iteration = %i\n",ntest[minpos].count);
        fprintf(fpw, "%s\t", ntest[minpos].data);
        fprintf(fpw, "%i\n", ntest[minpos].count);


if(n==1){
if(ntest[0].count==-1)
{
    if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c1") == -1)
    perror("mq_unlink failure in test_ipc");
    break;
}
}


if(n==2){
if(ntest[0].count==-1 && ntest[1].count==-1)
{
    if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c1") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd2) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c2") == -1)
    perror("mq_unlink failure in test_ipc");
    break;
}
}


if(n==3){
if(ntest[0].count==-1 && ntest[1].count==-1 && ntest[2].count==-1)
{
    if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c1") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd2) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c2") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd3) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c3") == -1)
    perror("mq_unlink failure in test_ipc");
    break;
}
}


if(n==4){
if(ntest[0].count==-1 && ntest[1].count==-1 && ntest[2].count==-1 && ntest[3].count==-1)
{
    if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c1") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd2) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c2") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd3) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c3") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd4) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c4") == -1)
    perror("mq_unlink failure in test_ipc");
    break;
}
}


if(n==5){
if(ntest[0].count==-1 && ntest[1].count==-1 && ntest[2].count==-1 && ntest[3].count==-1 && ntest[4].count==-1)
{
    if (mq_close(mqfd) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c1") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd2) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c2") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd3) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c3") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd4) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c4") == -1)
    perror("mq_unlink failure in test_ipc");

    if (mq_close(mqfd5) == -1)
    perror("mq_close failure on mqfd");
    if (mq_unlink("/c5") == -1)
    perror("mq_unlink failure in test_ipc");
    break;
}
}

	}
	   fclose(fpw);
 gettimeofday(&current_time, NULL);
    printf("END of the code\nseconds : %ld\nmicro seconds : %ld\n", current_time.tv_sec, current_time.tv_usec);
    printf("Time it take in micro seconds = %ld\n", current_time.tv_sec % 100 * 1000000 + current_time.tv_usec - strt);
    printf("\n");

}


    return 0;
}
