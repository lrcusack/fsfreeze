#include<linux/slab.h>
#include<linux/gfp.h>


typedef struct qnode{
	void* val;
	struct qnode* next;
} qnode;

typedef struct {
	struct qnode* head;
	struct qnode* tail;
	int length;
} kqueue;

static inline kqueue* kq_create(void){
	kqueue* kq;
	kq=(kqueue*) kmalloc(sizeof(kqueue),GFP_KERNEL);
	
	if(kq==NULL){
		printk("can't allocate memory\n");
		return NULL;
	}
	kq->length = 0;
	return kq;
}

static inline void kq_delete(kqueue *kq){
	struct qnode* curr = kq->head;
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

static inline void print_thing(kqueue *kq){
	struct qnode* curr = kq->head;
	while(curr!= NULL){
		printk("%c \n",*(char*)curr->val);
		curr = curr->next;
	}

}

static inline int kq_enqueue( kqueue *kq, void* value){

	struct qnode* new;
	new=(qnode*) kmalloc(sizeof(qnode),GFP_KERNEL);
	
	
	if(!new){
		printk("can't create struct qnode\n");
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
	struct qnode* pop;
	if(0==kq->length) return NULL;
	
	pop = kq->head;
	element = pop->val;
	kq->head=kq->head->next;
	
	kq->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
