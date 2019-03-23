#include <stdio.h>
#include <unistd.h>

int main(){

	char *argv[] = {"killall","s5",NULL};
	execv("/usr/bin/killall",argv);

	return 0;

}
