/****************************************************************************
 * This file is part of libhawaiishell.
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

#include "mantle_p.h"

namespace Hawaii {

/*
 * MantlePrivate
 */

MantlePrivate::MantlePrivate(Mantle *parent)
    : engine(new QQmlEngine(parent))
    , q_ptr(parent)
{
}

/*
 * Mantle
 */

Mantle::Mantle(QObject *parent)
    : QObject(parent)
    , d_ptr(new MantlePrivate(this))
{
}

Mantle::~Mantle()
{
    delete d_ptr;
}

QQmlEngine *Mantle::engine() const
{
    Q_D(const Mantle);
    return d->engine;
}

QString Mantle::shell() const
{
    Q_D(const Mantle);
    return d->shell;
}

Package Mantle::shellPackage() const
{
    Q_D(const Mantle);
    return d->shellPackage;
}

void Mantle::setShell(const QString &name)
{
    Q_D(Mantle);

    if (d->shell != name) {
        d->shell = name;
        Q_EMIT shellChanged(d->shell);
    }
}

void Mantle::setShellPackage(const Package &package)
{
    Q_D(Mantle);
    d->shellPackage = package;
    Q_EMIT shellPackageChanged(package);
}

} // namespace Hawaii

#include "moc_mantle.cpp"
