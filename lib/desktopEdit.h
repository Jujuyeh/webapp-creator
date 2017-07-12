#define DESKTOPEDIT_H
#ifndef DESKTOPEDIT_H

// The function inserts the URLs and settings of the webapp into a desktop file.
void insertDesktop(char name[], char com[], char title[], char url[], int arg[],
				   char subUrl1[], char subUrl2[], char subUrl3[], int urls[],
				   char PROVIDER[], char USER_AGENT[], bool https, bool ogra);

#endif
