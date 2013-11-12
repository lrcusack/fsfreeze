#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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
	ll=(struct llqueue*) malloc(sizeof(struct llqueue));
	
	if(ll==NULL){
		printf("can't allocate memory\n");
		return NULL;
	}
	
	return ll;
}

static inline void ll_delete(llqueue *ll){
	node* curr = ll->head;
	int ii;
	for(ii=0; ii < (ll->length); ii++){

		ll->head=ll->head->next;
		free(curr->val);
		free(curr);
		curr=ll->head;
	}
	
	if(ll->head==ll->tail){
		free(ll->head->val);
		free(ll->head);
	}
	
	free(ll);
	
	return;
}


static inline int ll_enqueue( llqueue *ll, char* string){

	node* new;
	new=(node*) malloc(sizeof(node));
	
	if(!new){
		printf("can't create node\n");
		return 0;
	}
	
	new->val=string;
	
	if(ll->length==0){
		new->next=NULL;
		ll->head=new;
		ll->tail=new;
		ll->head->next=NULL;
		ll->tail->next=NULL;
	}
	
	else{
		ll->tail->next=new;
		ll->tail=new;
		ll->tail->next=NULL;
	}
	
	return 1;
}


static inline int ll_dequeue( llqueue *ll, char* element){
	
	if(0==ll->length) return 0;
	
	node* pop =ll->head;
	
	strncpy(element,ll->head->val,10);
	ll->head=ll->head->next;
	
	ll->length--;
	free(pop);

	return 1;

	//for edge case were list is empty, return 0
}
