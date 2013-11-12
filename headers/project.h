/**
 * header of definitions that are important throughout the project
 * 
 * @author Liam Cusack
 */

#define CHARDEV_NAME "/proc/whatever"
#define FREEZEDIR "/freezer/"
#define RESTOREDIR "/freezer_restore/"
#define LOG_NAME "logfile.txt"
#define LOG_FORMAT "%d %s"
#define DELIM '\n'

/*make the userspace helper take one of these enums */
typedef enum{
	CREATE, //write to the log
	MODIFY, //writes to the log, makes a copy of the file
	DELETE  //makes a copy of the file that we are deleting
} change_type_t;

