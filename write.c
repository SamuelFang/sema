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

int main() {
    // not sure why not working
    // key_t key = ftok("write.c", 'E');
    // int semid = semget(key, 1, 0666 | IPC_CREAT);
    // if (semid < 0){
        // printf("Semaphore: %s\n", strerror(errno));
    // }
    // struct sembuf sops;
    // sops.sem_num = 0;
    // sops.sem_op = -1;
    // semop(semid, &sops, 1);
    // int shmid = shmget(key, 256, 0);
    int dir = open("story.txt", O_RDWR | O_APPEND,0644);
    if (dir < 0){
        printf("File: %s\n", strerror(errno));
    }
    // shmid = shmget(key,256, 0666 | IPC_CREAT);
    // int *len = shmat(shmid,0,0);
    // fseek(dir, -1*(*len), SEEK_END);
    // char prev[256];
    // read(dir, prev, *len);
    // printf("The story so far: %s\n", prev);
    char line[256];
    printf("Your addition: ");
    fgets(line, 256, stdin);
    printf("\n");
    write(dir, line, strlen(line));
    close(dir);
    // sops.sem_op = 1;
    // semop(semid, &sops, 1);
    return 0;
}