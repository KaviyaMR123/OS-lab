#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int size;
    int is_allocated;
} Partition;

void first_fit(Partition partitions[], int partition_count, int size, int process_id);
void best_fit(Partition partitions[], int partition_count, int size, int process_id);
void worst_fit(Partition partitions[], int partition_count, int size, int process_id);
void print_partitions(Partition partitions[], int partition_count);
int main()
{
    int partition_count;
    printf("Enter the number of partitions: ");
    scanf("%d", &partition_count);
    Partition *partitions = (Partition *)malloc(partition_count * sizeof(Partition));
    for (int i = 0; i < partition_count; i++) 
    {
        printf("Enter size of partition %d: ", i + 1);
        scanf("%d", &partitions[i].size);
        partitions[i].is_allocated = 0;
    }

    int process_count;
    printf("Enter the number of processes: ");
    scanf("%d", &process_count);

    int *process_sizes = (int *)malloc(process_count * sizeof(int));
    for (int i = 0; i < process_count; i++) 
    {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &process_sizes[i]);
    }
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < process_count; i++) 
    {
        first_fit(partitions, partition_count, process_sizes[i], i + 1);
    }
    print_partitions(partitions, partition_count);
    for (int i = 0; i < partition_count; i++) 
    {
        partitions[i].is_allocated = 0;
    }

    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < process_count; i++) 
    {
        best_fit(partitions, partition_count, process_sizes[i], i + 1);
    }
    print_partitions(partitions, partition_count);
    for (int i = 0; i < partition_count; i++) 
    {
        partitions[i].is_allocated = 0;
    }
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < process_count; i++) 
    {
        worst_fit(partitions, partition_count, process_sizes[i], i + 1);
    }
    print_partitions(partitions, partition_count);
    free(partitions);
    free(process_sizes);
    return 0;
}

void first_fit(Partition partitions[], int partition_count, int size, int process_id) 
{
    for (int i = 0; i < partition_count; i++) 
    {
        if (!partitions[i].is_allocated && partitions[i].size >= size) 
        {
            partitions[i].is_allocated = process_id;
            printf("Process %d allocated in partition %d\n", process_id, i + 1);
            return;
        }
    }
    printf("Process %d could not be allocated\n", process_id);
}
void best_fit(Partition partitions[], int partition_count, int size, int process_id) 
{
    int best_index = -1;
    for (int i = 0; i < partition_count; i++) 
    {
        if (!partitions[i].is_allocated && partitions[i].size >= size) 
        {
            if (best_index == -1 || partitions[i].size < partitions[best_index].size) 
            {
                best_index = i;
            }
        }
    }
    if (best_index != -1) 
    {
        partitions[best_index].is_allocated = process_id;
        printf("Process %d allocated in partition %d\n", process_id, best_index + 1);
    } else 
    {
        printf("Process %d could not be allocated\n", process_id);
    }
}

void worst_fit(Partition partitions[], int partition_count, int size, int process_id) 
{
    int worst_index = -1;
    for (int i = 0; i < partition_count; i++) 
    {
        if (!partitions[i].is_allocated && partitions[i].size >= size) 
        {
            if (worst_index == -1 || partitions[i].size > partitions[worst_index].size) 
            {
                worst_index = i;
            }
        }
    }
    if (worst_index != -1) 
    {
        partitions[worst_index].is_allocated = process_id;
        printf("Process %d allocated in partition %d\n", process_id, worst_index + 1);
    } else 
    {
        printf("Process %d could not be allocated\n", process_id);
    }
}
void print_partitions(Partition partitions[], int partition_count) 
{
    printf("Partition status:\n");
    for (int i = 0; i < partition_count; i++) 
    {
        printf("Partition %d: Size = %d, Process = %d\n", i + 1, partitions[i].size, partitions[i].is_allocated);
    }
}
