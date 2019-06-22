#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

struct task{
    char taskName[100];
    int startTime;
    int endTime;
    struct task *next;
};
struct task *week[7];
////////function prototypes
struct task* create_node(int day);
void addTask();
int checkTaskName(struct task *newtask,int day);
int checkTaskTime(struct task *newtask,int day);
////////main
int main() {
    for(int i=0;i<7;i++){
        week[i]=NULL;
    }
    addTask();

    return 0;
}
struct task* create_node(int day){ //creates one task
    struct task *newtask=(struct task *)malloc(sizeof(struct task));
    printf("Enter the name of the task\n");
    scanf("%s",newtask->taskName);
    printf("Enter the start time\n");
    scanf("%d",&newtask->startTime);
    printf("Enter the end time\n");
    scanf("%d",&newtask->endTime);
    int name = checkTaskName(newtask,day);
    int time = checkTaskTime(newtask,day);
        if(name==1){
            printf("Conflict with name\n");
        }else if(time==1){
            printf("Conflict with time\n");
        }else {
            printf("There is no error and the new task is created\n");
            return newtask;
        }
}
void addTask(){
    int day;
    printf("Enter the day\n");
    scanf("%d",&day);
    struct task *newtask=create_node(day);
        if(week[day]==NULL){
            week[day] = newtask;
            newtask->next=NULL;
        }else{
            struct task *current=week[day];
            while(current!=NULL){
                current=current->next;
            }
            current->next=newtask;
            newtask->next=NULL;
        }
}

int  checkTaskName(struct task *newtask,int day) {
    struct task *current = week[day];
    while (current != NULL) {
        current = current->next;
        if (strcmp(newtask->taskName, current->taskName) == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}
int checkTaskTime(struct task *newtask,int day){
    struct task *current=week[day];
        while(current!=NULL){
            current=current->next;
            if((current->startTime< newtask->startTime <current->endTime) || (current->startTime< newtask->endTime <current->endTime)){
                return 1;
            }else{
                return 0;
            }
        }
}



