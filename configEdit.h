#define CONFIGEDIT_H
#ifndef CONFIGEDIT_H

// This function sets the config.js file of Ogra's alternate webapp container
void insertConfig (char name[], char maint[], char url[], char subUrl1[], 
				   char subUrl2[], char subUrl3[], int urls[], bool hapticLinks,
				   char USER_AGENT[], bool https, bool UA, bool audibleLinks);

#endif