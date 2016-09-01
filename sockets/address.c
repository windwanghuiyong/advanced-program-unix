#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

#if defined(BSD)
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#if defined(SOLARIS)
#include <netinet/in.h>
#endif

/********************************
    打印自定义处理地址和名字的方式
********************************/
void print_flags(struct addrinfo *addrinfo_ptr)
{
    printf("flag: ");
    if (addrinfo_ptr->ai_flags == 0)
        printf("0\n");
    else
    {
		if (addrinfo_ptr->ai_flags & AI_ADDRCONFIG)		// 查询配置的地址类型
            printf("addrconfig\n");
        if (addrinfo_ptr->ai_flags & AI_PASSIVE)		// 套接字地址用于监听绑定
            printf("passive\n");
        if (addrinfo_ptr->ai_flags & AI_CANONNAME)		// 需要一个规范的名字
            printf("cannon\n");
        if (addrinfo_ptr->ai_flags & AI_NUMERICHOST)	// 以数字格式指定主机地址
            printf("numhost\n");
        if (addrinfo_ptr->ai_flags & AI_NUMERICSERV)	// 将服务指定为数字端口号
            printf("numserv\n");
        if (addrinfo_ptr->ai_flags & AI_V4MAPPED)		// 如果没有找到 IPv6 地址, 返回映射到 IPv6 格式的 IPv4 地址
            printf("v4mapped\n");
        if (addrinfo_ptr->ai_flags & AI_ALL)			// 查找 IPv4 和 IPv6 地址
            printf("all\n");
    }
}

/**********************
    打印套接字通信域
**********************/
void print_family(struct addrinfo *addrinfo_ptr)
{
    printf("family: ");
    switch (addrinfo_ptr->ai_family) {
        case AF_INET:
            printf("inet\n");
            break;
        case AF_INET6:
            printf("inet6\n");
            break;
        case AF_UNIX:
            printf("unix\n");
            break;
        case AF_UNSPEC:
            printf("unspecified\n");
            break;
        default:
            printf("unknown\n");
    }
}

/**********************
    打印套接字类型
**********************/
void print_socktype(struct addrinfo *addrinfo_ptr)
{
    printf("socktype: ");
    switch (addrinfo_ptr->ai_socktype)
    {
        case SOCK_STREAM:
            printf("stream\n");
            break;
        case SOCK_DGRAM:
            printf("datagram\n");
            break;
        case SOCK_SEQPACKET:
            printf("seqpacket\n");
            break;
        case SOCK_RAW:
            printf("raw\n");
            break;
        default:
            printf("unknown(%d)\n", addrinfo_ptr->ai_socktype);
    }
}

/*************************
    打印因特网域套接字协议
*************************/
void print_protocol(struct addrinfo *addrinfo_ptr)
{
    printf("protocol: ");
    switch (addrinfo_ptr->ai_protocol) {
        case 0:
            printf("default\n");
            break;
        case IPPROTO_TCP:
            printf("TCP\n");
            break;
        case IPPROTO_UDP:
            printf("UDP\n");
            break;
        case IPPROTO_RAW:
            printf("raw\n");
            break;
        default:
            printf("unknown(%d)\n", addrinfo_ptr->ai_protocol);
    }
}

void print_hint_flags()
{
	printf("%xH\n", AI_PASSIVE);
	printf("%xH\n", AI_CANONNAME);
	printf("%xH\n", AI_NUMERICHOST);
	printf("%xH\n", AI_ALL);
	printf("%xH\n", AI_ADDRCONFIG);
	printf("%xH\n", AI_V4MAPPED);
	printf("%xH\n", AI_NUMERICSERV);
	return;
}
	
/********************************
	实例 16-9
	usage: nodename service
	第1个参数: MacBook.local
	第2个参数: ftp nfs
********************************/
int print_addr_info(char *hostname, char *servname)
{
    struct addrinfo		*addrinfo_list;
	struct addrinfo		*addrinfo_ptr;
    struct addrinfo		hint;						// 链表结构
    struct sockaddr_in	*sinp;						// IPv4 域套接字地址格式
    const char			*addr;
    int					err;
    char				abuf[INET_ADDRSTRLEN];		// IPv4地址长度

    /* 初始化链表结构 */
    hint.ai_flags     = AI_CANONNAME;
    hint.ai_family    = 0;
    hint.ai_socktype  = 0;
    hint.ai_protocol  = 0;
    hint.ai_addrlen   = 0;
	hint.ai_addr      = NULL;
    hint.ai_canonname = NULL;
    hint.ai_next      = NULL;

    if ((err = getaddrinfo(hostname, servname, &hint, &addrinfo_list)) != 0)
        printf("getaddrinfo error: %s\n", gai_strerror(err));

    for (addrinfo_ptr = addrinfo_list; addrinfo_ptr != NULL; addrinfo_ptr = addrinfo_ptr->ai_next)
    {
        printf("-------------------------\n");
        print_flags(addrinfo_ptr);
        print_family(addrinfo_ptr);
        print_socktype(addrinfo_ptr);
        print_protocol(addrinfo_ptr);
        printf("addrlen: %d\n", addrinfo_ptr->ai_addrlen);

        if (addrinfo_ptr->ai_family == AF_INET)
        {
            sinp = (struct sockaddr_in *) addrinfo_ptr->ai_addr; //通用套接字地址格式强制转换成 IPv4 域套接字地址格式
            addr = inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);  //二进制格式转换成点分十进制格式
            printf("address: %s\n", addr ? addr : "unknown");
            printf("port: %d\n", ntohs(sinp->sin_port));    //网络字节序转换成主机字节序
        }
        printf("host: %s\n", addrinfo_ptr->ai_canonname ? addrinfo_ptr->ai_canonname : "-");
    }
    printf("-------------------------\n");
    return 0;
}

/********************
	获取主机环境信息
********************/
void get_hostent(void)
{
    struct hostent *myhost;
	
	sethostent(1);
    while ((myhost = gethostent()) != NULL)
	{
		
		
		printf("hostname: %s\n",  myhost->h_name);
		printf("aliases:  %s\n", *myhost->h_aliases);
		printf("addrtype: ");
		switch (myhost->h_addrtype) 
		{
			case AF_INET:
				printf("inet\n");
				break;
			case AF_INET6:
				printf("inet6\n");
				break;
			case AF_UNIX:
				printf("unix\n");
				break;
			case AF_UNSPEC:
				printf("unspecified\n");
				break;
			default:
				printf("unknown\n");
		}
		printf("h_length: %d bytes\n",  myhost->h_length);
		printf("addrlist: %s\n", *myhost->h_addr_list);
		printf("\n");
	}
	endhostent();
	return;
}

/**************************
	获取网络名称和网络编号
**************************/
void get_netent(void)
{
	struct netent *mynet;
	
	setnetent(1);
	while ((mynet = getnetent()) != NULL)
		printf("netname: %s\n", mynet->n_name);
	endnetent();
	return;
}

/**************************
	获取协议名称和协议编号
**************************/
void get_protoent(void)
{
	struct protoent *myproto;
	
	setprotoent(1);
	while ((myproto = getprotoent()) != NULL)
		printf("protoname: %s\n", myproto->p_name);
	endprotoent();
	return;
}

/**************************
	获取服务名称和端口号
**************************/
void get_servent(void)
{
	struct servent *myserv;
	
	setservent(1);
	while ((myserv = getservent()) != NULL)
		printf("servname: %s\n", myserv->s_name);
	endservent();
	return;
}
