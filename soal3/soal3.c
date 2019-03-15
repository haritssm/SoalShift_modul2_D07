#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int status;
	pid_t pid1,pid2;
	FILE *f,*output;
	char str[100];

	pid1 = fork();
	if(pid1 ==0){
		char *argv[3] = {"unzip","campur2.zip",NULL};
		execv("/usr/bin/unzip",argv);
	}
	else{
		while((wait(&status)) > 0);

		//char *argv[9] = {"find","./campur2","-name","*.txt","-printf","%f\n",">","daftar.txt",NULL};
		//execv("/usr/bin/find",argv);

		f = popen("find ./campur2 -name '*.txt' -printf '%f\n'","r");
		output = fopen("daftar.txt","a");
		while(fgets(str, sizeof(str), f) != NULL){
			printf("%s",str);
			fprintf(output,"%s",str);
		}
		pclose(f);

		//output = fopen("daftar.txt","a");
		//fprintf(output,"%s",str);
		fclose(output);
	}

}
