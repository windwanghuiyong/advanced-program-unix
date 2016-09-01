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
