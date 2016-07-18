/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtQml/QtQml>

#include "hardwareengine.h"

class HardwarePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri org.hawaiios.hardware
        Q_ASSERT(uri == QStringLiteral("org.hawaiios.hardware"));

        qmlRegisterType<HardwareEngine>(uri, 0, 1, "HardwareEngine");
        qmlRegisterUncreatableType<Battery>(uri, 0, 1, "Battery",
                                            QStringLiteral("Cannot create Battery object"));
        qmlRegisterUncreatableType<StorageDevice>(uri, 0, 1, "StorageDevice",
                                                  QStringLiteral("Cannot create StorageDevice object"));
    }
};

#include "plugin.moc"
