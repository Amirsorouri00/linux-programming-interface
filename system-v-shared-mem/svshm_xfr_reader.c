#include "./svshm_xfr.h"

int main (int argc, char *argv[])
{
    int semid, shmid, xfrs, bytes;
    struct shmseg *shmp;

    /* Get IDs for semaphore set and shared memory created by writer */

    semid = semget(SEM_KEY, 0, 0);
    if (-1 == semid)
        errExit("semget");

    shmid = shmget(SHM_KEY, 0, 0);
    if(-1 == shmid)
        errExit("shmget");
    
    shmp = shmat(shmid, NULL, SHM_RDONLY);
    if ( (void *) -1 == shmp )
        errExit("shmat");

    /* Transfer blocks of data from shared memory to stdout */

    for (xfrs = 0, bytes = 0; ; xfrs++){
        if (-1 == reserveSem(semid, READ_SEM))      /* Wait for our turn */
            errExit("reserveSem");
        
        if (0 == shmp->cnt)         /* Writer  encountered EOF */
            break;
        bytes += shmp->cnt;

        if(write(STDOUT_FILENO, shmp->buf, shmp->cnt) != shmp->cnt)
            fatal("partial/failed write");
        
        if (-1 == releaseSem(semid, WRITE_SEM))         /* Give writer a turn */
            errExit("releaseSem");
    }

    if (-1 == shmdt(shmp))
        errExit("shmdt");
    
    /* Give writer one more turn, so it can clean up */
    if (-1 == releaseSem(semid, WRITE_SEM))
        errExit("releaseSem");

    fprintf(stderr, "Received %d bytes (%d xfrs)\n", bytes, xfrs);
    exit(EXIT_SUCCESS);
}