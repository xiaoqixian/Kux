#include <pthread.h>
#include <stdio.h>

void* func(void* arg) {
    printf("hello world\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, func, NULL);
        pthread_join(threads[i], NULL);
    }
    return 0;
}
