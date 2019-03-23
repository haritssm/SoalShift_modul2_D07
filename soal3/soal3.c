#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
	int status;
	pid_t pid1,pid2,pid3;
	int pipe1[2],pipe2[2];
	FILE *f;
	char str[500];

	pid1 = fork();
	if(pid1 ==0){
		char *argv[3] = {"unzip","campur2.zip",NULL};
		execv("/usr/bin/unzip",argv);
	}
	else{
		while(wait(&status) > 0);

		pid2 = fork();
		pipe(pipe1);
		pipe(pipe2);
		if(pid2 == 0){
			dup2(pipe1[1],STDOUT_FILENO);
			close(pipe1[0]);

			char *argv[3] = {"ls","/home/zicoritonda/sisop/Modul2/SoalShiftModul2/soal3/campur2",NULL};
			execv("/bin/ls",argv);
		}
		else{
			pid3 = fork();
			if(pid3 ==0){
				dup2(pipe1[0],STDIN_FILENO);
				dup2(pipe2[1],STDOUT_FILENO);
				close(pipe1[1]);
				close(pipe2[0]);

				char *argv[7] = {"find","./campur2","-name","*.txt","-printf","%f\n",NULL};
				execv("/usr/bin/find",argv);
			}
			else{
				dup2(pipe2[0],STDIN_FILENO);
				close(pipe2[1]);

				int lebar = read(pipe2[0],str,sizeof(str));
				//printf("\n");
				//printf("%.*s\n",lebar,str);
				close(pipe2[0]);
				f = fopen("daftar.txt","a");
				fprintf(f,"%.*s",lebar,str);
				fclose(f);
			}
		}
	}

}
