#include <iostream>
#include <fstream>
#include "configEdit.h"

using namespace std;

// This function sets the config.js file of Ogra's alternate webapp container
void insertConfig (char name[], char maint[], char url[], char subUrl1[], 
				   char subUrl2[], char subUrl3[], int urls[], bool hapticLinks,
				   char USER_AGENT[], bool https, bool UA, bool audibleLinks){
	fstream f;
	f.open("/tmp/webappCreator/config.js");
	f  << "var webappName = \"" << name << '.' << maint << "\"\n"
	"var webappUrl = \"http";
	if (https) {f << 's';}
	f  << "://" << url <<"/\",\n"
	"var webappUrlPattern = \"";
	if (urls[0]==1) {
		f << "http";
		if (https) {f << 's';}
		f << "://" << subUrl1;
	}
	if (urls[1]==1) {
		f << ", http";
		if (https) {f << 's';}
		f << "://" << subUrl2;
	}
	if (urls[2]==1) {
		f << ", http";
		if (https) {f << 's';}
		f << "://" << subUrl3;
	}
	f << "\"\n";
	if (UA) {f << "var webappUA = \"" << USER_AGENT << "\"\n";}
	if (hapticLinks) {f << "var hapticLinks = \"true\"\n";}
	if (audibleLinks) {f << "var audibleLinks = \"true\"\n";}
	f.close();
}