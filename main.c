#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

struct task{
    char taskName[50];
    int startTime;
    int endTime;
    struct task *next;
};

////////function prototypes

struct task* create_node();
void add_node(struct task *taskList, struct task *new_task);
void addTask(struct task *week[]);
int checkTaskTime(struct task *week[],int day,struct task *new_task);
int checkTaskName(struct task *week[],int day, struct task *new_task);


////////main

int main() {
    struct task *week[7];
    for(int i=0;i<7;i++){
        week[i]=(struct task *)malloc(sizeof(struct task));
        week[i]->next=NULL;

    }
    while(1) {
        printf("hello\n");
        addTask(week);
    }
    return 0;
}
struct task* create_node(){ //creates one task
    struct task *newtask=(struct task *)malloc(sizeof(struct task));
    printf("Enter the name of the task\n");
    scanf("%s",newtask->taskName);
    printf("Enter the start time\n");
    scanf("%d",&newtask->startTime);
    printf("Enter the end time\n");
    scanf("%d",&newtask->endTime);
            return newtask;
}
void add_node(struct task *taskList, struct task *new_task){
    struct task *current=taskList;
    while(current->next!=NULL){
        current=current->next;
    }
    new_task->next = current->next;
    current->next = new_task;
}
void addTask(struct task *week[]) {
    int day;
    printf("Enter the day\n");
    scanf("%d",&day);
    struct task *new_node = create_node();
    if(week[day]->next!=NULL) {
        int time = checkTaskTime(week, day, new_node);
        int name = checkTaskName(week, day, new_node);
        if (time == 1) {
            printf("Conflict with time\n");
        } else if (name == 1) {
            printf("Conflict with name\n");
        } else {
            add_node(week[day], new_node);
            printf("There is no error and the new task is created\n");
        }
    }else{
        add_node(week[day], new_node);
        printf("There is no error and the new task is created\n");
    }
}
int checkTaskTime(struct task *week[],int day,struct task *new_task){
    struct task *current=week[day];
        while(current!=NULL){
            if(current->startTime < new_task->startTime < current->endTime || new_task->startTime < current->startTime < new_task->endTime){
                return 1;
            }
            current=current->next;
        }
        return 0;
}
int checkTaskName(struct task *week[],int day, struct task *new_task){
    struct task *current=week[day];
    while(current!=NULL){
        if(strcmp(week[day]->taskName,new_task->taskName)==0){
            return 1;
        }
        current=current->next;
    }
    return 0;
}




