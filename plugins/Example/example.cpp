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

        //ndefRecord.setLocale("en-EN");

        ndefRecord.setText(text.toUtf8());

        m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << QNdefMessage(ndefRecord));
    }
}
void Example::ndefWriteURI(const QUrl &uri) {

    if (m_target != NULL) {
        QNdefNfcUriRecord ndefRecord;

//        ndefRecord.setEncoding(QNdefNfcTextRecord::Utf8);

        //ndefRecord.setLocale("en-EN");

        ndefRecord.setUri(uri);

        m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << QNdefMessage(ndefRecord));
    }
}
void Example::ndefReadMessages() {
    qDebug() << "Dit komt van onszelf 1";

    if (m_target != NULL) {
        QNdefNfcUriRecord ndefRecord;

//        ndefRecord.setEncoding(QNdefNfcTextRecord::Utf8);
        qDebug() << "Dit komt van onszelf 2";

        //ndefRecord.setLocale("en-EN");
        m_request  = m_target->readNdefMessages();
        //ndefRecord.setUri(uri);
        qDebug() << "Dit komt van onszelf 3";
        //m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << QNdefMessage(ndefRecord));
        //return "Dit komt uit de C++ lees functie";
    }
}
void Example::ndefMessageRead(const QNdefMessage &message){
    qDebug() << "ONze eigen def FUNCTIE";
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
//    connect(target, &QNearFieldTarget::error, this, &Example::targetError);

}

void Example::targetLost(QNearFieldTarget *target)
{
    m_target = NULL;
}