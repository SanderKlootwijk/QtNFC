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

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>

#include <QtNfc/qnearfieldtarget.h>

QT_FORWARD_DECLARE_CLASS(QNearFieldManager)
//QT_FORWARD_DECLARE_CLASS(QNdefMessage)

class Example: public QObject {
    Q_OBJECT

public:
    Example();
    ~Example() = default;

    Q_INVOKABLE void speak();
    Q_INVOKABLE void ndefwrite();

private:
    enum TouchAction {
        NoAction,
        ReadNdef,
        WriteNdef
    };
    QNearFieldManager *m_manager;
    TouchAction m_touchAction;
    QNearFieldTarget *m_target;
    QNearFieldTarget::RequestId m_request;
    void targetDetected(QNearFieldTarget *target);
    void targetLost(QNearFieldTarget *target);
};

#endif
