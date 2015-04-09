/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>

#define SHMSZ     27

extern double mysecond();
main()
{
    int shmid;
    key_t key;
    int *shm, *s;
    //time_t start,end;
    double start,end;

    /*
     * We need to get the segment named
     * "5678", created by the server.
     */
    key = 5678;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */

    start = mysecond(); 
    //start = time(NULL); 
    for (s = shm; *s != 100; s++)
        printf("%d", *s);
    putchar('\n');
    //end = time(NULL); 
    end = mysecond(); 
    
    printf("%11.6f\n", (end-start));

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm = 101;

    exit(0);
}

