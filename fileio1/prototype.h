/* 文件状态标志 */
extern int		get_flag(int fd);
extern int		set_flag(int fd, int flags);
extern int		cls_flag(int fd, int flags);

/* 限制 */
extern long		open_max(void);
extern char		*path_alloc(size_t *sizep);

extern int		stdin_offset(void);
extern int		file_hole(void);
extern int		mycat(void);
extern int		read_write(void);
extern void		offset_bits(void);

extern int		creatat(char *dir_path, char *relative_path);

/* 非阻塞 I/O */
extern int nonblock_write(void);

/* 记录锁 */
extern int		lock_region(int fd, int cmd, int type, off_t offset, int whence, off_t len);
extern pid_t	lock_test(int fd, int type, off_t offset, int whence, off_t len);
