#include <vxworks.h>
#include <fcntl.h>
#include <stdio.h>
#include <ioLib.h>
#include <taskLib.h>
#define F_OK    0
#define R_OK    4
#define X_OK    1
#define W_OK    2


int fcntl(int fd, int cmd, struct flock *lock){
	return 0;
}

int access(const char *pathname, int mode){
	int rc = -1;
	if (mode == F_OK) {
		  FILE* file = fopen(pathname, "r");
		  if (NULL ==file) {
			  rc = -1;
		  }else{
			  fclose(file);
			  rc = 0;
		  }
	}else{
		rc=0;
	}
	return rc;
}

int fsync(int fd){
	int ret;

	/*
	 * The results of ioctl are driver dependent.  Some will return the
	 * number of bytes sync'ed.  Only if it returns 'ERROR' should we
	 * flag it.
	 */
	if ((ret = ioctl(fd, FIOSYNC, 0)) != ERROR)
		return (0);
	return (ret);
}

int fchmod(int fildes,mode_t mode){
	return 0;
}

int getpid(){
	return taskIdSelf();
}

FILE * popen ( const char * command , const char * type ){
	printf("not supported popen.\n");
	return NULL;
}
int pclose ( FILE * stream ){
	return 0;
}

