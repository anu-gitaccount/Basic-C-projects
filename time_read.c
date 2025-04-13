
/*TRL == time read line*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//trl func (return strings)
char *trl(int timeout) {

    //this will be returned to main function
    static char buf[512];

    //specific variable type
    fd_set rfds;

    //for timeput part
    struct timeval tv;

    //return value
    int ret;


    FD_ZERO(&rfds);
    FD_SET(0 , &rfds);

    tv.tv_sec = timeout;
    tv.tv_usec = 0;

    //rfds is a file discryptors
    ret = select(1, &rfds , 0 , 0, &tv);

    //here in fd_isset check is any file discryptors have any std data
    //0 -> means stdin file dys
    if (ret && FD_ISSET(0 , &rfds)) {
        memset(buf , 0 , 512);
        ret = read(0 , buf , 511);

        if (ret < 1) 
            return 0;
        ret--;
        buf[ret] = 0;

        return buf;
    }
    else {
        return 0;
    }



}


int main(void) {

    char *name;

    printf("Enter your Name ? Type in 3 sec :\n");
    name = trl(3);

    if (name) 
        printf("Hello %s\n" , name);
    else 
        printf("\nToo slow! \n");


    return 0;
}