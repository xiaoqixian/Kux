/*
 * test gethostbyname() function
 */

#include <stdio.h>
//#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
struct hostent defination

struct hostent {
    char* h_name; //official name of host
    char** h_aliases; //alias list
    int h_addrtype; //host address type
    int h_length; //length of address
    char** h_addr_list; //list of addresses
}
*/

int main(int argc, char* argv[]) {
    struct hostent* host;
    host = gethostbyname(argv[1]);
    if (host == NULL) {
        fprintf(stderr, "gethostbyname %s: %s\n", argv[1], hstrerror(h_errno));
        return -1;
    }
    
    printf("host official name: %s\n\n", host->h_name);
    
    int addr_type = host->h_addrtype;
    char str[INET_ADDRSTRLEN];
    switch (addr_type) {
        case AF_INET:
            printf("address list:\n");
            char** addr_list = host->h_addr_list;
            for (; *addr_list != NULL; addr_list++) {
                printf("%s\n", inet_ntop(AF_INET, addr_list, str, sizeof(str)));
            }
            break;
        default:
            fprintf(stderr, "unknown address type\n");
            return -1;
    }
}
