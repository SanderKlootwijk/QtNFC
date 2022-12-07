/*
 * Copyright (C) 2022  Sander Klootwijk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * qtnfc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.7
import Ubuntu.Components 1.3
//import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

import QtNfc 5.12

import Example 1.0

MainView {
    id: root
    objectName: 'mainView'
    applicationName: 'qtnfc.sanderklootwijk'
    automaticOrientation: true
    anchorToKeyboard: true

    property bool nfctag: false

    width: units.gu(45)
    height: units.gu(75)

    Page {
        anchors.fill: parent

        header: PageHeader {
            id: header
            title: i18n.tr('QtNFC')
        }

        ColumnLayout {
            spacing: units.gu(2)
            anchors {
                margins: units.gu(2)
                top: header.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            Item {
                height: units.gu(2)
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: root.nfctag ? "NFC tag detected" : "No NFC tag detected"
                color: root.nfctag ? "green" : "red"
            }

            Label {
                id: nfcLabel
                anchors.horizontalCenter: parent.horizontalCenter
                text: 'Text on NFC tag: '
            }

            Label {
                id: label
                anchors.horizontalCenter: parent.horizontalCenter
                text: i18n.tr('Press the button below to write a message to a NFC tag')
            }

            TextField {
                id: inputField
                width: parent.width
                height: units.gu(3.5)
                anchors.horizontalCenter: parent.horizontalCenter
                inputMethodHints: Qt.ImhUrlCharactersOnly | Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
            }

            Button {
                id: writeButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: i18n.tr('Write')
                onClicked: {
                    console.log("Writing to NFC tag")
                    Example.ndefWrite(inputField.text)


                }
            }
            Button {
                id: writeUriButton
                anchors.horizontalCenter: parent.horizontalCenter
                text: i18n.tr('WriteURL')
                onClicked: {
                    tryit.polling = false
                    console.log("Writing to NFC tag")
                    Example.ndefWriteURI(inputField.text)
                    tryit.polling = true
                }
            }

            // NdefTextRecord {
            //     id: ndefRecord
            //     text: "This is a test..."
            // }

            NearField {

                id: tryit
                filter: [ NdefFilter { type: "T"; typeNameFormat: NdefRecord.NfcRtd; minimum: 1; maximum: 1} ]
                orderMatch: false
                
                onMessageRecordsChanged: {
                    console.log("read",JSON.stringify(messageRecords))
                    console.log(messageRecords[0]["text"])
                    nfcLabel.text = 'Text on NFC tag: ' + '\n' + messageRecords[0]["text"]
                    //if(messageRecords[0].type == "T") {
                    //}
                }
                    
                onTagFound: {
                    console.log("tag found!")
                    root.nfctag = true
                }
                onTagRemoved: {
                    console.log("tag removed!")
                    root.nfctag = false
                }
            }
        }
    }
}