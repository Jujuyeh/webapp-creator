#include <QFile>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QIODevice>
#include <QColor>
#include <QRegExp>

//#include <QDebug>

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>

#include "mytype.h"
#include "libwebappcreator.h"

using namespace std;

#ifdef Q_PROCESSOR_ARM
const char workPath[] = "/home/phablet/.cache/webapp-creator.jujuyeh/webappCreator/", clickPath[] = "/home/phablet/.cache/webapp-creator.jujuyeh/", soundPath[] = "/opt/click.ubuntu.com/webapp-creator.jujuyeh/current/extras/Click.wav", genericIcon[] = "/opt/click.ubuntu.com/webapp-creator.jujuyeh/current/share/qml/webapp-creator/placeholder-app-icon.svg"; //UBUNTU TOUCH
#else
const char workPath[] = "~/webappCreator/", clickPath[] = "~/webappCreator/", soundPath[]="~/Click.wav", genericIcon[] = "~/placeholder-app-icon.svg"; //DESKTOP
#endif

MyType::MyType(QObject *parent) :
    QObject(parent)
{

}


// The function inserts [name], [desc], [title], [version], [alias] and [maint] into
// the corresponding field of manifest.json.
void MyType::insertManifest (QString qname, QString qdesc, QString qtitle, QString qversion,
                     QString qalias, QString qmaint, bool ogra){
    string version = qversion.toUtf8().data();
    /*
    char name[SHORT] = {'\0'};
    strcat(name, qname.toUtf8().data());

    char desc[LONGER] = {'\0'};
    strcat(desc, qdesc.toUtf8().data());

    char title[SHORT] = {'\0'};
    strcat(title, qtitle.toUtf8().data());

    char alias[SHORT] = {'\0'};
    strcat(alias, qalias.toUtf8().data());

    char maint[SHORT] = {'\0'};
    strcat(maint, qmaint.toUtf8().data());

    */
    /*
    char file[] = "";
    strcat(file,workPath);
    strcat(file,"manifest.json");
    fstream f(file);
    f  << "{\n"
    */
    QDir appDir;
    appDir.mkpath(workPath);
    appDir.cd(workPath);

    QFile manifest(appDir.filePath("manifest.json"));
    if (!manifest.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&manifest);
    out << "{\n"

    "    \"description\": \"" << qdesc.toUtf8().data() << "\",\n"
    "    \"framework\": \"ubuntu-sdk-15.04.6\",\n"
    "    \"hooks\": {\n"
    "        \"" << qname.toUtf8().data() << "\": {\n";
    if (ogra) {out << "            \"apparmor\": \"app.json\",\n";}
    else {out << "            \"apparmor\": \"" << qname.toUtf8().data() << ".apparmor\",\n"; }
    out << "            \"desktop\": \"" << qname.toUtf8().data() << ".desktop\"\n"
    "        }\n"
    "    },\n"
    "    \"maintainer\": \"" << qmaint.toUtf8().data() << "\",\n"
    "    \"name\": \"" << qname.toUtf8().data() << '.' << qalias.toUtf8().data() << "\",\n"
    "    \"title\": \"" << qtitle.toUtf8().data() << "\",\n"
    "    \"version\": \"" << version.data() << "\"\n"
    "}";
    manifest.close();
    // MADEWITH file
       QFile madewith(appDir.filePath("MADEWITH"));
        if (!madewith.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outm(&madewith);
        outm << "Webapp Creator";
        madewith.close();
}

// The function inserts the corresponding policy groups into the apparmor file.
void MyType::insertApparmor (QString qgroups, QString qname, bool ogra){

    char groups[SHORT] = {'\0'};
    strcat(groups, qgroups.toUtf8().data());

    char file[] = "";
    strcat(file,workPath);
    if (ogra) {
        strcat(file,"app.json");
    }
    else {
        strcat(file,qname.toUtf8().data());
        strcat(file,".apparmor");
    }
    fstream f(file);
    f  << "{\n";
    if (!ogra) { f  << "    \"template\": \"ubuntu-webapp\",\n";}
    f  << "    \"policy_groups\": [\n";
    if (qgroups.toUtf8().data()[0]=='1'){f  << "        \"accounts\",\n";}
    if (qgroups.toUtf8().data()[1]=='1'){f  << "        \"audio\",\n";}
    if (qgroups.toUtf8().data()[2]=='1'){f  << "        \"calendar\",\n";}
    if (qgroups.toUtf8().data()[3]=='1'){f  << "        \"camera\",\n";}
    if (qgroups.toUtf8().data()[4]=='1'){f  << "        \"connectivity\",\n";}
    if (qgroups.toUtf8().data()[5]=='1'){f  << "        \"contacts\",\n";}
    if (qgroups.toUtf8().data()[6]=='1'){f  << "        \"content_exchange\",\n";}
    if (qgroups.toUtf8().data()[7]=='1'){f  << "        \"content_exchange_source\",\n";}
    if (qgroups.toUtf8().data()[8]=='1'){f  << "        \"debug\",\n";}
    if (qgroups.toUtf8().data()[9]=='1'){f  << "        \"history\",\n";}
    if (qgroups.toUtf8().data()[10]=='1'){f << "        \"in-app-purchases\",\n";}
    if (qgroups.toUtf8().data()[11]=='1'){f << "        \"keep-display-on\",\n";}
    if (qgroups.toUtf8().data()[12]=='1'){f << "        \"location\",\n";}
    if (qgroups.toUtf8().data()[13]=='1'){f << "        \"microphone\",\n";}
    if (qgroups.toUtf8().data()[14]=='1'){f << "        \"music_files\",\n";}
    if (qgroups.toUtf8().data()[15]=='1'){f << "        \"music_files_read\",\n";}
    if (qgroups.toUtf8().data()[16]=='1'){f << "        \"networking\",\n";}
    if (qgroups.toUtf8().data()[17]=='1'){f << "        \"picture_files\",\n";}
    if (qgroups.toUtf8().data()[18]=='1'){f << "        \"picture_files_read\",\n";}
    if (qgroups.toUtf8().data()[19]=='1'){f << "        \"push-notification-client\",\n";}
    if (qgroups.toUtf8().data()[20]=='1'){f << "        \"sensors\",\n";}
    if (qgroups.toUtf8().data()[21]=='1'){f << "        \"usermetrics\",\n";}
    if (qgroups.toUtf8().data()[22]=='1'){f << "        \"video\",\n";}
    if (qgroups.toUtf8().data()[23]=='1'){f << "        \"video_files\",\n";}
    if (qgroups.toUtf8().data()[24]=='1'){f << "        \"video_files_read\",\n";}
    if (qgroups.toUtf8().data()[25]=='1'){f << "        \"webview\"\n";}
    f << "    ],\n"
    "    \"policy_version\": 1.3\n"
    "}";
    f.close();
}

// The function inserts the URLs and settings of the webapp into a desktop file.
void MyType::insertDesktop(QString qname, QString qcom, QString qtitle, QString qurl, QString qarg,
                   QString qsubUrl1, QString qsubUrl2, QString qsubUrl3, QString qurls,
                   QString qPROVIDER, QString qUSER_AGENT, bool https, bool ogra, bool png, QString qhex){
    char name[SHORT] = {'\0'};
    strcat(name, qname.toUtf8().data());

    char com[SHORT] = {'\0'};
    strcat(com, qcom.toUtf8().data());

    char title[SHORT] = {'\0'};
    strcat(title, qtitle.toUtf8().data());

    char url[SHORT] = {'\0'};
    strcat(url, qurl.toUtf8().data());

    char arg[SHORT] = {'\0'};
    strcat(arg, qarg.toUtf8().data());

    char subUrl1[SHORT] = {'\0'};
    strcat(subUrl1, qsubUrl1.toUtf8().data());

    char subUrl2[SHORT] = {'\0'};
    strcat(subUrl2, qsubUrl2.toUtf8().data());

    char subUrl3[SHORT] = {'\0'};
    strcat(subUrl3, qsubUrl3.toUtf8().data());

    char urls[SHORT] = {'\0'};
    strcat(urls, qurls.toUtf8().data());

    char PROVIDER[SHORT] = {'\0'};
    strcat(PROVIDER, qPROVIDER.toUtf8().data());

    char USER_AGENT[SHORT] = {'\0'};
    strcat(USER_AGENT, qUSER_AGENT.toUtf8().data());

    char hex[SHORT] = {'\0'};
    strcat(hex, qhex.toUtf8().data());

    char file[] = "";
    strcat(file,workPath);
    strcat(file,qname.toUtf8().data());
    strcat(file,".desktop");
    fstream f(file);
    f  << "[Desktop Entry]\n"
    "Name=" << qtitle.toUtf8().data() << "\n"
    "Comment= " << qcom.toUtf8().data() << "\n"
    "Type=Application\n";
    if (png) { f << "Icon=" << qname.toUtf8().data() << ".png\n";}
    else { f << "Icon=" << qname.toUtf8().data() << ".svg\n";}
    f << "Exec=";
    if (!ogra) {
        f << "webapp-container";
        if (arg[0]=='1') {f << " --fullscreen";}
        if (arg[1]=='1') {f << " --accountProvider=\"" << qPROVIDER.toUtf8().data() << '"';}
        if (arg[2]=='1') {f << " --accountSwitcher";}
        if (arg[3]=='1') {f << " --store-session-cookies";}
        if (arg[4]=='1') {f << " --enable-media-hub-audio";}
        if (arg[5]=='1') {f << " --user-agent-string=\"" << qUSER_AGENT.toUtf8().data() << '"';}
        if (arg[6]=='1') {f << " --enable-back-forward";}
        if (arg[7]=='1' && arg[6] == '0') {f << " --enable-addressbar";}

        f << " --webappUrlPatterns=https?://" << qurl.toUtf8().data() << "/* http";
        if (https) {f << 's';}
        f << "://" << qurl.toUtf8().data();

        if (urls[0]=='1') {
            f << ", http";
            if (https) {f << 's';}
            f << "://" << qsubUrl1.toUtf8().data();
        }
        if (urls[1]=='1') {
            f << ", http";
            if (https) {f << 's';}
            f << "://" << qsubUrl2.toUtf8().data();
        }
        if (urls[2]=='1') {
            f << ", http";
            if (https) {f << 's';}
            f << "://" << qsubUrl3.toUtf8().data();
        }
    }
    else {f << "qmlscene %u qml/Main.qml";}
    f << '\n' <<"Terminal=false\n"
    "X-Ubuntu-Touch=true\n"
         "X-Ubuntu-Splash-Color=" << qhex.toUtf8().data() << "\n";
    f.close();
}

// This function sets the config.js file of Ogra's alternate webapp container
void MyType::insertConfig (QString qname, QString qalias, QString qurl, QString qsubUrl1,
                   QString qsubUrl2, QString qsubUrl3, QString qurls, bool hapticLinks,
                   QString qUSER_AGENT, bool https, bool UA, bool audibleLinks){

    char name[SHORT] = {'\0'};
    strcat(name, qname.toUtf8().data());

    char alias[SHORT] = {'\0'};
    strcat(alias, qalias.toUtf8().data());
/*
    char maint[SHORT] = {'\0'};
    strcat(maint, qmaint.toUtf8().data());
*/
    char url[SHORT] = {'\0'};
    strcat(url, qurl.toUtf8().data());


    char subUrl1[SHORT] = {'\0'};
    strcat(subUrl1, qsubUrl1.toUtf8().data());

    char subUrl2[SHORT] = {'\0'};
    strcat(subUrl2, qsubUrl2.toUtf8().data());

    char subUrl3[SHORT] = {'\0'};
    strcat(subUrl3, qsubUrl3.toUtf8().data());

    char urls[SHORT] = {'\0'};
    strcat(urls, qurls.toUtf8().data());

    char USER_AGENT[SHORT] = {'\0'};
    strcat(USER_AGENT, qUSER_AGENT.toUtf8().data());

    char file[] = "";
    strcat(file,workPath);
    strcat(file,"config.js");
    fstream f(file);
    f  << "var webappName = \"" << qname.toUtf8().data() << '.' << qalias.toUtf8().data() << "\"\n"
    "var webappUrl = \"http";
    if (https) {f << 's';}
    f  << "://" << qurl.toUtf8().data() <<"/\"\n"
    "var webappUrlPattern = \"";
    if (qurls.toUtf8().data()[0]=='1') {
        f << "http";
        if (https) {f << 's';}
        f << "://" << qsubUrl1.toUtf8().data();
    }
    if (qurls.toUtf8().data()[1]=='1') {
        f << ", http";
        if (https) {f << 's';}
        f << "://" << qsubUrl2.toUtf8().data();
    }
    if (qurls.toUtf8().data()[2]=='1') {
        f << ", http";
        if (https) {f << 's';}
        f << "://" << qsubUrl3.toUtf8().data();
    }
    f << "\"\n";
    if (UA) {f << "var webappUA = \"" << qUSER_AGENT.toUtf8().data() << "\"\n";}
    if (hapticLinks) {f << "var hapticLinks = \"true\"\n";}
    if (audibleLinks) {f << "var audibleLinks = \"true\"\n";}
    f.close();
}

// This function sets the qml files of Ogra's alternate webapp container
void MyType::insertQML (QString qname, QString qalias){

    char name[SHORT] = {'\0'};
    strcat(name, qname.toUtf8().data());

    char alias[SHORT] = {'\0'};
    strcat(alias, qalias.toUtf8().data());




    char file[] = "";
    strcat(file,workPath);
    strcat(file,"qml/Main.qml");
    fstream f(file);
    f  << "import QtQuick 2.4\n"
    "import Ubuntu.Web 0.2\n"
    "import Ubuntu.Components 1.3\n"
    "import com.canonical.Oxide 1.19 as Oxide\n"
    "import \"UCSComponents\"\n"
    "import Ubuntu.Content 1.1\n"
    "//import \"actions\" as Actions\n"
    "import QtMultimedia 5.0\n"
    "import QtFeedback 5.0\n"
    "import QtQuick.Window 2.2\n"
    "\n"
    "import \".\"\n"
    "import \"../config.js\" as Conf\n"
    "\n"
    "MainView {\n"
    "    objectName: \"mainView\"\n"
    "\n"
    "anchors {\n"
    "            fill: parent\n"
    "        }\n"
    "\n"
    "    applicationName: \"" << qname.toUtf8().data() << '.' << qalias.toUtf8().data() << "\"\n"
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
    "        header: Rectangle {\n"
    "        color: \"#000000\"\n"
    "            width: parent.width\n"
    "            height: units.dp(0)\n"
    "            z: 1\n"
    "            }\n"
    "        anchors {\n"
    "            fill: parent\n"
    "            bottom: parent.bottom\n"
    "        }\n"
    "\n"
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
    "        WebContext {\n"
    "                id: webcontext\n"
    "                userAgent: myUA\n"
    "        }\n"
    "\n"
    "        WebView {\n"
    "\n"
    "            id: webview\n"
    "            width: parent.width + units.dp(2)\n"
    "            anchors {\n"
    "                horizontalCenter: parent.horizontalCenter\n"
    "                     top: parent.top\n"
    "                     bottom: parent.bottom\n"
    "            }\n"
    "\n"
    "            context: webcontext\n"
    "            url: myUrl\n"
    "\n"
    "            preferences.localStorageEnabled: true\n"
    "            preferences.allowFileAccessFromFileUrls: true\n"
    "            preferences.allowUniversalAccessFromFileUrls: true\n"
    "            preferences.appCacheEnabled: true\n"
    "            preferences.javascriptCanAccessClipboard: true\n"
    "            filePicker: filePickerLoader.item\n"
    "\n"
    "    contextualActions: ActionList {\n"
    "             Action {\n"
    "                 text: i18n.tr(webview.contextualData.href.toString())\n"
    "                 enabled: contextualData.herf.toString()\n"
    "             }\n"
    "\n"
    "             Action {\n"
    "                 text: i18n.tr(\"Copy Link\")\n"
    "                 enabled: webview.contextualData.href.toString()\n"
    "                 onTriggered: Clipboard.push([webview.contextualData.href])\n"
    "             }\n"
    "\n"
    "             Action {\n"
    "                 text: i18n.tr(\"Share Link\")\n"
    "                 enabled: webview.contextualData.href.toString()\n"
    "                 onTriggered: {\n"
    "                     var component = Qt.createComponent(\"Share.qml\")\n"
    "                     console.log(\"component...\"+component.status)\n"
    "                     if (component.status == Component.Ready) {\n"
    "                         var share = component.createObject(webview)\n"
    "                         share.onDone.connect(share.destroy)\n"
    "                         share.shareLink(webview.contextualData.href.toString(), webview.contextualData.title)\n"
    "                     } else {\n"
    "                         console.log(component.errorString())\n"
    "                     }\n"
    "                  }\n"
    "             }\n"
    "\n"
    "                  Action {\n"
    "                      text: i18n.tr(\"Copy Image\")\n"
    "                      enabled: webview.contextualData.img.toString()\n"
    "                      onTriggered: Clipboard.push([webview.contextualData.img])\n"
    "                  }\n"
    "\n"
    "                  Action {\n"
    "                      text: i18n.tr(\"Download Image\")\n"
    "                      enabled: webview.contextualData.img.toString() && downloadLoader.status == Loader.Ready\n"
    "                      onTriggered: downloadLoader.item.downloadPicture(webview.contextualData.img)\n"
    "                  }\n"
    "    }\n"
    "\n"
    "             function navigationRequestedDelegate(request) {\n"
    "                var url = request.url.toString();\n"
    "\n"
    "                if (Conf.hapticLinks) {\n"
    "                    vibration.start()\n"
    "                }\n"
    "\n"
    "                if (Conf.audibleLinks) {\n"
    "                    clicksound.play()\n"
    "                }\n"
    "\n"
    "                if(isValid(url) == false) {\n"
    "                    console.warn(\"Opening remote: \" + url);\n"
    "                    Qt.openUrlExternally(url)\n"
    "                    request.action = Oxide.NavigationRequest.ActionReject\n"
    "                }\n"
    "            }\n"
    "            Component.onCompleted: {\n"
    "                preferences.localStorageEnabled = true\n"
    "                if (Qt.application.arguments[2] != undefined ) {\n"
    "                    console.warn(\"got argument: \" + Qt.application.arguments[1])\n"
    "                    if(isValid(Qt.application.arguments[1]) == true) {\n"
    "                        url = Qt.application.arguments[1]\n"
    "                    }\n"
    "                }\n"
    "                console.warn(\"url is: \" + url)\n"
    "            }\n"
    "            onGeolocationPermissionRequested: { request.accept() }\n"
    "\n"
    "           Loader {\n"
    "                id: downloadLoader\n"
    "                source: \"Downloader.qml\"\n"
    "                asynchronous: true\n"
    "            }\n"
    "\n"
    "            Loader {\n"
    "                id: filePickerLoader\n"
    "                source: \"ContentPickerDialog.qml\"\n"
    "                asynchronous: true\n"
    "            }\n"
    "            function isValid (url){\n"
    "                var pattern = myPattern.split(',');\n"
    "                for (var i=0; i<pattern.length; i++) {\n"
    "                    var tmpsearch = pattern[i].replace(/\\*/g,'(.*)')\n"
    "                    var search = tmpsearch.replace(/^https\\?:\\/\\//g, '(http|https):\\/\\/');\n"
    "                    if (url.match(search)) {\n"
    "                       return true;\n"
    "                    }\n"
    "                }\n"
    "                return false;\n"
    "            }\n"
    "        }\n"
    "\n"
    "        ThinProgressBar {\n"
    "            webview: webview\n"
    "            width: parent.width + units.gu(5)\n"
    "            z: 2\n"
    "            anchors {\n"
    "               horizontalCenter: parent.horizontalCenter\n"
    "               top: parent.top\n"
    "            }\n"
    "        }\n"
    "         RadialBottomEdge {\n"
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
    "\n"
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
    "                    id: home\n"
    "                    iconName: \"home\"\n"
    "                    onTriggered: {\n"
    "                        webview.url = myUrl\n"
    "                    }\n"
    "                    text: qsTr(\"Home\")\n"
    "                },\n"
    "                  RadialAction {\n"
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
    "\n"
    " Connections {\n"
    "    target: Qt.inputMethod\n"
    "    onVisibleChanged: nav.visible = !nav.visible\n"
    "  }\n"
    "    Connections {\n"
    "        target: webview\n"
    "        onFullscreenRequested: webview.fullscreen = fullscreen\n"
    "\n"
    "        onFullscreenChanged: {\n"
    "                nav.visible = !webview.fullscreen\n"
    "                if (webview.fullscreen == true) {\n"
    "                    window.visibility = 5\n"
    "                                width: parent.width + units.dp(2)\n"
    "                } else {\n"
    "                    window.visibility = 4\n"
    "                                width: parent.width + units.dp(2)\n"
    "                }\n"
    "            }\n"
    "    }\n"
    "    Connections {\n"
    "        target: UriHandler\n"
    "        onOpened: {\n"
    "            if (uris.length === 0 ) {\n"
    "                return;\n"
    "            }\n"
    "            webview.url = uris[0]\n"
    "        }\n"
    "    }\n"
    "}\n";
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
    "import QtQuick 2.4\n"
    "import Ubuntu.Components 1.3\n"
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
    "import QtQuick 2.4\n"
    "import Ubuntu.Components 1.3\n"
    "\n"
    "    ProgressBar {\n"
    "    property var webview\n"
    " id: progressbar\n"
    "\n"
    " property int minimum: 0\n"
    " property int maximum: 100\n"
    " property int value: webview.loadProgress\n"
    " property color color: \"#19B6ED\"\n"
    "     showProgressPercentage: false\n"
    "  visible: webview ? webview.loading\n"
    "                       // Workaround for https://bugs.launchpad.net/oxide/+bug/1290821.\n"
    "                       // Note: this also works with a QtWebKit webview by chance,\n"
    "                       // because !undefined evaluates to true.\n"
    "                       && !webview.lastLoadStopped\n"
    "                     : false\n"
    " height: units.dp(2.5)\n"
    " clip: true\n"
    " \n"
    " Rectangle {\n"
    " id: border\n"
    " anchors.fill: parent\n"
    "\n"
    " color: \"#CDCDCD\"\n"
    " border.width: 0\n"
    " border.color: parent.color\n"
    " }\n"
    "\n"
    " Rectangle {\n"
    " id: highlight\n"
    " property int widthDest: ( ( progressbar.width * ( value- minimum ) ) / ( maximum - minimum ) - 4 )\n"
    " width: highlight.widthDest\n"
    "\n"
    "anchors {\n"
    " left: parent.left\n"
    " top: parent.top\n"
    " bottom: parent.bottom\n"
    " margins: 0\n"
    " }\n"
    " color: parent.color\n"
    " }\n"
    "}";
    f.close();
    char file4[] = "";
    strcat(file4,workPath);
    strcat(file4,"qml/UCSComponents/EmptyState.qml");
    f.open(file4);
    f << "import QtQuick 2.4\n"
    "import Ubuntu.Components 1.3\n"
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
    f << "import QtQuick 2.4\n"
    "import Ubuntu.Components 1.3\n"
    "\n"
    "Action {\n"
    "    property string iconName: \"add\"\n"
    "    property string iconSource\n"
    "    property color iconColor: \"Black\"\n"
    "    property color backgroundColor: \"white\"\n"
    "    property string text\n"
    "    property bool top: false\n"
    "    property bool enabled: true\n"
    "}";
    f.close();
    char file6[] = "";
    strcat(file6,workPath);
    strcat(file6,"qml/UCSComponents/RadialBottomEdge.qml");
    f.open(file6);
    f <<"import QtQuick 2.4\n"
    "import QtFeedback 5.0\n"
    "import Ubuntu.Components 1.3\n"
    "import QtQuick.Window 2.1\n"
    "\n"
    "Item {\n"
    "    id: bottomEdge\n"
    "    \n"
    "    property int hintSize: units.gu(8)\n"
    "    property color hintColor: Theme.palette.normal.overlay\n"
    "    property string hintIconName: \"grip-large\"\n"
    "    property alias hintIconSource: hintIcon.source\n"
    "    property color hintIconColor: \"#000000\"\n"
    "    property bool bottomEdgeEnabled: true\n"
    "\n"
    "    property int expandAngle : Screen.orientation == Qt.LandscapeOrientation ? 600 : 360\n"
    "    property real expandedPosition: (0.85 - 0.25 * expandAngle/360) * height\n"
    "    property real collapsedPosition: height - hintSize/2\n"
    "\n"
    "    property list<RadialAction> actions\n"
    "    property real actionButtonSize: units.gu(7)\n"
    "    property real actionButtonDistance: 1.6* hintSize\n"
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
    "        opacity: 0.9 * (((bottomEdge.height - bottomEdgeHint.y) / bottomEdge.height) * 2)/((expandAngle * .003))\n"
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
    "        radius: width\n"
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
    "            border.color: \"#000000\"\n"
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
    "                opacity: modelData.enabled ? 1.0 : 0.7\n"
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
    "                \n"
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
    "                   damping: .2 \n"
    "                 // epsilon: .05\n"
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
    char file7[] = "";
    strcat(file7,workPath);
    strcat(file7,"qml/Share.qml");
    f.open(file7);
    f  <<"/*\n"
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
    "import QtQuick 2.4\n"
    "import Ubuntu.Components 1.3\n"
    "import Ubuntu.Components.Popups 1.0\n"
    "import Ubuntu.DownloadManager 0.1\n"
    "import Ubuntu.Content 0.1\n"
    "\n"
    "Item {\n"
    "    id: shareItem\n"
    "\n"
    "    signal done()\n"
    "\n"
    "    Component {\n"
    "        id: shareDialog\n"
    "        ContentShareDialog {\n"
    "            Component.onDestruction: shareItem.done()\n"
    "        }\n"
    "    }\n"
    "\n"
    "    Component {\n"
    "        id: contentItemComponent\n"
    "        ContentItem { }\n"
    "    }\n"
    "\n"
    "    function share(url, name, contentType) {\n"
    "        var sharePopup = PopupUtils.open(shareDialog, shareItem, {\"contentType\" :        contentType})\n"
    "        sharePopup.items.push(contentItemComponent.createObject(shareItem, {\"url\" : url, \"name\" : name}))\n"
    "    }\n"
    "\n"
    "    function shareLink(url, title) {\n"
    "        share(url, title, ContentType.Links)\n"
    "    }\n"
    "\n"
    "}";
    f.close();
    char file8[] = "";
    strcat(file8,workPath);
    strcat(file8,"qml/ContentShareDialog.qml");
    f.open(file8);
    f  <<"/*\n"
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
         "import QtQuick 2.4\n"
         "import Ubuntu.Components 1.3\n"
         "import Ubuntu.Components.Popups 1.0\n"
         "import Ubuntu.Content 0.1\n"
         "\n"
         "PopupBase {\n"
         "    id: shareDialog\n"
         "    anchors.fill: parent\n"
         "    property var activeTransfer\n"
         "    property var items: []\n"
         "    property alias contentType: peerPicker.contentType\n"
         "\n"
         "    Rectangle {\n"
         "        anchors.fill: parent\n"
         "        ContentPeerPicker {\n"
         "            id: peerPicker\n"
         "            handler: ContentHandler.Share\n"
         "            visible: parent.visible\n"
         "\n"
         "            onPeerSelected: {\n"
         "                activeTransfer = peer.request()\n"
         "                activeTransfer.items = shareDialog.items\n"
         "                activeTransfer.state = ContentTransfer.Charged\n"
         "                PopupUtils.close(shareDialog)\n"
         "            }\n"
         "\n"
         "            onCancelPressed: {\n"
         "                PopupUtils.close(shareDialog)\n"
         "            }\n"
         "        }\n"
         "    }\n"
         "}";
    f.close();
    char file9[] = "";
    strcat(file9,workPath);
    strcat(file9,"qml/ContentDownloadDialog.qml");
    f.open(file9);
    f  <<"/*\n"
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
         "import Ubuntu.Components.Popups 1.0\n"
         "import Ubuntu.Content 0.1\n"
         "\n"
         "PopupBase {\n"
         "    id: downloadDialog\n"
         "    anchors.fill: parent\n"
         "    property var activeTransfer\n"
         "    property var downloadId\n"
         "    property alias contentType: peerPicker.contentType\n"
         "\n"
         "    Rectangle {\n"
         "        anchors.fill: parent\n"
         "        ContentPeerPicker {\n"
         "            id: peerPicker\n"
         "            handler: ContentHandler.Destination\n"
         "            visible: parent.visible\n"
         "\n"
         "            onPeerSelected: {\n"
         "                activeTransfer = peer.request()\n"
         "                activeTransfer.downloadId = downloadDialog.downloadId\n"
         "                activeTransfer.state = ContentTransfer.Downloading\n"
         "                PopupUtils.close(downloadDialog)\n"
         "            }\n"
         "\n"
         "            onCancelPressed: {\n"
         "                PopupUtils.close(downloadDialog)\n"
         "            }\n"
         "        }\n"
         "    }\n"
         "}";
          f.close();
          char file10[] = "";
          strcat(file10,workPath);
          strcat(file10,"qml/Downloader.qml");
          f.open(file10);
          f  <<"/*\n"
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
               "import QtQuick 2.4\n"
               "import Ubuntu.Components 1.1\n"
               "import Ubuntu.Components.Popups 1.0\n"
               "import Ubuntu.DownloadManager 0.1\n"
               "import Ubuntu.Content 0.1\n"
               "import \"MimeTypeMapper.js\" as MimeTypeMapper\n"
               "import \"FileExtensionMapper.js\" as FileExtensionMapper\n"
               "\n"
               "Item {\n"
               "    id: downloadItem\n"
               "\n"
               "    Component {\n"
               "        id: downloadDialog\n"
               "        ContentDownloadDialog { }\n"
               "    }\n"
               "\n"
               "    Component {\n"
               "        id: metadataComponent\n"
               "        Metadata {\n"
               "            showInIndicator: true\n"
               "        }\n"
               "    }\n"
               "\n"
               "    Component {\n"
               "        id: downloadComponent\n"
               "        SingleDownload {\n"
               "            autoStart: false\n"
               "            property var contentType\n"
               "            onDownloadIdChanged: {\n"
               "                PopupUtils.open(downloadDialog, downloadItem, {\"contentType\" : contentType, \"downloadId\" : downloadId})\n"
               "            }\n"
               "\n"
               "            onFinished: {\n"
               "                metadata.destroy()\n"
               "                destroy()\n"
               "            }\n"
               "        }\n"
               "    }\n"
               "\n"
               "    function download(url, contentType, headers, metadata) {\n"
               "        var singleDownload = downloadComponent.createObject(downloadItem)\n"
               "        singleDownload.contentType = contentType\n"
               "        if (headers) { \n"
               "            singleDownload.headers = headers\n"
               "        }\n"
               "        singleDownload.metadata = metadata\n"
               "        singleDownload.download(url)\n"
               "    }\n"
               "\n"
               "    function downloadPicture(url, headers) {\n"
               "        var metadata = metadataComponent.createObject(downloadItem)\n"
               "        download(url, ContentType.Pictures, headers, metadata)\n"
               "    }\n"
               "\n"
               "    function downloadMimeType(url, mimeType, headers, filename) {\n"
               "        var metadata = metadataComponent.createObject(downloadItem)\n"
               "        var contentType = MimeTypeMapper.mimeTypeToContentType(mimeType)\n"
               "        if (contentType == ContentType.Unknown && filename) {\n"
               "            // If we can't determine the content type from the mime-type\n"
               "            // attempt to discover it from the file extension\n"
               "            contentType = FileExtensionMapper.filenameToContentType(filename)\n"
               "        }\n"
               "        if (mimeType == \"application/zip\" && is7digital(url)) {\n"
               "            // This is problably an album download from 7digital (although we \n"
               "            // can't be 100% certain). 7digital albums are served as a zip\n"
               "            // so we let download manager extract the zip and send its contents\n"
               "            // on to the selected application via content-hub\n"
               "            contentType = ContentType.Music\n"
               "            metadata.extract = true\n"
               "        }\n"
               "        metadata.title = filename\n"
               "        download(url, contentType, headers, metadata)\n"
               "    }\n"
               "\n"
               "    function is7digital(url) {\n"
               "        return url.toString().search(/[^\\/]+:\\/\\/[^\\/]*7digital.com\\//) !== -1\n"
               "    }\n"
               "\n"
               "}";
          f.close();

}

// This function creates the Webapp files and folders
void MyType::createFiles(QString qname, bool ogra, bool png, bool selIcon, QString iconSource){
    //Create working folder
    QDir appDir;
    appDir.mkpath(workPath);
    appDir.cd(workPath);

    //create manifest file
    QFile manifest(appDir.filePath("manifest.json"));
    if (!manifest.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream out(&manifest);
    out << "";
    manifest.close();

    //Create desktop file
    char desktopName[256] = "";
    strcat(desktopName, qname.toUtf8().data());
    strcat(desktopName, ".desktop");

    QFile desktop(appDir.filePath(desktopName));
    if (!desktop.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream outDesk(&desktop);
    outDesk << "";
    desktop.close();

    //Copy sound file
    //Debug: importing image after QFile::copy creates appchachefolder/HubIncoming
    QFile iconFile;

    char icon[512]="";
    char copiedIcon[512]="";

    if (selIcon) {
        strcat(icon, iconSource.toUtf8().data()); //Get the rute to the icon
        //qDebug() << "SelIcon: " << icon;

        if (png) {
            strcat(icon, "png"); //Add extension to the source icon rute
            //qDebug() << "SelIcon: PNG " << icon;
            strcat(copiedIcon, qname.toUtf8().data());
            strcat(copiedIcon,".png"); //Add extension to the target icon
            //qDebug() << "copiedIcon extesion PNG: " << copiedIcon;
        }
        else {
            strcat(icon, "svg");
            //qDebug() << "SelIcon: SVG " << icon;
            strcat(copiedIcon, qname.toUtf8().data());
            strcat(copiedIcon,".svg");
            //qDebug() << "copiedIcon ext SVG: " << copiedIcon;
        }
        iconFile.copy(icon, appDir.filePath(copiedIcon));
        //qDebug() << "Ande copias?: " << appDir.filePath(copiedIcon);
    }
    else {
        strcat(copiedIcon, qname.toUtf8().data());
        strcat(copiedIcon,".svg");
        iconFile.copy(genericIcon, appDir.filePath(copiedIcon));
    }

    //qDebug() << "icon: source final" << icon;

    if (ogra) {
        appDir.mkpath("qml/UCSComponents");
        appDir.mkpath("sounds");

        //Copy sound file
        QFile soundFile;

        char soundNewName[256] = "";
        strcat(soundNewName, workPath);
        strcat(soundNewName, "sounds/Click.wav");
        soundFile.copy(soundPath, soundNewName);

        //Create app.jason
        QFile appJson(appDir.filePath("app.json"));
        if (!appJson.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outAppJson(&appJson);
        outAppJson << "";
        appJson.close();

        //Create config.js
        QFile configJs(appDir.filePath("config.js"));
        if (!configJs.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outConfigJs(&configJs);
        outConfigJs << "";
        configJs.close();

        //Create Main.qml
        QFile mainQml(appDir.filePath("qml/Main.qml"));
        if (!mainQml.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outMainQml(&mainQml);
        outMainQml << "";
        mainQml.close();

        //Create ContentPickerDialog.qml
        QFile cpd(appDir.filePath("qml/ContentPickerDialog.qml"));
        if (!cpd.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outCpd(&cpd);
        outCpd << "";
        cpd.close();

        //Create MimeTypeMapper.js
        QFile mtm(appDir.filePath("qml/MimeTypeMapper.js"));
        if (!mtm.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outMtm(&mtm);
        outMtm << "";
        mtm.close();

        //Create ThinProgressBar.qml
        QFile tpb(appDir.filePath("qml/ThinProgressBar.qml"));
        if (!tpb.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outTpb(&tpb);
        outTpb << "";
        tpb.close();

                //Create Share.qml
        QFile shr(appDir.filePath("qml/Share.qml"));
        if (!shr.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outShr(&shr);
        outShr << "";
        shr.close();

        //Create ContentShareDialog.qml
        QFile csd(appDir.filePath("qml/ContentShareDialog.qml"));
        if (!csd.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
        QTextStream outCsd(&csd);
        outCsd << "";
        csd.close();

        //Create ContentDownloadDialog.qml
        QFile cdd(appDir.filePath("qml/ContentDownloadDialog.qml"));
        if (!cdd.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
        QTextStream outCdd(&cdd);
        outCdd << "";
        cdd.close();

        //Create Downloader.qml
        QFile dld(appDir.filePath("qml/Downloader.qml"));
        if (!dld.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
        QTextStream outDld(&dld);
        outDld << "";
        dld.close();

        //Create EmptyState.qml
        QFile emptyState(appDir.filePath("qml/UCSComponents/EmpytState.qml"));
        if (!emptyState.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outEs(&emptyState);
        outEs << "";
        emptyState.close();

        //Create RadicalAction.qml
        QFile radicalAction(appDir.filePath("qml/UCSComponents/RadialAction.qml"));
        if (!radicalAction.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outRa(&radicalAction);
        outRa << "";
        radicalAction.close();

        //Create RadialBottomEdge.qml
        QFile rbe(appDir.filePath("qml/UCSComponents/RadialBottomEdge.qml"));
        if (!rbe.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outRbe(&rbe);
        outRbe << "";
        rbe.close();
    }
    else {
        //Create apparmor
        char apparmorName[256] = "";
        strcat(apparmorName, qname.toUtf8().data());
        strcat(apparmorName, ".apparmor");

        QFile apparmorFile(appDir.filePath(apparmorName));
        if (!apparmorFile.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outArmor(&apparmorFile);
        outArmor << "";
        apparmorFile.close();

        QFile excludes(appDir.filePath(".excludes"));
        if (!excludes.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream outExcludes(&excludes);
        outExcludes << "Makefile\n"
        "*.tmp\n"
        ".bzr\n"
        ".git\n"
        "po\n";
        excludes.close();

    }
}

// This function generates the click package
void MyType::genClick(){
    QProcess m_process;
    m_process.setWorkingDirectory(clickPath);
    m_process.start("click build webappCreator/");
    m_process.waitForFinished(-1);

}

// This function deletes al generated data in /tmp by Webapp Creator
void MyType::cleanTmp(){
    QProcess m_process;
    m_process.setWorkingDirectory(clickPath);
    m_process.start("rm -dfr webappCreator/");
    m_process.waitForFinished(-1);

}


//It returns true if [word] contains only lowercase characters.
bool MyType::lowercase(QString qword) {

    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    //char* word = qword.toUtf8().data();

    bool lowc = true;
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] < 'a' || word[i] > 'z') {lowc = false;}
    }
    return lowc;
}

//It returns false if [word] contains non-numeric characters other than dots.
bool MyType::interger(QString qword) {

    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    //char* word = qword.toUtf8().data();

    bool inter = true;
    for (int i = 0; i < strlen(word); i++) {
        if ((word[i] < '0' || word[i] > '9') && word[i] != '.') {inter = false;}
    }
    return inter;
}

//It returns true if [word] contains one '@' and at least one dot.
bool MyType::email(QString qword) {

    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    //char* word = qword.toUtf8().data();

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
bool MyType::URL(QString qword) {

    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    //char* word = qword.toUtf8().data();

    bool dot = false;
        for (int i = 0; i < strlen(word); i++) {
            if (word[i] == '.' && i < strlen(word) - 1) {dot = true;}
            else if (word[i] == ' ') {return false;}
        }
        return dot;
}

//It returns false if [word] starts with "http"
bool MyType::noHttp (QString qword) {

    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    //char* word = qword.toUtf8().data();

    if (word[0] == 'h' && word[1] == 't' && word[2] == 't' && word[3] == 'p') {
        return false;
    }
    else {return true;}
}

bool noHttp (char word[]) {
    if (word[0] == 'h' && word[1] == 't' && word[2] == 't' && word[3] == 'p') {
        return false;
    }
    else {return true;}
}

//It returns true if word is at least two characters long
bool MyType::validName (QString qword) {
    char word[LONG] = {'\0'};
    strcat(word, qword.toUtf8().data());

    if (strlen(word) == 1) {
        return true;
    }
    else {return false;}

}

//get red
int MyType::getRed(const QColor &color) {
     return color.red();
}

//get green
int MyType::getGreen(const QColor &color) {
    return color.green();
}

//get blue
int MyType::getBlue(const QColor &color) {
     return color.blue();
}

//to double
double MyType::colorToDouble (QString s)  {
       return s.toDouble();
}

//It returns true if word consist of a hash (#) followed by six hex numbers
bool MyType::validColor (QString word) {
    QRegExp rx("#[0-9a-fA-F]{6}");
    return rx.exactMatch(word);
}

//It returns true if word is valid SVG or PNG image file
/*bool MyType::validImage (QString qword[]) {
    int n = strlen(word);
    if ((((word[n-3] == 'p' || word[n-3] == 'P') &&
    (word[n-2] == 'n' || word[n-2] == 'N')) ||
    ((word[n-3] == 's' || word[n-3] == 'S') &&
    (word[n-2] == 'v' || word[n-2] == 'V'))) &&
    (word[n-1] == 'g' || word[n-1] == 'G')) {
        return true;
    }
    else { return false; }
} */

MyType::~MyType() {

}
