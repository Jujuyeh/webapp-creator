import QtQuick 2.4
import Ubuntu.Components 1.3
import Webapp_Creator 1.0

//import Ubuntu.Components.Popups 1.3

//import Qt.labs.settings 1.0
import Ubuntu.Components.ListItems 1.3 as ListItemm

import Ubuntu.Content 1.3

/*!
    \brief MainView with a Label and Button elements.
*/

MainView {
	id: mainView
    objectName: "mainView"

    applicationName: "webapp-creator.jujuyeh"

    anchorToKeyboard: true

    width: units.gu(40)
    height: units.gu(75)

   	MyType {
		id: lib
   	}
    //property alias appStore: appStore
    property list<ContentItem> importItems
    property string iconImageSource: "placeholder-app-icon.svg"
    property string permissionsVector: "00000000000000001000000001" //setup as a string but used as vector
    property string permissionsCustom: "00000000000000001000000001" //setup as a string but used as vector
    property string optionsVector: "000000000" //setup as a string but used as vector
    property string optionsCustom: "000000000" //setup as a string but used as vector

    //Font sizes and so
    property string fontTitle: "large"
    property int fontId: units.gu(2.75)
    property int fontBasicInfo: units.gu(2.25)
    //-----------------

    //Margins
    property int marginColumn: units.gu(1)

    //Colors
    property string lightColor: "#386790"
    property string darkColor: "#225684"
    property string lighterColor: UbuntuColors.porcelain



    PageStack {
        id: mainPageStack
        anchors.fill: parent
        Component.onCompleted: mainPageStack.push(pageMain)


        Page {
            id: pageMain
            anchors.fill: parent

            header: PageHeader {
                id: pageHeader
                title: i18n.tr("Webapp Creator")
                StyleHints {
                    foregroundColor: "White"
                    backgroundColor: darkColor
                    dividerColor: darkColor
                }
                trailingActionBar {
                    numberOfSlots: 1
                    actions: [
                        Action {
                            id: actionNew
                            iconName: "info"
                            shortcut: "Ctrl+i"
                            text: i18n.tr("Information")
                            onTriggered: {
                                mainPageStack.push(Qt.resolvedUrl("pageAbout.qml"));
                            }
                        }
                    ]
                }
            }
            Flickable {
                id: flickable
                anchors {
                    fill: parent
                    top: pageHeader.bottom
                    topMargin: pageHeader.height * 1.75
                    bottomMargin: units.gu(5)
                    leftMargin: marginColumn
                    rightMargin: marginColumn
                }
                contentHeight: urlColumn.height + mainColumn.height + secondaryColumn.height 
                 + webappTypeColumn.height + units.gu(15)

                Column {
                    id: urlColumn
                    spacing: units.gu(2)
                    UbuntuShape {
                        id: webAppIcon
                        source: Image {
                            id: imageSource
                            source: iconImageSource
                        }
                        anchors.horizontalCenter: parent.horizontalCenter
                        width: units.gu(20)
                        height: width
                        color: lightColor
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                var importPage = mainPageStack.push(Qt.resolvedUrl("ImportPage.qml"),{"contentType": ContentType.Pictures, "handler": ContentHandler.Source})
                                importPage.imported.connect(function(fileUrl) {
                                    // Resource optimizations for low-end devices
                                    mainPageStack.clear()

                                    iconImageSource = fileUrl
                                    mainPageStack.push(pageMain)
                                })
                            }
                        }
                        Label {
                            visible: iconImageSource === "placeholder-app-icon.svg" ? true : false
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            anchors.topMargin: webAppIcon.height / 1.4
                            text: i18n.tr("SVG or PNG icon. 1:1 ratio")
                            wrapMode: Text.Wrap
                        }
                    }    width: parent.width	- marginColumn * 4
                    anchors.horizontalCenter: parent.horizontalCenter

                    TextField {
                        color: text != "" && (!lib.URL(text) || !lib.noHttp(text)) ? UbuntuColors.red : "#000000"

                        id: appUrl
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        placeholderText: i18n.tr("Website <b>URL</b>. Without 'http://'")
                        //onAccepted: appTitle.focus = true;
                    }
                }
                Column {
                    id: mainColumn
                    spacing: units.gu(2)
                    width: parent.width	- marginColumn * 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: urlColumn.bottom
                    anchors.topMargin: units.gu(5)
                    Label {
                        id: basicInfoTitle
                        width: parent.width
                        height: units.gu(3)
                        text: i18n.tr("Basic Info")
                        font.bold: true
                    }

                    TextField {
                        id: appTitle
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("The <b>title</b> to be shown in the app scope")
                    }
                    TextField {
                        color: text != "" && !lib.lowercase(text) ? UbuntuColors.red : "#000000"
                        id: appName
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhUrlCharactersOnly //Should be: inputMethodHints: Qt.ImhLowercaseOnly
                        placeholderText: i18n.tr("Lowercase app <b>name</b> with no spaces")

                    }
                    TextArea {
                        id: appDescription
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        width: parent.width
                        height: units.gu(15)
                        contentWidth: width
                        contentHeight: height + units.gu(20)
                        maximumLineCount: 0
                        placeholderText: i18n.tr("App <b>description</b> to be shown in the OpenStore")
                    }

                    TextField {
                        id: appMaintainer
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Maintainer's <b>real name</b>")
                    }
                    TextField {
                        color: text != "" && !lib.email(text) ? UbuntuColors.red : "#000000"
                        //font.weight: text != "" && !lib.email(text) ? 100 : 20

                        id: appEmail
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhEmailCharactersOnly
                        placeholderText: i18n.tr("Maintainer's <b>email</b>")

                    }
                    TextField {
                        color: text != "" && !lib.lowercase(text) ? UbuntuColors.red : "#000000"
                        //font.weight: text != "" && !lib.lowercase(text) ? 100 : 20

                        id: appNick
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        //font.capitalization: Font.AllLowercase
                        inputMethodHints: Qt.ImhUrlCharactersOnly //Should be: inputMethodHints: Qt.ImhLowercaseOnly
                        placeholderText: i18n.tr("Lowercase maintainer's <b>nickname</b> with no spaces")

                    }
                    TextField {
                        id: appVersion
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("App <b>version</b>")
                        inputMethodHints: Qt.ImhDigitsOnly
                    }
                }

                Column {
                    id: secondaryColumn
                    spacing: units.gu(2)
                    anchors.top: mainColumn.bottom
                    width: parent.width	- marginColumn * 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: units.gu(5)
                    Label {
                        id: secondayInfo
                        width: parent.width
                        height: units.gu(3)
                        text: i18n.tr("Additional Info")
                        font.bold: true
                    }
                                        
                    Label {
                        width: parent.width
                        height: units.gu(3)
                        text: i18n.tr("Add any URL under the main URL that should be opened in the app")
                        wrapMode: Text.Wrap
                    }
                    TextField {
                        color: text != "" && (!lib.URL(text) || !lib.noHttp(text)) ? UbuntuColors.red : "#000000"
                        id: appUrlPattern
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        placeholderText: i18n.tr("Access to SubURL 1")
                        //--webappUrlPatterns=https?://www.xxx.xxx/* http://www.xxx.xxy %u
                    }
                    TextField {
                        color: text != "" && (!lib.URL(text) || !lib.noHttp(text)) ? UbuntuColors.red : "#000000"
                        id: appUrlPattern2
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        placeholderText: i18n.tr("Access to SubURL 2")

                    }
                    TextField {
                        color: text != "" && (!lib.URL(text) || !lib.noHttp(text)) ? UbuntuColors.red : "#000000"
                        id: appUrlPattern3
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        inputMethodHints: Qt.ImhUrlCharactersOnly
                        placeholderText: i18n.tr("Access to SubURL 3")

                    }
                    Row {
                        spacing: units.gu(1)
                        CheckBox {
                            id: httpsUrl
                            checked: false
                        }
                        Label {
                            height: units.gu(3)
                            text: i18n.tr("Use https access")
                        }
                    }
                    //Splash Screen Guidelines: https://docs.ubuntu.com/phone/en/platform/guides/splash-screens
                    //In the next release
                    /*
                    TextField {
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Splash screen. Cambiar a selector de imágenes")
                        //X-Ubuntu-Splash-Image= in .desktop
                    }
                    TextField {
                        id: appSplashColor
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Splash screen color. Cambiar a color picker")
                        //X-Ubuntu-Splash-Color
                    }
                    TextField {
                        id: appSplashColorHeader
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Splash screen color header. Cambiar a color picker")
                        //X-Ubuntu-Splash-Color-Header
                    }
                    TextField {
                        id: appSplashColorFooter
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Splash screen color footer. Cambiar a color picker")
						//X-Ubuntu-Splash-Color-Footer
                    }  
                    */

                    Label {
                        id: spalshScreenTitle
                        width: parent.width
                        height: units.gu(3)
                        text: i18n.tr("Splash screen color")
                        font.bold: true
                    }
                    TextField {
                        id:sliderText
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        text: Qt.rgba(red.value/255, green.value/255, blue.value/255, 1)
                    }

                        //Ubuntu shape with live color from both input and sliders
                        UbuntuShapeOverlay{
                            id: rect
                            width: parent.width
                            anchors {
                                left: parent.left
                                right: parent.right
                            }
                            height: units.gu(15)

                            color: sliderText.text
                            z:-1

                    //TODO: Live slider movement from sliedrText
                    Slider {
                    id: red
                        function formatValue(v) { return v.toFixed(0) }
                        minimumValue: 0
                        maximumValue: 255
                        anchors {
                            horizontalCenter: rect.horizontalCenter
                        }
                        live: true
                        Label {
                               anchors.right: parent.left
                               text: "R"
                               fontSize: "small"
                               color: Qt.rgba(1 - red.value/255,1 - green.value/255, 1 - blue.value/255, 1)
                           }
                    }
                    Slider {
                    id: green
                    anchors {
                        top: red.bottom
                        horizontalCenter: rect.horizontalCenter
                    }
                    Label {
                           anchors.right: parent.left
                           text: "G"
                           fontSize: "small"
                           color: Qt.rgba(1 - red.value/255,1 - green.value/255, 1 - blue.value/255, 1)
                       }
                        function formatValue(v) { return v.toFixed(0) }
                        minimumValue: 0
                        maximumValue: 255
                        live: true
                    }
                    Slider {
                    id: blue
                    anchors {
                        top: green.bottom
                        horizontalCenter: rect.horizontalCenter

                     }
                    Label {
                           anchors.right: parent.left
                           text: "B"
                           fontSize: "small"
                           color: Qt.rgba(1 - red.value/255,1 - green.value/255, 1 - blue.value/255, 1)
                       }
                        function formatValue(v) { return v.toFixed(0) }
                        minimumValue: 0
                        maximumValue: 255
                        live: true
                    }
                }


                }
                Column {
                    id: webappTypeColumn
                    anchors.top: secondaryColumn.bottom
                    width: parent.width	+ marginColumn * 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: units.gu(5)
                    function isRed() {
                        var anyRed = false;
                        if (appUrl.color == UbuntuColors.red || appName.color == UbuntuColors.red || appEmail.color == UbuntuColors.red || appNick == UbuntuColors.red || appUrlPattern.color == UbuntuColors.red || appUrlPattern2.color == UbuntuColors.red || appUrlPattern3.color == UbuntuColors.red){
                            anyRed = true;
                        }
                        return anyRed
                    }
                    function isEmpty() {
                        var anyEmpty = false;
                        if (appUrl.text == "" || appTitle.text == "" || appName.text == "" || appDescription.text == "" || appMaintainer.text == "" || appEmail.text == "" || appNick.text == "" || appVersion.text == ""){
                            anyEmpty = true;
                        }
                        return anyEmpty
                    }
                    Text {
                        width: parent.width	- marginColumn * 6
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: UbuntuColors.red
                        visible: webappTypeColumn.isEmpty()
                        text: i18n.tr("Please, fill all <b>Basic Info</b> fields ")
                    }
                    Text {
                        width: parent.width	- marginColumn * 6
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: UbuntuColors.red
                        visible: webappTypeColumn.isRed()
                        text: i18n.tr("Please, check fields in red")
                    }
                    ListItem{
                    width: parent.width
                    divider.visible: true
                    }
                    ListItem{
                        width: parent.width
                        divider.visible: true
                        ListItemLayout {
                            title.text: i18n.tr("Simple Webapp")
                            title.color: webappTypeColumn.isRed() || webappTypeColumn.isEmpty() ? UbuntuColors.graphite : "#000000"
                            width: parent.width - marginColumn * 2
                            anchors.horizontalCenter: parent.horizontalCenter
                            Icon {
                                name: "next"
                                SlotsLayout.position: SlotsLayout.Trailing;
                                width: units.gu(2)
                            }
                        }
                        onClicked: {
                            Qt.inputMethod.hide();
                            if (!webappTypeColumn.isRed() && !webappTypeColumn.isEmpty()) {mainPageStack.push(pageSimpleWebapp);}
                        }
                    }
                    
                    ListItem{
                        width: parent.width
                        divider.visible: true
                        ListItemLayout {
                            title.text: i18n.tr("Alternate Webapp (Ogra)")
                            title.color: webappTypeColumn.isRed() || webappTypeColumn.isEmpty() ? UbuntuColors.graphite : "#000000"
                            width: parent.width - marginColumn * 2
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: parent.height
                            Icon {
                                name: "next"
                                SlotsLayout.position: SlotsLayout.Trailing;
                                width: units.gu(2)
                            }
                        }
                        onClicked: {
                            Qt.inputMethod.hide();
                            if (!webappTypeColumn.isRed() && !webappTypeColumn.isEmpty()) {mainPageStack.push(Qt.resolvedUrl("pageOgraWebapp.qml"));}
                        }
                    }
				}


            } // Flickable


        } //Main Page
        
        Page {
			id: pageSimpleWebapp
			visible: false
			anchors.fill: parent

			header: PageHeader {
				id: pageHeaderSimple
				title: i18n.tr("Simple Webapp")
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
                                mainPageStack.pop(pageSimpleWebapp);
                            }
                        }
                    ]
                }
				trailingActionBar {
					numberOfSlots: 1
					actions: [
						Action {
							id: actionNewSimple
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
			Flickable {
				id: flickableSimple
				anchors {
					fill: parent
					top: pageHeaderSimple.bottom
					topMargin: pageHeaderSimple.height
					bottomMargin: units.gu(5)
					leftMargin: marginColumn
					rightMargin: marginColumn
				}
				contentHeight: buttonsColumn.height + permissionsColumn.height + optionsColumn.height + grantPermColumn.height + units.gu(20)

				Column {
					id: permissionsColumn
					spacing: units.gu(2)
					anchors.top: parent.top
					width: parent.width	- marginColumn * 4
					anchors.horizontalCenter: parent.horizontalCenter
					anchors.topMargin: units.gu(5)
				
					Label {
						id: typeTitle
						width: parent.width
						height: units.gu(3)
						text: i18n.tr("Webapp Style")
						font.bold: true
					}
					ComboButton {
						id: combo
						width: parent.width
						text: i18n.tr("Select")
						//expanded: true
						expandedHeight: units.gu(25)
						onClicked: expanded = !expanded;
						UbuntuListView {
							id: appType
							model: listModel
							delegate: ListItem {
								id: expandingItem
								height: units.gu(5)
								Text { 
									width: parent.width - marginColumn * 6
									text: i18n.tr(type) 
									anchors.centerIn: parent
								}
								onClicked: {
									combo.expanded = false;
									combo.text = i18n.tr(type);
                                    switch (combo.text) {
                                        case i18n.tr("Default"): defaultLabel.text = i18n.tr("It keeps the essential properties for the WebApp functioning. No session cookies will be stored and a navigation bar will appear. In case of doubt, choose this option.")
                                            desfaultLabelPerms.text = i18n.tr("Permissions: Networking, Webview")
                                            break
                                        case i18n.tr("Multimedia"): defaultLabel.text = i18n.tr("Audio and video permissions are activated. Session cookies will be stored and a navigation bar will appear. Recommended for social networks")
                                            desfaultLabelPerms.text = i18n.tr("Permissions: audio, camera, keep-display-on, microphone, music_files, picture_files, video, video_files")
                                            //100110110
                                            //01010000000101101100001101
                                            break
                                        case i18n.tr("Game"): defaultLabel.text = i18n.tr("Audio and video permissions are activated. Session cookies will be stored and fullscreen is enabled. Recommended for games")
                                            desfaultLabelPerms.text = i18n.tr("Permissions: audio, keep-display-on, music_files, sensors, video")
                                            //100110000
                                            //01000000000100101100101001
                                            break
                                    }

								}
							}
						}
					}
					
				}
				ListModel {
					id: listModel
					ListElement { type: "Default" }
					ListElement { type: "Multimedia" }
					ListElement { type: "Game" }
					ListElement { type: "Custom" }
				}


                Column {
                    id: defaultColumn
                    width: parent.width	- marginColumn * 4
                    visible: combo.text !== i18n.tr("Custom") ? true : false;
                    spacing: units.gu(2)
                    //height: units.gu(10)
                    anchors.top: permissionsColumn.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: units.gu(3)
                    Label {
                        id: defaultLabel
                        width: parent.width - marginColumn * 4
                        anchors.horizontalCenter: parent.horizontalCenter
                        //text: i18n.tr("It keeps the essential properties for the WebApp functioning. No session cookies will be stored and a navigation bar will appear. In case of doubt, choose this option")
                        wrapMode: Text.Wrap

                    }
                    Label {
                        id: desfaultLabelPerms
                        width: parent.width - marginColumn * 4
                        anchors.horizontalCenter: parent.horizontalCenter
                        wrapMode: Text.Wrap
                    }
                }
                Column {
					id: optionsColumn
                    visible: combo.text === i18n.tr("Custom") ? true : false;
					spacing: units.gu(2)
					height: visible ? units.gu(57) : 0
					anchors.top: permissionsColumn.bottom
					width: parent.width	- marginColumn * 4
					anchors.horizontalCenter: parent.horizontalCenter
					anchors.topMargin: units.gu(3)
					
					//TODO: --inspector[=PORT] Run a remote inspector on a specified port or 9221 as the default port

					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: fullScreen
							checked: false
                            onClicked: {checked ? optionsCustom = "1" + optionsCustom.slice(1) : optionsCustom = "0" + optionsCustom.slice(1)
                            }
						}
						Label {
							text: i18n.tr("Display app in full screen mode")
						}
					}
					//--fullscreen

					TextField {
                        id: appProviderName
                        width: parent.width
                        anchors {
                            left: parent.left
                            right: parent.right
                        }
                        placeholderText: i18n.tr("Online account provider for the app")
                        //--accountProvider=PROVIDER_NAME
                        onFocusChanged: text != "" ? optionsCustom = optionsCustom.slice(0,1) + "1" + optionsCustom.slice(2) : optionsCustom = optionsCustom.slice(0,1) + "0" + optionsCustom.slice(2)
                    }

                    Row {
						width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: accountSwitch
							checked: false
                            onClicked: checked ? optionsCustom = optionsCustom.slice(0,2) + "1" + optionsCustom.slice(3) : optionsCustom = optionsCustom.slice(0,2) + "0" + optionsCustom.slice(3)
						}
						Label {
							text: i18n.tr("Switch Online Accounts identities")
                            wrapMode: Text.WrapAnywhere
						}
					}
                    //--accountSwitcher
                    
                    Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: storeCookies
							checked: false
                            onClicked: checked ? optionsCustom = optionsCustom.slice(0,3) + "1" + optionsCustom.slice(4) : optionsCustom = optionsCustom.slice(0,3) + "0" + optionsCustom.slice(4)
						}
						Label {
							text: i18n.tr("Store session cookies")
						}
					}
					//--store-session-cookies
                    
                    Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: mediahubAudio
							checked: false
                            onClicked: checked ? optionsCustom = optionsCustom.slice(0,4) + "1" + optionsCustom.slice(5) : optionsCustom = optionsCustom.slice(0,4) + "0" + optionsCustom.slice(5)
						}
						Label {
							text: i18n.tr("Enable media-hub for audio playback")
						}
					}
                    //--enable-media-hub-audio 
                    
                    TextArea {
                        id: appUserAgent
						width: parent.width
						height: units.gu(15)
						contentWidth: width
						contentHeight: height + units.gu(20)
						maximumLineCount: 0
                        placeholderText: i18n.tr("Optional: Override the default User Agent with the provided one")
                        onFocusChanged: text != "" ? optionsCustom = optionsCustom.slice(0,5) + "1" + optionsCustom.slice(6) : optionsCustom = optionsCustom.slice(0,5) + "0" + optionsCustom.slice(6)
					}
                    //--user-agent-string=USER_AGENT Overrides the default User Agent with the provided one.
                    
					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: enableBack
							checked: false

                            onClicked: {
                                if (checked) {
                                    enableBar.checked = true;
                                    optionsCustom = optionsCustom.slice(0,6) + "11" + optionsCustom.slice(8)
                                } else optionsCustom = optionsCustom.slice(0,6) + "0" + optionsCustom.slice(7);
                            }
						}
						Label {
							text: i18n.tr("Display back, forward and address bar")
						}
					}
					//--enable-back-forward Enable the display of the back and forward buttons (implies --enable-addressbar)
					
					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: enableBar
							checked: false
                            onClicked: {
                                if (!checked) {
                                    enableBack.checked = false;
                                    optionsCustom = optionsCustom.slice(0,6) + "00" + optionsCustom.slice(8);
                                } else optionsCustom = optionsCustom.slice(0,7) + "1" + optionsCustom.slice(8);
                            }
						}
						Label {
							text: i18n.tr("Display the address bar")
						}
					}
					//--enable-addressbar
					
					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: useOverlay
							checked: false
                            onClicked: checked ? optionsCustom = optionsCustom.slice(0,8) + "1" : optionsCustom = optionsCustom.slice(0,8) + "0"
						}
						Label {
							text: i18n.tr("Open external URLs in overlay")
							//--open-external-url-in-overlay
						}
					}
				}
				Column {
					id: grantPermColumn
                    visible: combo.text === i18n.tr("Custom") ? true : false;
                    spacing: units.gu(3)
                    height: !visible ? 0 : ContentItem.height
					anchors.top: optionsColumn.bottom
					width: parent.width	- marginColumn * 4
					anchors.horizontalCenter: parent.horizontalCenter
					anchors.topMargin: units.gu(5)
					//Permissions
					Label {
						text: i18n.tr("Permissions")
						font.bold: true
					}
					Label {
						text: i18n.tr("Mandatory")
						anchors.horizontalCenter: parent.horizontalCenter
					}
					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permNetworking
							checked: true
							onClicked: checked = true
						}
						Label {
                            text: i18n.tr("Networking") // groups[16]
						}
					}
					Row {
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permWebview
							checked: true
							onClicked: checked = true
						}
						Label {
                            text: i18n.tr("Webview") // groups[25]
						}
					}
                    Label {
                        text: i18n.tr("Permissions")
						anchors.horizontalCenter: parent.horizontalCenter
					}
					Row {
                        width: parent.width
						spacing: units.gu(1)
						CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permAccounts
							checked: false
                            onClicked: {checked ? permissionsCustom = "1" + permissionsCustom.slice(1) : permissionsCustom = "0" + permissionsCustom.slice(1)}
						}
						Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>accounts:</b> " + i18n.tr("Webapp will be able to ask access to user accounts") // groups[0]
                            wrapMode: Text.Wrap
						}
					}
					Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permAudio
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,1) + "1" + permissionsCustom.slice(2) : permissionsCustom = permissionsCustom.slice(0,1) + "0" + permissionsCustom.slice(2)
						}
						Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>audio:</b> " + i18n.tr("Webapp will have access to audio") // groups[1]
                            wrapMode: Text.Wrap
						}
					}
					
					Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permCalendar
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,2) + "1" + permissionsCustom.slice(3) : permissionsCustom = permissionsCustom.slice(0,2) + "0" + permissionsCustom.slice(3)
						}
						Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>calendar:</b> " + i18n.tr("Webapp will have access to calendar") // groups[2]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permCamera
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,3) + "1" + permissionsCustom.slice(4) : permissionsCustom = permissionsCustom.slice(0,3) + "0" + permissionsCustom.slice(4)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>camera:</b> " + i18n.tr("Webapp will ask for camera access") // groups[3]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permConnectivity
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,4) + "1" + permissionsCustom.slice(5) : permissionsCustom = permissionsCustom.slice(0,4) + "0" + permissionsCustom.slice(5)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>connectivity:</b> " + i18n.tr("Webapp will ask for coarse network connectivity information access") // groups[4]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permContacts
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,5) + "1" + permissionsCustom.slice(6) : permissionsCustom = permissionsCustom.slice(0,5) + "0" + permissionsCustom.slice(6)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>contacts:</b> " + i18n.tr("Webapp will access contacts") // groups[5]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permContentEx
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,6) + "1" + permissionsCustom.slice(7) : permissionsCustom = permissionsCustom.slice(0,6) + "0" + permissionsCustom.slice(7)
						}
                        Label {
                            width: parent.width	- marginColumn * 4
                            text: "<b>content_exchange:</b> " + i18n.tr("Webapp will be target of content-hub") // groups[6]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permContentExSource
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,7) + "1" + permissionsCustom.slice(8) : permissionsCustom = permissionsCustom.slice(0,7) + "0" + permissionsCustom.slice(8)
						}
                        Label {
                            width: parent.width	- marginColumn * 4
                            text: "<b>content_exchange_source:</b> " + i18n.tr("Webapp will be source to content-hub") // groups[7]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permDebug
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,8) + "1" + permissionsCustom.slice(9) : permissionsCustom = permissionsCustom.slice(0,8) + "0" + permissionsCustom.slice(9)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>debug:</b> " + i18n.tr("Webapp will be run in debug mode. Not suited for final webapp") // groups[8]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permHistory
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,9) + "1" + permissionsCustom.slice(10) : permissionsCustom = permissionsCustom.slice(0,9) + "0" + permissionsCustom.slice(10)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>history:</b> " + i18n.tr("Webapp will ask for the history-service (SMS and call logs)") // groups[9]
                            wrapMode: Text.Wrap
						}
					}
					
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permInAppPurchases
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,10) + "1" + permissionsCustom.slice(11) : permissionsCustom = permissionsCustom.slice(0,10) + "0" + permissionsCustom.slice(11)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>in-app-purchases:</b> " + i18n.tr("Webapp will be able to accept purchases. Deprecated?") // groups[10]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permDisplayOn
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,11) + "1" + permissionsCustom.slice(12) : permissionsCustom = permissionsCustom.slice(0,11) + "0" + permissionsCustom.slice(12)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>keep-display-on:</b> " + i18n.tr("The screen will be on while webapp is shown") // groups[11]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permLocation
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,12) + "1" + permissionsCustom.slice(13) : permissionsCustom = permissionsCustom.slice(0,12) + "0" + permissionsCustom.slice(13)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>location:</b> " + i18n.tr("Webapp will ask to access GPS location") // groups[12]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permMic
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,13) + "1" + permissionsCustom.slice(14) : permissionsCustom = permissionsCustom.slice(0,13) + "0" + permissionsCustom.slice(14)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>microphone:</b> " + i18n.tr("Webapp will ask to access the microphone") // groups[13]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permMusicFiles
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,14) + "1" + permissionsCustom.slice(15) : permissionsCustom = permissionsCustom.slice(0,14) + "0" + permissionsCustom.slice(15)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>music_files:</b> " + i18n.tr("Webapp will be target or source of music files only") // groups[14]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permMusicFilesRead
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,15) + "1" + permissionsCustom.slice(16) : permissionsCustom = permissionsCustom.slice(0,15) + "0" + permissionsCustom.slice(16)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>music_files_read:</b> " + i18n.tr("Webapp will be able to read music files") // groups[15]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permPicFile
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,17) + "1" + permissionsCustom.slice(18) : permissionsCustom = permissionsCustom.slice(0,17) + "0" + permissionsCustom.slice(18)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>picture_files:</b> " + i18n.tr("Webapp will be target or source of picture files") // groups[17]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permPicFilesRead
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,18) + "1" + permissionsCustom.slice(19) : permissionsCustom = permissionsCustom.slice(0,18) + "0" + permissionsCustom.slice(19)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>picture_files_read:</b> " + i18n.tr("Webapp will be able to read picture files") // groups[18]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permNotifictions
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,19) + "1" + permissionsCustom.slice(20) : permissionsCustom = permissionsCustom.slice(0,19) + "0" + permissionsCustom.slice(20)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>push_notification_client:</b> " + i18n.tr("Webapp will be able to receive push notifications. Limited by the OS") // groups[19]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permSensors
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,20) + "1" + permissionsCustom.slice(21) : permissionsCustom = permissionsCustom.slice(0,20) + "0" + permissionsCustom.slice(21)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>sensors:</b> " + i18n.tr("Webapp will be able to access to device sensors") // groups[20]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permUserMetrics
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,21) + "1" + permissionsCustom.slice(22) : permissionsCustom = permissionsCustom.slice(0,21) + "0" + permissionsCustom.slice(22)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>user_metrics:</b> " + i18n.tr("Webapp will be able to access to home screen metrics") // groups[21]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permVideo
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,22) + "1" + permissionsCustom.slice(23) : permissionsCustom = permissionsCustom.slice(0,22) + "0" + permissionsCustom.slice(23)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>video:</b> " + i18n.tr("Webapp will be able to ask for video access") // groups[22]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permVideoFiles
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,23) + "1" + permissionsCustom.slice(24) : permissionsCustom = permissionsCustom.slice(0,23) + "0" + permissionsCustom.slice(24)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>video_files:</b> " + i18n.tr("Webapp will be source or target of video files") // groups[23]
                            wrapMode: Text.Wrap
						}
					}
                    Row {
                        width: parent.width
						spacing: units.gu(1)
                        CheckBox {
                            anchors.verticalCenter: parent.verticalCenter
							id: permVideoFilesRead
							checked: false
                            onClicked: checked ? permissionsCustom = permissionsCustom.slice(0,24) + "1" + permissionsCustom.slice(25) : permissionsCustom = permissionsCustom.slice(0,24) + "0" + permissionsCustom.slice(25)
						}
                        Label {
                            width: parent.width - marginColumn * 4
                            text: "<b>video_files_read:</b> " + i18n.tr("Webapp will be able to read video files") // groups[24]
                            wrapMode: Text.Wrap
						}
					}
					
				}
				Column {
					id: buttonsColumn
                    anchors.top: combo.text === i18n.tr("Custom") ? grantPermColumn.bottom : defaultColumn.bottom
					width: parent.width	- marginColumn * 4
					anchors.horizontalCenter: parent.horizontalCenter
					anchors.topMargin: units.gu(5)
					spacing: units.gu(3)
					
					Button {
						width: units.gu(25)
						height: width * .2
                        color: combo.text === i18n.tr("Select") ? UbuntuColors.graphite : UbuntuColors.green
						anchors {
							horizontalCenter: parent.horizontalCenter
							bottomMargin: units.gu(1)
						}
                        text: combo.text === i18n.tr("Select") ? i18n.tr("Select a profile") : i18n.tr("Create Webapp")
                        onClicked: {
                            //Get proper permissions and options vectors
                            switch (combo.text) {
                                case i18n.tr("Default"): permissionsVector = "00000000000000001000000001"; //Networking, webview
                                    optionsVector = "000000000"
                                    break
                                case i18n.tr("Multimedia"): permissionsVector = "01010000000101101100001101";
                                    optionsVector = "100110110"
                                    break
                                case i18n.tr("Game"): permissionsVector = "01000000000100101100101001";
                                    optionsVector = "100110000"
                                    break
                                case i18n.tr("Custom"): permissionsVector = permissionsCustom;
                                    optionsVector = optionsCustom;
                                    break
                            }
                            if (combo.text !== i18n.tr("Select")) {
                                //Copy default icon or selected one
                                if (iconImageSource === "placeholder-app-icon.svg") { var png = false; var selIcon = false;}
                                else { var selIcon = true; var png = iconImageSource.slice(iconImageSource.length - 3) === "png";}

                                console.log("\nqml: createFiles ")
                                lib.createFiles(appName.text, false, png, selIcon, iconImageSource.slice(7,iconImageSource.length - 3)); //TODO: check bool png

                                console.log("\nqml: insertManifest ")
                                lib.insertManifest(appName.text, appDescription.text, appTitle.text, appVersion.text, appNick.text, appMaintainer.text + " <"+appEmail.text+">", false); //false -> isOgra

                                console.log("\nqml: insertApparmor: Permissions ")
                                lib.insertApparmor(permissionsVector, appName.text, false); //Depends on the apparmor profile
                                                                                            //false -> isOgra
                                //Set how any SubURL are filled
                                var urls = "";
                                if (appUrlPattern.text !== "") {urls = "1"} else {urls = "0"};
                                if (appUrlPattern2.text !== "") {urls += "1"} else {urls += "0"};
                                if (appUrlPattern3.text !== "") {urls += "1"} else {urls = "0"};

                                console.log("\nqml: insertDesktop ")
                                lib.insertDesktop(appName.text, appDescription.text, appTitle.text, appUrl.text, optionsVector, appUrlPattern.text, appUrlPattern2.text, appUrlPattern3.text, urls, appProviderName.text, appUserAgent.text, httpsUrl.checked, false, png, sliderText.text); //false -> isOgra?

                                //Generate the click
                                console.log("\nqml: genClick ")
                                lib.genClick();

                                //v1.5 check if everything was ok

                                lib.cleanTmp();


                                /*
                                //Open the click with Telegram, OpenStore, etc.
                                var clickUrl = "file:///home/phablet/.cache/webapp-creator.jujuyeh/" + appName.text + "." + appNick.text + "_" + appVersion.text + "_all.click"
                                var sharePage = mainPageStack.push(Qt.resolvedUrl("SharePage.qml"), {"url": clickUrl, "contentType": ContentType.All, "handler": ContentHandler.Share});
                                sharePage.imported.connect(function(clickUrl) {
                                    // Resource optimizations for low-end devices
                                    mainPageStack.clear()
                                    mainPageStack.push(pageMain)
                                })
                                */
                                mainPageStack.pop();
                                mainPageStack.push(Qt.resolvedUrl("pageInstallShare.qml"));
                            }
                        }
					}
				}
			} //Flickable

		} //Page Simple Webapp



    } // MainPageStack

}



