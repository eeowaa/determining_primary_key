#include <stdlib.h> /* exit, stderr */
#include <errno.h>  /* errno */
#include <string.h> /* strcpy */
#include <stdio.h>  /* printf, perror, getc */
#include <limits.h> /* PATH_MAX */
#include <math.h>   /* pow */

/* compile-time variables */
#define RS '\n'
#define FS '\t'

/* global variables */
char program[PATH_MAX];
char file[PATH_MAX] = "";
FILE *fp;
int c;
int num_fields;
int num_combinations;
int num_records;

/* functions */
void read_record(void);
void analyze_file(void);

int main(int argc, char **argv)
{
	int i;
	char usage[] = "Usage: %s [-h | --help] FILE\n";

	/* parse program arguments */
	strcpy(program, argv[0]);
	for (i = 1; i < argc; ++i) {
		if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
			printf(usage, program);
			exit(0);
		} else {
			strncpy(file, argv[i], PATH_MAX);
		}
	}
	if (!file[0]) {
		fprintf(stderr, usage, program);
		exit(1);
	}
	errno = 0;
	if (!(fp = fopen(file, "r"))) {
		perror(file);
		exit(1);
	}

	/* compute requirements */
	analyze_file();

	/* close file handle and exit */
	exit(0);
}

void analyze_file(void)
{
	/* count number of fields in first record */
	num_fields = 0;
FirstField:
	switch (c = getc(fp)) {
	case FS:
		num_fields = 1;
		goto NextField;
	case RS:
	case EOF:
		goto EndFieldCount;
	default:
		num_fields = 1;
		goto FirstField;
	}
NextField:
	switch (c = getc(fp)) {
	case FS:
		++num_fields;
		goto NextField;
	case RS:
	case EOF:
		++num_fields;
		goto EndFieldCount;
	default:
		goto NextField;
	}
EndFieldCount:
	fprintf(stderr, "fields per record = %d\n", num_fields);
	fprintf(stderr, "combinations per record = %d\n",
		num_combinations = pow(2, num_fields) - 1);

	/* count number of records in file */
	num_records = 1;
NextRecord:
	switch (c = getc(fp)) {
	case RS:
		++num_records;
		goto NextRecord;
	case EOF:
		break;
	default:
		goto NextRecord;
	}
	fprintf(stderr, "number of records = %d\n", num_records);

	/* reset file position to beginning of file */
	fseek(fp, 0L, SEEK_SET);
}

void read_record(void)
{
	/* count number of fields in first record */
	num_fields = 0;
FirstField:
	switch (c = getc(fp)) {
	case FS:
		num_fields = 1;
		goto NextField;
	case RS:
	case EOF:
		goto EndFieldCount;
	default:
		num_fields = 1;
		goto FirstField;
	}
NextField:
	switch (c = getc(fp)) {
	case FS:
		++num_fields;
		goto NextField;
	case RS:
	case EOF:
		++num_fields;
		goto EndFieldCount;
	default:
		goto NextField;
	}
EndFieldCount:
	fprintf(stderr, "fields per record = %d\n", num_fields);
	fprintf(stderr, "combinations per record = %d\n",
		num_combinations = pow(2, num_fields) - 1);

	/* count number of records in file */
	num_records = 1;
NextRecord:
	switch (c = getc(fp)) {
	case RS:
		++num_records;
		goto NextRecord;
	case EOF:
		break;
	default:
		goto NextRecord;
	}
	fprintf(stderr, "number of records = %d\n", num_records);

	/* reset file position to beginning of file */
	fseek(fp, 0L, SEEK_SET);
}
