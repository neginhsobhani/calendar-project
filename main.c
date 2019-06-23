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
////////function prototypes
struct task* create_node();
void add_node(struct task *taskList, struct task *new_task);
void addTask(struct task *taskList);
////////main
int main() {
    struct task *list = (struct task *) malloc(sizeof(struct task));
    list->next = NULL;
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
void addTask(struct task *taskList) {
    struct task *new_node = create_node();
    add_node(taskList,new_node);
}



