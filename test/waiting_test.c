#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;
    
    // Création du premier processus enfant
    pid1 = fork();
    if (pid1 == 0) {
        // Code du processus enfant
        printf("Enfant 1 (PID: %d) en cours d'exécution...\n", getpid());
        sleep(2); // Simule un travail
        printf("Enfant 1 (PID: %d) terminé.\n", getpid());
        exit(0);
    }

    // Création du deuxième processus enfant
    pid2 = fork();
    if (pid2 == 0) {
        // Code du processus enfant
        printf("Enfant 2 (PID: %d) en cours d'exécution...\n", getpid());
        sleep(5); // Simule un travail plus long
        printf("Enfant 2 (PID: %d) terminé.\n", getpid());
        exit(0);
    }

    // Le parent attend n'importe quel enfant avec wait()
    int status;
    pid_t pid_terminated = wait(&status);
    printf("Parent a attendu la fin du processus PID: %d\n", pid_terminated);

    // Le parent attend spécifiquement l'enfant 2 avec waitpid()
    waitpid(pid2, &status, 0);
    printf("Parent a attendu spécifiquement la fin du processus PID: %d\n", pid2);

    return 0;
}
