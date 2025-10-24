#ifndef SHARED_H
#define SHARED_H

#define TABLE_SIZE 2   // The table can hold up to 2 items at a time

// Shared memory structure
typedef struct {
    int buffer[TABLE_SIZE];  // the items on the table
    int count;               // how many items are currently on the table
} SharedTable;

#endif
