#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void viewing() {
    printf("The story so far:\n");
    FILE *dir = fopen("story.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    if (dir < 0){
        printf("File: %s\n", strerror(errno));
    }
    else{
        while ((read = getline(&line, &len, dir)) != -1) {
            printf("%s", line);
        }
    }
    fclose(dir);
}

void creating() {
    union semun {
        int val;
        struct semid_ds * buf;
        unsigned short * array;
        struct seminfo * __buf;
    } sem;
    key_t key = ftok("control.c", 'E');
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    printf("Semaphore created\n");
    if (semid < 0){
        printf("Semaphore: %s\n", strerror(errno));
    }
    else{
        sem.val = 1;
        if (semctl(semid, 0, SETVAL, sem.val) < 0){
            printf("Shared memory: %s\n", strerror(errno));
        }
    }
    printf("Shared memory created\n");
    FILE *dir = fopen("story.txt", "w");
    if (dir < 0){
        printf("File: %s\n", strerror(errno));
    }
    fclose(dir);
    printf("File created\n");
}

void removing() {
    key_t key = ftok("control.c", 'E');
    viewing();
    int semid = semget(key, 1, 0);
    if (semid < 0){
        printf("Semaphore: %s\n", strerror(errno));
    }
    semctl(semid, 0, IPC_RMID);
    printf("Semaphore removed\n");
    semctl(semid, 0, IPC_RMID);
    printf("Shared memory removed\n");
    int rem = remove("story.txt");
    if (rem < 0){
        printf("File: %s\n", strerror(errno));
    }
    printf("File removed\n");
}

int main(int argc, char *argv[]){
    if (argc == 2){
        if (!strcmp(argv[1], "-c")){
            creating();
        }
        if (!strcmp(argv[1], "-r")){
            removing();
        }
        if (!strcmp(argv[1], "-v")){
            viewing();
        }
    }
}