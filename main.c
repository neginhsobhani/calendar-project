#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct task{
    char taskName[100];
    int startTime;
    int endTime;
    struct task *next;
};
struct task *week[7];

struct task* create_node();

int main() {
    for(int i=0;i<7;i++){
        week[i]=NULL;
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
void addTask(){
    int day;
    printf("Enter the day\n");
    scanf("%d",&day);
    struct task *newtask=create_node();
        if(week[day]==NULL){
            week[day] = newtask;
            newtask->next=NULL;
        }else{
            struct task *current=week[day];
            while(current->next!=NULL){
                current=current->next;
            }
            current->next=newtask;
            newtask->next=NULL;
        }
}


