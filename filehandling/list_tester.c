#include "../headers/project.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include "../headers/klist.h"

int main(){
	//trying to test klist.h implementation
	kqueue test_queue* = kq_create();
	kq_enqueue(test_queue, 'f');
	kq_enqueue(test_queue, 'u');
	kq_enqueue(test_queue, 'c');
	kq_enqueue(test_queue, 'k');
	print_thing(test_queue);


}
