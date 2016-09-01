#ifndef ERRORHANDING_HEADER
#define ERRORHANDING_HEADER

#define MAXLINE 128

extern void prt_err(const char *fmt, ...);
extern int  error_handing(void);
extern void errno_specify(void);

#endif
