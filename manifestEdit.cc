#include <iostream>
#include <fstream>
#include "manifestEdit.h"

using namespace std;

// The function inserts [name], [desc], [title], [version] and [maint] into
// the corresponding field of manifest.json.
void insertManifest (char name[], char desc[], char title[], char version[],
					 char maint[]){
	fstream f("/tmp/webappCreator/manifest.json");
	f  << "{\n"
	"    \"name\": \"com.ubuntu." << name << "\",\n"
	"    \"description\": \"" << desc << "\",\n"
	"    \"title\": \"" << title << "\",\n"
	"    \"hooks\": {\n"
	"        \"" << name << "\": {\n"
	"            \"apparmor\": \"com.ubuntu." << name << ".apparmor\",\n"
	"            \"desktop\": \"com.ubuntu." << name << ".desktop\",\n"
	"        }\n"
	"    },\n"
	"    \"version\": \"" << version << "\",\n"
	"    \"maintainer\": \"" << maint <<"\",\n"
	"    \"framework\": \"ubuntu-sdk-15.04.6\"\n"
	"}";
	f.close();
}

int main() {
	char name[] = "baaaanaaana", desc[] = "blablablabla", title[] = "Banana", 
	version[] = "1.3", maint[] = "JUEEEEEEEEEEEE";
	insertManifest(name,desc,title,version,maint);
	return 0;
}