#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
void print_all(char**str,int len,bool swi_a){
    for(int i=0;i<len;i++){
        if(swi_a ||str[i][0] != '.'){
            printf("%s\n",str[i]);  
       }
    }
}
void time_sort(char**str,int len){
    for(int i=0;i<len;i++){
        struct stat tm1;
        stat(str[i],&tm1);
    for(int d=i+1;d<len;d++){
        struct stat tm2;
        stat(str[d],&tm2);
    if(tm1.st_mtim.tv_sec<tm2.st_mtim.tv_sec){
            char* strm=str[i];
            str[i]=str[d];
            str[d]=strm;
             stat(str[i],&tm1);
        }else if(tm1.st_mtim.tv_sec==tm2.st_mtim.tv_sec){
        if(tm1.st_mtim.tv_nsec<=tm2.st_mtim.tv_nsec){
        char* strm=str[i];
            str[i]=str[d];
            str[d]=strm;
            stat(str[d],&tm2);
        }
        }
      }
    }
}
void sorting(char** str,int len){
    char* string;
    int i,j;
    for(i=0;i<len-1;i++){
        for(j=i+1;j<len;j++){
            if(strcmp(str[i],str[j])>0){
                string=str[i];
                str[i]=str[j];
                str[j]=string;
            }
        }
    }
}
void come_code_a(char* str,bool swi_tt,bool swi_aa) {
    DIR* folder;
    folder=opendir(str);
    if(folder == NULL) {
        printf("my_ls: cannot access '%s': No such file or directory",str);
        exit(EXIT_FAILURE);
    }
    int d=0;
    int size=10;
    char** files=malloc(size*sizeof(char*));
    if(files==NULL){
        printf("my_ls: memory allocation error");
        exit(EXIT_FAILURE);
    }
    struct dirent* read;
    while((read=readdir(folder)) != NULL){
        if( swi_aa||(read->d_name[0] != '.')){
            if(d==size){
                size*=2;
                files=realloc(files,size*sizeof(char*));
                if(files==NULL){
                printf("my_ls: memory allocation error.");
                exit(EXIT_FAILURE);
                }
            }
            files[d]=malloc(strlen(read->d_name)+1);
            strcpy(files[d], read->d_name);
            d++;
        }
    }
    if(swi_tt){
        time_sort(files,d);
    }else{
        sorting(files,d);
    }
    print_all(files,d,swi_aa);
    for(int i=0;i<d;i++){
        free(files[i]);
    }
    free(files);
    closedir(folder);
}
void come_code(int argc,char* argv[]) {
    int opt;
    bool swi_ttt=false;
    bool swi_aaa=false;
    while((opt=getopt(argc,argv,"at"))!=-1){
        switch(opt){
            case'a':
            swi_aaa=true;
            break;
            case't':
            swi_ttt=true;
            break;
            default:
            printf("Usage: %s [-a] [-t] [directory...]\n",argv[0]);
        }
    }
    if(optind>=argc){
        come_code_a(".",swi_ttt,swi_aaa);
    }else{
        while(optind<argc){
            come_code_a(argv[optind],swi_ttt,swi_aaa);
            optind++;
        }
    }
}
int main(int argc, char* argv[]){
    come_code(argc,argv);
}