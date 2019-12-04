
Skip to content
Pull requests
Issues
Marketplace
Explore
@EduardoMSA
Learn Git and GitHub without any code!

Using the Hello World guide, you’ll start a branch, write comments, and open a pull request.
Code Pull requests 0 Projects 0 Wiki Security Pulse
ap-labs/labs/openmp/logger.c
@reyes-g reyes-g Adding the openmp lab 10ec604 4 hours ago
@obedmr
@reyes-g
125 lines (108 sloc) 2.58 KB
#include <stdio.h>
#include "logger.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>


#define RESET		0
#define BRIGHT 		1
#define DIM		    2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		    1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

#define STD     1
#define SYS     0
int LogFlag =1;


int initLogger(char *logType) {
    if(strcmp(logType,"stdout")==0){
        LogFlag=STD;
    }
    else if(strcmp(logType,"syslog")==0){
        LogFlag=SYS;
    }
    else{
        printf("Error, invalid argument");
        return -1;
    }
    printf("Initializing Logger on: %s\n", logType);
    return 0;
}

void textcolor(int attribute, int foreground, int background){
    char command[13];
	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attribute, foreground + 30, background + 40);
	printf("%s", command);
}

int infof(const char *format, ...){
    va_list ls;
    va_start(ls,format);
    if(LogFlag){

        textcolor(BRIGHT,WHITE,BLUE);
        vfprintf(stdout,format,ls);

        textcolor(RESET,WHITE,BLACK);
        return 1;
    }
    else{
        openlog("log",LOG_CONS,LOG_SYSLOG);
        syslog(LogFlag,format,ls);
        closelog();
    }
    va_end(ls);

}
int warnf(const char *format, ...){
    va_list ls;
    va_start(ls,format);
    if(LogFlag){

        textcolor(BRIGHT,WHITE,YELLOW);
        vfprintf(stdout,format,ls);
        textcolor(RESET,WHITE,BLACK);
        return 1;
    }
    else{
        openlog("log",LOG_CONS,LOG_SYSLOG);
        syslog(LogFlag,format,ls);
        closelog();
    }
    va_end(ls);

}
int errorf(const char *format, ...){
    va_list ls;
    va_start(ls,format);
    if(LogFlag){

        textcolor(BRIGHT,WHITE,RED);
        vfprintf(stdout,format,ls);
        textcolor(RESET,WHITE,BLACK);
        return 1;
    }
    else{
        openlog("log",LOG_CONS,LOG_SYSLOG);
        syslog(LogFlag,format,ls);
        closelog();
    }
    va_end(ls);

}
int panicf(const char *format, ...){
    va_list ls;
    va_start(ls,format);
    if(LogFlag){
        textcolor(BRIGHT,RED,WHITE);
        vfprintf(stdout,format,ls);
        textcolor(RESET,WHITE,BLACK);
        return 1;
    }
    else{
        openlog("log",LOG_CONS,LOG_SYSLOG);
        syslog(LogFlag,format,ls);
        closelog();
    }
    va_end(ls);

}

    © 2019 GitHub, Inc.
    Terms
    Privacy
    Security
    Status
    Help

    Contact GitHub
    Pricing
    API
    Training
    Blog
    About
