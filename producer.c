#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include "shared.h"

#define SHM_NAME "/table"
#define SEM_MUTEX "/sem_mutex"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL  "/sem_full"

int main() {
    int shm_fd;
    SharedTable *table;

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(SharedTable));
    table = mmap(0, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    table->count = 0;

    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, TABLE_SIZE);
    sem_t *full  = sem_open(SEM_FULL,  O_CREAT, 0666, 0);

    int item = 1;
    while (1) {
        sem_wait(empty);
        sem_wait(mutex);

        // Critical section
        table->buffer[table->count] = item;
        table->count++;
        printf("Producer: produced item %d (count=%d)\n", item, table->count);

        sem_post(mutex);
        sem_post(full);

        item++;
        sleep(1);
    }

    return 0;
}
