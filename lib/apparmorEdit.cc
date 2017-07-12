#include <iostream>
#include <cstring>
#include <fstream>
#include "apparmorEdit.h"

using namespace std;

// The function inserts the corresponding policy groups into the apparmor file.
void insertApparmor (int groups[], char name[]){
	fstream f;
	char file[512] = "/tmp/webappCreator/com.ubuntu.";
	strcat(file, name);
	strcat(file, ".apparmor");
	f.open(file);
	f  << "{\n"
	"    \"policy_groups\": [\n";
	if (groups[0]==1){f  << "        \"accounts\",\n";}
	if (groups[1]==1){f  << "        \"audio\",\n";}
	if (groups[2]==1){f  << "        \"calendar\",\n";}
	if (groups[3]==1){f  << "        \"camera\",\n";}
	if (groups[4]==1){f  << "        \"connectivity\",\n";}
	if (groups[5]==1){f  << "        \"contacts\",\n";}
	if (groups[6]==1){f  << "        \"content_exchange\",\n";}
	if (groups[7]==1){f  << "        \"content_exchange_source\",\n";}
	if (groups[8]==1){f  << "        \"debug\",\n";}
	if (groups[9]==1){f  << "        \"history\",\n";}
	if (groups[10]==1){f << "        \"in-app-purchases\",\n";}
	if (groups[11]==1){f << "        \"keep-display-on\",\n";}
	if (groups[12]==1){f << "        \"location\",\n";}
	if (groups[13]==1){f << "        \"microphone\",\n";}
	if (groups[14]==1){f << "        \"music_files\",\n";}
	if (groups[15]==1){f << "        \"music_files_read\",\n";}
	if (groups[16]==1){f << "        \"networking\",\n";}
	if (groups[17]==1){f << "        \"picture_files\",\n";}
	if (groups[18]==1){f << "        \"picture_files_read\",\n";}
	if (groups[19]==1){f << "        \"push-notification-client\",\n";}
	if (groups[20]==1){f << "        \"sensors\",\n";}
	if (groups[21]==1){f << "        \"usermetrics\",\n";}
	if (groups[22]==1){f << "        \"video\",\n";}
	if (groups[23]==1){f << "        \"video_files\",\n";}
	if (groups[24]==1){f << "        \"video_files_read\",\n";}
	if (groups[25]==1){f << "        \"webview\"\n";}
	f << "    ],\n"
	"    \"policy_version\": 1.3\n"
	"}";
	f.close();
}
