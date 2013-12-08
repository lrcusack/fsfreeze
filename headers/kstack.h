#include<linux/slab.h>
#include<linux/gfp.h>


typedef struct snode{
	void* val;
	struct snode* next;
} snode;

typedef struct {
	struct snode* head;
	struct snode* tail;
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
	struct snode* curr = ks->head;
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

	struct snode* new;
	new=(struct snode*) kmalloc(sizeof(struct snode),GFP_KERNEL);
	
	if(!new){
		printk("can't create struct snode\n");
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
	struct snode* pop;
	if(0==ks->length) return NULL;
	
	pop = ks->head;
	element = pop->val;
	ks->head=ks->head->next;
	
	ks->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
