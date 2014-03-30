/****************************************************************************
 * This file is part of libhawaii.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/QQmlComponent>

#include <hawaii/appinfo.h>

#include "applicationiconprovider.h"
#include "applicationsmodel.h"

using namespace Hawaii;

class HawaiiShellApplicationsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

void HawaiiShellApplicationsPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QByteArray(uri) == QByteArray("Hawaii.Shell.Applications"));

    // @uri Hawaii.Shell.Applications
    qmlRegisterType<ApplicationsModel>(uri, 1, 0, "ApplicationsModel");
    qmlRegisterUncreatableType<AppInfo>(uri, 1, 0, "AppInfo",
                                        QStringLiteral("Do not create AppInfo"));
}

void HawaiiShellApplicationsPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);

    engine->addImageProvider("appicon", new ApplicationIconProvider);
}

#include "plugin.moc"
