#ifndef _STATUS_H
#define _STATUS_H

typedef enum {
	OK,
	ERROPEN,
	ERRACCESS,
	ERRCLOSE,
	ERRALLOC,
	ERRDATE,
	ERRFULL,
	ERREMPTY,
	ERRABSENT,
	ERREXIST,
	ERRINDEX,
	ERRUNABLE,	
	ERRUNKNOWN,
} status;

extern char* message(status s);

#endif //_STATUS_H
