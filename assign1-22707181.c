/*
This program allows the user to output the head (first 10 lines) of a provided file.
It will print indiscriminately if:
    no -e or -o options are provided;
    both -e and -o options are provided.

Alice Karatchentzeff de Vienne
22707181
alice.karatchentzeff@ucdconnect.ie

Works completely
"*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

void printVersionInfo();
void printOptionList();

int main(int argc, char* argv[]) {
    int opt;
    int numLines = 10;
    int lineCounter = 0;
    bool even = false;
    bool odd = false;
    char* line;
    size_t size;
    FILE* source;

    /*Process all options*/
    while ((opt = getopt(argc, argv, "n:Vheo")) != -1) {
        switch (opt) {
            case 'n':
                numLines = atoi(optarg);
                break;
            case 'V':
                printVersionInfo();
                break;
            case 'h':
                printOptionList();
                return 0;
            case 'e':
                even = true;
                break;
            case 'o':
                odd = true;
                break;
            default:
                fprintf(stderr, "An error occurrerd while processing options\n");
                break;
        }
    }

    /*Print both even and odd if none has been selected*/
    if (!even && !odd) {
        even = true;
        odd = true;
    }

    /*Select input source as stdin if no provided file*/
    if (optind >= argc) {
        source = stdin;
    } else {
        source = fopen(argv[optind], "r");
    }

    /*Print lines following option specifications, if any*/
    for (int i = 0; lineCounter != numLines && (getline(&line, &size, source) != -1); i++) {
        if(even && (i+1)%2 == 0 || odd && (i+1)%2 == 1) { // line count starts at 1
            fprintf(stdout, "%s", line);
            lineCounter++;
        }
    }

    fclose(source);
    return 0;
}


void printVersionInfo() {
    fprintf(stdout, "Alice Karatchentzeff de Vienne\n"
                    "22707181\n"
                    "alice.karatchentzeff@ucdconnect.ie\ns");
}

void printOptionList() {
    fprintf(stdout, "Options:\n"
                    "\t-n K\tPrint frst K lines\n"
                    "\t-V\tPrint version info\n"
                    "\t-h\tPrint option list and exit\n"
                    "\t-e|-o\tPrint even|odd lines\n");
}