all:
	gcc grav/main.c grav/cli.c grav/process.c -g -Wall -Werror -pedantic -o grv
