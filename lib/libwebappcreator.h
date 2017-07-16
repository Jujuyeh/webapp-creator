#define LIBWEBAPPCREATOR_H
#ifndef LIBWEBAPPCREATOR_H

// The function inserts [name], [desc], [title], [version] and [maint] into
// the corresponding field of manifest.json.
void insertManifest(char name[], char desc[], char title[], char version[],
					 char maint[]);

// The function inserts the corresponding policy groups into the apparmor file.
void insertApparmor(int groups[], char name[]);

// The function inserts the URLs and settings of the webapp into a desktop file.
void insertDesktop(char name[], char com[], char title[], char url[], int arg[],
				   char subUrl1[], char subUrl2[], char subUrl3[], int urls[],
				   char PROVIDER[], char USER_AGENT[], bool https, bool ogra);

// This function sets the config.js file of Ogra's alternate webapp container
void insertConfig (char name[], char maint[], char url[], char subUrl1[], 
				   char subUrl2[], char subUrl3[], int urls[], bool hapticLinks,
				   char USER_AGENT[], bool https, bool UA, bool audibleLinks);

// This function sets the qml files of Ogra's alternate webapp container
void insertQML (char name[], char maint[]);

// This function creates the Webapp files and folders
void createFiles(char name[], bool ogra);

// This function generates the click package
void genClick();

#endif