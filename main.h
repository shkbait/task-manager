#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <stddef.h>
struct task{
    int id;
    char title[256];
    int priority;
    int completed;

};

int save_task( struct task *tasks,size_t len, const char *filename);

void task_menu();

int add_task(struct task **tasks, size_t *len, size_t *size);


// struct task* add_task(struct task *tasks,size_t *len,size_t *size);

struct task* import_task(struct task *tasks,size_t *len,const char *filename,size_t *size);

#endif