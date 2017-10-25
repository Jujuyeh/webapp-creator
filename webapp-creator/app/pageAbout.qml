import QtQuick 2.4
import Ubuntu.Components 1.3

Page {
    property string darkColor: "#225684"

    id: pageAbout
    anchors.fill: parent
    property real ee
    header: PageHeader {
        id: pageAboutHeader
        title: i18n.tr("About the App")
        StyleHints {
            foregroundColor: "White"
            backgroundColor: darkColor
            dividerColor: darkColor
        }
    }
    Flickable {
        id: flick
        anchors {
            fill: parent
            margins: units.gu(3)
            //bottomMargin: 0
            topMargin: pageAboutHeader.height * 1.75
        }
        //clip: true
        contentWidth: aboutColumn.width
        contentHeight: aboutColumn.height + licenseColumn.height + units.gu(15)

        Column {
            id: aboutColumn
            width: parent.parent.width
            spacing: units.gu(3)
			
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("Webapp Creator")
                fontSize: "x-large"
            }

            UbuntuShape {
                id: appLogo
                width: units.gu(12); height: units.gu(12)
                anchors.horizontalCenter: parent.horizontalCenter
                radius: "medium"
                image: Image {
                    source: Qt.resolvedUrl("../../../graphics/webapp-creator.svg")        // LOGO DE LA APP
                }
                                                                                                                                                            MouseArea {
                                                                                                                                                                anchors.fill: parent
                                                                                                                                                                onClicked: {
                                                                                                                                                                    ee += 1;
                                                                                                                                                                    if (ee >2) { ciber.visible = true; juju.visible = true; mateo.visible = true;}
                                                                                                                                                                }
                                                                                                                                                            }
            }

            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("Version: ") + "1.3"
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                text: i18n.tr("Maintained by:")
                fontSize: "large"
                font.bold: true
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                linkColor: darkColor
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: "<a href='https://github.com/mateosalta/'>Mateo Salta</a> (@mateosalta)"
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                linkColor: darkColor
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: "<a href='https://telegram.me/cibersheep/'>Joan CiberSheep</a> (@cibersheep)"
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                linkColor: darkColor
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: "<a href='https://telegram.me/Jujuyeh/'>Paul Hodgetts</a> (@Jujuyeh)"
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("Webapp Creator's code hosted on <a href='https://github.com/Jujuyeh/webapp-creator'>GitHub</a>")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("Special thanks to:")
                fontSize: "large"
                font.bold: true
            }

            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("<a href='http://bhdouglass.com/'>Brian Douglass</a> (@bhdouglass)")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
	    
			Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("<a href='https://www.innerzaurus.com'>Miguel</a> (@mimecar)")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }

            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("<a href='https://github.com/ogra1/'>Oliver Grawert</a> (ogra)")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }

            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("<a href='https://ubports.com/'>UBports</a>")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("<a href='https://launchpad.net/instantfx/'>Stefano Verzegnassi</a>")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("With the collaboration and feedback of:") + " <a href='https://github.com/CesarHerreraG'>César Herrera</a>, Pgcor, <a href='https://github.com/Anne017'>Anne017</a>, <a href='https://github.com/alexanderisme>alexanderisme</a>"
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("Icons")
                fontSize: "large"
                font.bold: true
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: "Suru, <a href='https://thenounproject.com/search/?q=mobile&i=857674'>DewDrops</a>"
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }



        }
        Column {
            id: licenseColumn
            width: parent.parent.width
            anchors.top: aboutColumn.bottom
            spacing: units.gu(1)
            anchors.topMargin: units.gu(10)
            Label {
                anchors.margins: units.gu(5)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                text: i18n.tr("License:")
                fontSize: "large"
            }

            Label {
                anchors.margins: units.gu(7)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.")
            }
            Label {
                anchors.margins: units.gu(7)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: i18n.tr("This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.")
            }
            Label {
                anchors.margins: units.gu(7)
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                //TRANSLATORS: Please make sure the URLs are correct
                text: i18n.tr("See the <a href='https://www.gnu.org/licenses/gpl-3.0.en.html'>GNU General Public License</a> for more details.")
                linkColor: darkColor
                onLinkActivated: Qt.openUrlExternally(link)
            }

        }












































        Image {
            id: ciber
            source: "../../../graphics/ci.svg"
            width: units.gu(10)
            height: width
            anchors.top: parent.top
            anchors.topMargin: units.gu(10)
            visible: false


            NumberAnimation on x {
                            id: getIn
                            from: units.gu(190)
                            to: units.gu(6)
                            duration: 2000
                        }
            onVisibleChanged: getIn.start()
        }
        Image {
            id: mateo
            source: "../../../graphics/ms.svg"
            width: units.gu(10)
            height: width
            anchors.top: parent.top
            anchors.topMargin: units.gu(10)
            anchors.right: parent.right
            //anchors.rightMargin: units.gu(2)
            visible: false
            opacity: 0


            NumberAnimation on opacity {
                            id: getMaIn
                            to: 1.0
                            duration: 3000
                        }
            onVisibleChanged: getMaIn.start()
        }
        Image {
            id: juju
            source: "../../../graphics/ju.svg"
            width: units.gu(10)
            height: width
            anchors.top: parent.top
            anchors.topMargin: units.gu(10)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(6)
            visible: false
            opacity: 0


            NumberAnimation on opacity {
                            id: getJuIn
                            to: 1.0
                            duration: 3000
                        }
            onVisibleChanged: getJuIn.start()
        }

    }


} //Page



