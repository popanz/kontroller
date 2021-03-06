import QtQuick 2.0
import QtQuick.Controls 1.4
import eu.tgcm 1.0
import "."

Item {
    Remote {
        id: remoteController
        client: appClient
    }

    property int buttonWidth : 25 * touchScalingFactor;
    Rectangle {
        anchors.fill: parent
        color:"#000";
        Image {
            width: buttonWidth
            height: buttonWidth
            id: btnUp
            anchors.bottom: btnOk.top
            anchors.bottomMargin: 5 * scalingFactor
            anchors.left: btnOk.left
            source: "icons/go-up.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteController.up()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            anchors.top: btnOk.bottom
            anchors.topMargin: 5 * scalingFactor
            anchors.left: btnOk.left
            source: "icons/go-down.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteController.down()
            }
        }
        Image {
            id:btnLeft
            width: buttonWidth
            height: buttonWidth
            anchors.bottom: btnOk.bottom
            anchors.right: btnOk.left
            anchors.rightMargin: 5 * scalingFactor
            source: "icons/go-left.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteController.left()
            }
        }
        Image {
            id: btnRight
            width: buttonWidth
            height: buttonWidth
            anchors.bottom: btnOk.bottom
            anchors.left: btnOk.right
            anchors.leftMargin: 5 * scalingFactor
            source: "icons/go-right.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteController.right()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            anchors.top: parent.top
            anchors.topMargin : 5 * scalingFactor
            anchors.left: parent.left
            anchors.leftMargin: 5 * scalingFactor
            source: "icons/back.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteController.back()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            anchors.top:parent.top
            anchors.topMargin: 5 * scalingFactor
            anchors.right: parent.right
            anchors.rightMargin: 5 * scalingFactor
            source: "icons/home.png"
            MouseArea {
                anchors.fill: parent
                onClicked: remoteServiceController.home()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            anchors.bottom: btnUp.bottom
            anchors.left: btnLeft.left
            source:"icons/info.png"
            MouseArea {
                anchors.fill: parent
                onClicked:remoteController.info()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            anchors.bottom: btnUp.bottom
            anchors.left: btnRight.left
            source: "icons/contextmenu.png"
            MouseArea {
                anchors.fill: parent
                onClicked:remoteController.contextMenu()
            }
        }
        Image {
            width: buttonWidth
            height: buttonWidth
            id: btnOk
            anchors.horizontalCenter: parent.horizontalCenter
            y: buttonWidth * 2 + 10 * scalingFactor
            source: "icons/ok.png"
            MouseArea{
                anchors.fill: parent
                onClicked: remoteController.select()
            }
        }

    }

/*    Text {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        text : scalingFactor + " " + touchScalingFactor
        color: Styling.linkColor
        id : txtScale
    }

    Text {
        id:txtDpi
        anchors.bottom: txtScale.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        color:Styling.linkColor
        text: deviceInformation.dpi + " " + deviceInformation.size().width + "x" + deviceInformation.size().height
    }

    Text {
        anchors.bottom: txtDpi.top
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        color:Styling.linkColor
        text: deviceInformation.logicalDpi()
    } */
}
