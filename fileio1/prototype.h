extern int  stdin_offset(void);
extern long get_open_max(void);
extern int  file_hole(void);
extern int  mycat(void);
extern int  read_write(void);
extern void offset_bits(void);
extern int  get_flag(int fd);
extern int  set_flag(int fd, int flags);
extern int  cls_flag(int fd, int flags);
extern int  creatat(char *dir_path, char *relative_path);

#include <fcntl.h>
int		open(const char *path, int oflag, ... /* mode_t mode */);
int		openat(int fd, const char *path, int oflag, ... /* mode_t mode */);
int		create(const char *path, mode_t mode);
int		fcntl(int fd, int cmd, ... /* int arg */);
#include <unistd.h>
int		close(int fd);
off_t	lseek(int fd, off_t offset, int whence);
ssize_t	read(int fd, void *buf, size_t nbytes);
ssize_t	write(int fd, const void *buf, size_t nbytes);
ssize_t	pread(int fd, void *buf, size_t nbytes, off_t offset);
ssize_t	pwrite(int fd, const void *buf, size_t nbytes, off_t offset);
int		dup(int fd);
int		dup2(int fd, int fd2);
int		fsync(int fd);
int		fdatasync(int fd);
void	sync(void);
// #include <sys/ioctl.h>
int ioctl(int fd, int request, ...);
