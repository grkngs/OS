#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cputimedur;
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
pthread_mutex_t mutex;
pthread_mutex_t mutex2;
// A structure to represent a queue
struct Queue {
    int front, rear, size;
    int tsize;
    unsigned capacity;
    int* array;
    int* threadid;
    int arrivesize;
    struct timeval* arrive_time;
    struct timeval* end_time;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->tsize = 0;
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));


    queue->threadid = (int*)malloc(
        queue->capacity * sizeof(int));
    queue->arrivesize=0;
    queue->arrive_time = (struct timeval*)malloc(
        queue->capacity * sizeof(struct timeval));
    return queue;
}

// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item, int threadId, struct timeval ttime)
{


    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    queue->threadid[queue->rear] = threadId;
    queue->tsize = queue->tsize + 1;
    queue->arrive_time[queue->rear] = ttime;
    queue->arrivesize = queue->arrivesize + 1;

}




// Function to remove an item from queue.
// It changes front and size
int dequeue(struct Queue* queue, int* threadId, struct timeval* ttime)
{


    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    *threadId = queue->threadid[queue->front];
    *ttime = queue->arrive_time[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;

    queue->tsize = queue->tsize - 1;

    queue->arrivesize = queue->arrivesize - 1;
    return item;
}

// Function to get front of queue
int front(struct Queue* queue, int* threadId, struct timeval* ttime)
{
    if (isEmpty(queue))
        return -1;
        *threadId = queue->threadid[queue->front];
        *ttime = queue->arrive_time[queue->front];
    return queue->array[queue->front];
}

// Function to get rear of queue
int rear(struct Queue* queue, int* threadId, struct timeval* ttime)
{
    if (isEmpty(queue))
        return -1;
    *threadId = queue->threadid[queue->rear];
    *ttime = queue->arrive_time[queue->front];
    return queue->array[queue->rear];
}

typedef struct {
    //Or whatever information that you need
    int *max_cpu;
    int *min_cpu;
    int *max_io;
    int *min_io;
    int i;
    struct Queue **queue;
    int *duration;
    FILE *rf;
    int infilecheck;
} thargs;

struct Queue* myqu;
int uniformDistr(int rangeLow,int rangeHigh)
{
double myRand = rand()/(1.0 + RAND_MAX);
int range = rangeHigh - rangeLow + 1;
int myRand_scaled = (myRand * range) + rangeLow;
return myRand_scaled;
}
int mainCon;
pthread_cond_t wait[5];
pthread_cond_t wait2[5];
int isAliveCheck[5] = {0,0,0,0,0};
int durations[5] = {0,0,0,0,0};
int cocoka = 0;
void* ps(void* arg) {

    thargs *actual_args = arg;
    int mycputime=0;
    int cput;
    int ioput;
    int it = actual_args->i;
    int initial = 0;
    int ioburst = 0;
    int duration = *(actual_args->duration);
    isAliveCheck[it] = 1;
if(actual_args->infilecheck==0){
    for(int i=0; i<duration; i++){
    durations[it] += 1;
    cput = uniformDistr(*actual_args->min_cpu,*actual_args->max_cpu);
    ioburst = uniformDistr(*actual_args->min_io,*actual_args->max_io);
    struct timeval ttime;
    gettimeofday(&ttime, NULL);
pthread_mutex_lock(&mutex);
    enqueue(myqu, cput,pthread_self(),ttime);
    cocoka = 1;
pthread_mutex_unlock(&mutex);

pthread_mutex_lock(&mutex2);
    pthread_cond_wait(&wait[it], &mutex2);
pthread_mutex_unlock(&mutex2);

    usleep(ioburst*1000);

}
}

else{

    char x[1024];
    while (fscanf(actual_args->rf, " %1023s", x) == 1) {

        if(strcmp(x,"CPU")==0){
            fscanf(actual_args->rf, " %1023s", x);
            cput =atoi(x);
            struct timeval ttime;
            durations[it] += 1;
            gettimeofday(&ttime, NULL);
            pthread_mutex_lock(&mutex);
            enqueue(myqu, cput,pthread_self(),ttime);
            pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex2);
            pthread_cond_wait(&wait[it], &mutex2);

pthread_mutex_unlock(&mutex2);
        }
        if(strcmp(x,"IO")==0){
            fscanf(actual_args->rf, " %1023s", x);
            ioburst =atoi(x);

            usleep(ioburst*1000);
        }

    }
}


printf("\n");
    isAliveCheck[it] = 0;
    free(actual_args);
   pthread_exit(NULL);
   return 0;
}

int isAlive(int size){
    for(int i=0; i<size; i++){
        if(isAliveCheck[i]==1){
            return 1;

            }
    }
    return 0;
}

int checkT(struct Queue* q, int index){
    for(int i=0; i<q->size; i++){
        if(q->threadid[i]==index)
            return 1;
    }
    return 0;
}
// Queue elements after sortedIndex are
// already sorted. This function returns
// index of minimum element from front to
// sortedIndex
int minIndex(struct Queue* q, int sortedIndex)
{
    int min_index = -1;
    int min_val = 1000000;
    int min_arrive = 1000000;
    int n = q->size;
    int curt = 0;
    int curttest = 0;
    struct timeval ttime;
    struct timeval ttime2;
    for (int i=0; i<n; i++)
    {
        int curr = front(q,&curt,&ttime);
        dequeue(q,&curttest,&ttime2);  // This is dequeue() in C++ STL

        // we add the condition i <= sortedIndex
        // because we don't want to traverse
        // on the sorted part of the queue,
        // which is the right part.
        if (curr <= min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr;
        }

        enqueue(q,curr,curt,ttime);  // This is enqueue() in
                       // C++ STL
    }
    return min_index;
}

// Moves given minimum element to rear of
// queue
void insertMinToRear(struct Queue* q, int min_index)
{
    int min_val;
    int mint;
    int n = q->size;
    int curt = 0;
    int curtest = 0;
    struct timeval ttime;
    struct timeval mintime;
    struct timeval ttime2;
    for (int i = 0; i < n; i++)
    {
        int curr = front(q,&curt,&ttime);
        dequeue(q,&curtest,&ttime2);
        if (i != min_index)
            enqueue(q,curr,curt,ttime);
        else{
            min_val = curr;
            mint = curt;
            mintime = ttime;
            }
    }
    enqueue(q,min_val,mint,mintime);
}

void sortQueue(struct Queue* q)
{
    for (int i = 1; i <= q->size; i++)
    {
        int min_index = minIndex(q, q->size - i);
        insertMinToRear(q, min_index);
    }
}

void printq(struct Queue* q){
    for(int i=0; i<q->size; i++){
        printf("%d %d \n", q->array[i], q->threadid[i]);
    }
}

int main (int argc, char *argv[]) {


    int n = atoi(argv[1]);
    int mincpu = atoi(argv[2]);
    int maxcpu = atoi(argv[3]);
    int minio = atoi(argv[4]);
    int maxio = atoi(argv[5]);
    char outfile[sizeof(argv[6])];
    strcpy(outfile,argv[6]);
    int duration = atoi(argv[7]);
    char algo[sizeof(argv[8])];
    strcpy(algo,argv[8]);
    int quantum = atoi(argv[9]);

    char infileprefix[sizeof(argv[10])];
    strcpy(infileprefix,argv[10]);
    FILE *rf;

    char he[1024];
    int rc;
    pthread_t threads[n];
    cputimedur = duration;
    myqu = createQueue(duration*n);
    int er=0;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\n mutex init has failed\n");
    }
    if (pthread_mutex_init(&mutex2, NULL) != 0) {
        printf("\n mutex init has failed\n");
    }

   for(int i = 0; i < n; i++ ) {

        thargs *args = malloc(sizeof *args);
        args->infilecheck = 0;
        args->max_cpu = &maxcpu;
        args->min_cpu = &mincpu;
        args->max_io = &maxio;
        args->min_io = &minio;
        args->duration = &duration;
        args->i = i;
        if(strcmp(infileprefix,"no-infile")!=0){
        args->infilecheck = 1;
        char str[12];
        sprintf(str, "%d", i+1);
        strcpy(he,infileprefix);
        strcat(he, str);
        strcat(he, ".txt");
        rf = fopen(he, "r");
        args->rf = rf;

}

        if (pthread_cond_init(&wait[i], NULL) != 0) {
        printf("\n mutex init has failed\n");
    }
        isAliveCheck[i]==1;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		rc = pthread_create(&threads[i],&attr,ps,args);
      if (rc) {
         printf("Error:unable to create thread, %d\n", rc);
         exit(-1);
      }
      sleep(1);
   }
   int burst;
    int t=5;
    FILE *fp = fopen(outfile, "w");
    sleep(3);
    long starttime = 0;
    int counter = n*duration;
    //Fcfs
    int strt;
    int concon = 0;
    int concon2 = 0;
    int tutucu = 0;
    struct timeval current_time;
    struct timeval current_time2;
    struct timeval current_time3;
    struct timeval current_time4;
    int waitingTime[n];
    for(int i=0; i<n ; i++){
        waitingTime[i] = 0;
    }
    if(strcmp(algo,"FCFS")==0){
    while(isAlive(n)==1){

    if(isEmpty(myqu)!=1){
        pthread_mutex_lock(&mutex);
         burst = dequeue(myqu,&t, &current_time3);
        pthread_mutex_unlock(&mutex);

         counter = counter-1;
        for(int i=0; i<n; i++){

            int tt = threads[i];

            if(tt == t){
            if(concon2 == 0){
                    gettimeofday(&current_time, NULL);
                    starttime = 0;
                    concon2 = 1;

                }else{
                    gettimeofday(&current_time2, NULL);
                    long seconds = current_time2.tv_sec - current_time.tv_sec;
                    starttime = (seconds*1000000+current_time2.tv_usec)-current_time.tv_usec;
                }
                int digit = 0;
                for(int i = starttime; i >= 10; i = i/10)
{
 digit++;
}
for(int i = 1; i < 10-digit; i++){
	fprintf(fp,"%d",0);
}
                fprintf(fp,"%ld \t %d \t %d \n", starttime, burst, i+1);

                gettimeofday(&current_time4, NULL);
                long seconds = current_time4.tv_sec - current_time3.tv_sec;
                waitingTime[i] += (seconds*1000000+current_time4.tv_usec)-current_time3.tv_usec;

                usleep(burst*1000);
                pthread_cond_signal(&wait[i]);
            }
        }
        }
        else{

        }

    }
}

    else if(strcmp(algo,"SJF")==0){

        while(isAlive(n)){
            if(isEmpty(myqu)!=1){
                pthread_mutex_lock(&mutex);
                sortQueue(myqu);
                burst = dequeue(myqu,&t,&current_time3);
                pthread_mutex_unlock(&mutex);
                counter = counter-1;

                for(int i=0; i<n; i++){

            int tt = threads[i];

            if(tt == t){
            if(concon2 == 0){
                    gettimeofday(&current_time, NULL);
                    starttime = 0;
                    concon2 = 1;

                }else{
                    gettimeofday(&current_time2, NULL);
                    long seconds = current_time2.tv_sec - current_time.tv_sec;
                    starttime = (seconds*1000000+current_time2.tv_usec)-current_time.tv_usec;
                }
                gettimeofday(&current_time4, NULL);
                long seconds = current_time4.tv_sec - current_time3.tv_sec;
                waitingTime[i] += ((seconds*1000000+current_time4.tv_usec)-current_time3.tv_usec);

                int digit = 0;
                for(int i = starttime; i >= 10; i = i/10)
{
 digit++;
}
for(int i = 1; i < 10-digit; i++){
	fprintf(fp,"%d",0);
}

                fprintf(fp,"%ld \t %d \t %d \n", starttime, burst, i+1);
                usleep(burst*1000);
                pthread_cond_signal(&wait[i]);
            }
        }
            }
        }

    }

    else if(strcmp(algo,"RR")==0){
    int coco[n];
    for(int i=0; i<n; i++){
        coco[i] = 0;
    }
		while(isAlive(n)){

    if(isEmpty(myqu)!=1){
            int cap = myqu->size;

		    pthread_mutex_lock(&mutex);


				int burst = dequeue(myqu,&t,&current_time3);
				int k;
				for(int i=0; i<n; i++){
                int tt = threads[i];
                if(tt==t){
                k = i;
                break;
                }
                }


				if(burst > quantum)
				{
					enqueue(myqu,burst-quantum,t,current_time3);
					burst = quantum;
					for(int i=0; i<n; i++){
                        coco[i] = 0;
					}
				}
				else if(burst == quantum)
				{
					burst = quantum;

					for(int i=0; i<n; i++){
                        coco[i] = 0;
					}
					coco[k] = 1;
				}
				else
				{
                    for(int i=0; i<n; i++){
                        coco[i] = 0;
					}
					coco[k] = 1;
				}
        pthread_mutex_unlock(&mutex);



                if(concon2 == 0){
                    gettimeofday(&current_time, NULL);
                    starttime = 0;
                    concon2 = 1;

                }else{
                    gettimeofday(&current_time2, NULL);
                    long seconds = current_time2.tv_sec - current_time.tv_sec;
                    starttime = (seconds*1000000+current_time2.tv_usec)-current_time.tv_usec;
                }
                gettimeofday(&current_time4, NULL);
                long seconds = current_time4.tv_sec - current_time3.tv_sec;
                waitingTime[k] += ((seconds*1000000+current_time4.tv_usec)-current_time3.tv_usec);


                int digit = 0;
                for(int i = starttime; i >= 10; i = i/10)
{
 digit++;
}
for(int i = 1; i < 10-digit; i++){
	fprintf(fp,"%d",0);
}

                fprintf(fp,"%ld \t %d \t %d \n", starttime, burst, k+1);
                usleep(burst*1000);




                for(int i=0; i<n; i++){
                    if(coco[i] == 1){
                        pthread_cond_signal(&wait[i]);
                        cocoka=0;
                    }
                }
       }

    }
    }

    for(int i=0; i<n; i++){
        printf("%s %d \t %d \n", "Total waiting time for process ",i+1,waitingTime[i]);
    }
    for(int i=0; i<n; i++){
        printf("%s %d \t %d \n", "Average response time for process ",i+1,waitingTime[i]/durations[i]);
    }
    fclose(fp);

   return 0;
}
