#include<linux/slab.h>
#include<linux/gfp.h>


typedef struct node{
	void* val;
	struct node* next;
} node;

typedef struct {
	node* head;
	node* tail;
	int length;
} llqueue;

static inline llqueue* ll_create(void){
	llqueue* ll;
	ll=(llqueue*) kmalloc(sizeof(llqueue),GFP_KERNEL);
	
	if(ll==NULL){
		printk("can't allocate memory\n");
		return NULL;
	}
	
	return ll;
}

static inline void ll_delete(llqueue *ll){
	node* curr = ll->head;
	while(curr!=NULL){
		ll->head=ll->head->next;
		kfree(curr);
		curr=ll->head;
	}
	
	if(ll->head==ll->tail){
		kfree(ll->head);
	}
	
	kfree(ll);
	
	return;
}


static inline int ll_enqueue( llqueue *ll, void* value){

	node* new;
	new=(node*) kmalloc(sizeof(node),GFP_KERNEL);
	
	if(!new){
		printk("can't create node\n");
		return 0;
	}
	
	new->val=value;
	new->next=NULL;
	
	
	if(ll->length==0){
		ll->head=new;
	}
	
	else{
		ll->tail->next=new;
	}
	
	ll->tail=new;
	
	ll->length++;
	
	return 1;
}


static inline void* ll_dequeue( llqueue *ll){
	
	if(0==ll->length) return NULL;
	
	node* pop =ll->head;
	
	void* element = pop->val;
	ll->head=ll->head->next;
	
	ll->length--;
	kfree(pop);

	return element;

	//for edge case were list is empty, return 0
}
