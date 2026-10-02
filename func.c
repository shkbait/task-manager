#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

int save_task( struct task *tasks,size_t len, const char *filename){
            if(tasks==NULL) return 0;
            FILE *file_w =fopen(filename,"w");
            if(file_w==NULL){
                printf("Opening error\n");
                return 0;
            }
            for(size_t i=0;i<len;i++){
                fprintf(file_w,"%d;%s;%d;%d\n", 
                    tasks[i].id, 
                    tasks[i].title, 
                    tasks[i].priority, 
                    tasks[i].completed);

            }
            fclose(file_w);
            printf("Successfully saved to tasks.txt\n");
            return 1;
}

void task_menu(){
        printf("===== TASK MANAGER =====\n");
        printf("1. Add task\n2.Show all tasks\n3. Find task\n4.Complete task\n5. Delete task\n6.Save task\n7.Exit\n");
        printf("\nWARNING!\nPlease save your tasks using 6. Save task\n");
}

// struct task* add_task(struct task *tasks,size_t *len,size_t *size){
//                 if(*len>=*size){
//                 size_t new_size=*size+2;
//                 struct task *new_tasks=realloc(tasks,new_size*sizeof(struct task));
//                 if(new_tasks==NULL){
//                     printf("memmory error\n");
//                     return tasks;
//                 }
//                 tasks=new_tasks;
//                 *size=new_size;
//             }
//             tasks[*len].id=(int)(*len+1);
//             tasks[*len].completed=0;
//             tasks[*len].priority=1;

//             printf("Enter title\n");
//             fgets(tasks[*len].title,sizeof(tasks[*len].title),stdin);
//             tasks[*len].title[strcspn(tasks[*len].title,"\n")]='\0';
//             printf("Success\n");
//             (*len)++;
//             return tasks;
// }
int add_task(struct task **tasks,size_t *len,size_t *size){
                if(*len>=*size){
                size_t new_size=*size+2;
                struct task *new_tasks=realloc(*tasks,new_size*sizeof(struct task));
                if(new_tasks==NULL){
                    printf("memmory error\n");
                    return 0;
                }
                *tasks=new_tasks;
                *size=new_size;
            }
            (*tasks)[*len].id=(int)(*len+1);
            (*tasks)[*len].completed=0;
            (*tasks)[*len].priority=1;

            printf("Enter title\n");
            fgets((*tasks)[*len].title,sizeof((*tasks)[*len].title),stdin);
            (*tasks)[*len].title[strcspn((*tasks)[*len].title,"\n")]='\0';
            printf("Success\n");
            (*len)++;
            return 1;
}

struct task* import_task(struct task *tasks,size_t *len,const char *filename,size_t *size){
    FILE *file = fopen(filename,"r");
    if(file==NULL){
        return tasks;
    }
        
        int t_id,t_priority,t_completed;
        char t_title[256];
        while(fscanf(file, "%d;%255[^;];%d;%d\n",&t_id,t_title,&t_priority,&t_completed)==4){
            if(*len>=*size){
                size_t new_size=*size+2;
                struct task *new_tasks=realloc(tasks,new_size*sizeof(struct task));
                if(new_tasks==NULL){
                    printf("Memmory error\n");
                    return tasks;
                    
                }
                tasks=new_tasks;
                *size=new_size;
            }
            tasks[*len].id = t_id;
            strcpy(tasks[*len].title, t_title);
            tasks[*len].priority = t_priority;
            tasks[*len].completed = t_completed;
            (*len)++;
        }
        fclose(file);
        if(*len>0){
            printf("Successfully imported %zu tasks from 'tasks.txt'\n", *len);
        }
        return tasks;
    }
