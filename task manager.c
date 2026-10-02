#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
    size_t size=2;
    size_t len=0;
    struct task *tasks = malloc(size*sizeof(struct task));
    if(tasks==NULL){
        printf("memmory error\n");
        return 1;
    }
    tasks=import_task(tasks,&len, "/Users/a1111/Documents/учеба/C/tasks.txt", &size);
    // FILE *file = fopen("/Users/a1111/Documents/учеба/C/tasks.txt","r");
    // if(file!=NULL){
    //     int t_id,t_priority,t_completed;
    //     char t_title[256];
    //     while(fscanf(file, "%d;%255[^;];%d;%d\n",&t_id,t_title,&t_priority,&t_completed)==4){
    //         if(len>=size){
    //             size_t new_size=size+2;
    //             struct task *new_tasks=realloc(tasks,new_size*sizeof(struct task));
    //             if(new_tasks==NULL){
    //                 printf("Memmory error\n");
    //                 break;
                    
    //             }
    //             tasks=new_tasks;
    //             size=new_size;
    //         }
    //         tasks[len].id = t_id;
    //         strcpy(tasks[len].title, t_title);
    //         tasks[len].priority = t_priority;
    //         tasks[len].completed = t_completed;
    //         len++;
    //     }
    //     fclose(file);
    //     if(len>0){
    //         printf("Successfully imported %zu tasks from 'tasks.txt'\n", len);
    //     }
    // }
    while(1){
        task_menu();
        int selector;
        if(scanf("%d",&selector)!=1){
            break;
        }
        getchar();
        if(selector==7){
            printf("...\n");
            break;
        }else if(selector==1){
            // if(len>=size){
            //     size_t new_size=size+2;
            //     struct task newdata=(realloc(tasks,new_size * sizeof(struct task)));
            //     if(newdata=NULL){
            //         printf("memory error\n");
            //         continue;
            //     }
            //     tasks=newdata;
            //     size=new_size;
            // }
            printf("\nChoose: %d\n",selector);
            // if(len>=size){
            //     size_t new_size=size+2;
            //     struct task *new_tasks=realloc(tasks,new_size*sizeof(struct task));
            //     if(new_tasks==NULL){
            //         printf("memmory error\n");
            //         continue;
            //     }
            //     tasks=new_tasks;
            //     size=new_size;
            // }
            // tasks[len].id=(int)(len+1);
            // tasks[len].completed=0;
            // tasks[len].priority=1;

            if(add_task(&tasks,&len,&size)){
                save_task(tasks,len,"/Users/a1111/Documents/учеба/C/tasks.txt");
            }else{
                printf("Task was not added due to memory error.\n");
            }
            // printf("Enter title\n");
            // fgets(tasks[len].title,sizeof(tasks[len].title),stdin);
            // tasks[len].title[strcspn(tasks[len].title,"\n")]='\0';
            // printf("Success\n");
            // len++;
            // tasks=add_task(tasks,&len,&size);
            // save_task(tasks,len,"/Users/a1111/Documents/учеба/C/tasks.txt");

            // for(size_t i=0;i<1;i++){
            //     // data = append(data, &len, &size,fgets(data[i],MAXLEN,stdin));
            //     if (data[i]!=NULL){
            //         free(data[i]);
            //     }
            //     data[i]=(char*)malloc(MAXLEN*sizeof(char));
            //     if(data[i]==NULL){
            //         printf("memory error\n");
            //         return 1;
            //     }
            //     printf("enter task %zu:",i+1);
            //     fgets(data[i],MAXLEN,stdin);
            //     data[i][strcspn(data[i],"\n")]='\0';
            // }

            

        }else if(selector==2){
            printf("\n");
            printf("all tasks:\n");
            if(len==0){
                printf("Empty\n");
            }else{
                for(size_t i=0;i<len;i++){
                    printf("ID: %d | Title: %s | Priority: %d | Status: %s\n",
                           tasks[i].id,
                           tasks[i].title,
                           tasks[i].priority,
                           tasks[i].completed ? "Completed" : "In Progress");
                }
            }
        }else if(selector==3){
            printf("Enter task title for search\n");
            // fgets(tasks[len].title,sizeof(tasks[len].title),stdin);
            // tasks[len].title[strcspn(tasks[len].title,"\n")]='\0';
            char searchx[256];
            int found_count=0;
            fgets(searchx,sizeof(searchx),stdin);
            searchx[strcspn(searchx,"\n")]='\0';
            for(size_t i=0;i<len;i++){
                if(strstr(tasks[i].title, searchx)!=NULL){
                    printf("ID: %d | Title: %s | Priority: %d | Status: %s\n",
                           tasks[i].id,
                           tasks[i].title,
                           tasks[i].priority,
                           tasks[i].completed ? "Completed" : "In Progress");
                           found_count++;
                }
                
            }
            if (found_count==0){
                printf("No matching '%s'\n",searchx);
            }

        }else if(selector==4){
            // printf("Enter task title for complete\n");
            char compsearch[256];
            int compsearch_count=0;
            // fgets(compsearch,sizeof(compsearch),stdin);
            // compsearch[strcspn(compsearch,"\n")]='\0';
            for(size_t i=0;i<len;i++){
                    printf("ID: %d | Title: %s | Priority: %d | Status: %s\n",
                           tasks[i].id,
                           tasks[i].title,
                           tasks[i].priority,
                           tasks[i].completed ? "Completed" : "In Progress");
            }
            printf("Enter task ID to continue\n");
            int comp_id;
            if (scanf("%d", &comp_id) != 1) {
                getchar();
                printf("Incorrect ID\n");
                continue;
            }
            getchar();

            int tfound=0;
            for(size_t i=0;i<len;i++){
                char select;
                if((comp_id)==tasks[i].id){
                    tfound=1;
                    printf("complete this task? y/n\n");
                    
                    
                    if(scanf(" %c",&select)!= 1){
                        getchar();
                        printf("Incorrect command\n");
                    }else {
                        getchar(); 
                        if(select=='N'||select=='n'){
                            tasks[i].completed=0;
                        }else if(select=='Y'||select=='y'){
                            tasks[i].completed=1;
                        }else{
                            printf("Incorrect command\n");
                        }
                    }
                    break;

                }
            }
            if(!tfound){
                printf("ID not found\n");
            }
            save_task(tasks,len,"/Users/a1111/Documents/учеба/C/tasks.txt");

        }else if(selector==6){
            if(len==0){
                printf("Empty\n");
                continue;
            }
            FILE *file_w =fopen("/Users/a1111/Documents/учеба/C/tasks.txt","w");
            if(file_w==NULL){
                printf("Opening error\n");
                continue;
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
        }else if(selector==5){
            printf("\nall tasks:\n");
            if(len == 0){
                printf("No tasks to delete.\n");
                continue;
            }
            for(size_t i=0; i<len; i++){
                printf("ID: %d | Title: %s\n", tasks[i].id, tasks[i].title);
            }
            printf("\nEnter ID to delete\n");
            int delid;
            if(scanf("%d",&delid)!=1){
                getchar();
                printf("Incorrect ID\n");
                continue;
            }
            getchar();
            int found_index = -1;
            for(size_t i=0; i<len; i++){
                if(tasks[i].id == delid){
                    found_index = (int)i;
                    break;
                }
            }//а это что сука
            if(found_index == -1){
                printf("ID not found\n");
            } else {
                for(size_t i = (size_t)found_index; i < len - 1; i++){
                    tasks[i] = tasks[i + 1];
                }
                len--;
                printf("Task deleted successfully!\n");
                
                for(size_t i = 0; i < len; i++){
                    tasks[i].id = (int)(i + 1);
                }
                save_task(tasks, len, "/Users/a1111/Documents/учеба/C/tasks.txt");
            }
        }

    }// end of while
    // for(int i=0;i<size;i++){
    //     if(data[i]!=NULL){
    //     free(data[i]);
    //     }
    // } 
    free(tasks); 
    return 0;    
}



