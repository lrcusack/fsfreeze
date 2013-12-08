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
} kstack;

static inline kstack* ks_create(void){
	kstack* ks;
	ks=(kstack*) kmalloc(sizeof(kstack),GFP_KERNEL);
	
	if(ks==NULL){
		printk("can't allocate memory\n");
		return NULL;
	}
	ks->length = 0;
	return ks;
}

static inline void ks_delete(kstack *ks){
	struct node* curr = ks->head;
	while(curr!=NULL){
		ks->head=ks->head->next;
		kfree(curr);
		curr=ks->head;
	}
	
	if(ks->head==ks->tail){
		kfree(ks->head);
	}
	
	kfree(ks);
	
	return;
}

//changed this to LIFO
static inline int ks_push( kstack *ks, void* value){

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
		new->next = ks->head;
		ks->head=new;
	}
	
	ks->length++;
	
	return 1;
}

//already dequeues from the front of the list so is all good
static inline void* ks_pop( kstack *ks){
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
