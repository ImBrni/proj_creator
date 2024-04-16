#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROGRAM_NAME "proj_creator"
#define VERSION 0.1
#define PRINT_VERSION printf("%s V%.1lf.%d\n", PROGRAM_NAME, VERSION, minor_version);

int minor_version = 0;

struct Template {
	char* name;
	char* desc;
	char* file_name;
	char* project_file;
};

const struct Template templates[] = {
	{"c", "Starting c project file", "main.c", "#include <stdio.h>\n\nint main(void) {\n\n\tprintf(\"Hello World!\\n\");\n\n\treturn 0;\n}"},
	{"bash", "bash script starter", "script.sh", "#!/bin/bash\n\nvar=\"Hello World!\"\n\necho \"$var\""},
	{"python", "python hello world with main", "main.py", "def main():\n\tprint(\"Hello World!\")\n\nif __name__ == \"__main__\":\n\tmain()"},
	{"go", "golang hello world", "main.go", "package main\n\nimport \"fmt\"\n\nfunc main() {\n\tfmt.Println(\"Hello World!\")\n}"},
};

int templates_num = sizeof(templates) / sizeof(struct Template);

void usage(int exit_code) {
	PRINT_VERSION

	fputs("\n\
Usage: [OPTION] ... [TEMPLATE_NAME] \n\
\n\
\t-h\tPrints out this help message and exits\n\
\t-v\tPrints out program version\n\
\t-n\tGive a custom name to the generated file\n\
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

	char* filename = NULL;
	char* selected = NULL;
	int no_write = 0;
	int wanted = -1;
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
				return 0;
			case 'o':
				no_write = 1;
				break;
			case 'n':
				filename = optarg;
				break;
			case '?':
				if (optopt == 'n')
					fprintf (stderr, "Option -%c requires an argument\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}

	selected = argv[optind++];

	if(!selected) {
		printf("You need to select a template, use -h to print help\n");
		return 1;
	}

	for (index = optind; index < argc; index++)
		printf ("%s is not a valid argument\n", argv[index]);

	for(int i = 0; i < templates_num; i++){
		if(strcmp(selected, templates[i].name) == 0) {
			wanted = i;
			break;
		}
	}

	if(wanted == -1) {
		printf("The %s template is not found\n", selected);
		return 1;
	}


	if(no_write) {
		fprintf(stdout, "%s\n", templates[wanted].project_file);
		return 0;
	}

	filename = filename == NULL ? templates[wanted].file_name : filename;
	FILE* file = fopen(filename, "w");

	if(file == NULL) {
		fprintf(stderr, "Error getting file handle\n");
		return 1;
	}

	if(access(filename, W_OK) == 0) {
		printf("%s already exists\n", filename);
		return 0;
	}

	fprintf(file, "%s\n", templates[wanted].project_file);

	fclose(file);

	return 0;
}
