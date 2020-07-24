#ifndef _CONFIG_H_  
#define _CONFIG_H_  

#ifndef SQLITE_OMIT_LOAD_EXTENSION
#define SQLITE_OMIT_LOAD_EXTENSION 1   // 不需要动态库支持
#endif  
#define HAVE_UTIME                          // 使用utime函数而不是utimes函数  
#include <semaphore.h> 
/*  
* 不使用VxWorks提供的POSIX标准中的互斥信号量递归接口,因为对于内核程序,POSIX支持* 的不是太好 
*/  
#define SQLITE_HOMEGROWN_RECURSIVE_MUTEX    1

#ifndef _LINUX
#include <vxWorks.h> 
#endif

#define _BSD_SOURCE
#define	_POSIX_SOURCE
     
#define PROT_READ       0x1             /* page can be read */
#define PROT_WRITE      0x2             /* page can be written */
#define MAP_SHARED      0x01            /* Share changes */
#define MAP_FAILED ((void *) -1)
#define SEM_FAILED ((sem_t *)(-1))
#define F_OK 0
#define W_OK 2
#define R_OK 4
      
#define register_t unsigned int

#define	PAD_(t)	(sizeof(register_t) <= sizeof(t) ? \
		0 : sizeof(register_t) - sizeof(t))
      
struct proc;      
      
struct	access_args {
	char *path;
	char path_[PAD_(char *)];
	int	flags;
	char flags_[PAD_(int)];
};
int	access __P((struct proc *, struct access_args *));      

struct	fcntl_args {
	int	fd;	char fd_[PAD_(int)];
	int	cmd;	char cmd_[PAD_(int)];
	long	arg;	char arg_[PAD_(long)];
};
int	fcntl __P((struct proc *, struct fcntl_args *));

struct	fchmod_args {
	int	fd;	char fd_[PAD_(int)];
	int	mode;	char mode_[PAD_(int)];
};
int	fchmod __P((struct proc *, struct fchmod_args *));
      
struct	mmap_args {
	caddr_t	addr;	char addr_[PAD_(caddr_t)];
	size_t	len;	char len_[PAD_(size_t)];
	int	prot;	char prot_[PAD_(int)];
	int	flags;	char flags_[PAD_(int)];
	int	fd;	char fd_[PAD_(int)];
	int	pad;	char pad_[PAD_(int)];
	off_t	pos;	char pos_[PAD_(off_t)];
};
int	mmap __P((struct proc *, struct mmap_args *));
      
struct	munmap_args {
	void *	addr;	char addr_[PAD_(void *)];
	size_t	len;	char len_[PAD_(size_t)];
};
int	munmap __P((struct proc *, struct munmap_args *));
      
      
      
#endif // _CONFIG_H_  
