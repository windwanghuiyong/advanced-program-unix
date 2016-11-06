#include <sys/types.h>
#include <unistd.h>

extern int	signal_handler(void);
extern void print_mask(const char *str);
extern void initSigSetHandler(void);
extern void tellParent(pid_t pid);
extern void waitParent(void);
extern void tellChild(pid_t pid);
extern void waitChild(void);
