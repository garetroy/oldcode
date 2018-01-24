#ifndef MAIN_H
#define MAIN_H

#define _XOPEN_SOURCE
#define __USE_XOPEN
#define _GNU_SOURCE
#include <gnu/libc-version.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <errno.h>
#include <crypt.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <alloca.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <sys/time.h>
#include <sys/times.h>
#include <time.h>
#include <limits.h>
#include <sys/utsname.h>


#define BUFF_SIZE 1024

typedef enum
{
	false,
	true

} Bool;

int clock_timer();


#endif