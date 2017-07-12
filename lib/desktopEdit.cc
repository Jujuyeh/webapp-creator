#include <iostream>
#include <fstream>
#include <cstring>
#include "desktopEdit.h"

using namespace std;

// The function inserts the URLs and settings of the webapp into a desktop file.
void insertDesktop(char name[], char com[], char title[], char url[], int arg[],
				   char subUrl1[], char subUrl2[], char subUrl3[], int urls[],
				   char PROVIDER[], char USER_AGENT[], bool https, bool ogra){
	fstream f;
	char file[512] = "/tmp/webappCreator/com.ubuntu.";
	strcat(file, name);
	strcat(file, ".desktop");
	f.open(file);
	f  << "[Desktop Entry]\n"
	"Name=" << title << "\n"
	"Comment= \"" << com << "\"\n"
	"Type=Application\n"
	"Icon=" << name << ".png\n"
	"Exec=";
	if (!ogra) {
		f << "webapp-container";
		if (arg[0]==1) {f << " --fullscreen";}
		if (arg[1]==1) {f << " --accountProvider=" << PROVIDER;}
		if (arg[2]==1) {f << " --accountSwitcher";}
		if (arg[3]==1) {f << " --store-session-cookies";}
		if (arg[4]==1) {f << " --enable-media-hub-audio";}
		if (arg[5]==1) {f << " --user-agent-string=" << USER_AGENT;}
		if (arg[6]==1) {f << " --enable-back-foward";}
		if (arg[7]==1) {f << " --enable-addressbar";}
		
		f << " --webappUrlPatterns=https?://" << url << "/* http";
		if (https) {f << 's';}
		f << "://" << url;
		
		if (urls[0]==1) {
			f << ", http";
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
	}
	else {f << "qmlscene %u qml/Main.qml";}
	f << '\n' <<"Terminal=false\n"
	"X-Ubuntu-Touch=true\n"
	"Name[en_US]=" << name << ".desktop";
	f.close();
}
