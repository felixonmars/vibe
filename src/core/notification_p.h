/*
 * This file is part of Vibe.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
 */

#pragma once

#include <QtCore/private/qobject_p.h>

#include "notification.h"

class OrgFreedesktopNotificationsInterface;

namespace Vibe {

class NotificationPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(Notification)
public:
    NotificationPrivate();

    OrgFreedesktopNotificationsInterface *iface;

    QString appName;
    QString appIcon;
    QString summary;
    QString body;
    quint32 replacesId;
    int timeout;
    QVariantMap hints;
    QStringList actions;
};

} // namespace Vibe
