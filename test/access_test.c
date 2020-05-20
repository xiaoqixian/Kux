#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    char* path = "parse_test.c";
    char* path2 = "~/pros/sd";
    
    if (access(path, F_OK) == -1) {
        printf("path not exits\n");
    }
    
    if (access(path2, F_OK) == -1) {
        printf("path2 not exits\n");
    }
    return 0;
}
