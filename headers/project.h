/**
 * header of definitions that are important throughout the project
 * 
 * @author Liam Cusack
 */

#define CHARDEV_NAME "/proc/whatever"
#define FREEZEDIR "/freezer/"
#define RESTOREDIR "/freezer_restore/"
#define LOG_NAME "logfile.txt"
#define LOG_FORMAT " %c %s"
#define DELIM '\n'

typedef enum{
	CREATE,
	MODIFY,
	DELETE
} change_type_t;

