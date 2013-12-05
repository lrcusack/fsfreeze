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
} kqueue;

static inline kqueue* kq_create(void){
	kqueue* kq;
	kq=(kqueue*) kmalloc(sizeof(kqueue),GFP_KERNEL);
	
	if(kq==NULL){
		printk("can't allocate memory\n");
		return NULL;
	}
	
	return kq;
}

static inline void kq_delete(kqueue *kq){
	struct node* curr = kq->head;
	while(curr!=NULL){
		kq->head=kq->head->next;
		kfree(curr);
		curr=kq->head;
	}
	
	if(kq->head==kq->tail){
		kfree(kq->head);
	}
	
	kfree(kq);
	
	return;
}


static inline int kq_enqueue( kqueue *kq, void* value){

	struct node* new;
	new=(struct node*) kmalloc(sizeof(struct node),GFP_KERNEL);
	
	if(!new){
		printk("can't create struct node\n");
		return 0;
	}
	
	new->val=value;
	new->next=NULL;
	
	
	if(kq->length==0){
		kq->head=new;
	}
	
	else{
		kq->tail->next=new;
	}
	
	kq->tail=new;
	
	kq->length++;
	
	return 1;
}


static inline void* kq_dequeue( kqueue *kq){
	void* element;
	struct node* pop;
	if(0==kq->length) return NULL;
	
	pop = kq->head;
	element = pop->val;
	kq->head=kq->head->next;
	
	kq->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
