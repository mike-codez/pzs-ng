#ifndef _ZSFUNCTIONS_H_
#define _ZSFUNCTIONS_H_

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#ifdef	USE_HSREGEX
 #include "hsregex.h"
#else
 #include <regex.h>
#endif
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/param.h>
#include <unistd.h>
#ifndef PATH_MAX
#define _LIMITS_H_
 #ifdef _SunOS_
  #include <syslimits.h>
 #else
  #include <sys/syslimits.h>
 #endif
#endif

#ifndef PATH_MAX
 #define PATH_MAX 1024
 #define NAME_MAX 255
 #define _ALT_MAX
#endif

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "objects.h"
#include "macros.h"
#ifdef _WITH_SS5
#include "constants.ss5.h"
#else
#include "constants.h"
#endif

#if ( debug_mode == TRUE )
#include <stdarg.h>
#endif

#define createzerofile(filename) fclose(fopen(filename, "a+"))

/*
 * Remove the portion of PARAM matched by PATTERN according to OP, where OP
 * can have one of 4 values: RP_LONG_LEFT    remove longest matching portion
 * at start of PARAM RP_SHORT_LEFT   remove shortest matching portion at
 * start of PARAM RP_LONG_RIGHT   remove longest matching portion at end of
 * PARAM RP_SHORT_RIGHT  remove shortest matching portion at end of PARAM
 */

#define RP_LONG_LEFT    1
#define RP_SHORT_LEFT   2
#define RP_LONG_RIGHT   3
#define RP_SHORT_RIGHT  4

struct GROUP {
	char           *name;
	gid_t		id;
};

struct USER {
	char           *name;
	uid_t		id;
};

/*extern struct USERINFO **userI;
extern struct GROUPINFO **groupI;
extern struct VARS raceI;*/
extern struct dirent **dirlist;
extern unsigned int direntries;

extern void	d_log(char *,...);

extern void	create_missing(char *);
extern char    *findfileext(DIR *, char *);
extern char    *findfileextsub(const char *, char *, char *);
extern char    *findfileextparent(DIR *, char *);
extern char    *findfileextfromlist(DIR *, char *);

extern int	findfileextcount(DIR *, char *);
extern int	file_count(DIR *);
extern unsigned int hexstrtodec(char *);
#if defined(__linux__) || defined(__NetBSD__)
extern int	selector(const struct dirent *);
#else
extern int	selector(struct dirent *);
#endif

/*extern void	rescandir(int);
extern void	rescanparent(int);*/
extern void	del_releasedir(DIR *, char *);
extern void	strtolower(char *);
extern void	space_to_dot(char *);
extern void	unlink_missing(char *);
extern char	israr(char *);
//extern char	isvideo(char *);
extern void	buffer_progress_bar(struct VARS *);
extern void	move_progress_bar(unsigned char, struct VARS *, struct USERINFO **, struct GROUPINFO **);
extern int	check_dupefile(DIR *, char *);
extern long	findfile(DIR *, char *);
extern char    *findfilename(char *, char *, struct VARS *);
extern char    *check_nocase_linkname(char *, char *);
extern void	removedotfiles(DIR *);
extern void	removecomplete(int);
extern short	matchpath(char *, char *);
extern short	matchpartialpath(char *, char *);
extern short	matchpartialdirname(char *, char *, char *);
extern short	strcomp(char *, char *);
extern short	subcomp(char *, char *);
extern short	fileexists(char *);
extern void	createlink(char *, char *, char *, char *);
extern void	readsfv_ffile(struct VARS *);
extern void	get_rar_info(char *, struct VARS *);
extern int	execute(char *);

#ifdef USING_GLFTPD
extern char    *get_g_name(int);
extern char    *get_u_name(int);
extern int	buffer_groups(char *, int);
extern int	buffer_users(char *, int);
#endif

extern off_t	sfv_compare_size(char *, off_t);
extern void	mark_as_bad(char *);
extern int	extractDirname(char *dirname, char *absoluteDirname);
extern void     createstatusbar(const char *bar);
extern int      chmod_each(const char *list, mode_t mode);


/* split from zsipscript-c.c */
extern void writelog(GLOBAL *, char *, char *);
extern void buffer_paths(GLOBAL *, char [2][PATH_MAX], int *, int);
extern void remove_nfo_indicator(GLOBAL *);
extern void remove_sample_indicator(GLOBAL *);
extern void getrelname(GLOBAL *);
extern unsigned char get_filetype(GLOBAL *, char *);

#if ( audio_group_sort == TRUE )
extern char *remove_pattern(char *, char *, int);
#endif
extern void    *ng_realloc(void *, int, int, int, struct VARS *, int);
extern void    *ng_realloc2(void *, int, int, int, int);
extern void    *ng_free(void *);
extern int	copyfile(char *, char *);
extern int	make_sfv(char *);
extern unsigned int match_lenient(DIR *, char *);
extern unsigned int insampledir(char *);
#endif

extern int _err_file_banned(const char *fn, struct VARS *v);
