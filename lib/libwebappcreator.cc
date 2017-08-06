#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include "libwebappcreator.h"

using namespace std;

const char workPath[] = "/home/phablet/.cache/webapp-creator.jujuyeh/webappCreator/", soundPath[] = "/opt/click.ubuntu.com/webapp-creator.jujuyeh/current/extras/Click.wav", genericIcon[] = "/opt/click.ubuntu.com/webapp-creator.jujuyeh/current/share/qml/webapp-creator/placeholder-app-icon.svg"; //UBUNTU TOUCH
// const char workPath[] = "~/webappCreator/", soundPath[]="~/Click.wav", genericIcon[] = "~/placeholder-app-icon.svg"; //DESKTOP


// The function inserts [name], [desc], [title], [version], [alias] and [maint] into
// the corresponding field of manifest.json.
void insertManifest (char name[], char desc[], char title[], char version[],
					 char alias[], char maint[], bool ogra){
	char file[] = "";
	strcat(file,workPath);
	strcat(file,"manifest.json");
	fstream f(file);
	f  << "{\n"
	"    \"description\": \"" << desc << "\",\n"
	"    \"framework\": \"ubuntu-sdk-15.04.6\",\n"
	"    \"hooks\": {\n"
	"        \"" << name << "\": {\n";
	if (ogra) {
		f << "            \"apparmor\": \"app.json\",\n"
		"            \"desktop\": \"app.desktop\"\n";
	}
	else {
		f << "            \"apparmor\": \"" << name << ".apparmor\",\n"
		"            \"desktop\": \"" << name << ".desktop\"\n";
	}
	f << "        }\n"
	"    },\n"
	"    \"maintainer\": \"" << maint << "\",\n"
	"    \"name\": \"" << name << '.' << alias << "\",\n"
	"    \"title\": \"" << title << "\",\n"
	"    \"version\": \"" << version << "\"\n"
	"}";
	f.close();
}

// The function inserts the corresponding policy groups into the apparmor file.
void insertApparmor (char groups[], char name[], bool ogra){
	char file[] = "";
	strcat(file,workPath);
	if (ogra) {
		strcat(file,"app.json");
	}
	else {
		strcat(file,name);
		strcat(file,".apparmor");
	}
	fstream f(file);
	f  << "{\n";
	if (!ogra) { f  << "    \"template\": \"ubuntu-webapp\",\n";}
	f  << "    \"policy_groups\": [\n";
	if (groups[0]=='1'){f  << "        \"accounts\",\n";}
	if (groups[1]=='1'){f  << "        \"audio\",\n";}
	if (groups[2]=='1'){f  << "        \"calendar\",\n";}
	if (groups[3]=='1'){f  << "        \"camera\",\n";}
	if (groups[4]=='1'){f  << "        \"connectivity\",\n";}
	if (groups[5]=='1'){f  << "        \"contacts\",\n";}
	if (groups[6]=='1'){f  << "        \"content_exchange\",\n";}
	if (groups[7]=='1'){f  << "        \"content_exchange_source\",\n";}
	if (groups[8]=='1'){f  << "        \"debug\",\n";}
	if (groups[9]=='1'){f  << "        \"history\",\n";}
	if (groups[10]=='1'){f << "        \"in-app-purchases\",\n";}
	if (groups[11]=='1'){f << "        \"keep-display-on\",\n";}
	if (groups[12]=='1'){f << "        \"location\",\n";}
	if (groups[13]=='1'){f << "        \"microphone\",\n";}
	if (groups[14]=='1'){f << "        \"music_files\",\n";}
	if (groups[15]=='1'){f << "        \"music_files_read\",\n";}
	if (groups[16]=='1'){f << "        \"networking\",\n";}
	if (groups[17]=='1'){f << "        \"picture_files\",\n";}
	if (groups[18]=='1'){f << "        \"picture_files_read\",\n";}
	if (groups[19]=='1'){f << "        \"push-notification-client\",\n";}
	if (groups[20]=='1'){f << "        \"sensors\",\n";}
	if (groups[21]=='1'){f << "        \"usermetrics\",\n";}
	if (groups[22]=='1'){f << "        \"video\",\n";}
	if (groups[23]=='1'){f << "        \"video_files\",\n";}
	if (groups[24]=='1'){f << "        \"video_files_read\",\n";}
	if (groups[25]=='1'){f << "        \"webview\"\n";}
	f << "    ],\n"
	"    \"policy_version\": 1.3\n"
	"}";
	f.close();
}

// The function inserts the URLs and settings of the webapp into a desktop file.
void insertDesktop(char name[], char com[], char title[], char url[], char arg[],
				   char subUrl1[], char subUrl2[], char subUrl3[], char urls[],
				   char PROVIDER[], char USER_AGENT[], bool https, bool ogra, bool png){
	char file[] = "";
	strcat(file,workPath);
	strcat(file,name);
	strcat(file,".desktop");
	fstream f(file);
	f  << "[Desktop Entry]\n"
	"Name=" << title << "\n"
	"Comment= \"" << com << "\"\n"
	"Type=Application\n";
	if (png) { f << "Icon=" << name << ".png\n";}
	else { f << "Icon=" << name << ".svg\n";}
	f << "Exec=";
	if (!ogra) {
		f << "webapp-container";
		if (arg[0]=='1') {f << " --fullscreen";}
		if (arg[1]=='1') {f << " --accountProvider=" << PROVIDER;}
		if (arg[2]=='1') {f << " --accountSwitcher";}
		if (arg[3]=='1') {f << " --store-session-cookies";}
		if (arg[4]=='1') {f << " --enable-media-hub-audio";}
		if (arg[5]=='1') {f << " --user-agent-string=" << USER_AGENT;}
		if (arg[6]=='1') {f << " --enable-back-forward";}
		if (arg[7]=='1' && arg[6] == '0') {f << " --enable-addressbar";}
		if (arg[8]=='1') {f << " --open-external-url-in-overlay";}
		
		f << " --webappUrlPatterns=https?://" << url << "/* http";
		if (https) {f << 's';}
		f << "://" << url;
		
		if (urls[0]=='1') {
			f << ", http";
			if (https) {f << 's';}
			f << "://" << subUrl1;
		}
		if (urls[1]=='1') {
			f << ", http";
			if (https) {f << 's';}
			f << "://" << subUrl2;
		}
		if (urls[2]=='1') {
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

// This function sets the config.js file of Ogra's alternate webapp container
void insertConfig (char name[], char alias[], char url[], char subUrl1[], 
				   char subUrl2[], char subUrl3[], char urls[], bool hapticLinks,
				   char USER_AGENT[], bool https, bool UA, bool audibleLinks){
	char file[] = "";
	strcat(file,workPath);
	strcat(file,"config.js");
	fstream f(file);
	f  << "var webappName = \"" << name << '.' << alias << "\"\n"
	"var webappUrl = \"http";
	if (https) {f << 's';}
	f  << "://" << url <<"/\",\n"
	"var webappUrlPattern = \"";
	if (urls[0]=='1') {
		f << "http";
		if (https) {f << 's';}
		f << "://" << subUrl1;
	}
	if (urls[1]=='1') {
		f << ", http";
		if (https) {f << 's';}
		f << "://" << subUrl2;
	}
	if (urls[2]=='1') {
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

// This function sets the qml files of Ogra's alternate webapp container
void insertQML (char name[], char alias[]){
	char file[] = "";
	strcat(file,workPath);
	strcat(file,"qml/Main.qml");
	fstream f(file);
	f  << "import QtQuick 2.2\n"
	"import Ubuntu.Web 0.2\n"
	"import Ubuntu.Components 1.1\n"
	"import com.canonical.Oxide 1.0 as Oxide\n"
	"import \"UCSComponents\"\n"
	"import Ubuntu.Content 1.1\n"
	"import QtMultimedia 5.0\n"
	"import QtFeedback 5.0\n"
	"import \".\"\n"
	"import \"../config.js\" as Conf\n"
	"\n"
	"MainView {\n"
	"    objectName: \"mainView\"\n"
	"\n"
	"    applicationName: \"" << name << '.' << alias << "\"\n"
	"\n"
	"    useDeprecatedToolbar: false\n"
	"    anchorToKeyboard: true\n"
	"    automaticOrientation: true\n"
	"\n"
	"    property string myUrl: Conf.webappUrl\n"
	"    property string myPattern: Conf.webappUrlPattern\n"
	"\n"
	"    property string myUA: Conf.webappUA ? Conf.webappUA : \"Mozilla/5.0 (Linux; Android 5.0; Nexus 5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/38.0.2125.102 Mobile Safari/537.36\"\n"
	"\n"
	"    Page {\n"
	"        id: page\n"
	"        anchors {\n"
	"            fill: parent\n"
	"            bottom: parent.bottom\n"
	"        }\n"
	"        width: parent.width\n"
	"        height: parent.height\n"
	"\n"
	"        HapticsEffect {\n"
	"            id: vibration\n"
	"            attackIntensity: 0.0\n"
	"            attackTime: 50\n"
	"            intensity: 1.0\n"
	"            duration: 10\n"
	"            fadeTime: 50\n"
	"            fadeIntensity: 0.0\n"
	"        }\n"
	"\n"
	"        SoundEffect {\n"
	"            id: clicksound\n"
	"            source: \"../sounds/Click.wav\"\n"
	"        }\n"
	"\n"
	"        WebContext {\n"
	"            id: webcontext\n"
	"            userAgent: myUA\n"
	"        }\n"
	"        WebView {\n"
	"            id: webview\n"
	"            anchors {\n"
	"                fill: parent\n"
	"                bottom: parent.bottom\n"
	"            } \n"
	"            width: parent.width\n"
	"            height: parent.height\n"
	"\n"
	"            context: webcontext\n"
	"            url: myUrl\n"
	"            preferences.localStorageEnabled: true\n"
	"            preferences.allowFileAccessFromFileUrls: true\n"
	"            preferences.allowUniversalAccessFromFileUrls: true\n"
	"            preferences.appCacheEnabled: true\n"
	"            preferences.javascriptCanAccessClipboard: true\n"
	"            filePicker: filePickerLoader.item\n"
	"\n"
	"            function navigationRequestedDelegate(request) {\n"
	"                var url = request.url.toString();\n"
	"                var pattern = myPattern.split(',');\n"
	"                var isvalid = false;\n"
	"\n"
	"                if (Conf.hapticLinks) {\n"
	"                    vibration.start()\n"
	"                }\n"
	"\n"
	"                if (Conf.audibleLinks) {\n"
	"                    clicksound.play()\n"
	"                }\n"
	"\n"
	"                for (var i=0; i<pattern.length; i++) {\n"
	"                    var tmpsearch = pattern[i].replace(/\\*/g,'(.*)')\n"
	"                    var search = tmpsearch.replace(/^https\\?:\\/\\//g, '(http|https):\\/\\/');\n"
	"                    if (url.match(search)) {\n"
	"                       isvalid = true;\n"
	"                       break\n"
	"                    }\n"
	"                } \n"
	"                if(isvalid == false) {\n"
	"                    console.warn(\"Opening remote: \" + url);\n"
	"                    Qt.openUrlExternally(url)\n"
	"                    request.action = Oxide.NavigationRequest.ActionReject\n"
	"                }\n"
	"            }\n"
	"            Component.onCompleted: {\n"
	"                preferences.localStorageEnabled = true\n"
	"                if (Qt.application.arguments[1].toString().indexOf(myUrl) > -1) {\n"
	"                    console.warn(\"got argument: \" + Qt.application.arguments[1])\n"
	"                    url = Qt.application.arguments[1]\n"
	"                }\n"
	"                console.warn(\"url is: \" + url)\n"
	"            }\n"
	"            onGeolocationPermissionRequested: { request.accept() }\n"
	"            Loader {\n"
	"                id: filePickerLoader\n"
	"                source: \"ContentPickerDialog.qml\"\n"
	"                asynchronous: true\n"
	"            }\n"
	"        }\n"
	"        ThinProgressBar {\n"
	"            webview: webview\n"
	"            anchors {\n"
	"                left: parent.left\n"
	"                right: parent.right\n"
	"                top: parent.top\n"
	"            }\n"
	"        }\n"
	"        RadialBottomEdge {\n"
	"            id: nav\n"
	"            visible: true\n"
	"            actions: [\n"
	"                RadialAction {\n"
	"                    id: reload\n"
	"                    iconName: \"reload\"\n"
	"                    onTriggered: {\n"
	"                        webview.reload()\n"
	"                    }\n"
	"                    text: qsTr(\"Reload\")\n"
	"                },\n"
	"                RadialAction {\n"
	"                    id: forward\n"
	"                    enabled: webview.canGoForward\n"
	"                    iconName: \"go-next\"\n"
	"                    onTriggered: {\n"
	"                        webview.goForward()\n"
	"                    }\n"
	"                   text: qsTr(\"Forward\")\n"
	"                 },\n"
	"                RadialAction {\n"
	"                    id: back\n"
	"                    enabled: webview.canGoBack\n"
	"                    iconName: \"go-previous\"\n"
	"                    onTriggered: {\n"
	"                        webview.goBack()\n"
	"                    }\n"
	"                    text: qsTr(\"Back\")\n"
	"                }\n"
	"            ]\n"
	"        }\n"
	"    }\n"
	"    Connections {\n"
	"        target: Qt.inputMethod\n"
	"        onVisibleChanged: nav.visible = !nav.visible\n"
	"    }\n"
	"    Connections {\n"
	"        target: webview\n"
	"        onFullscreenChanged: nav.visible = !webview.fullscreen\n"
	"    }\n"
	"    Connections {\n"
	"        target: UriHandler\n"
	"        onOpened: {\n"
	"            if (uris.length === 0 ) {\n"
	"                return;\n"
	"            }\n"
	"            webview.url = uris[0]\n"
	"            console.warn(\"uri-handler request\")\n"
	"        }\n"
	"    }\n"
	"}";
	f.close();
	char file1[] = "";
	strcat(file1,workPath);
	strcat(file1,"qml/ContentPickerDialog.qml");
	f.open(file1);
	f  << "/*\n"
	" * Copyright 2014 Canonical Ltd.\n"
	" *\n"
	" * This file is part of webbrowser-app.\n"
	" *\n"
	" * webbrowser-app is free software; you can redistribute it and/or modify\n"
	" * it under the terms of the GNU General Public License as published by\n"
	" * the Free Software Foundation; version 3.\n"
	" *\n"
	" * webbrowser-app is distributed in the hope that it will be useful,\n"
	" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	" * GNU General Public License for more details.\n"
	" *\n"
	" * You should have received a copy of the GNU General Public License\n"
	" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
	" */\n"
	"\n"
	"import QtQuick 2.0\n"
	"import Ubuntu.Components 1.1\n"
	"import Ubuntu.Components.Popups 1.0 as Popups\n"
	"import Ubuntu.Content 0.1\n"
	"import \"MimeTypeMapper.js\" as MimeTypeMapper\n"
	"\n"
	"Component {\n"
	"    Popups.PopupBase {\n"
	"        id: picker\n"
	"        objectName: \"contentPickerDialog\"\n"
	"\n"
	"        // Set the parent at construction time, instead of letting show()\n"
	"        // set it later on, which for some reason results in the size of\n"
	"        // the dialog not being updated.\n"
	"        parent: QuickUtils.rootItem(this)\n"
	"\n"
	"        property var activeTransfer\n"
	"        property var selectedItems\n"
	"\n"
	"        Rectangle {\n"
	"            anchors.fill: parent\n"
	"\n"
	"            ContentTransferHint {\n"
	"                anchors.fill: parent\n"
	"                activeTransfer: picker.activeTransfer\n"
	"            }\n"
	"\n"
	"            ContentPeerPicker {\n"
	"                id: peerPicker\n"
	"                anchors.fill: parent\n"
	"                visible: true\n"
	"                contentType: ContentType.All\n"
	"                handler: ContentHandler.Source\n"
	"\n"
	"                onPeerSelected: {\n"
	"                    if (model.allowMultipleFiles) {\n"
	"                        peer.selectionType = ContentTransfer.Multiple\n"
	"                    } else {\n"
	"                        peer.selectionType = ContentTransfer.Single\n"
	"                    }\n"
	"                    picker.activeTransfer = peer.request()\n"
	"                    stateChangeConnection.target = picker.activeTransfer\n"
	"                }\n"
	"\n"
	"                onCancelPressed: {\n"
	"                    webview.focus = true\n"
	"                    model.reject()\n"
	"                }\n"
	"            }\n"
	"        }\n"
	"\n"
	"        Connections {\n"
	"            id: stateChangeConnection\n"
	"            onStateChanged: {\n"
	"                if (picker.activeTransfer.state === ContentTransfer.Charged) {\n"
	"                    selectedItems = []\n"
	"                    for(var i in picker.activeTransfer.items) {\n"
	"                        selectedItems.push(String(picker.activeTransfer.items[i].url).replace(\"file://\", \"\"))\n"
	"                    }\n"
	"                    acceptTimer.running = true\n"
	"                }\n"
	"            }\n"
	"        }\n"
	"\n"
	"        // FIXME: Work around for browser becoming insensitive to touch events\n"
	"        // if the dialog is dismissed while the application is inactive.\n"
	"        // Just listening for changes to Qt.application.active doesn't appear\n"
	"        // to be enough to resolve this, so it seems that something else needs\n"
	"        // to be happening first. As such there's a potential for a race\n"
	"        // condition here, although as yet no problem has been encountered.\n"
	"        Timer {\n"
	"            id: acceptTimer\n"
	"            interval: 100\n"
	"            repeat: true\n"
	"            onTriggered: {\n"
	"                if(Qt.application.active) {\n"
	"                    webview.focus = true\n"
	"                    model.accept(selectedItems)\n"
	"                }\n"
	"            }\n"
	"        }\n"
	"\n"
	"        Component.onCompleted: {\n"
	"            if(acceptTypes.length === 1) {\n"
	"                var contentType = MimeTypeMapper.mimeTypeToContentType(acceptTypes[0])\n"
	"                if(contentType == ContentType.Unknown) {\n"
	"                    // If we don't recognise the type, allow uploads from any app\n"
	"                    contentType = ContentType.All\n"
	"                }\n"
	"                peerPicker.contentType = contentType\n"
	"            } else {\n"
	"                peerPicker.contentType = ContentType.All\n"
	"            }\n"
	"            show()\n"
	"        }\n"
	"    }\n"
	"}";
	f.close();
	char file2[] = "";
	strcat(file2,workPath);
	strcat(file2,"qml/MimeTypeMapper.js");
	f.open(file2);
	f << "/*\n"
	" * Copyright 2014 Canonical Ltd.\n"
	" *\n"
	" * This file is part of webbrowser-app.\n"
	" *\n"
	" * webbrowser-app is free software; you can redistribute it and/or modify\n"
	" * it under the terms of the GNU General Public License as published by\n"
	" * the Free Software Foundation; version 3.\n"
	" *\n"
	" * webbrowser-app is distributed in the hope that it will be useful,\n"
	" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	" * GNU General Public License for more details.\n"
	" *\n"
	" * You should have received a copy of the GNU General Public License\n"
	" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
	"*/\n"
	"\n"
	"\n"
	"function mimeTypeToContentType(mimeType) {\n"
	"    if(mimeType.search(\"image/\") === 0) {\n"
	"        return ContentType.Pictures;\n"
	"    } else if(mimeType.search(\"audio/\") === 0) {\n"
	"        return ContentType.Music;\n"
	"    } else if(mimeType.search(\"video/\") === 0) {\n"
	"        return ContentType.Videos;\n"
	"    } else if(mimeType.search(\"text/x-vcard\") === 0) {\n"
	"        return ContentType.Contacts;\n"
	"    } else if(mimeType.search(\"application/epub[+]zip\") === 0\n"
	"              || mimeType.search(\"application/vnd\\.amazon\\.ebook\") === 0\n"
	"              || mimeType.search(\"application/x-mobipocket-ebook\") === 0\n"
	"              || mimeType.search(\"application/x-fictionbook+xml\") === 0\n"
	"              || mimeType.search(\"application/x-ms-reader\") === 0) {\n"
	"        return ContentType.EBooks; \n"
	"    } else if(mimeType.search(\"text/\") === 0\n"
	"              || mimeType.search(\"application/pdf\") === 0\n"
	"              || mimeType.search(\"application/x-pdf\") === 0\n"
	"              || mimeType.search(\"application/vnd\\.pdf\") === 0) {\n"
	"        return ContentType.Documents;\n"
	"    } else {\n"
	"        return ContentType.Unknown;\n"
	"    }\n"
	"}";
	f.close();
	char file3[] = "";
	strcat(file3,workPath);
	strcat(file3,"qml/ThinProgressBar.qml");
	f.open(file3);
	f << "/*\n"
	" * Copyright 2014 Canonical Ltd.\n"
	" *\n"
	" * This file is part of webbrowser-app.\n"
	" *\n"
	" * webbrowser-app is free software; you can redistribute it and/or modify\n"
	" * it under the terms of the GNU General Public License as published by\n"
	" * the Free Software Foundation; version 3.\n"
	" *\n"
	" * webbrowser-app is distributed in the hope that it will be useful,\n"
	" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	" * GNU General Public License for more details.\n"
	" *\n"
	" * You should have received a copy of the GNU General Public License\n"
	" * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n"
	" */\n"
	"\n"
	"import QtQuick 2.0\n"
	"import Ubuntu.Components 1.1\n"
	"\n"
	"ProgressBar {\n"
	"    property var webview\n"
	"\n"
	"    height: units.dp(3)\n"
	"\n"
	"    showProgressPercentage: false\n"
	"    value: webview ? webview.loadProgress / 100 : 0.0\n"
	"    visible: webview ? webview.loading\n"
	"                       // Workaround for https://bugs.launchpad.net/oxide/+bug/1290821.\n"
	"                       // Note: this also works with a QtWebKit webview by chance,\n"
	"                       // because !undefined evaluates to true.\n"
	"                       && !webview.lastLoadStopped\n"
	"                     : false\n"
	"}";
	f.close();
	char file4[] = "";
	strcat(file4,workPath);
	strcat(file4,"qml/UCSComponents/EmptyState.qml");
	f.open(file4);
	f << "import QtQuick 2.0\n"
	"import Ubuntu.Components 1.1\n"
	"\n"
	"/*\n"
	" Component which displays an empty state (approved by design). It offers an\n"
	" icon, title and subtitle to describe the empty state.\n"
	"*/\n"
	"\n"
	"Item {\n"
	"    id: emptyState\n"
	"\n"
	"    // Public APIs\n"
	"    property alias iconName: emptyIcon.name\n"
	"    property alias iconSource: emptyIcon.source\n"
	"    property alias iconColor: emptyIcon.color\n"
	"    property alias title: emptyLabel.text\n"
	"    property alias subTitle: emptySublabel.text\n"
	"\n"
	"    height: childrenRect.height\n"
	"\n"
	"    Icon {\n"
	"        id: emptyIcon\n"
	"        anchors.horizontalCenter: parent.horizontalCenter\n"
	"        height: units.gu(10)\n"
	"        width: height\n"
	"        color: \"#BBBBBB\"\n"
	"    }\n"
	"\n"
	"    Label {\n"
	"        id: emptyLabel\n"
	"        anchors.top: emptyIcon.bottom\n"
	"        anchors.topMargin: units.gu(5)\n"
	"        anchors.horizontalCenter: parent.horizontalCenter\n"
	"        fontSize: \"large\"\n"
	"        font.bold: true\n"
	"    }\n"
	"\n"
	"    Label {\n"
	"        id: emptySublabel\n"
	"        anchors.top: emptyLabel.bottom\n"
	"        anchors.horizontalCenter: parent.horizontalCenter\n"
	"    }\n"
	"}";
	f.close();
	char file5[] = "";
	strcat(file5,workPath);
	strcat(file5,"qml/UCSComponents/RadialAction.qml");
	f.open(file5);
	f << "import QtQuick 2.0\n"
	"import Ubuntu.Components 1.1\n"
	"\n"
	"Action {\n"
	"    property string iconName: \"add\"\n"
	"    property string iconSource\n"
	"    property color iconColor: \"Black\"\n"
	"    property color backgroundColor: \"White\"\n"
	"    property string text\n"
	"    property bool top: false\n"
	"    property bool enabled: true\n"
	"}";
	f.close();
	char file6[] = "";
	strcat(file6,workPath);
	strcat(file6,"qml/UCSComponents/RadialBottomEdge.qml");
	f.open(file6);
	f << "import QtQuick 2.0\n"
	"import QtFeedback 5.0\n"
	"import Ubuntu.Components 1.1\n"
	"import QtGraphicalEffects 1.0\n"
	"\n"
	"Item {\n"
	"    id: bottomEdge\n"
	"\n"
	"    property int hintSize: units.gu(8)\n"
	"    property color hintColor: Theme.palette.normal.overlay\n"
	"    property string hintIconName: \"view-grid-symbolic\"\n"
	"    property alias hintIconSource: hintIcon.source\n"
	"    property color hintIconColor: UbuntuColors.coolGrey\n"
	"    property bool bottomEdgeEnabled: true\n"
	"\n"
	"    property real expandedPosition: 0.6 * height\n"
	"    property real collapsedPosition: height - hintSize/2\n"
	"\n"
	"    property list<RadialAction> actions\n"
	"    property real actionButtonSize: units.gu(7)\n"
	"    property real actionButtonDistance: 1.5* hintSize\n"
	"\n"
	"    anchors.fill: parent\n"
	"\n"
	"    HapticsEffect {\n"
	"        id: clickEffect\n"
	"        attackIntensity: 0.0\n"
	"        attackTime: 50\n"
	"        intensity: 1.0\n"
	"        duration: 10\n"
	"        fadeTime: 50\n"
	"        fadeIntensity: 0.0\n"
	"    }\n"
	"\n"
	"    Rectangle {\n"
	"        id: bgVisual\n"
	"\n"
	"        z: 1\n"
	"        visible: bottomEdgeHint.y !== collapsedPosition\n"
	"        color: \"black\"\n"
	"        anchors.fill: parent\n"
	"        opacity: 0.9 * (((bottomEdge.height - bottomEdgeHint.y) / bottomEdge.height) * 2)\n"
	"\n"
	"        MouseArea {\n"
	"            anchors.fill: parent\n"
	"            enabled: bgVisual.visible\n"
	"            onClicked: bottomEdgeHint.state = \"collapsed\"\n"
	"            z: 1\n"
	"        }\n"
	"\n"
	"    }\n"
	"\n"
	"    Rectangle {\n"
	"        id: bottomEdgeHint\n"
	"\n"
	"        color: hintColor\n"
	"        width: hintSize\n"
	"        height: width\n"
	"        radius: width/2\n"
	"        visible: bottomEdgeEnabled\n"
	"\n"
	"        anchors.horizontalCenter: parent.horizontalCenter\n"
	"        y: collapsedPosition\n"
	"        z: parent.z + 1\n"
	"\n"
	"        Rectangle {\n"
	"            id: dropShadow\n"
	"            width: parent.width\n"
	"            height: parent.height\n"
	"            border.color: \"#B3B3B3\"\n"
	"            color: \"Transparent\"\n"
	"            radius: parent.radius + 1\n"
	"            z: -1\n"
	"            anchors {\n"
	"                centerIn: parent\n"
	"                verticalCenterOffset: -1 //units.gu(-0.3)\n"
	"            }\n"
	"        }\n"
	"\n"
	"        Icon {\n"
	"            id: hintIcon\n"
	"            width: hintSize/4\n"
	"            height: width\n"
	"            name: hintIconName\n"
	"            color: hintIconColor\n"
	"            anchors {\n"
	"                centerIn: parent\n"
	"                verticalCenterOffset: width * ((bottomEdgeHint.y - expandedPosition)\n"
	"                                               /(expandedPosition - collapsedPosition))\n"
	"            }\n"
	"        }\n"
	"\n"
	"        property real actionListDistance: -actionButtonDistance * ((bottomEdgeHint.y - collapsedPosition)\n"
	"                                                                   /(collapsedPosition - expandedPosition))\n"
	"\n"
	"        Repeater {\n"
	"            id: actionList\n"
	"            model: actions\n"
	"            delegate: Rectangle {\n"
	"                id: actionDelegate\n"
	"                readonly property real radAngle: (index % actionList.count * (360/actionList.count)) * Math.PI / 180\n"
	"                property real distance: bottomEdgeHint.actionListDistance\n"
	"                z: -1\n"
	"                width: actionButtonSize\n"
	"                height: width\n"
	"                radius: width/2\n"
	"                anchors.centerIn: parent\n"
	"                color: modelData.backgroundColor\n"
	"                transform: Translate {\n"
	"                    x: distance * Math.sin(radAngle)\n"
	"                    y: -distance * Math.cos(radAngle)\n"
	"                }\n"
	"\n"
	"                Icon {\n"
	"                    id: icon\n"
	"                    anchors.centerIn: parent\n"
	"                    width: parent.width/2\n"
	"                    height: width\n"
	"//                    name: !modelData.iconSource ? modelData.iconName : undefined\n"
	"//                    source: modelData.iconSource ? Qt.resolvedUrl(modelData.iconSource) : undefined\n"
	"                    color: modelData.iconColor\n"
	"                    opacity: modelData.enabled ? 1.0 : 0.2\n"
	"                    Component.onCompleted: modelData.iconSource ? source = Qt.resolvedUrl(modelData.iconSource) : name = modelData.iconName\n"
	"                }\n"
	"\n"
	"                Label {\n"
	"                    visible: text && bottomEdgeHint.state == \"expanded\"\n"
	"                    text: modelData.text\n"
	"                    anchors {\n"
	"                        top: !modelData.top ? icon.bottom : undefined\n"
	"                        topMargin: !modelData.top ? units.gu(3) : undefined\n"
	"                        bottom: modelData.top ? icon.top : undefined\n"
	"                        bottomMargin: modelData.top ? units.gu(3) : undefined\n"
	"                        horizontalCenter: icon.horizontalCenter\n"
	"                    }\n"
	"                    color: Theme.palette.normal.foregroundText\n"
	"                    font.bold: true\n"
	"                    fontSize: \"medium\"\n"
	"\n"
	"                }\n"
	"\n"
	"                MouseArea {\n"
	"                    anchors.fill: parent\n"
	"                    enabled: modelData.enabled\n"
	"                    onClicked: {\n"
	"                        clickEffect.start()\n"
	"                        bottomEdgeHint.state = \"collapsed\"\n"
	"                        modelData.triggered(null)\n"
	"                    }\n"
	"                }\n"
	"            }\n"
	"        }\n"
	"\n"
	"        MouseArea {\n"
	"            id: mouseArea\n"
	"\n"
	"            property real previousY: -1\n"
	"            property string dragDirection: \"None\"\n"
	"\n"
	"            z: 1\n"
	"            anchors.fill: parent\n"
	"            visible: bottomEdgeEnabled\n"
	"\n"
	"            preventStealing: true\n"
	"            drag {\n"
	"                axis: Drag.YAxis\n"
	"                target: bottomEdgeHint\n"
	"                minimumY: expandedPosition\n"
	"                maximumY: collapsedPosition\n"
	"            }\n"
	"\n"
	"            onReleased: {\n"
	"                if ((dragDirection === \"BottomToTop\") &&\n"
	"                        bottomEdgeHint.y < collapsedPosition) {\n"
	"                    bottomEdgeHint.state = \"expanded\"\n"
	"                } else {\n"
	"                    if (bottomEdgeHint.state === \"collapsed\") {\n"
	"                        bottomEdgeHint.y = collapsedPosition\n"
	"                    }\n"
	"                    bottomEdgeHint.state = \"collapsed\"\n"
	"                }\n"
	"                previousY = -1\n"
	"                dragDirection = \"None\"\n"
	"            }\n"
	"\n"
	"            onClicked: {\n"
	"                if (bottomEdgeHint.y === collapsedPosition)\n"
	"                    bottomEdgeHint.state = \"expanded\"\n"
	"                else\n"
	"                    bottomEdgeHint.state = \"collapsed\"\n"
	"            }\n"
	"\n"
	"            onPressed: {\n"
	"                previousY = bottomEdgeHint.y\n"
	"            }\n"
	"\n"
	"            onMouseYChanged: {\n"
	"                var yOffset = previousY - bottomEdgeHint.y\n"
	"                if (Math.abs(yOffset) <= units.gu(2)) {\n"
	"                    return\n"
	"                }\n"
	"                previousY = bottomEdgeHint.y\n"
	"                dragDirection = yOffset > 0 ? \"BottomToTop\" : \"TopToBottom\"\n"
	"            }\n"
	"        }\n"
	"\n"
	"        state: \"collapsed\"\n"
	"        states: [\n"
	"            State {\n"
	"                name: \"collapsed\"\n"
	"                PropertyChanges {\n"
	"                    target: bottomEdgeHint\n"
	"                    y: collapsedPosition\n"
	"                }\n"
	"            },\n"
	"            State {\n"
	"                name: \"expanded\"\n"
	"                PropertyChanges {\n"
	"                    target: bottomEdgeHint\n"
	"                    y: expandedPosition\n"
	"                }\n"
	"            },\n"
	"\n"
	"            State {\n"
	"                name: \"floating\"\n"
	"                when: mouseArea.drag.active\n"
	"            }\n"
	"        ]\n"
	"\n"
	"        transitions: [\n"
	"            Transition {\n"
	"                to: \"expanded\"\n"
	"                SpringAnimation {\n"
	"                    target: bottomEdgeHint\n"
	"                    property: \"y\"\n"
	"                    spring: 2\n"
	"                    damping: 0.2\n"
	"                }\n"
	"            },\n"
	"\n"
	"            Transition {\n"
	"                to: \"collapsed\"\n"
	"                SmoothedAnimation {\n"
	"                    target: bottomEdgeHint\n"
	"                    property: \"y\"\n"
	"                    duration: UbuntuAnimation.BriskDuration\n"
	"                }\n"
	"            }\n"
	"        ]\n"
	"    }\n"
	"}";
	f.close();
}

// This function creates the Webapp files and folders
void createFiles(char name[], bool ogra, bool png, bool selIcon){
	char dir[] = "mkdir ";
	strcat(dir,workPath);
	system(dir);
	char manifest[] = "> ";
	strcat(manifest, workPath);
	strcat(manifest, "manifest.json");
	system(manifest);
	char desktop[] = "> ";
	strcat(desktop, workPath);
	strcat(desktop, name);
	strcat(desktop, ".desktop");
	system(desktop);
	char icon[512] = "cp ";
	if (selIcon) {
		strcat(icon,workPath);
		strcat(icon,"*.");
		if (png) {
			strcat(icon, "png ");
			strcat(icon, workPath);
			strcat(icon, name);
			strcat(icon,".png");
		}
		else {
			strcat(icon, "svg ");
			strcat(icon, workPath);
			strcat(icon, name);
			strcat(icon,".svg");
		}
	}
	else {
		strcat(icon, genericIcon);
		strcat(icon, " ");
		strcat(icon, workPath);
		strcat(icon, name);
		strcat(icon,".svg");
	}
	system(icon);
	if (ogra) {
		char qmldir[] = "mkdir ";
		strcat(qmldir, workPath);
		strcat(qmldir, "qml");
		system(qmldir);
		char soundsdir[] = "mkdir ";
		strcat(soundsdir, workPath);
		strcat(soundsdir, "sounds");
		system(soundsdir);
		char sound[] = "cp ";
		strcat(sound,soundPath);
		strcat(sound," ");
		strcat(sound,workPath);
		strcat(sound,"sounds");
		system(sound);
		char UCSCdir[] = "mkdir ";
		strcat(UCSCdir, workPath);
		strcat(UCSCdir, "qml/UCSComponents");
		system(UCSCdir);
		char appjson[] = "> ";
		strcat(appjson, workPath);
		strcat(appjson, "app.json");
		system(appjson);
		char config[] = "> ";
		strcat(config, workPath);
		strcat(config, "config.js");
		system(config);
		char mainqml[] = "> ";
		strcat(mainqml, workPath);
		strcat(mainqml, "qml/Main.qml");
		system(mainqml);
		char CPDqml[] = "> ";
		strcat(CPDqml, workPath);
		strcat(CPDqml, "qml/ContentPickerDialog.qml");
		system(CPDqml);
		char MTMqml[] = "> ";
		strcat(MTMqml, workPath);
		strcat(MTMqml, "qml/MimeTypeMapper.js");
		system(MTMqml);
		char TPBqml[] = "> ";
		strcat(TPBqml, workPath);
		strcat(TPBqml, "qml/ThinProgressBar.qml");
		system(TPBqml);
		char ESqml[] = "> ";
		strcat(ESqml, workPath);
		strcat(ESqml, "qml/UCSComponents/EmptyState.qml");
		system(ESqml);
		char RAqml[] = "> ";
		strcat(RAqml, workPath);
		strcat(RAqml, "qml/UCSComponents/RadialAction.qml");
		system(RAqml);
		char RBEqml[] = "> ";
		strcat(RBEqml, workPath);
		strcat(RBEqml, "qml/UCSComponents/RadialBottomEdge.qml");
		system(RBEqml);
	}
	else {
		char apparmor[] = "> ";
		strcat(apparmor, workPath);
		strcat(apparmor, name);
		strcat(apparmor, ".apparmor");
		system(apparmor);
		char excludes[] = "> ";
		strcat(excludes, workPath);
		strcat(excludes, ".excludes");
		system(excludes);
		char excludesFile[] = "";
		strcat(excludesFile, workPath);
		strcat(excludesFile, ".excludes");
		fstream f(excludesFile);
		f << "Makefile\n"
		"*.tmp\n"
		".bzr\n"
		".git\n"
		"po\n";
		f.close();
	}
}

// This function generates the click package
void genClick(){
	char click[] = "click build ";
	strcat(click, workPath);
	system(click);
}

// This function deletes all temporary data generated by Webapp Creator
void cleanTmp(){
	char clearFiles[] = "rm -dfr ";
	strcat(clearFiles, workPath);
	system(clearFiles);
}

//It returns true if [word] contains only lowercase characters.
bool lowercase(char word[]) {
	bool lowc = true;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] < 'a' || word[i] > 'z') {lowc = false;}
	}
	return lowc;
}

//It returns false if [word] contains non-numeric characters other than dots.
bool interger(char word[]) {
	bool inter = true;
	for (int i = 0; i < strlen(word); i++) {
		if ((word[i] < '0' || word[i] > '9') && word[i] != '.') {inter = false;}
	}
	return inter;
}

//It returns true if [word] contains one '@' and at least one dot.
bool email(char word[]) {
	bool at = false, dot = false;
	for (int i = 0; i < strlen(word); i++) {
		if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')
		   || (word[i] >= '0' && word[i] <= '9') || word[i] == '.' || word[i] == '+'
		   || word[i] == '-' || word[i] == '_' || word[i] == '@') {
			if (!at && word[i] == '@') {at = true;}
			else if (at && word[i] == '@') {return false;}
			else if (at && word[i] == '.' && i < strlen(word) - 1) {dot = true;}
		}
		else { return false; }
	}
	return at && dot;
}

//It returns true if [word] contains at least one dot.
bool URL(char word[]) {
	bool dot = false;
	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == '.' && i < strlen(word) - 1) {dot = true;}
		else if (word[i] == ' ') {return false;}
	}
	return dot;
}

//It returns false if [word] starts with "http"
bool noHttp (char word[]) {
	if (word[0] == 'h' && word[1] == 't' && word[2] == 't' && word[3] == 'p') {
		return false;
	}
	else {return true;}
}
