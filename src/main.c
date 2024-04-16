#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROGRAM_NAME "proj_creator"
#define VERSION 0.1
#define PRINT_VERSION printf("%s V%.1lf.%d\n", PROGRAM_NAME, VERSION, minor_version);

int minor_version = 0;

struct Template {
	char* name;
	char* desc;
	char* project_file;
};

struct Template templates[] = {
	{"c", "Starting c project file","this is a c file"},
	{"bash", "bash script starter","this is a bash file"},
};

int templates_num = sizeof(templates) / sizeof(struct Template);

void usage(int exit_code) {
	PRINT_VERSION

	fputs("\n\
Usage: [OPTION] ... [TEMPLATE_NAME] \n\
\n\
\t-h\tPrints out this help message and exits\n\
\t-v\tPrints out program version\n\
\t-n\tGive a custom to the generated file\n\
\t-o\tDo not create project file, only print it to stdout\n\
\n\
Available templates:\n", stdout);

	for(int i = 0; i < templates_num; i++) {
		printf("\t%s\t%s\n", templates[i].name, templates[i].desc);
	}
	putc('\n', stdout);

	exit(exit_code);
}

int main(int argc, char** argv) {

	if(argc < 2)
		usage(0);

	FILE* filename = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "hvon:")) != -1)
		switch (c)
		{
			case 'h':
				usage(0);
				break;
			case 'v':
				PRINT_VERSION
				break;
			case 'o':
				filename = stdout;
				break;
			case 'n':
				filename = (FILE*)optarg;
				break;
			case '?':
				if (optopt == 'n')
					fprintf (stderr, "A -%c opcionak kell faljnev argumentumot adni\n", optopt);
				else
					fprintf (stderr, "Ismeretlen opcio: `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}

	for (index = optind; index < argc; index++)
		printf ("Nem opcio a(z): %s\n", argv[index]);

	

	return 0;
}
