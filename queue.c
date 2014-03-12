/**
 * queue.c
 *
 * This file contains the implementation of the job queue
 */

#define MAX_NUM_NODES 1000


// The Node of a Queue
typedef struct Node {
  dispatch_fn func;
  void * func_arg;
  struct Node * next;
  struct Node * prev;
} Node;

// The Queue Struct
typedef struct Queue {
	struct Node * head;
	struct Node * tail;
	int size;
	int maxSize;
} Queue;


// Create a new queue
struct Queue * makeQueue() {

	// Allocate memory for queue
	Queue * q = (Queue *) malloc (sizeof(Queue));

	// Initialize the variables
	q->size = 0;
	q->maxSize = MAX_NUM_NODES;
	q->head = NULL;
	q->tail = NULL;

	// Return the initialized queue
	return q;
}


// Add a job to the queue
void addJob(Queue * q, dispatch_fn func, void * arg) {
	
	// Only add the job to the queue if it is not at capacity 
	if (q->size < q->maxSize) {

		Node * temp = (Node *) malloc (sizeof(Node));
		
		temp->func = func;
		temp->func_arg = arg;
		temp->next = NULL;

		// The first job added to the list
		if (q->head == NULL) {
			q->head = temp;
			q->tail = temp;
			q->head->prev = NULL;

		} else {
			q->tail->next = temp;
			q->tail->next->prev = tail;
			q->tail = temp;
		}

		// Increment the size of the queue
		q->size++;

	}
}

// Remove a job from the queue to be used by a threadpool
void removeJob(Queue * q, dispatch_fn * func, void ** arg) {

	// Only remove a job if there is at least one already on the queue 
	if (q->size > 0) {

		Node * temp = q->head;

		// Set these pointers in the thread to the valued of the job info
		*func = temp->func_to_dispatch;
		*arg  = temp->func_arg;

		// Remove the last job on the queue
		if (q->head == q->tail) {
			q->head = NULL;
			q->tail = NULL;
			free(temp); // delete the memory of this node

		} else {
			q->head = q->head->next;
			q->head->prev = NULL;
			free(temp); // delete the memory of this node
		}

		// Decrement the size of the queue
		q->size--;

	}
		
}

// Can another job be added to the queue
int canAddJob(struct Queue * q) {
	return(q->size < q->maxSize);
}

// Is there a job to be done
int isJobAvailable(struct Queue * q) {
  return(q->head != NULL);
}