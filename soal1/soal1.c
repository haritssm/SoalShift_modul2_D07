#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(char *argv[]){
	int status;
	int pipe_fd1[2];
	pid_t ls_pid, mv_pid;

	pipe(pipe_fd1);

	ls_pid = fork();
	if(ls_pid == 0){//first child
		dup2(pipe_fd1[1], STDOUT_FILENO);
		close(pipe_fd1[0]);

		char *argv[3] = {"ls","*.txt",NULL};
		execv("/bin/ls",argv);
		//execlp("ls", "ls", argv[1], NULL);
	}
	else if(ls_pid > 0){//parent
		dup2(pipe_fd1[0], STDIN_FILENO);
		close(pipe_fd1[1]);
		
		//while ((wait(&status)) > 0);
		//char *argv[7] = {"xargs",argv[2],"{}","mv", "{}", "new_{}", NULL};
		//execv("/bin/mv",argv);
		execlp("xargs", "xargs","-i", "mv", "{}", "new_{}",NULL);
	} 

}
