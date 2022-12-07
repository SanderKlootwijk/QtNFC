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

#include <QDebug>
#include <QNdefRecord>
#include <QNdefNfcTextRecord>
#include <QNdefNfcUriRecord>
#include <QNdefMessage>
#include <QNearFieldManager>
#include <QNearFieldTarget>

#include "example.h"
// NFCCommunicator
Example::Example() {
    //! [QNearFieldManager init]
    m_manager = new QNearFieldManager(this);
    connect(m_manager, &QNearFieldManager::targetDetected,
            this, &Example::targetDetected);
    connect(m_manager, &QNearFieldManager::targetLost,
            this, &Example::targetLost);
    //! [QNearFieldManager init]
}

void Example::speak() {
    qDebug() << "hello world!";
}

void Example::ndefWrite(const QString &text) {
    if (m_target != NULL) {
        QNdefNfcTextRecord ndefRecord;
        ndefRecord.setEncoding(QNdefNfcTextRecord::Utf8);
        ndefRecord.setText(text.toUtf8());
        m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << QNdefMessage(ndefRecord));
    }
}
void Example::ndefWriteURI(const QUrl &uri) {
    if (m_target != NULL) {
        QNdefNfcUriRecord ndefRecord;
        ndefRecord.setUri(uri);
        m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << QNdefMessage(ndefRecord));
    }
}
void Example::ndefReadMessages() {
    if (m_target != NULL) {
        QNdefNfcUriRecord ndefRecord;
        m_request  = m_target->readNdefMessages();
        qDebug() << "Dit komt van onszelf 3";
    }
}
void Example::ndefMessageRead(const QNdefMessage &message){
    for (const QNdefRecord &record : message) {
        if (record.isRecordType<QNdefNfcTextRecord>()) {
            qDebug() << ((QNdefNfcTextRecord)record).text(); 
//            addRecord<TextRecordEditor>(ui, record);
        } else if (record.isRecordType<QNdefNfcUriRecord>()) {
            qDebug() << "abc";//((QNdefNfcUriRecord)record).uri().toString(); 
//            addRecord<UriRecordEditor>(ui, record);
//        } else if (record.typeNameFormat() == QNdefRecord::Mime &&
  //                record.type().startsWith("image/")) {
  //          addRecord<MimeImageRecordEditor>(ui, record);
    //    } else if (record.isEmpty()) {
      //      addRecord<EmptyRecordLabel>(ui);
        //} else {
          //  addRecord<UnknownRecordLabel>(ui, record);
        }
    }
}
void Example::targetDetected(QNearFieldTarget *target)
{
    qDebug() << "In Target Detected";
    m_target = target;
    connect(target, &QNearFieldTarget::ndefMessageRead, this, &Example::ndefMessageRead);
}
void Example::targetLost(QNearFieldTarget *target)
{
    m_target = NULL;
}