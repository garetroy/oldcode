/*(-1> 0 ? printf("\nTrue\n") : printf("\nFalse\n")); temporary for understanding syntax*/
/*Open and close a lot for habituation purposes*/
#include "main.h"

int clock_timer(){
	clock_t ti;
	struct tms tie;
	long clockTicks = sysconf(_SC_CLK_TCK);

	ti = times(&tie);
	if(ti == -1){perror("times() failed"); return -1;}

	printf("   User time:%.2f\n   System CPU time: %.2f\n   User CPU time total: %.2f\n   System CPU time total: %.2f\n",
		(double)tie.tms_utime/clockTicks,(double)tie.tms_stime/clockTicks,(double)tie.tms_cutime/clockTicks,(double)tie.tms_cstime/clockTicks);

	return 0;
}

int main(int argc, const char *argv[]){

	if(argc != 2){perror("Shows libc_version through various calls, put in a filename\n"); return -1;};
	
	int fd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	int testing;
	const char *libc_version = gnu_get_libc_version();

	/*Opens file and writes string*/
	openFlags = O_WRONLY | O_CREAT | O_DIRECTORY | O_NOFOLLOW | O_TRUNC | O_APPEND | O_EXCL;
	/*
		Writing Only
		Creates file if file is not already present
		Fails if the pathname is not a directory
		Dosen't derefrence symbolic links on file
		Trunicates the file to position 0
		Appends to the end of the file
		Assures that if created(even by any proccess), then it won't create it again. This
		makes it an "Atomic Process" as well.
	*/
	filePerms = S_IRUSR | S_IWUSR; //User can read & write only

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}
	numRead = write(fd,libc_version,strlen(libc_version));
	if(numRead != strlen(libc_version)){perror("Error writing to file"); close(fd); return -1;}
	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Opens file and seeks to the front and the back adding strings*/
	char *startstring = "Libc Version:";
	char *endstring = "\n";
	int offset;
	openFlags = O_WRONLY | O_NOFOLLOW | O_EXCL;
	filePerms = S_IWUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	offset = lseek(fd, 0, SEEK_SET);
	if(offset == -1){perror("lseek could not go to begging of file"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	numRead = write(fd,startstring,strlen(startstring));
	if(numRead != strlen(startstring)){perror("Did not write startstring"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	numRead = write(fd,libc_version,strlen(libc_version));
	if(numRead != strlen(libc_version)){perror("libc_version could not be written"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	offset = lseek(fd, -1, SEEK_END);
	if(offset == -1){perror("lseek could not go to begging of file"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}
	numRead = write(fd,endstring,strlen(endstring));
	if(numRead != strlen(endstring)){perror("Did not write endstring"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Creates a file hole
		This allows us to write bytes past the end of file, not making the file any bigger
		But sometimes it does take up more disk space(through the kernels doings, so be aware)
		though it is used so that a file can store more data without taking up disk space.
		It takes up space until it's written over.
	*/
	
	char *randomstring = "asdjfalksdjfal;sdkjf";
	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}
	offset = lseek(fd, 10, SEEK_END);
	numRead = write(fd,randomstring,strlen(randomstring));
	if(numRead != strlen(randomstring)){perror("Could not write randomnum"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}
	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Opens, tests(a few) and sets the status Flags*/
	int flags, accessMode;
	openFlags = O_RDONLY| O_NOFOLLOW | O_EXCL;
	filePerms = S_IRUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	flags = fcntl(fd, F_GETFL);
	if(flags == -1){perror("Could not get flags using fcntrl"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	printf("Flags--\n");
	(flags & O_APPEND ? printf("  This shouldn't have the append flag\n"):printf("  No append flag!\n"));

	accessMode = flags & O_ACCMODE;
	(accessMode == O_RDONLY ? printf("  Read only\n"):(accessMode == O_WRONLY? printf("  Write only\n"):printf("  Read & Write\n")));

	flags |= O_APPEND;
	if(fcntl(fd, F_SETFL, flags) == -1){perror("Could not set flags"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;} 
	//Only works with O_APPEND, O_NONBLOCK, O_NOATIME, O_ASYNC, and O_DIRECT 
	//(with some exceptions of modified Unix implementations)

	flags = fcntl(fd, F_GETFL);
	if(flags == -1){perror("Could not get flags using fcntrl"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	(flags & O_APPEND ? printf("  Appened flag added!\n"):printf("  No append flag added\n"));

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Duplicates file three times with dup and dup2. 
		The purpose: Would not share the same file offset pointer*/
	int newFd;
	openFlags = O_RDONLY | O_NOFOLLOW | O_EXCL;
	filePerms = S_IRUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	printf("Utilizing dup--\n");

	newFd = dup(fd); //This duplicates the file finding the loswest fd available and using that fd.
	if(newFd == -1){perror("dup() failed"); return -1;}
	printf("  dup() used the new fd:%d\n", newFd);
	close(newFd);

	newFd = dup2(fd, 17); //This duplicates the file, but with a specified fd, closing the fd if it's already open.
	if(newFd == -1){perror("dup() failed"); return -1;}

	printf("  dup2() used the new fd:17\n");
	
	close(newFd);
	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Opens then uses pread and reads out the rest of the file*/
	char *buff = NULL;
	openFlags = O_RDONLY | O_NOFOLLOW | O_EXCL;
	filePerms = S_IRUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	numRead = pread(fd, &buff, 11, 5);
	if(numRead != 11){perror("pread failed"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	printf("Reading from file--\n  Got this from the pread(starting at offset 5, reading 11 positions over): %s\n", &buff);

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Opens then uses pwrite, putting a string (changing Version to Verzion) */
	buff = "z";
	openFlags = O_WRONLY | O_NOFOLLOW | O_EXCL;
	filePerms = S_IWUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	numRead = pwrite(fd, buff, 1, 8);
	if(numRead == -1){perror("pwrite failed"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Utilizes Scatter-Gather I/O*/
	struct iovec iov[2];
	struct stat newStruct; //random structure for example
	buff = "Hello";
	ssize_t totalReq = 0;
	openFlags = O_WRONLY | O_NOFOLLOW | O_EXCL | O_APPEND;
	filePerms = S_IWUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	iov[0].iov_base = &newStruct; //address of struct added to iovec struct
	iov[0].iov_len = sizeof(struct stat); //len of struct
	totalReq += iov[0].iov_len;

	iov[1].iov_base = buff;
	iov[1].iov_len = 100;
	totalReq += 100;

	numRead = writev(fd, iov, 2);
	if(numRead == -1){perror("writev failed"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Trunicates the file with ftrunicates*/
	openFlags = O_RDWR | O_NOFOLLOW | O_EXCL;
	filePerms = S_IRUSR | S_IWUSR;

	fd = open(argv[1],openFlags,filePerms);
	if(fd == -1){perror("Could not open file"); return -1;}

	if(ftruncate(fd, 14) == -1){perror("ftrunicate failed"); if(close(fd) == -1){perror("close had a problem"); return -1;} return -1;}

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Makes temporary files using tmpfile and mkstemp */
	char template[] = "./tempfileXXXXXX"; //has to be a char array and has to have six X's at end
	FILE *fp = NULL;
	fd = mkstemp(template);
	if(fd == -1){perror("mkstemp could not function correctly"); return -1;}

	unlink(template); //Always have to unlink with mksftemp
	if(close(fd) == -1){perror("close had a problem"); return -1;}

	fp = tmpfile(); //enables stdio modification
	if(fp == NULL){perror("tmpfile had an error"); return -1;}

	if(close(fd) == -1){perror("close had a problem"); return -1;}

	/*Prints Proccess and Parent Proccess ID*/
	pid_t thispid;
	pid_t parentpid;

	printf("Proccess and Parent Proccess ID--\n");

	thispid = getpid(); //"always" successful
	printf("  This is the pid: %d\n", thispid);

	parentpid = getppid();//"always" successful
	printf("  This is the parent proccess ID: %d\n", parentpid);

	/*Gets/Modifies and writes the enviroment*/
	char *termEnviroment = NULL;
	char *shellEnviroment = NULL;
	char *userEnviroment = NULL;
	char *homeEnviroment = NULL;
	char *newenv = "COW=/MOO";
	char *addedenv = NULL;

	termEnviroment = getenv("TERM");
	if(termEnviroment == NULL){perror("getenv failed for TERM"); return -1;}
	shellEnviroment = getenv("SHELL");
	if(shellEnviroment == NULL){perror("getenv failed for SHELL"); return -1;}
	userEnviroment = getenv("USER");
	if(userEnviroment == NULL){perror("getenv failed for USER"); return -1;}
	homeEnviroment = getenv("HOME");
	if(homeEnviroment == NULL){perror("getenv failed for HOME"); return -1;}

	printf("Enviroment--\n  Your terminal is located here: %s\n  Your shell: %s\n  You are: %s\n  Home directory: %s\n",
		termEnviroment,shellEnviroment, userEnviroment, homeEnviroment);

	testing = putenv(newenv);
	if(testing < 0){perror("putenv failed"); return -1;}

	addedenv = getenv("COW");
	if(addedenv == NULL){perror("genv faild for COW"); return -1;}

	printf("  The new enviroment added is COW located at %s\n", addedenv);

	testing = unsetenv("COW");
	if(testing == -1){perror("unsetenv failed"); return -1;}

	addedenv = NULL;
	addedenv = getenv("COW");
	if(addedenv == NULL){printf("  COW removed from enviroment!\n");}

	//setenv is used the same as putenv, except different format setenv(const  char *name, const char *value, int overwrite)
		//returns -1 on error
	//clearenv is used to clear the whole enviroment, not going to use it here (returns non-zero on success)

	/*Utilizing calloc,realloc,alloca*/
	int *p = NULL;
	void *ptrtomem;

	p = calloc(100,sizeof(int)); //Allocates 100 ints in p
	if(p == NULL){perror("calloc failed"); return -1;}

	p = realloc(p, 200000); //Resizes the allocaiton
	if(p == NULL){perror("realloc failed"); return -1;}
	
	free(p);

	p = alloca(1000); //dyamically created on stack, this is good for jumps, also faster than malloc, but not
		//to be used too frequently. Dosen't need to be freed (stack)

	/*Opening Password File, checks for shadow file, reads groups, and writes them*/
	struct passwd *passwdInfo = NULL;
	struct group *groupInfo = NULL;

	passwdInfo = getpwnam(userEnviroment);
	if(passwdInfo == NULL){perror("getpwnam failed"); return -1;}

	//My system has shadowing enabled
	printf("Using pwd file---\n  Login name: %s\n  Encrypted password: %s\n  User ID: %ld\n  Group ID: %ld\n  Additional User Info: %s\n  Initial working dir: %s\n  Login Shell: %s\n",
		passwdInfo->pw_name, passwdInfo->pw_passwd, passwdInfo->pw_uid, passwdInfo->pw_gid, passwdInfo->pw_gecos,
		passwdInfo->pw_dir, passwdInfo->pw_shell);

	groupInfo = getgrgid(passwdInfo->pw_gid);
	if(groupInfo == NULL){perror("getgrgid failed"); return -1;}

	printf("Using group file---\n  Group name: %s\n  Encrypted Password: %s\n  Group ID: %ld\n  First member of group: %s\n",
		groupInfo->gr_name, groupInfo->gr_passwd, groupInfo->gr_gid, groupInfo->gr_mem[0]);

	/*Get's all info about User and Group Info and writes it*/
	struct passwd *pwd = NULL;

	printf("All User and Group Info--\n");
	while((pwd = getpwent()) != NULL)
		printf("  User Name:%s, User ID:%ld\n", pwd->pw_name, pwd->pw_uid);
	endpwent(); //In a way closes the scan
	//can "seek" using setpwent

	/*
	Getting info if shadowfile exists
		Needs to be run as a privliged user to utilize this
	struct spwd *shadowInfo;

	shadowInfo = getspnam(userEnviroment);
	if(shadowInfo == NULL){perror("getspent failed!"); return -1;}
	printf("Using shadow file---\n  Login Name:%s\n  Encrypted Password: %s\n  Last time password changed: %ld\n  Account Expires: %ld\n",
		shadowInfo->sp_namp, shadowInfo->sp_pwdp, shadowInfo->sp_lstchg, shadowInfo->sp_expire);

		Disabled
	*/

	/*Takes advantage of crypt for random char strings
		need to include -lcrypt*/
	char *password1 = NULL;
	char *password2 = NULL;
	char *password3 = NULL;

	password1 = crypt("password", "ac");
	if(password1 == NULL){perror("crypt failed on password1"); return -1;}
	password2 = crypt("dog", "zd");
	if(password2 == NULL){perror("crypt failed on password2"); return -1;}
	password3 = crypt("cat", "ac");
	if(password3 == NULL){perror("crypt failed on password3"); return -1;}

	printf("Utilizing Crypt--\n  Passowrd 1: %s\n  Password 2: %s\n  Password 3: %s\n", password1, password2, password3);

	/*Finds Real, Effective, and saved set IDS and writes them (also explains them)
		Real - Actual PID
		Effective - Determine Permissions grandted to proccess(usually same as real, but can be changed)
			File-system ID's used in place of Effective in linux used with supplementary ID's
		Saved Set - Used for Set-user-id programs

		Parts are disabled because of needing priviliged access
	*/
	uid_t realid;
	uid_t effectiveid;
	//uid_t tempid;
	gid_t realgid;
	gid_t effectivegid;
	//gid_t tempgid;

	//These functions "always" return successful
	realid = getuid();
	effectiveid = geteuid();
	realgid = getgid();
	effectivegid = getegid();

	printf("ID's--\n  Real ID: %ld\n  Effective ID: %ld\n  Real Group ID: %ld\n  Effective Group ID: %ld\n",
		realid, effectiveid, realgid, effectivegid);

	/*
	testing = setuid(2000); //modifiying effective, if priviliged user calls, then all id's changed
	if(testing != 0){perror("setuid failed"); return -1;}
	
	realid = getuid();
	effectiveid = geteuid();
	realgroupid = getgid();
	effectivegroupid = getegid();
	printf("  Changed uid to 2000:\n   Effective ID: %ld\n   Real Group ID: %ld\n   Effective Group ID: %ld\n",
		realid, effectiveid, realgroupid, effectivegroupid);

	testing = setuid(tempid);
	if(testing != 0){perror("setuid failed"); return -1;}

		Disabled
		Following are used to modify other ID's:
			setre(g/u)id - Setting real and effective
			setres(g/u)id - Setting all ID's
			setfs(g/u)id - Setting File-System ID's
	*/


	/*Get's time, modifiying times multiple ways utilizing ctime,gmtime,localtime,mktime,asctime,strftime,currTime&strptime*/
	time_t t;
	time_t mkt;
	struct timeval tv;
	struct tm *gmt;
	struct tm *localt;
	struct tm *outputt;
	char *ct = NULL;
	char *asct = NULL;
	size_t strft;
	buff = NULL;
	const char *format = "%A %B %d at %T %Z";
	char *testingc = NULL;

	t = time(NULL); //time_t
	if(time == -1){perror("time() failed"); return -1;}

	testing = gettimeofday(&tv, NULL); //timeval
	if(testing != 0){perror("gettimeofday() failed"); return -1;}

	printf("Calendar time--\n  Seconds from EPOC(time() function): %ld\n  Seconds(and microseconds) from EPOC(gettimeofday()): %ld.%ld\n",
		t, tv.tv_sec, tv.tv_usec);

	ct = ctime(&t); //time_t to fixed format
	if(ct == NULL){perror("ctime() failed"); return -1;}

	gmt = gmtime(&t); //time_t to tm
	if(gmt == NULL){perror("gmtime() failed"); return -1;}

	localt = localtime(&t); //time_t to tm
	if(localt == NULL){perror("localtime() failed"); return -1;}

	mkt = mktime(localt); //tm to time_t
	if(mkt == -1){perror("mktime() failed"); return -1;}

	asct = asctime(localt);//tm to fixed format
	if(asct == NULL){perror("asctime() failed"); return -1;}

	printf("  Mktime Seconds from EPOC: %ld\n  Ctime: %s  Gmtime: %d:%d:%d %d/%d/%d\n  Localtime: %d:%d:%d %d/%d/%d\n  Asctime: %s", 
		mkt,ct,gmt->tm_hour,gmt->tm_min,gmt->tm_sec,gmt->tm_mon,gmt->tm_mday,(gmt->tm_year + 1900),
		localt->tm_hour,localt->tm_min,localt->tm_sec,localt->tm_mon,localt->tm_mday,(localt->tm_year + 1900),asct);

	//strft = strftime(buff, 1000, format, localt); //tm to desired format
	//if(strft == 0){perror("strftime failed"); return -1;}

	/*Adjusting locals and clock
		char *setlocal(int category, char *locale) returns NULL on fail
		int settimeofday(const struct timeval *tv, const struct timezone *tz) returns 0 if successful
		int adjtime(struct timeval *new, struct timeval *old), returns 0 if successful

		This is just written out for future reference, don't want to modify my locals/clock
	*/

	/*Finding total and CPU process time */
	int i = 0;

	printf("Process time--\n  Before while loop:\n");

	testing = clock_timer();
	if(testing == -1){perror("clock_timer() failed"); return -1;}

	while(i != 2){
		sleep(1);
		++i;
	}

	printf("  After while loop:\n");
	testing = clock_timer();
	if(testing == -1){perror("clock_timer() failed"); return -1;}

	/*Finding System Limits */
	long argmax; //maximum arguments possible
	long loginnamemax; //max size of login
	long openmax; //max file discriptors a proccess can have open
	long groupsmax; //Max number of supp groups of which a proccess can be a member
	long maxsigque; //Max number of qued realtime signals
	long maxpath; //maximum number a bytes ina filename

	argmax = sysconf(_SC_ARG_MAX);
	if(argmax == -1){perror("sysconf on _SC_ARG_MAX failed"); return -1;}
	loginnamemax = sysconf(_SC_LOGIN_NAME_MAX);
	if(loginnamemax == -1){perror("sysconf on _SC_LOGIN_NAME_MAX failed"); return -1;}
	openmax = sysconf(_SC_OPEN_MAX);
	if(openmax == -1){perror("sysconf on _SC_OPEN_MAX failed"); return -1;}
	groupsmax = sysconf(_SC_NGROUPS_MAX);
	if(groupsmax == -1){perror("sysconf on _SC_NGROUPS_MAX failed"); return -1;}
	maxsigque = sysconf(_SC_SIGQUEUE_MAX);
	if(maxsigque == -1){perror("sysconf on _SC_SIGQUEUE_MAX failed"); return -1;}
	maxpath = sysconf(_PC_PATH_MAX);
	if(maxpath == -1){perror("sysconf on _PC_PATH_MAX failed"); return -1;}

	printf("System Limits--\n  Maximum Arguments: %ld\n  Maximum size of login name: %ld\n  Maximum file discriptors a proccess can have open: %ld\n",
		argmax,loginnamemax,openmax);
	printf("  Maximum number of support groups which a process can be a member of: %ld\n  Max number of qued realtime signals: %ld\n  Max number of bytes in filename: %ld\n",
		groupsmax,maxsigque,maxpath);

	/*System ID using uname*/
	struct utsname sysid;

	testing = uname(&sysid);
	if(testing != 0){perror("uname failed"); return -1;}

	printf("System Identification--\n  Implementation name:%s\n  Node name(network):%s\n  Relase: %s\n  Version: %s\n  Machine:%s\n",
		sysid.sysname,sysid.nodename,sysid.release,sysid.version,sysid.machine);

	return 0;

}