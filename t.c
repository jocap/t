#include <assert.h>
#include <err.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char** nargv;
	int exists, r;

	/* get title of current window */

	char* title = reallocarray(NULL, PATH_MAX, sizeof(char));
	if (title == NULL) err(1, "reallocarray");

	FILE* p = popen("xtitle", "r");
	if (p == NULL) err(1, "popen");

	int c;
	int len = 0;
	while ((c = getc(p)) != EOF) {
		if (len >= PATH_MAX) errx(1, "title is too long");
		title[len] = c;
		len++;
	}
	title[len-1] = 0; /* remove newline */

	r = pclose(p);
	if (r == -1) err(1, "pclose");

	if (title[0] != '/') {
		exists = 0;
		goto create_argv;
	}

	/* check if title matches directory (or file) */

	struct stat s;

check:

	r = stat(title, &s);
	if (r == -1) {
		if (errno == ENOENT) exists = 0;
		else err(1, "stat");
	} else {
		exists = 1;
	}

	/* if file, get dirname instead */

	if (!S_ISDIR(s.st_mode)) {
		char* newtitle = dirname(title);
		if (newtitle == NULL) err(1, "dirname");
		title = newtitle;
		goto check;
	}

	/* create new argv */

create_argv:

	nargv = reallocarray(NULL, argc + 3, sizeof(char*));
	if (nargv == NULL) err(1, "reallocarray");

	int i;
	nargv[0] = "urxvtc";
	if (exists) {
		nargv[1] = "-cd";
		nargv[2] = title;
		i = 3;
	} else {
		i = 1;
	}

	nargv[i] = NULL;

	if (argc > 1) {
		nargv[i++] = "-e";
		for (int j = 1; j <= argc; j++) {
			nargv[i++] = argv[j];
		}
	}

	/* launch terminal emulator */

	execvp(nargv[0], nargv);
	err(1, "execvp");
}
