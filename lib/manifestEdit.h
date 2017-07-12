#define MANIFESTEDIT_H
#ifndef MANIFESTEDIT_H

// The function inserts [name], [desc], [title], [version] and [maint] into
// the corresponding field of manifest.json.
void insertManifest(char name[], char desc[], char title[], char version[],
					 char maint[]);
					 
#endif
