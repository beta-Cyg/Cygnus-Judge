#include<cstdio>
#include<cstring>
#include"project_info.h"
using namespace std;

int main(int argc,char** args){
    if(strcmp(args[argc-1],"start")==0){
        FILE* type_output=nullptr;
        int failed_cnt=0;
        while(type_output==nullptr){
            type_output=fopen(USER"/.judge/running_type","w");
            failed_cnt++;
            if(failed_cnt!=1)
                printf("%d try failed\n",failed_cnt-1);
        }
        fprintf(type_output,"1");
    }
    else if(strcmp(args[argc-1],"stop")==0){
        FILE* type_output=nullptr;
        int failed_cnt=0;
        while(type_output==nullptr){
            type_output=fopen(USER"/.judge/running_type","w");
            failed_cnt++;
            if(failed_cnt!=1)
            printf("%d try failed\n",failed_cnt-1);
        }
        fprintf(type_output,"0");
    }
    else if(strcmp(args[argc-1],"type")==0){
        FILE* type_output=nullptr;
        int failed_cnt=0;
        while(type_output==nullptr){
            type_output=fopen(USER"/.judge/running_type","r");
            failed_cnt++;
            if(failed_cnt!=1)
                printf("%d try failed\n",failed_cnt-1);
        }
        int running_type;
        fscanf(type_output,"%d",&running_type);
        printf("%d\n",running_type);
    }

    return 0;
}