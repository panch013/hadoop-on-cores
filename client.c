/*
 * shm-client - client program to demonstrate shared memory.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <time.h>

extern double mysecond();
main(int argc, char *argv[])
{
    int shmid_1, shmid_2, shmid_3, shmid_4;
    key_t key_1, key_2, key_3, key_4;
    int *shm_1, *shm_2, *shm_3, *shm_4, *s_1, *s_2, *s_3, *s_4;
    //time_t start,end;
    double start,end;

    int SHMSZ_1 = atoi(argv[1]);
    int LIMIT_1 = atoi(argv[2]);
    int SHMSZ_2 = atoi(argv[3]);
    int LIMIT_2 = atoi(argv[4]);
    int SHMSZ_3 = atoi(argv[5]);
    int LIMIT_3 = atoi(argv[6]);
    int SHMSZ_4 = atoi(argv[7]);
    int LIMIT_4 = atoi(argv[8]);
    /*
     * We need to get the segment named
     * "5678", created by the server.
     * key = 5678;
     */
    key_1 = atoi(argv[9]);
    key_2 = atoi(argv[10]);
    key_3 = atoi(argv[11]);
    key_4 = atoi(argv[12]);

    /*
     * Locate the segment.
     */
    if ((shmid_1 = shmget(key_1, SHMSZ_1, 0666)) < 0) {
        perror("shmget 1");
        exit(1);
    }
    if ((shmid_2 = shmget(key_2, SHMSZ_2, 0666)) < 0) {
        perror("shmget 2");
        exit(1);
    }
    if ((shmid_3 = shmget(key_3, SHMSZ_3, 0666)) < 0) {
        perror("shmget 3");
        exit(1);
    }
    if ((shmid_4 = shmget(key_4, SHMSZ_4, 0666)) < 0) {
        perror("shmget 4");
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
    if ((shm_3 = shmat(shmid_3, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((shm_4 = shmat(shmid_4, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now read what the server put in the memory.
     */

    start = mysecond(); 
    //start = time(NULL); 
    int i = 0;
    for (s_1 = shm_1; i < LIMIT_1; s_1++){
        //printf("%d\t", *s);
        *s_1;
        i++;
    }
    putchar('\n');
    //end = time(NULL); 
    end = mysecond(); 
    
    printf("%11.6f\n", (end-start));

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm_1 = LIMIT_1+1;

    start = mysecond(); 
    //start = time(NULL); 
    i = 0;
    for (s_2 = shm_2; i < LIMIT_2; s_2++){
        //printf("%d\t", *s);
        *s_2;
        i++;
    }
    //end = time(NULL); 
    end = mysecond(); 
    
    printf("%11.6f\n", (end-start));

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm_2 = LIMIT_2+1;

    start = mysecond(); 
    //start = time(NULL); 
    i = 0;
    for (s_3 = shm_3; i < LIMIT_3; s_3++){
        //printf("%d\t", *s);
        *s_3;
        i++;
    }
    //end = time(NULL); 
    end = mysecond(); 
    
    printf("%11.6f\n", (end-start));

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm_3 = LIMIT_3+1;
    
    start = mysecond(); 
    //start = time(NULL); 
    i = 0;
    for (s_4 = shm_4; i < LIMIT_4; s_4++){
        //printf("%d\t", *s);
        *s_4;
        i++;
    }
    //end = time(NULL); 
    end = mysecond(); 
    
    printf("%11.6f\n", (end-start));

    /*
     * Finally, change the first character of the 
     * segment to '*', indicating we have read 
     * the segment.
     */
    *shm_4 = LIMIT_4+1;
    exit(0);
}

