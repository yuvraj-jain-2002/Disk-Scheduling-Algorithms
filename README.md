# Disk Scheduling Algorithms

## Introduction
The program services a disk with 300 cylinders numbered 0 to 299. It services the requests (a list of 20 cylinder numbers) given in the file request.bin. This file contains (4 byte) integer values representing requests ranging from 0 − 299. The program takes the initial position of the disk head as the first command line argument and the direction of the head as the second command line argument. It will then output the requests in the order in which they are serviced, and the total amount of head movements required by each algorithm. The following disc scheduling algorithms are implemented:
- FCFS
- SSTF 
- SCAN 
- C-SCAN 
- LOOK
- C-LOOK 

## Sample Output

**Output when the first command line argument is 100 (head) and the second command line argument is RIGHT (direction):**
```c
    Total requests = 20 
    Initial Head Position: 100 
    Direction of Head: RIGHT 

    FCFS DISK SCHEDULING ALGORITHM:

    49, 61, 8, 31, 100, 130, 162, 173, 280, 250, 293, 230, 52, 72, 65, 81, 160, 181, 200, 245 

    FCFS - Total head movements = 909 

    SSTF DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293 

    SSTF - Total head movements = 377 

    SCAN DISK SCHEDULING ALGORITHM 

    100, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293, 81, 72, 65, 61, 52, 49, 31, 8 

    SCAN - Total head movements = 490 

    C-SCAN DISK SCHEDULING ALGORITHM 

    100, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293, 8, 31, 49, 52, 61, 65, 72, 81 

    C-SCAN - Total head movements = 579 

    LOOK DISK SCHEDULING ALGORITHM 

    100, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293, 81, 72, 65, 61, 52, 49, 31, 8 

    LOOK - Total head movements = 478 

    C-LOOK DISK SCHEDULING ALGORITHM 

    100, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293, 8, 31, 49, 52, 61, 65, 72, 81 

    C-LOOK - Total head movements = 551 
```

**Output when the first command line argument is 100 (head) and the second command line argument is LEFT (direction):**
```c
    Total requests = 20 
    Initial Head Position: 100 
    Direction of Head: LEFT 

    FCFS DISK SCHEDULING ALGORITHM:

    49, 61, 8, 31, 100, 130, 162, 173, 280, 250, 293, 230, 52, 72, 65, 81, 160, 181, 200, 245 

    FCFS - Total head movements = 909 

    SSTF DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293 

    SSTF - Total head movements = 377 

    SCAN DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293 

    SCAN - Total head movements = 393 

    C-SCAN DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 293, 280, 250, 245, 230, 200, 181, 173, 162, 160, 130 

    C-SCAN - Total head movements = 568 

    LOOK DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 130, 160, 162, 173, 181, 200, 230, 245, 250, 280, 293 

    LOOK - Total head movements = 377 

    C-LOOK DISK SCHEDULING ALGORITHM 

    100, 81, 72, 65, 61, 52, 49, 31, 8, 293, 280, 250, 245, 230, 200, 181, 173, 162, 160, 130 

    C-LOOK - Total head movements = 540  
```
