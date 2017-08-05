//Common includes

#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <malloc.h>
#include <dirent.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h> //link this with -lpthread while compiling
#include<rpc/des_crypt.h>
#include<crypt.h> //link with -lcrypt while compiling

//Method definitions

long long int keygen(void);

long long int power(long long int,long long int, long long int);

void reverse(char[]);

void myitoa(long long int, char[]);


