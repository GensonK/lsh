#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>

char cmd[1024];



char *args[100];

void exProgA_exProgB();
void info();
void get_dir();
void change_dir();
void run_prog();
int case_identify(char *demo);
void find_args(char *cmd);
void my_grep();
int main(int argc,char *argv[]){
	int i;
	while(1){
		memset(cmd,0,1024);
		memset(args,0,1024);
		printf("\nyour command: ");
		fgets(cmd,1024,stdin);
		if(cmd==NULL){
			printf("nothing input...");
		}
		else{
			cmd[strlen(cmd)-1]='\0';
			find_args(cmd);
			switch(case_identify(args[0])){
					
				case 1:
					info();
					break;	
				case 2:
					exit(1);
					break;
				case 3:
					get_dir();
					break;
				case 4:
					change_dir();
					break;
				case 5:				
					run_prog();
					break;
				case 6:
					printf("invalid input");
					break;
				case 7:
					my_grep();
				case 8:
					exProgA_exProgB();
					
				}
		}
		}	
		}
	int case_identify(char *demo){
		if(strcasecmp(demo,"info")==0)
			return 1;
		else if(strcasecmp(demo,"exit")==0)
			return 2;
		else if(strcasecmp(demo,"pwd")==0)
			return 3;
		else if(strcasecmp(demo,"cd")==0)
			return 4;
		else if(strcasecmp(demo,"ex")==0)
			return 5;
		else if(strcasecmp(demo,"mygrep")==0)
			return 7;
		else if(strcasecmp(demo,"./name1")==0)
			return 8;
		else return 6;	
	} 
	void info(){
		char hostname[100];
		gethostname(hostname, sizeof(hostname));
		printf("XJCO2211 Simplified Shell by %s",hostname);
	}
	void get_dir(){
		printf("\nyour current working directory is: %s\n",getcwd(NULL,99));	
	}
	void change_dir(){
		if(args[1]==NULL){
		fprintf(stderr,"no directory input");
			return;
			}
		else if(chdir(args[1])==-1){
			perror("wrong directory");
			}
		else{
			printf("change done");
			get_dir();
			}
	}
	
	void find_args(char *cmd){
		

		int count=0;
		args[0]=strtok(cmd," ");
		while(args[count]!=NULL){
			count++;
			args[count]=strtok(NULL," ");
		}
	}
	
	
	
void run_prog(){
	pid_t pid;
  	int status;
  	pid = fork();
	if (pid == 0) {
		
   	 	if (execvp(args[1], args) == -1){
   	 		perror("wrong in executing");
			}
    	
    	exit(EXIT_FAILURE);
    }
   else if (pid < 0) {
    	perror("error in forking");
  }else {
    	do {
    		
      		waitpid(pid, &status, WUNTRACED);
   		 } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  } 
  void my_grep(){
  	int k=0;
  	int count=0;
  	char in[1024],ag[100];
  	int j;
  	if(strcasecmp(args[1],"-c")!=0||args[2]==NULL||args[3]==NULL){
  		printf("non-standard command\nEXAMPLE:mygrep -c pattern file ");
	  }
  	else{
  		strcpy(ag,args[2]);
  		FILE *fp;
  		
  		int i=0;
  		fp=fopen(args[3],"r");
  	if(fp!=NULL){
  		in[i]=getc(fp);
  		while(in[i]!=EOF){
  			i++;
  			in[i]=getc(fp);
  			
		}
		i=0;
		while(i<strlen(in)){
			
			if(in[i]==ag[0]){
				for(j=0;j<strlen(ag);j++){
					
					if(in[j+i]==ag[j]){
						k+=1;
					}
				}
			
			if(k==strlen(ag)){
				
				count++;
			
			}
		}
			i++;
			k=0;
		}
		printf("%d",count);
		
	  }
	else{
		fprintf(stderr,"wrong in reading file");
	}
	  
  
  }
  }
  void exProgA_exProgB(){
    pid_t pid1;
    int status;
    int fd[2];
    if(pipe(fd) < 0){
        printf("PIPE FILE\n");
    }
    pid1 = fork();
    if(pid1 == 0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        if(execvp(args[0],args)==-1)
            perror("Error2");
        exit(EXIT_FAILURE);
    }
    else if(pid1 < 0)
        perror("Failure");
    else{
        
    	do {
    		
      		waitpid(pid1, &status, WUNTRACED);
   		 } while (!WIFEXITED(status) && !WIFSIGNALED(status));
   		close(fd[1]);
        dup2(fd[0],STDIN_FILENO);

        if(execvp(args[1],NULL)==-1)
        perror("Error1");
        exit(EXIT_FAILURE);
       	
    }
    
  
    

}
	


  


		
	
	
	
	
