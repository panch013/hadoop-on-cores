#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

/**
SHMSZ > 4*LIMIT

SHMSZ has to be shmall? (32MB on cello) 

Always execute 'ipcrm shm <shmid>' before running the server
**/

main(int argc, char *argv[])
{
    int c;
    int shmid,i;
    key_t key;
    int *shm, *s;

    int SHMSZ = atoi(argv[1]);
    int LIMIT = atoi(argv[2]);
    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */

    printf("SIZE: %d\n", SHMSZ);
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
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
     * Now put some things into the memory for the
     * other process to read.
     */
    s = shm;

    printf("LIMIT: %d\n", LIMIT);
    for (c = 0; c < LIMIT; c++){
        *s = c;
        //printf("%d\t", *s);
        s++;
    }
    *s = LIMIT;

    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm != (LIMIT+1))
        sleep(1);

    printf("Stopped!\n ");
    exit(0);
}
