#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define TEST printf("[(%s/%d) %s ]\n", __FILE__, __LINE__, __func__); fflush(stdin);
#define TEST_ printf("---------------------------------------------[(%s/%d) %s ]\n", __FILE__, __LINE__, __func__); fflush(stdin);
#define TESTn(i) printf("[(%s/%d) %s ]%s:%ld\n", __FILE__, __LINE__, __func__, #i, (long)(i)); fflush(stdin);
#define TESTu(i) printf("[(%s/%d) %s ]%s:%lu\n", __FILE__, __LINE__, __func__, #i, (unsigned long)(i)); fflush(stdin);
#define TESTx(i) printf("[(%s/%d) %s ]%s:%lx\n", __FILE__, __LINE__, __func__, #i, (unsigned long)(i)); fflush(stdin);
#define TESTd(i) printf("[(%s/%d) %s ]%s:%lf\n", __FILE__, __LINE__, __func__, #i, (double)(i)); fflush(stdin);
#define TESTp(i) printf("[(%s/%d) %s ]%s:%p\n", __FILE__, __LINE__, __func__, #i, (i)); fflush(stdin);
#define TIME printf("[(%s/%d) %s ]%lf[s]\n", __FILE__, __LINE__, __func__, time_diff()); fflush(stdin);
#define STOP {char c; read(STDIN_FILENO, &c, sizeof(char));}

double	time_diff(void);

#ifndef double_time_diff_void
	#define double_time_diff_void
	double	time_diff(void)
	{
		static struct timespec	p = {0};
		struct timespec			n;
		unsigned int			sec;
		int						nsec;
		if (!p.tv_sec)
		{
			clock_gettime(CLOCK_REALTIME, &p);
			return (0);
		}
		clock_gettime(CLOCK_REALTIME, &n);
		sec = n.tv_sec - p.tv_sec;
		nsec = n.tv_nsec - p.tv_nsec;
		p = n;
		return ((double)sec + (double)nsec / (1000 * 1000 * 1000));
	}
#endif


#endif

/* 一定回数でプログラムを強制終了 */

//* test */static	size_t stc = 0;
//* test */const int stc_max = 10000;
//* test */const int onoff = 1;
//* test */stc++;
//* test */if (stc > stc_max && onoff)
//* test */{
//* test */	printf("the number is too big"); TEST
//* test */	exit(0);
//* test */}

/* 時間を計測 */
//* test */	double	time_diff(void)
//* test */	{
//* test */		static struct timespec	p = {0};
//* test */		struct timespec			n;
//* test */		unsigned int			sec;
//* test */		int						nsec;
//* test */
//* test */		if (!p.tv_sec)
//* test */		{
//* test */			clock_gettime(CLOCK_REALTIME, &p);
//* test */			return (0);
//* test */		}
//* test */		clock_gettime(CLOCK_REALTIME, &n);
//* test */		sec = n.tv_sec - p.tv_sec;
//* test */		nsec = n.tv_nsec - p.tv_nsec;
//* test */		p = n;
//* test */		return ((double)sec + (double)nsec / (1000 * 1000 * 1000));
//* test */	}



/*ショートカット


#include "debug.h"

#ifndef _H 
#include ""
#endif





 */
