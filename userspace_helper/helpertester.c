//helpertester
#include <stdio.h>
#include <stdlib.h>

int main(){
	char c;
	FILE* dis = fopen("/freezer/thuglife.txt","a");
	fprintf(dis, "ya bish\n why you so bishmade doe\nyo ass is marked up\n");
	fclose(dis);
	printf("press any key to continue\n");
	scanf("%c", &c);
	dis = fopen("/freezer/thuglife.txt","a");
	fprintf(dis, "dat shit worked\n");
	return 0;
}
