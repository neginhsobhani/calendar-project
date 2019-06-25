#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

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

void save(struct task *week[]);

struct task *create_node_lode(struct task node);

struct task **load(struct task *loaded_week[]);

////////main

int main() {
    struct task **week;
    week = calloc(sizeof(struct task), 7);
    for (int i = 0; i < 7; i++) {
        week[i] = (struct task *) malloc(sizeof(struct task));
        week[i]->next = NULL;
        week[i]->isHead = 1;
    }
    while (1) {
        printf("[1] new task\n[2] show task\n[3] save\n[4] load\n[5] quit\n");
        char key = getch();
        getch();
        if (key == '1') {
            addTask(week);
        } else if (key == '2') {
            showTask(week);
        } else if (key == '3') {
            save(week);
        } else if (key == '4') {
            week = load(week);
        } else if (key == '5') {
            break;
        }
    }
    return 0;
}

struct task *create_node() { //creates one task
    struct task *newtask = (struct task *) malloc(sizeof(struct task));
    newtask->isHead = 0;
    printf("Enter the name of the task\n");
    scanf("%s", newtask->taskName);
    printf("Enter the start time\n");
    scanf("%d", &newtask->startTime);
    printf("Enter the end time\n");
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
    printf("Enter the day\n");
    scanf("%d", &day);
    struct task *new_node = create_node();
    if (week[day]->next != NULL) {
        int time = checkTaskTime(week, day, new_node);
        int name = checkTaskName(week, day, new_node);
        printf("%d", time);
        if (time == 1) {
            printf("Conflict with time\n");
        } else if (name == 1) {
            printf("Conflict with name\n");
        } else {
            add_node(week[day], new_node);
            printf("There is no error and the new task is created\n");
        }
    } else {
        add_node(week[day], new_node);
        printf("There is no error and the new task is created\n");
    }
}

int checkTaskTime(struct task *week[], int day, struct task *new_task) {
    struct task *current = week[day];
    while (current != NULL) {
        if (((current->startTime < new_task->startTime) && (new_task->startTime < current->endTime)) ||
            ((new_task->startTime <= current->startTime) && (current->startTime < new_task->endTime))) {
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
    printf("0 (Saturday):");
    showDay(week, 0);
    printf("\n");
    printf("1 (Sunday): ");
    showDay(week, 1);
    printf("\n");
    printf("2 (Monday): ");
    showDay(week, 2);
    printf("\n");
    printf("3 (Tuesday): ");
    showDay(week, 3);
    printf("\n");
    printf("4 (Wednesday): ");
    showDay(week, 4);
    printf("\n");
    printf("5 (Thursday): ");
    showDay(week, 5);
    printf("\n");
    printf("6 (Friday): ");
    showDay(week, 6);
    printf("\n");


}

void showDay(struct task *week[], int day) {
    struct task *current = week[day]->next;
    while (current != NULL) {
        printf("%s (From: %d,To: %d)", current->taskName, current->startTime, current->endTime);
        current = current->next;
    }
}

void save(struct task *week[]) {
    FILE *fpsave = fopen(".\\save.bin", "wb");
    if (fpsave == NULL) {
        printf("Can not open file\n");
        return;
    }
    for (int i = 0; i < 7; i++) {
        struct task *current = week[i];
        while (current != NULL) {
            fwrite(current, sizeof(struct task), 1, fpsave);
            current = current->next;
        }
    }
    printf("Changes were saved\n");
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

struct task **load(struct task *loaded_week[7]) {
    FILE *fpload = fopen(".\\save.bin", "rb");
    if (fpload == NULL) {
        printf("Can not open file\n");
        return NULL;
    }
    int i = 0;
    struct task *current;
    while (true) {
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
    }
    printf("Data Was Loaded\n");
    fclose(fpload);
    return loaded_week;
}
