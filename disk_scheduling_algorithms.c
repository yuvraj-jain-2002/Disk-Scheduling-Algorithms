/*
* @author: Yuvraj Jain, jainy3
* date: 15th April 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

// Defining variables
#define TOTAL_REQS 20
#define DISK_CYLINDERS 300
#define SIZE_OF_VALUE 4
#define MEMORY TOTAL_REQS * SIZE_OF_VALUE

char * mmapfptr;
int requests[TOTAL_REQS];
int sortedrequests[TOTAL_REQS];
int direction;

void replace(int* i, int* j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}

void selectionSort(int arr[], int size)
{
    int i, j, min;

    // Loop through the array
    for (i = 0; i < size - 1; i++) {

        // Find the smallest element in the array
        min = i;
        for (j = i + 1; j < size; j++)
            if (arr[j] < arr[min])
                min = j; //Set minimum element to the smallest element

        // Replace the smallest element with the ith element of the array
        replace(&arr[min], &arr[i]);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
        printf("%d, ", arr[i]);
    printf("%d\n\n", arr[size-1]);
}

int FCFS(int initial, int req[]) {
        printf("FCFS DISK SCHEDULING ALGORIHM:\n\n");
                int total = 0;
                /* Loop through the array and services requests 
                   in the given order. Calculate absolute distance
                   from the track to the head and add it to the
                   total count.
                */
                for (int i = 0; i < TOTAL_REQS; i++){
                        total += abs(req[i] - initial);
                        initial = req[i];
                }
                printArray(req, TOTAL_REQS);
                printf("FCFS - Total head movements = %d\n\n", total);
                return 0;
}

int SSTF(int initial, int req[]) {
        int total = 0; //head movements
        int count = 0;
        printf("SSTF DISK SCHEDULING ALGORIHM:\n\n");
        int sstf_array[TOTAL_REQS];
        while(count != TOTAL_REQS){
                int min = 1000, difference, index;
                /*
                 Loop through the array and calculate absolute
                 distance for those requests that are closer 
                 to the initial position first. Keep updating 
                 the minimum value.
                */
                for (int i = 0; i < TOTAL_REQS; i++){
                        difference = abs(req[i] - initial);
                        if (min > difference){
                                min = difference;
                                index = i;
                        }
                }
                total += min;
                initial = req[index];
                sstf_array[count] = initial; // Add serviced request to array
                req[index] = 2024;
                count++;
        }
        printArray(sstf_array, TOTAL_REQS);
        printf("SSTF - Total head movements = %d\n\n", total);
        return 0;
}

int SCAN(int initial, int req[], int direction){
        int total = 0; //head movements
        int count = 0;
        int iterator = 0;
        int scan_array[TOTAL_REQS]; //array used to print the sequence of queries
        printf("SCAN DISK SCHEDULING ALGORIHM:\n\n");
        int index1 = 0;//index of element closest to initial
        // for loop to get the index of element closest to initial
        for (int i = 0; i < TOTAL_REQS; i++){
                if(req[i] >= initial){
                        index1 = i;
                        break;
                }
        }
        if(direction == 1){ // RIGHT
                // for loop to calculate head movements from index1 to
                // end of query
                for (iterator = index1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        scan_array[count] = initial;
                        count++;
                }
                // add the head movement from last in the query to 299
                total += abs(299 - req[iterator - 1]);
                initial = 299;
                // for loop to calculate head movements from 299 to
                // starting of the query (before index1)
                for (iterator = index1 - 1; iterator >= 0; iterator --){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        scan_array[count] = initial;
                        count++;
                }
        } else { // LEFT
                // for loop to calculate head movements from index1 to
                // start of query
                for (iterator = index1; iterator >= 0; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        scan_array[count] = initial;
                        count++;
                }
                // add the head movement from 0 to first in the query
                total += abs(req[iterator + 1] - 0);
                initial = 0;
                // for loop to calculate head movements from 0 to
                // end of the query (after index1)
                for (iterator = index1 + 1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        scan_array[count] = initial;
                        count++;
                }
        }
        printArray(scan_array, TOTAL_REQS);
        printf("SCAN - Total head movements = %d\n\n", total);
        return 0;
}

int CSCAN(int initial, int req[], int direction){
        int total = 0; //Total head movements
        int count = 0;
        int iterator = 0;
        int cscan_array[TOTAL_REQS];
        printf("C-SCAN DISK SCHEDULING ALGORIHM:\n\n");
        int index1 = 0;
        // for loop to get the index of element closest to initial
        for (int i = 0; i < TOTAL_REQS; i++){
                if(req[i] >= initial){
                        index1 = i;
                        break;
                }
        }
        if(direction == 1){ // RIGHT
                /*
                    Loop from the index to the end of the array
                    and calculate absolute distances.
                */
                for (iterator = index1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        cscan_array[count] = initial;
                        count++;
                }
                // add the head movement from last in the query to 299
                total += abs(299 - req[iterator - 1]);
                // add the head movement from 299 to 0
                total += abs(299 - 0);
                initial = 0;
                /*
                    Loop from the start of the array until before index1
                    and calculate absolute distances.
                */
                for (iterator = 0; iterator < index1; iterator ++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        cscan_array[count] = initial;
                        count++;
                }
        } else { //LEFT
                /*
                    Move left starting from the index1 to first in the
                    query and calculate absolute distances.
                */
                for (iterator = index1; iterator >= 0; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        cscan_array[count] = initial;
                        count++;
                }
                // add the head movement from first in the query to 0
                total += abs(req[iterator + 1] - 0);
                // add the head movement from 0 to 299
                total += abs(299 - 0);
                initial = 299;
                /*
                    Move from the last request to the query before
                    initial and calculate absolute distances.
                */
                for (iterator = 19; iterator > index1; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        cscan_array[count] = initial;
                        count++;
                }
        }
        printArray(cscan_array, TOTAL_REQS);
        printf("C-SCAN - Total head movements = %d\n\n", total);
        return 0;
}

int LOOK(int initial, int req[], int direction){
        int total = 0;  //Head movements
        int count = 0;
        int iterator = 0;
        int look_array[TOTAL_REQS];
        printf("LOOK DISK SCHEDULING ALGORIHM:\n\n");
        int index1 = 0;
        // Get index of the element closest to the initial position
        for (int i = 0; i < TOTAL_REQS; i++){
                if(req[i] >= initial){
                        index1 = i;
                        break;
                }
        }
        if(direction == 1){ // RIGHT
                /*
                    Move right starting from the index1 to the last
                    request in query and calculate absolute distances.
                */
                for (iterator = index1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        look_array[count] = initial;
                        count++;
                }
                // set the initial as the last query
                initial = req[iterator - 1];
                /*
                    Move left from the element before index to starting
                    of the query and calculate absolute distances.
                */
                for (iterator = index1 - 1; iterator >= 0; iterator --){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        look_array[count] = initial;
                        count++;
                }
        } else { //LEFT
                /*
                    Move left starting from the initial position to first in
                    query and calculate absolute distances.
                */
                for (iterator = index1; iterator >= 0; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        look_array[count] = initial;
                        count++;
                }
                // set the initial as the first query
                initial = req[iterator + 1];
                /*
                    Move right from the element after the initial
                    position until you reach the last request and
                    calculate absolute distances.
                */
                for (iterator = index1 + 1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        look_array[count] = initial;
                        count++;
                }
        }
        printArray(look_array, TOTAL_REQS);
        printf("LOOK - Total head movements = %d\n\n", total);
        return 0;
}

int CLOOK(int initial, int req[], int direction){
        int total = 0;
        int count = 0;
        int iterator = 0;
        int clook_array[TOTAL_REQS];
        printf("C-LOOK DISK SCHEDULING ALGORIHM:\n\n");
        int index1 = 0;
        // Find index of element closest to the initial position
        for (int i = 0; i < TOTAL_REQS; i++){
                if(req[i] >= initial){
                        index1 = i;
                        break;
                }
        }
        if(direction == 1){ // RIGHT
                 /*
                    Move right starting from the index until
                    you reach the last request and calculate
                    absolute distances.
                 */
                for (iterator = index1; iterator < TOTAL_REQS; iterator++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        clook_array[count] = initial;
                        count++;
                }
                // set the initial as the last query
                initial = req[iterator - 1];
                /*
                    Move right starting from the first request
                    until you reach the element right before the
                    initial position and calculate absolute distances.
                */
                for (iterator = 0; iterator < index1; iterator ++){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        clook_array[count] = initial;
                        count++;
                }
        } else { //LEFT
                /*
                    Move left from the initial position until
                    you reach the start of the array and calculate
                    absolute distances.
                */
                for (iterator = index1; iterator >= 0; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        clook_array[count] = initial;
                        count++;
                }
                // set the initial as the first query
                initial = req[iterator + 1];
                /*
                    Move left from the last request of the array until
                    you reach the position before index1 and calculate absolute distances.
                */
                for (iterator = 19; iterator > index1; iterator--){
                        total += abs(req[iterator] - initial);
                        initial = req[iterator];
                        clook_array[count] = initial;
                        count++;
                }
        }
        printArray(clook_array, TOTAL_REQS);
        printf("C-LOOK - Total head movements = %d\n\n", total);
        return 0;
}

int main(int argc, char *argv[]) {

        // If all arguments are not provided, return an error message
        if (argc < 3) {
                printf("Error, missing parameters. Please enter initial disk position and direction of head.");
                return -1;
        }

        printf("Total requests: %d\n", TOTAL_REQS);
        printf("Initial Head Position: %s\n", argv[1]);
        printf("Direction of Head: %s\n\n", argv[2]);

        int mmapfile_fd = open("request.bin", O_RDONLY); //Open binary file
        mmapfptr = mmap(0, MEMORY, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0);

        // Copy contents of binary file into an array
        for (int i = 0; i < TOTAL_REQS; i++) {
                memcpy(requests + i, mmapfptr + i*4, SIZE_OF_VALUE);
        }
        munmap(mmapfptr, MEMORY);

        // Copy contents of the requests array to another array
        for (int i = 0; i < TOTAL_REQS; i++) {
                sortedrequests[i] = requests[i];
        }
        // Sort the new array using selection sort
        selectionSort(sortedrequests, TOTAL_REQS);

        // Check if direction of head is LEFT or RIGHT
        int initial = atoi(argv[1]);
        if (strcmp(argv[2], "LEFT") == 0) {
                direction = 0; //LEFT
        } else {
                direction = 1; //RIGHT
        }

        FCFS(initial, requests);
        SSTF(initial, requests);
        SCAN(initial, sortedrequests, direction);
        CSCAN(initial, sortedrequests, direction);
        LOOK(initial, sortedrequests, direction);
        CLOOK(initial, sortedrequests, direction);
        return 0;
}
