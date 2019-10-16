#include <stdio.h>
#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <syslog.h>

#define RESET		0
#define BRIGHT 		1
#define DIM		2
#define UNDERLINE 	3
#define BLINK		4
#define REVERSE		7
#define HIDDEN		8

#define BLACK 		0
#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

#define STD 0
#define SYS 1
#define INVALID -1


int logT = STD;

void textcolor(int attr, int fg, int bg)
{	char command[13];
	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

int initLogger(char *logType) {
  if ((strcmp(logType, "stdout")==0) || (strcmp(logType, "")==0)){
    logT = STD;
    infof("\n \nInitializing Logger on: %s\n \n", logType);
  } else if (strcmp(logType, "syslog")==0){
    logT = STD;
    infof("\n \nInitializing Logger on: %s\n \n", logType);
    logT = SYS;
  } else{
    logT = STD;
    errorf("\n \nInvalid Log-Type\n \n");
    logT = INVALID;
  }
    return 0;
}

int infof(const char *format, ...){
      if(logT == INVALID){
        logT = STD;
        errorf("Invalid Log-Type \n");
        logT = INVALID;
        return -1;
      }
      va_list arg;
      va_start(arg, format);
      textcolor(DIM, GREEN, HIDDEN);
      if(logT){
        vsyslog(1,format,arg);
        return 0;
      }
      int out;
      out = vfprintf (stdout, format, arg);
      textcolor(RESET, WHITE, HIDDEN);
      va_end(arg);
      return out;
}

int warnf(const char *format, ...){
    if(logT == INVALID){
      logT = STD;
      errorf("Invalid Log-Type \n");
      logT = INVALID;
      return -1;
    }
    va_list arg;
    va_start(arg, format);
    textcolor(BRIGHT, YELLOW, HIDDEN);
    if(logT){
      vsyslog(1,format,arg);
      return 0;
    }
    int out;
    out = vfprintf (stdout, format, arg);
    textcolor(RESET, WHITE, HIDDEN);
    va_end(arg);
    return out;
}
int errorf(const char *format, ...){
    if(logT == INVALID){
      logT = STD;
      errorf("Invalid Log-Type \n");
      logT = INVALID;
      return -1;
    }
    va_list arg;
    va_start(arg, format);
    textcolor(UNDERLINE, MAGENTA, HIDDEN);
    if(logT){
      vsyslog(1,format,arg);
      return 0;
    }
    int out;
    out = vfprintf (stdout, format, arg);
    textcolor(RESET, WHITE, HIDDEN);
    va_end(arg);
    return out;
}
int panicf(const char *format, ...){
    if(logT == INVALID){
      logT = STD;
      errorf("Invalid Log-Type \n");
      logT = INVALID;
      return -1;
    }
    va_list arg;
    va_start(arg, format);
    textcolor(BLINK, RED, HIDDEN);
    if(logT){
      vsyslog(1,format,arg);
      return 0;
    }
    int out;
    out = vfprintf (stdout, format, arg);
    textcolor(RESET, WHITE, HIDDEN);
    va_end(arg);
    return out;
}
