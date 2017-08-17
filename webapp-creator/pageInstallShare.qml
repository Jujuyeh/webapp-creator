import QtQuick 2.4
import Ubuntu.Components 1.3
import Webapp_Creator 1.0

//import Ubuntu.Components.ListItems 1.3 as ListItemm
import Ubuntu.Content 1.3

Page {
	id: pageInstallShare
	anchors.fill: parent
	visible: false
	
	property string clickUrl: "file:///home/phablet/.cache/webapp-creator.jujuyeh/" + appName.text + "." + appNick.text + "_" + appVersion.text + "_all.click"

    header: PageHeader {
        id: pageHeaderInstall
        title: i18n.tr("Install and Share")
        StyleHints {
            foregroundColor: "White"
            backgroundColor: darkColor
            dividerColor: darkColor
        }
        leadingActionBar {
			numberOfSlots: 1
			actions: [
				Action {
					id: actionMenuSimple
					iconName: "back"
					shortcut: "Ctrl+b"
					text: i18n.tr("&Back")
					onTriggered: {
						Qt.inputMethod.hide();
						mainPageStack.pop();
					}
				}
			]
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
	
	//onVisibleChanged: if (visible) {buttonInstall.focus = true}
	
	Flickable {
		id: installFlickable
		anchors {
			fill: parent
			top: pageHeaderInstall.bottom
			topMargin: pageHeaderInstall.height
			bottomMargin: units.gu(5)
			leftMargin: marginColumn
			rightMargin: marginColumn
		}

        contentHeight: installMainColumn.height + buttonsInstallColumn.height + units.gu(25)
		Column {
			id: installMainColumn
			spacing: units.gu(2)
			anchors.top: parent.top
			width: parent.width	- marginColumn * 4
            anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: units.gu(5)

			Label {
				id: installTitle
				width: parent.width
                text: i18n.tr("Webapp created sucessfully")
				font.bold: true
			}
            Label {
				id: installExplanation
				width: parent.width
				text: i18n.tr("Click file is in: ") + clickUrl.slice(7,clickUrl.length)
				wrapMode: Text.Wrap
			}
        }

		Column {
			id: buttonsInstallColumn
            anchors.top: installMainColumn.bottom
			width: parent.width	- marginColumn * 4
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.topMargin: units.gu(5)
            anchors.bottomMargin: units.gu(10)
			spacing: units.gu(3)

			Button {
				id: buttonInstall
				width: units.gu(25)
				height: width * .2
				color: UbuntuColors.green
				anchors {
					horizontalCenter: parent.horizontalCenter
				}
				text: i18n.tr("Install or Save")
                onClicked: {
					//Share the click with Telegram, OpenStore, etc.
                    var InstallPage = mainPageStack.push(Qt.resolvedUrl("InstallPage.qml"), {"url": clickUrl, "contentType": ContentType.All, "handler": ContentHandler.Destination});
					InstallPage.imported.connect(function(clickUrl) {
						// Resource optimizations for low-end devices
						//mainPageStack.clear()
						mainPageStack.push(Qt.resolvedUrl("pageInstallShare.qml"))
					})
                }
			}
			Button {
				width: units.gu(25)
				height: width * .2
				color: UbuntuColors.graphite
				anchors {
					horizontalCenter: parent.horizontalCenter
					bottomMargin: units.gu(1)
				}
				text: i18n.tr("Share Webapp")
                onClicked: {
					//Open the click with Telegram, OpenStore, etc.
					var sharePage = mainPageStack.push(Qt.resolvedUrl("SharePage.qml"), {"url": clickUrl, "contentType": ContentType.All, "handler": ContentHandler.Share});
					sharePage.imported.connect(function(clickUrl) {
						// Resource optimizations for low-end devices
                        mainPageStack.push(Qt.resolvedUrl("pageInstallShare.qml"));
					})
                }
			}
			Button {
				width: units.gu(25)
				height: width * .2
				color: UbuntuColors.red
				anchors {
					horizontalCenter: parent.horizontalCenter
					bottomMargin: units.gu(1)
				}
				text: i18n.tr("Clear fields and reset")
                onClicked: {
					iconImageSource = "placeholder-app-icon.svg";
					appName.text ="";
					appDescription.text ="";
					appTitle.text ="";
					appVersion.text = "";
					appNick.text ="";
					appMaintainer.text = "";
					appEmail.text = "";
					appUrl.text ="";
					permissionsVector = permissionsCustom = "00000000000000001000000001";
					optionsVector = optionsCustom = "000000000";
					appUrlPattern.text ="";
					appUrlPattern2.text = "";
					appUrlPattern3.text ="";
					appProviderName.text="";
					appUserAgent.text ="";
					httpsUrl.checked = false;
                    mainPageStack.pop();
                    //TODO: Reset flickable to ¿flickable.flick(0,100);?
                    //to flick to the top
                }
			}
		}
	} //Flickable

} //ograPage

/*
				   
void {
*/
