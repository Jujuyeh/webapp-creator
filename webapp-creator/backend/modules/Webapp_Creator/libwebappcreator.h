// The function deletes the email from [maint]
Q_INVOKABLE void noMail(char maint[]);

// The function inserts [name], [desc], [title], [version] and [maint] into
// the corresponding field of manifest.json.
Q_INVOKABLE void insertManifest(char name[], char desc[], char title[], char version[],
					 char maint[], bool ogra);

// The function inserts the corresponding policy groups into the apparmor file.
Q_INVOKABLE void insertApparmor(int groups[], char name[]);

// The function inserts the URLs and settings of the webapp into a desktop file.
Q_INVOKABLE void insertDesktop(char name[], char com[], char title[], char url[], int arg[],
				   char subUrl1[], char subUrl2[], char subUrl3[], int urls[],
				   char PROVIDER[], char USER_AGENT[], bool https, bool ogra);

// This function sets the config.js file of Ogra's alternate webapp container
Q_INVOKABLE void insertConfig (char name[], char maint[], char url[], char subUrl1[], 
				   char subUrl2[], char subUrl3[], int urls[], bool hapticLinks,
				   char USER_AGENT[], bool https, bool UA, bool audibleLinks);

// This function sets the qml files of Ogra's alternate webapp container
Q_INVOKABLE void insertQML (char name[], char maint[]);

// This function creates the Webapp files and folders
Q_INVOKABLE void createFiles(char name[], bool ogra);

// This function generates the click package
Q_INVOKABLE void genClick();

// This function deletes al generated data in /tmp by Webapp Creator
Q_INVOKABLE void cleanTmp();
