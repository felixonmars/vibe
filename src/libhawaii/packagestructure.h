/****************************************************************************
 * This file is part of libhawaii.
 *
 * Copyright (C) 2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2011 Aaron Seigo <aseigo@kde.org>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#ifndef PACKAGESTRUCTURE_H
#define PACKAGESTRUCTURE_H

#include <QtCore/QObject>

#include <hawaii/hawaii_export.h>
#include <hawaii/package.h>

namespace Hawaii {

class PackageStructurePrivate;

class HAWAII_EXPORT PackageStructure : public QObject
{
    Q_OBJECT
public:
    explicit PackageStructure(QObject *parent = 0, const QVariantList &args = QVariantList());
    ~PackageStructure();

    virtual void initializePackage(Package *package);
    virtual void pathChanged(Package *package);

private:
    Q_DECLARE_PRIVATE(PackageStructure)
    PackageStructurePrivate *const d_ptr;
};

} // namespace Hawaii

#endif // PACKAGESTRUCTURE_H
