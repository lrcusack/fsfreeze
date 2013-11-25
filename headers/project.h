/**
 * header of definitions that are important throughout the project
 * 
 * @author Liam Cusack
 */

#define CHARDEV_NAME "/dev/chardev"
#define FREEZEDIR "/freezer/"
#define RESTOREDIR "/freezer_restore/"
#define LOG_NAME "/freezer_restore/logfile.txt"
#define LOG_FILE "logfile.txt"
#define LOG_FORMAT " %c %s"
#define DELIM '\n'
#define BUFLEN 64

<<<<<<< HEAD
/*make the userspace helper take one of these enums */
typedef enum{
	CREATE, //write to the log
	MODIFY, //writes to the log, makes a copy of the file
	DELETE  //makes a copy of the file that we are deleting
} change_type_t;
=======
>>>>>>> 8f5f378f6e404a4918220dad75cd730eb41cc4b2

