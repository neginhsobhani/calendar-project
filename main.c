#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

struct task {
    int isHead;
    char taskName[50];
    int startTime;
    int endTime;
    struct task *next;
};

///////function prototypes

struct task *create_node();

void add_node(struct task *taskList, struct task *new_task);

void addTask(struct task *week[]);

int checkTaskTime(struct task *week[], int day, struct task *new_task);

int checkTaskName(struct task *week[], int day, struct task *new_task);

void showTask(struct task *week[]);

void showDay(struct task *week[], int day);

void save(struct task *week[], char*name);

struct task *create_node_lode(struct task node);

struct task **load(struct task *loaded_week[],char *name);

void delete_node(struct task *week[],struct task *deleted,int day);

void delete(struct task *week[]);

void modify_node(struct task *week[],struct task *new_task,int day);

struct task *theModify(struct task *week[]);

void add_node_order(struct task *taskList,struct task *next_task,struct task *new_task);

void add_timeOrder(struct task *week[],struct task *new_task,int day);

void search(struct task *week[]);

void showInstruction();

////////main

int main() {
    struct task **week;
    week = calloc(sizeof(struct task), 7);
    for (int i = 0; i < 7; i++) {
        week[i] = (struct task *) malloc(sizeof(struct task));
        week[i]->next = NULL;
        week[i]->isHead = 1;
    }
    char userName[20];
    printf(" ---------------\n");
    printf("|Enter your name|\n");
    printf(" ---------------\n");
    gets(userName);
    printf(" -----------------------------\n");
    printf("       Welcome %s           \n",userName);
    printf(" -----------------------------\n");
    while (1) {
        printf("\n");
        printf("< [1]....Instruction >\n");
        printf("< [2]....New task    >\n");
        printf("< [3]....Delete task >\n");
        printf("< [4]....Search      >\n");
        printf("< [5]....Modify      >\n");
        printf("< [6]....Show task   >\n");
        printf("< [7]....Save        >\n");
        printf("< [8]....Load        >\n");
        printf("< [9]....Quit        >\n");

        char key = getch();
        getch();if(key == '1'){
            showInstruction();
        }else if (key == '2') {
            addTask(week);
        } else if (key == '3') {
            delete(week);
        }else if(key =='4') {
            search(week);
        }else if(key == '5'){
            theModify(week);
        }else if (key == '6') {
            showTask(week);
        } else if (key == '7') {
            save(week,userName);
        } else if (key == '8') {
            week = load(week,userName);
        }else if(key == '9') {
            printf(" -------------------------\n");
            printf("       Bye %s           \n",userName);
            printf(" -------------------------\n");
            break;
        }
    }
    return 0;
}

struct task *create_node() { //creates one task
    struct task *newtask = (struct task *) malloc(sizeof(struct task));
    newtask->isHead = 0;
    printf(" ----------------------------\n");
    printf("| Enter the name of the task |\n");
    printf(" ----------------------------\n");
    scanf("%s", newtask->taskName);
    printf(" ----------------------\n");
    printf("| Enter the start time |\n");
    printf(" ----------------------\n");
    scanf("%d", &newtask->startTime);
    printf(" --------------------\n");
    printf("| Enter the end time |\n");
    printf(" --------------------\n");
    scanf("%d", &newtask->endTime);
    return newtask;
}

void add_node(struct task *taskList, struct task *new_task) {
    struct task *current = taskList;
    while (current->next != NULL) {
        current = current->next;
    }
    new_task->next = current->next;
    current->next = new_task;
}

void addTask(struct task *week[]) {
    int day;
    printf(" ---------------\n");
    printf("| Enter the day |\n");
    printf(" ---------------\n");
    scanf("%d", &day);
    struct task *new_node = create_node();
    if (week[day]->next != NULL) {
        int time = checkTaskTime(week, day, new_node);
        int name = checkTaskName(week, day, new_node);
        if (time == 1 && name==1) {
            printf(" -------------------------------------\n");
            printf("| Conflict with both time and name !! |\n");
            printf(" -------------------------------------\n\n");
        }else if (name == 1) {
            printf(" --------------------\n");
            printf("| Conflict with name |\n");
            printf(" --------------------\n\n");
        }else if (time==1){
            printf(" --------------------\n");
            printf("| Conflict with time |\n");
            printf(" --------------------\n\n");
        }else{
            add_timeOrder(week,new_node,day);
            printf(" -----------------------------------------------\n");
            printf("| There is no error and the new task is created |\n");
            printf(" -----------------------------------------------\n\n");
        }
    } else {
       add_timeOrder(week,new_node,day);
        printf(" -----------------------------------------------\n");
        printf("| There is no error and the new task is created |\n");
        printf(" -----------------------------------------------\n\n");
    }
}

int checkTaskTime(struct task *week[], int day, struct task *new_task) {
    struct task *current = week[day];
    while (current != NULL) {
        if (((current->startTime < new_task->startTime) && (new_task->startTime < current->endTime)) ||
            ((new_task->startTime <= current->startTime) && (current->startTime < new_task->endTime)) ||
                (current->startTime==new_task->startTime && current->endTime==new_task->endTime)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int checkTaskName(struct task *week[], int day, struct task *new_task) {
    struct task *current = week[day];
    while (current != NULL) {
        if (strcmp(current->taskName, new_task->taskName) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void showTask(struct task *week[]) {
    printf(" ----------------\n");
    printf("| 0 (Saturday):  |");
    showDay(week, 0);
    printf("\n");
    printf(" ----------------\n");
    printf("| 1 (Sunday):    |");
    showDay(week, 1);
    printf("\n");
    printf(" ----------------\n");
    printf("| 2 (Monday):    |");
    showDay(week, 2);
    printf("\n");
    printf(" ----------------\n");
    printf("| 3 (Tuesday):   |");
    showDay(week, 3);
    printf("\n");
    printf(" ----------------\n");
    printf("| 4 (Wednesday): |");
    showDay(week, 4);
    printf("\n");
    printf(" ----------------\n");
    printf("| 5 (Thursday):  |");
    showDay(week, 5);
    printf("\n");
    printf(" ----------------\n");
    printf("| 6 (Friday):    |");
    showDay(week, 6);
    printf("\n");
    printf(" ----------------\n");

}

void showDay(struct task *week[], int day) { //shows each task
    struct task *current = week[day]->next;
    while (current != NULL) {
        printf(" \"%s\" (From: %d,To: %d)", current->taskName, current->startTime, current->endTime);
        if(current->next!=NULL){
            printf(" ->");
        }
        current = current->next;
    }
}

void save(struct task *week[], char*name) {
    char out[150]=".\\";
    strcat(out,name);
    strcat(out,".bin");
    FILE *fpsave = fopen(out, "wb");
    if (fpsave == NULL) {
        printf(" -------------------\n");
        printf("| Can not open file |\n");
        printf(" -------------------\n\n");
        return;
    }
    for (int i = 0; i < 7; i++) {
        struct task *current = week[i];
        while (current != NULL) {
            fwrite(current, sizeof(struct task), 1, fpsave);
            current = current->next;
        }
    }
    printf(" --------------------\n");
    printf("| Changes were saved |\n");
    printf(" --------------------\n\n");
    fclose(fpsave);
}

struct task *create_node_lode(struct task node) {
    struct task *nn = (struct task *) malloc(sizeof(struct task));
    nn->isHead = 0;
    strcpy(nn->taskName, node.taskName);
    nn->startTime = node.startTime;
    nn->endTime = node.endTime;
    nn->next = NULL;
    return nn;
}

struct task **load(struct task *loaded_week[7],char *name) {
    char out[150]=".\\";
    strcat(out,name);
    strcat(out,".bin");
    FILE *fpload = fopen(out,"rb");
    if (fpload == NULL) {
        printf(" -------------------\n");
        printf("| Can not open file |\n");
        printf(" -------------------\n\n");
        return NULL;
    }
    int i = 0;
    struct task *current;
    while (1) {
        struct task *load = (struct task *) malloc(sizeof(struct task));
        fread(load, sizeof(struct task), 1, fpload);
        if (feof(fpload)) {
            break;
        }
        if (load->isHead == 1) {
            loaded_week[i]->next = NULL;
            current = loaded_week[i];
            i++;
        } else {
            current->next = create_node_lode(*load);
            current = current->next;
        }
    }
    while (i < 7) {
        struct task *list = (struct task *) malloc(sizeof(struct task));
        list->next = NULL;
        list->isHead = 1;
        loaded_week[i] = list;
        i++;
    }
    printf(" -----------------\n");
    printf("| Data Was Loaded |\n");
    printf(" -----------------\n\n");
    fclose(fpload);
    return loaded_week;
}

void delete_node(struct task *week[],struct task *deleted,int day){
   struct task *current=week[day];
   while(current->next!=deleted){
       current=current->next;
   }
   struct task * temp=deleted->next;
   free(deleted);
   current->next=temp;
}

void delete(struct task *week[]){
    int day;
    char name[50];
    printf(" ----------------------------------------------\n");
    printf("| Enter the day of the task you want to delete |\n");
    printf(" ----------------------------------------------\n");
    scanf("%d",&day);
    printf(" -----------------------------------------------\n");
    printf("| Enter the name of the task you want to delete |\n");
    printf(" -----------------------------------------------\n");
    scanf("%s",name);
    struct task *current=week[day]->next;
    if(week[day]->next!=NULL) {
        while (current != NULL) {
            if (strncmp(current->taskName, name, strlen(name)) == 0) {
                delete_node(week, current, day);
                printf(" ------------------\n");
                printf("| Task was deleted |\n");
                printf(" ------------------\n\n");

                return;
            }
            current=current->next;
        }
        printf(" --------------------------------------\n");
        printf("| This task does not exist in this day |\n");
        printf(" --------------------------------------\n\n");

    }else {
        printf(" ------------------------------\n");
        printf("| There is no task in this day |\n");
        printf(" ------------------------------\n\n");
    }
}

void modify_node(struct task *week[],struct task *new_task,int day){
    struct task *current=week[day];
    while(current!=new_task){
        current=current->next;
    }
    struct task *modified=new_task;
    printf(" ------------------------------------------\n");
    printf("| Task found ||| Enter the new information |\n");
    printf(" ------------------------------------------\n\n");
    printf(" ----------------------------\n");
    printf("| Enter the name of the task |\n");
    printf(" ----------------------------\n");
    scanf("%s",modified->taskName);
    printf(" ----------------------------------\n");
    printf("| Enter the start time of the task |\n");
    printf(" ----------------------------------\n");
    scanf("%d",&modified->startTime);
    printf(" --------------------------------\n");
    printf("| Enter the end time of the task |\n");
    printf(" --------------------------------\n");
    scanf("%d",&modified->endTime);

}

struct task *theModify(struct task *week[]){
    int day;
    char name[50];
    printf(" ----------------------------------------------\n");
    printf("| Enter the DAY of the task you want to modify |\n");
    printf(" ----------------------------------------------\n");

    scanf("%d",&day);
    printf(" -----------------------------------------------\n");
    printf("| Enter the NAME of the task you want to modify |\n");
    printf(" -----------------------------------------------\n");

    scanf("%s",name);
    struct task *current=week[day]->next;
        if(week[day]->next!=NULL){
            while(current!=NULL) {
                if (strncmp(current->taskName, name, strlen(name)) == 0) {
                    struct task *new_task = current;
                    modify_node(week, new_task, day);
                    printf(" -------------------\n");
                    printf("| Task was modified |\n");
                    printf(" -------------------\n\n");


                    return NULL;
                }
                current = current->next;
            }
            printf(" --------------------------------------\n");
            printf("| This task does not exist in this day |\n");
            printf(" --------------------------------------\n\n");
        }else{
            printf(" ------------------------------\n");
            printf("| There is no task in this day |\n");
            printf(" ------------------------------\n\n");
        }
}

void add_node_order(struct task *taskList,struct task *greater,struct task *new_task){
    struct task *current=taskList;
        while(current->next!=greater){
            current=current->next;
        }
        new_task->next=current->next;
        current->next=new_task;
}

void add_timeOrder(struct task *week[],struct task *new_task,int day){
    struct task *current=week[day]->next;
        if(week[day]->next!=NULL){
            while(current!=NULL){
                if(new_task->startTime < current->startTime){
                    add_node_order(week[day],current,new_task);
                    return;
                }else{
                    current=current->next;
                }
            }
            add_node(week[day], new_task);
        }else{
            add_node(week[day], new_task);
        }
}

void search(struct task *week[]){
    int found=0;
        char name[50];
    printf(" ----------------------------\n");
    printf("| Enter the name of the task |\n");
    printf(" ----------------------------\n");
        scanf("%s",name);
        for(int i=0;i<7;i++){
            struct task *current=week[i]->next;
            if(week[i]->next!=NULL){
                while(current!=NULL){
                    if(strcmp(name,current->taskName)==0){
                        printf("*");
                        switch(i){
                            case 0:
                                printf(" Saturday");
                                break;
                            case 1:
                                printf(" Sunday");
                                break;
                            case 2:
                                printf(" Monday");
                                break;
                            case 3:
                                printf(" Tuesday");
                                break;
                            case 4:
                                printf(" Wednesday");
                                break;
                            case 5:
                                printf(" Thursday");
                                break;
                            case 6:
                                printf(" Friday");
                                break;
                            default:
                                break;
                        }
                        printf(" -> ( From %d , To %d ) \n",current->startTime,current->endTime);
                        printf(" -------------------------------\n");
                        found++;
                    }current=current->next;
                }
            }
        }if(found==0) {
        printf(" ---------------------------------------\n");
        printf("| This task does not exist in this week |\n");
        printf(" ---------------------------------------\n\n");
    }
    }

void showInstruction(){
    printf(" ----------------------------------------------------------------------\n");
    printf("|                |||A SMALL GUID TO THIS CALENDAR|||                    |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| NEW TASK->Lets you add new task to your weekly tasks.                 |\n");
    printf("| You need to enter NAME,START TIME and END TIME of the task.           |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| DELETE->Lets you delete any of your tasks.                            |\n");
    printf("| You need to enter the DAY and the NAME of the task.                   |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| SEARCH->Lets you find the day(s) and the time of a specific task.     |\n");
    printf("| You need to enter the NAME of the task.                               |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| MODIFY->Lets you change the name or the time of a task.               |\n");
    printf("| You need to enter the NAME,START TIME and END TIME of the task.       |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| SHOW TASK->Shows you all of the task in the week.                     |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| SAVE->Lets you save the changes you have made to your weekly tasks.   |\n");
    printf("| !!! Remember to save changes before quiting the program !!!           |\n");
    printf(" ----------------------------------------------------------------------\n");
    printf("| LOAD->Helps you load the file that was saved with your name.          |\n");
    printf("| If you want to make any changes to your own weekly planner            |\n");
    printf("| please first choose load option.                                      |\n");
    printf("| !!! If you save the changes to your file without loading it,          |\n");
    printf("| the last data will be removed,BE CAREFUL !!!                          |\n");
    printf(" ----------------------------------------------------------------------\n");
}


