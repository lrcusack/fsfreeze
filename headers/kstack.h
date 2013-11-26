#include<linux/slab.h>
#include<linux/gfp.h>


typedef struct node{
	void* val;
	struct node* next;
} node;

typedef struct {
	struct node* head;
	struct node* tail;
	int length;
} k_stack;

static inline k_stack* ks_create(void){
	k_stack* ks;
	ks=(kstack*) kmalloc(sizeof(k_stack),GFP_KERNEL);
	
	if(ks==NULL){
		printk("can't allocate memory\n");
		return NULL;
	}
	
	return kq;
}

static inline void ks_delete(k_stack *ks){
	struct node* curr = ks->head;
	while(curr!=NULL){
		ks->head=ks->head->next;
		kfree(curr);
		curr=ks->head;
	}
	
	if(ks->head==ks->tail){
		kfree(ks->head);
	}
	
	kfree(kq);
	
	return;
}

//changed this to FIFO
static inline int ks_enqueue( kqueue *ks, void* value){

	struct node* new;
	new=(struct node*) kmalloc(sizeof(struct node),GFP_KERNEL);
	
	if(!new){
		printk("can't create struct node\n");
		return 0;
	}
	
	new->val=value;
	new->next=NULL;
	
	
	if(ks->length==0){
		ks->head=new;
	}
	
	else{
		ks->next = ks->head;
		ks->head=new;
	}
	
	ks->length++;
	
	return 1;
}

//already dequeues from the front of the list so is all good
static inline void* ks_dequeue( kqueue *ks){
	void* element;
	struct node* pop;
	if(0==ks->length) return NULL;
	
	pop = ks->head;
	element = pop->val;
	ks->head=ks->head->next;
	
	ks->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
