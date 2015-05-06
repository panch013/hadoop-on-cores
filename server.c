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
    int shmid_1, shmid_2, i;
    key_t key_1, key_2;
    int *shm_1, *shm_2, *s_1, *s_2;

    int SHMSZ_1 = atoi(argv[1]);
    int LIMIT_1 = atoi(argv[2]);
    int SHMSZ_2 = atoi(argv[3]);
    int LIMIT_2 = atoi(argv[4]);
    key_1   = atoi(argv[5]);
    key_2   = atoi(argv[6]);
    /*
     * We'll name our shared memory segment
     * "5678".
     * key_1 = 5678;
     * key_2 = 5679;
     */

    /*
     * Create the segment.
     */

    if ((shmid_1 = shmget(key_1, SHMSZ_1, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shmid_2 = shmget(key_2, SHMSZ_2, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /*
     * Now we attach the segment to our data space.
     */
    if ((shm_1 = shmat(shmid_1, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((shm_2 = shmat(shmid_2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    /*
     * Now put some things into the memory for the
     * other process to read.
     * First segment will have data [0-LIMIT_1]
     * Second segment will have data [LIMIT_1-LIMIT_2]
     * LIMIT_1 < LIMIT_2
     */
    s_1 = shm_1;

    for (c = 0; c < LIMIT_1; c++){
        *s_1 = c;
        //printf("%d\t", *s);
        s_1++;
    }
    *s_1 = LIMIT_1;

    s_2 = shm_2;

    for (c = LIMIT_1; c < LIMIT_2; c++){
        *s_2 = c;
        //printf("%d\t", *s);
        s_2++;
    }
    *s_2 = LIMIT_2;
    /*
     * Finally, we wait until the other process 
     * changes the first character of our memory
     * to '*', indicating that it has read what 
     * we put there.
     */
    while (*shm_1 != (LIMIT_1+1))
        sleep(1);
    while (*shm_2 != (LIMIT_2+1))
        sleep(1);

    printf("Stopped!\n ");
    exit(0);
}
