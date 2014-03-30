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

#include <hawaii/pluginmetadata.h>

#include "packagesmodelitem.h"

using namespace Hawaii;

/*
 * PackagesModelItemPrivate
 */

class PackagesModelItemPrivate
{
public:
    PackagesModelItemPrivate()
    {
    }

    Package package;
};

/*
 * PackagesModelItem
 */

PackagesModelItem::PackagesModelItem(Package package, QObject *parent)
    : QObject(parent)
    , d_ptr(new PackagesModelItemPrivate())
{
    Q_D(PackagesModelItem);
    d->package = package;
}

PackagesModelItem::~PackagesModelItem()
{
    delete d_ptr;
}

QString PackagesModelItem::internalName() const
{
    Q_D(const PackagesModelItem);
    return d->package.metadata().internalName();
}

QString PackagesModelItem::name() const
{
    Q_D(const PackagesModelItem);
    return d->package.metadata().name();
}

QString PackagesModelItem::comment() const
{
    Q_D(const PackagesModelItem);
    return d->package.metadata().comment();
}

QUrl PackagesModelItem::filePath(const QString &key, const QString &fileName) const
{
    Q_D(const PackagesModelItem);

    if (!d->package.isValid())
        return QUrl();

    return QUrl::fromLocalFile(d->package.filePath(qPrintable(key), fileName));
}

#include "moc_packagesmodelitem.cpp"
