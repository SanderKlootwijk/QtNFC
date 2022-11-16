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

void Example::ndefwrite() {
    m_request = m_target->writeNdefMessages(QList<QNdefMessage>() << ndefMessage());
}

void Example::targetDetected(QNearFieldTarget *target)
{
    m_target = target;
}

void Example::targetLost(QNearFieldTarget *target)
{
    m_target = NULL;
}