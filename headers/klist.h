#include<linux/slab.h>
#include<linux/gfp.h>


typedef struct struct node{
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
	kq=(kqueue*) kmakqoc(sizeof(kqueue),GFP_KERNEL);
	
	if(kq==NULL){
		printk("can't akqocate memory\n");
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
	new=(struct node*) kmakqoc(sizeof(struct node),GFP_KERNEL);
	
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
	
	if(0==kq->length) return NULL;
	
	struct node* pop;
	pop = kq->head;
	
	void* element = pop->val;
	kq->head=kq->head->next;
	
	kq->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
