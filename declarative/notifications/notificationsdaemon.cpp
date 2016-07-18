/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2012-2016 Pier Luigi Fiorini
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

#include <QtCore/QAtomicInt>
#include <QtCore/QStandardPaths>
#include <QtGui/QGuiApplication>
#include <QtDBus/QDBusConnection>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlPropertyMap>
#include <QtDBus/QDBusArgument>

#include "config.h"
#include "notifications.h"
#include "notificationsdaemon.h"
#include "notificationsadaptor.h"
#include "notificationsimage.h"

/*
 * Latest specifications:
 * http://people.gnome.org/~mccann/docs/notification-spec/notification-spec-latest.html
 */

const QString serviceName("org.freedesktop.Notifications");
const QString servicePath("/org/freedesktop/Notifications");

Q_LOGGING_CATEGORY(NOTIFICATIONS, "hawall.qml.notifications")

NotificationsDaemon::NotificationsDaemon(Notifications *parent)
    : QObject(parent)
    , m_parent(parent)
{
    // Create the DBus adaptor
    new NotificationsAdaptor(this);

    // Create a seed for notifications identifiers, starting from 1
    m_idSeed = new QAtomicInt(1);

    // List of applications that will send us too many notifications
    // TODO: Add more from configuration
    m_spamApplications << QStringLiteral("Clementine") << QStringLiteral("Spotify");

    // Forward our signals to parent
    connect(this, SIGNAL(NotificationClosed(uint,uint)),
            m_parent, SIGNAL(notificationClosed(uint,uint)));
    connect(this, SIGNAL(ActionInvoked(uint,QString)),
            m_parent, SIGNAL(actionInvoked(uint,QString)));
}

NotificationsDaemon::~NotificationsDaemon()
{
    qDeleteAll(m_images);
    unregisterService();
    delete m_idSeed;
}

bool NotificationsDaemon::registerService()
{
    QDBusConnection bus = QDBusConnection::sessionBus();

    if (!bus.registerObject(servicePath, this)) {
        qCWarning(NOTIFICATIONS,
                  "Failed to register D-Bus object \"%s\" on session bus: \"%s\"",
                  qPrintable(servicePath),
                  qPrintable(bus.lastError().message()));
        return false;
    }

    if (!bus.registerService(serviceName)) {
        qCWarning(NOTIFICATIONS,
                  "Failed to register D-Bus service \"%s\" on session bus: \"%s\"",
                  qPrintable(serviceName),
                  qPrintable(bus.lastError().message()));
        return false;
    }

    return true;
}

void NotificationsDaemon::unregisterService()
{
    QDBusConnection bus = QDBusConnection::sessionBus();
    bus.unregisterObject(servicePath);
    bus.unregisterService(serviceName);
}

NotificationImage *NotificationsDaemon::imageFor(uint id) const
{
    return m_images.value(id);
}

uint NotificationsDaemon::Notify(const QString &appName, uint replacesId,
                                 const QString &appIcon, const QString &summary,
                                 const QString &body,
                                 const QStringList &actions,
                                 const QVariantMap &hints, int timeout)
{
    // Don't create a new notification if it comes from the same source
    if (m_notifications.values().contains(appName + summary))
        replacesId = m_notifications.key(appName + summary);

    // Calculate identifier
    uint id = replacesId > 0 ? replacesId : nextId();

    // Some applications (mostly media players) will send too many notifications,
    // for them we want to replace an older notification (if applicable)
    if (m_spamApplications.contains(appName)) {
        if (m_replaceableNotifications.contains(appName))
            id = m_replaceableNotifications.value(appName);
        else
            m_replaceableNotifications.insert(appName, id);
    }

    qCDebug(NOTIFICATIONS)
            << "Notification:"
            << "ID =" << id
            << "replaced =" << (replacesId == id)
            << appName << appIcon << summary << body
            << actions << hints << timeout;

    // Rectify appName if needed
    QString realAppName = appName;
    if (realAppName.isEmpty())
        realAppName = tr("Unknown Application");

    // Recalculate timeout depending on text, but ensure it last at least 5s
    bool isPersistent = timeout == 0;
    const int averageWordLength = 6;
    const int wordPerMinute = 250;
    int totalLength = summary.length() + body.length();
    timeout = 2000 + qMax(60000 * totalLength / averageWordLength / wordPerMinute, 3000);

    // Notification image
    NotificationImage *notificationImage = new NotificationImage();
    if (m_images.contains(id))
        delete m_images.take(id);
    m_images[id] = notificationImage;
    notificationImage->iconName = appIcon;

    // Fetch the image hint (we also support the obsolete icon_data hint which
    // is still used by applications compatible with the specification version
    if (hints.contains(QStringLiteral("image_data")))
        notificationImage->image.convertFromImage(decodeImageHint(hints["image_data"].value<QDBusArgument>()));
    else if (hints.contains(QStringLiteral("image-data")))
        notificationImage->image.convertFromImage(decodeImageHint(hints["image-data"].value<QDBusArgument>()));
    else if (hints.contains(QStringLiteral("image_path")))
        notificationImage->image = QPixmap(hints["image_path"].toString());
    else if (hints.contains(QStringLiteral("image-path")))
        notificationImage->image = QPixmap(hints["image-path"].toString());
    else if (hints.contains(QStringLiteral("icon_data")))
        notificationImage->image.convertFromImage(decodeImageHint(hints["icon_data"].value<QDBusArgument>()));

    // Retrieve icon from desktop entry, if any
    if (hints.contains(QStringLiteral("desktop-entry"))) {
        QString fileName = QStandardPaths::locate(QStandardPaths::ApplicationsLocation,
                                                  hints[QStringLiteral("desktop-entry")].toString());
        QSettings desktopEntry(fileName, QSettings::IniFormat);
        notificationImage->entryIconName = desktopEntry.value(QStringLiteral("Icon"), appIcon).toString();
    }

    // Create actions property map
    QVariantList actionsList;
    for (int i = 0; i < actions.size(); i += 2) {
        QVariantMap actionsMap;
        actionsMap[QStringLiteral("id")] = actions.at(i);
        actionsMap[QStringLiteral("text")] = actions.at(i + 1);
        actionsList.append(actionsMap);
    }

    // Create notification
    m_notifications.insert(id, appName + summary);
    bool hasIcon = !notificationImage->image.isNull() ||
            !notificationImage->iconName.isEmpty() ||
            !notificationImage->entryIconName.isEmpty();
    Q_EMIT m_parent->notificationReceived(id, realAppName, appIcon, hasIcon,
                                          summary, body, actionsList,
                                          isPersistent, timeout, hints);

    return id;
}

void NotificationsDaemon::CloseNotification(uint id)
{
    if (m_notifications.remove(id) > 0) {
        if (m_images.contains(id))
            delete m_images.take(id);

        Q_EMIT NotificationClosed(id, (uint)Notifications::CloseReasonByApplication);
    }
}

QStringList NotificationsDaemon::GetCapabilities()
{
    return QStringList()
            << "body"
            << "body-hyperlinks"
            << "body-markup"
            << "icon-static"
            << "actions"
            << "persistence";
}

QString NotificationsDaemon::GetServerInformation(QString &vendor, QString &version, QString &specVersion)
{
    vendor = QStringLiteral("Hawaii");
    version = QString::fromUtf8(LIBHAWAII_VERSION_STRING);
    specVersion = QStringLiteral("1.1");
    return QStringLiteral("Hawaii");
}

uint NotificationsDaemon::nextId()
{
    return (uint)m_idSeed->fetchAndAddAcquire(1);
}

#include "moc_notificationsdaemon.cpp"
