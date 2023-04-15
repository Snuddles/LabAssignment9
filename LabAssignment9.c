#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    // create a next pointer (for linkedlist structure)
    struct RecordType* next;
};

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
    struct RecordType *rPointer;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
    int size = x % tableSize; 
    return size;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
    // if the RecordType at that index is NULL
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
        // call the hash function to get the index
    int index = hash(record->id, tableSize);

    // if the RecordType at that index is NULL
    if (hashTable[index].rPointer == NULL)
    {
        // set 'record' equal to the HashType pointer in the table at index
        hashTable[index].rPointer = record;
        hashTable[index].rPointer->next = NULL;
    }
    else
    {
        // traverse to the end of the linkedlist and add 'record' to the end of it
        struct RecordType* curr = hashTable[index].rPointer;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = record;
        curr->next->next = NULL;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for (int i = 0; i < tableSize; i++)
    {
        if((hashTable + i)->rPointer != NULL)
        {
            struct RecordType *temp = (hashTable + i)->rPointer;
            printf("\nIndex %d", i + 1);
            while (temp != NULL)
            {
                printf(" -> %d, %c, %d", temp->id, temp->name, temp->order);
                temp = temp->next;
            }
            printf(" -> NULL");
        }
    }
    printf("\n");
    // for each entry in the table
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    //void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)

    // Initialize the hash table
    int TableSize = 11;
    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    // free all the allocated memory
    // Your hash implementation
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType) * TableSize);
    for (int i = 0; i < TableSize; ++i) {
        hashTable[i].rPointer = NULL;
    }
    for(int i = 0; i < recordSz; i++)
    {
        insertRecord(hashTable, pRecords + i, TableSize);
    }
    displayRecordsInHash(hashTable, TableSize);
    
    free(pRecords);
    free(hashTable);

    return 0;
}
