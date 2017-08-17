import QtQuick 2.4
import Ubuntu.Components 1.3
import Webapp_Creator 1.0

import Ubuntu.Components.ListItems 1.3 as ListItemm
import Ubuntu.Content 1.3

Page {
	id: pageOgraWebapp
	anchors.fill: parent
	visible: false

    header: PageHeader {
        id: pageHeaderOgra
        title: i18n.tr("Ogra's Container")
        StyleHints {
            foregroundColor: "White"
            backgroundColor: darkColor
            dividerColor: darkColor
        }
        trailingActionBar {
            numberOfSlots: 1
            actions: [
                Action {
                    id: actionOgraNew
                    iconName: "info"
                    shortcut: "Ctrl+i"
                    //enabled: pageMain.btnsEnabled
                    text: i18n.tr("Information")
                    onTriggered: {
                        mainPageStack.push(Qt.resolvedUrl("pageAbout.qml"));
                    }
                }
            ]
        }
    }

    ListModel {
        id: circlesModel
    }


	Flickable {
		id: ograFlickable
		anchors {
			fill: parent
			top: pageHeaderOgra.bottom
			topMargin: pageHeaderOgra.height
			bottomMargin: units.gu(5)
			leftMargin: marginColumn
			rightMargin: marginColumn
		}
        //contentHeight: ograOptsColumn.height + circleView.height + addOgraCircle.height + buttonsOgraColumn.height + units.gu(25)
        contentHeight: ograOptsColumn.height + buttonsOgraColumn.height + units.gu(25)
		Column {
			id: ograOptsColumn
			spacing: units.gu(2)
			anchors.top: parent.top
			width: parent.width	- marginColumn * 4
            anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: units.gu(5)

			Label {
				id: ograTitle
				width: parent.width
                height: units.gu(3)
                text: i18n.tr("Ogra Container Options")
				font.bold: true
			}
            
            TextArea {
                id: ograUserAgent
                width: parent.width
                height: units.gu(15)
                contentWidth: width
                contentHeight: height + units.gu(20)
                maximumLineCount: 0
                placeholderText: i18n.tr("Optional: Override the default User Agent with the provided one")
                onFocusChanged: text != "" ? optionsVector = optionsVector.slice(0,5) + "1" + optionsVector.slice(6) : optionsVector = optionsVector.slice(0,5) + "0" + optionsVector.slice(6)
            }
            Row {
                spacing: units.gu(1)
                CheckBox {
                    id: useOgraHapticLinks
                    checked: false
                }
                Label {
                    text: i18n.tr("Haptic Links")
                }
            }
            Row {
                spacing: units.gu(1)
                CheckBox {
                    id: useOgraAudibleLinks
                    checked: false
                }
                Label {
                    text: i18n.tr("Audible Links")
                }
            }
        }
        /* To finish and add on v1.5
        Label {
            id: ograCirclesTitle
            anchors.top: ograOptsColumn.bottom
            anchors.topMargin: units.gu(5)
            width: parent.width	- marginColumn * 4
            anchors.horizontalCenter: parent.horizontalCenter
            height: units.gu(3)
            text: i18n.tr("Template Circle Settings")
            font.bold: true
        }
        Column {
            id: circleView
            anchors.topMargin: units.gu(2)
            anchors.top: ograCirclesTitle.bottom
            spacing: units.gu(2)
            Label {
                width: parent.width	- marginColumn * 4
                anchors.horizontalCenter: parent.horizontalCenter
                height: units.gu(3)
                text: i18n.tr("Tap <b>+</b> to add a circle")
                visible: circlesModel.count === 0 ? true : false
            }

            ListView {
                anchors.topMargin: units.gu(5)
                height: circlesModel.count * units.gu(15)
                spacing: units.gu(5)

                width: parent.width	- marginColumn * 4

                model: circlesModel
                delegate: circlesDelegate
            }
            Component {
                id: circlesDelegate

                Column {
                    id: ograCirclesColumn
                    spacing: units.gu(2)

                    width: parent.width	- marginColumn * 4
                    anchors.topMargin: units.gu(5)
                    anchors.horizontalCenter: parent.horizontalCenter

                    Row {
                        spacing: units.gu(2)
                        Label {
                            text: i18n.tr("Circle ") + circle
                            font.bold: true
                        }
                    }
                    Row {
                        spacing: units.gu(2)

                        UbuntuShape {
                            id: webAppIcon
                            source: Image {
                                id: ograIconSource
                                source: icon
                            }
                            //anchors.horizontalCenter: parent.horizontalCenter
                            width: units.gu(5)
                            height: width
                            color: lightColor
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    var importPage = mainPageStack.push(Qt.resolvedUrl("ImportPage.qml"))
                                    importPage.imported.connect(function(fileUrl) {
                                        // Resource optimizations for low-end devices
                                        //mainPageStack.clear()

                                        console.log("Importing file: " + fileUrl)
                                        icon = fileUrl
                                        circlesModel.sync();
                                        //mainPageStack.push(Qt.resolvedUrl("pageOgraWebapp.qml"))
                                        mainPageStack.pop(Qt.resolvedUrl("ImportPage.qml"))
                                    })
                                }
                            }
                        }
                        TextField {
                            id: ograCircleUrl
                            //width: parent.width
                            anchors {
                                verticalCenter: webAppIcon.verticalCenter
                            }
                            placeholderText: url
                        }

                    }
                }
            }
        }


		Column {
			id: addOgraCircle
            anchors.top: circleView.bottom
			width: parent.width	+ marginColumn * 2
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: units.gu(5)
			//spacing: units.gu(3)
			ListItem{
				width: parent.width
				divider.visible: true
			}
			ListItem{
				width: parent.width
				divider.visible: true
				ListItemLayout {
					width: parent.width
					Icon {
							name: "add"
							anchors.horizontalCenter: parent.horizontalCenter
							width: units.gu(2)
						}
				}
				onClicked: {
                    Qt.inputMethod.hide();
                    circlesModel.append({"circle": circlesModel.count +1, "icon": "file:/", "url": "http://"});
                    //circleView.height += units.gu(5)

                    //console.log(circlesModel.get(circlesModel.count).circle)
				}
			}

		}
        */
		Column {
			id: buttonsOgraColumn
            //anchors.top: addOgraCircle.bottom
            anchors.top: ograOptsColumn.bottom
			width: parent.width	- marginColumn * 4
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: units.gu(5)
            anchors.bottomMargin: units.gu(10)
			spacing: units.gu(3)

			Button {
				width: units.gu(25)
				height: width * .2
				color: UbuntuColors.green
				anchors {
					horizontalCenter: parent.horizontalCenter
					bottomMargin: units.gu(1)
				}
				text: i18n.tr("Create Webapp")
                onClicked: {
					//Copy default icon or selected one
					if (iconImageSource === "placeholder-app-icon.svg") { var png = false; var selIcon = false;}
					else { var selIcon = true; var png = iconImageSource.slice(iconImageSource.length - 3) === "png";}

					console.log("\nqml: createFiles Ogra")
                    lib.createFiles(appName.text, true, png, selIcon, iconImageSource.slice(7,iconImageSource.length - 3)); //True = isOgra?

					console.log("\nqml: insertManifest ")
					lib.insertManifest(appName.text, appDescription.text, appTitle.text, appVersion.text, appNick.text, appMaintainer.text + " <"+appEmail.text+">", true); //True -> isOgra

					console.log("\nqml: insertApparmor: Permissions ")
					lib.insertApparmor(permissionsVector, appName.text, true); //Depends on the apparmor profile
																				//true -> isOgra
					//Set how any SubURL are filled
					var urls = "";
					if (appUrlPattern.text !== "") {urls = "1"} else {urls = "0"};
					if (appUrlPattern2.text !== "") {urls += "1"} else {urls += "0"};
					if (appUrlPattern3.text !== "") {urls += "1"} else {urls = "0"};
					
                    console.log("\nqml: urls")

					var useUA = appUserAgent.text !== "";
                    console.log("\nqml: insertConfig: ")
                    lib.insertConfig (appName.text, appNick.text, appUrl.text, appUrlPattern.text, appUrlPattern2.text, appUrlPattern3.text, urls, useOgraHapticLinks.checked, appUserAgent.text, httpsUrl.checked, useUA, useOgraAudibleLinks.checked);
					
                    console.log("\nqml: insertQML: ")
					lib.insertQML (appName.text, appNick.text);

					console.log("\nqml: insertDesktop ");
					lib.insertDesktop(appName.text, appDescription.text, appTitle.text, appUrl.text, optionsVector, appUrlPattern.text, appUrlPattern2.text, appUrlPattern3.text, urls, appProviderName.text, appUserAgent.text, httpsUrl.checked, true, png); //true -> isOgra?

					//Generate the click
					console.log("\nqml: genClick ");
					lib.genClick();
					
					//v1.5 check if everything was ok
					
					lib.cleanTmp();
					mainPageStack.pop()
					mainPageStack.push(Qt.resolvedUrl("pageInstallShare.qml"));
					
					/*
					//Open the click with Telegram, OpenStore, etc.
					var clickUrl = "file:///home/phablet/.cache/webapp-creator.jujuyeh/" + appName.text + "." + appNick.text + "_" + appVersion.text + "_all.click"
					var sharePage = mainPageStack.push(Qt.resolvedUrl("SharePage.qml"), {"url": clickUrl, "contentType": ContentType.All, "handler": ContentHandler.Share});
					sharePage.imported.connect(function(clickUrl) {
						// Resource optimizations for low-end devices
						mainPageStack.pop()
						mainPageStack.push(Qt.resolvedUrl("pageOgraWebapp.qml"))
					})
					*/
                }
			}
		}
	} //Flickable

} //ograPage

/*
				   
void {
*/
