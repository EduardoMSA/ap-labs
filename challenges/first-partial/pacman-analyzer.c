#include <stdio.h>
#include <stdlib.h>

#define REPORT_FILE "packages_report.txt"

void analizeLog(char *logFile, char *report);

int main(int argc, char **argv) {

    if (argc < 2) {
	printf("Usage:./pacman-analizer.o pacman.log\n");
	return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.

    FILE *fp;
    fp = fopen(file)

    printf("Report is generated at: [%s]\n", report);
}
