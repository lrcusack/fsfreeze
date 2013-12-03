#include<stdio.h>
#include<stdlib.h>

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
	ll=(llqueue*) malloc(sizeof(llqueue));
	
	if(ll==NULL){
		printf("can't allocate memory\n");
		return NULL;
	}
	
	return ll;
}

static inline void ll_delete(llqueue *ll){
	node* curr = ll->head;
	while(curr!=NULL){
		ll->head=ll->head->next;
		free(curr);
		curr=ll->head;
	}
	
	if(ll->head==ll->tail){
		free(ll->head);
	}
	
	free(ll);
	
	return;
}


static inline int ll_enqueue( llqueue *ll, void* value){

	node* new;
	new=(node*) malloc(sizeof(node));
	
	if(!new){
		printf("can't create node\n");
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


static inline int ll_dequeue( llqueue *ll, void** element){
	
	if(0==ll->length) return 0;
	
	node* pop =ll->head;
	
	*element = pop->val;
	ll->head=ll->head->next;
	
	ll->length--;
	free(pop);

	return 1;

	//for edge case were list is empty, return 0
}
