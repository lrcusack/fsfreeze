#include <linux/kernel.h>
#include <linux/slab.h>

typedef struct node{

	char* val;
	struct node* next;
} node;

typedef struct llqueue{
	struct node* head;
	struct node* tail;
	int length;
} llqueue;

static inline llqueue* ll_create(void){
	llqueue* ll;
	ll=(struct llqueue*) kmalloc(sizeof(struct llqueue));
	
	if(!ll){
		printk("can't allocate memory\n");
		return 0;
	}
	
	return 0;
}

static inline void ll_delete(llqueue *ll){
	node* curr = ll->head;
	int ii;
	for(ii=0; ii < (ll->length); ii++){

		ll->head=ll->head->next;
		kfree(curr->val);
		kfree(curr);
		curr=ll->head;
	}
	
	if(ll->head==ll->tail){
		kfree(ll->head->val);
		kfree(ll->head);
	}
	
	kfree(ll);
	
	return;
}

static inline int ll_enqueue( llqueue *ll, char* string){

	node* new;
	new=(node*) kmalloc(sizeof(node));
	
	if(!new){
		printk("can't create node\n");
		return 0;
	}
	
	new->val=string;
	
	if(ll->length==0){
		new->next=0;
		ll->head=new;
		ll->tail=new;
		ll->head->next=0;
		ll->tail->next=0;
	}
	
	else{
		ll->tail->next=new;
		ll->tail=new;
		ll->tail->next=0;
	}
	
	return 1;
}

static inline int ll_dequeue( llqueue *ll, char* element){
	
	if(0==ll->length) return 0;
	
	node* pop =ll->head;
	
	element = ll->head->val;
	ll->head=ll->head->next;
	
	ll->length--;
	kfree(pop);

	return 1;
}
