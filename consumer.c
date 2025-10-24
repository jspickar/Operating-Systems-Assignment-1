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

    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    table = mmap(0, sizeof(SharedTable), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *mutex = sem_open(SEM_MUTEX, 0);
    sem_t *empty = sem_open(SEM_EMPTY, 0);
    sem_t *full  = sem_open(SEM_FULL, 0);

    while (1) {
        sem_wait(full);
        sem_wait(mutex);

        // Critical section
        int item = table->buffer[table->count - 1];
        table->count--;
        printf("Consumer: consumed item %d (count=%d)\n", item, table->count);

        sem_post(mutex);
        sem_post(empty);

        sleep(2);
    }

    return 0;
}
