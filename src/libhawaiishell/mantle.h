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

#ifndef MANTLE_H
#define MANTLE_H

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include <hawaii/package.h>
#include <hawaiishell/hawaiishell_export.h>

namespace Hawaii {

class MantlePrivate;

class HAWAIISHELL_EXPORT Mantle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString shell READ shell NOTIFY shellChanged)
    Q_PROPERTY(QString lookAndFeel READ lookAndFeel NOTIFY lookAndFeelChanged)
public:
    explicit Mantle(QObject *parent = 0);
    ~Mantle();

    QQmlEngine *engine() const;

    QString shell() const;
    Package shellPackage() const;

    QString lookAndFeel() const;
    Package lookAndFeelPackage() const;

Q_SIGNALS:
    void shellChanged(const QString &shell);
    void shellPackageChanged(const Package &package);

    void lookAndFeelChanged(const QString &name);
    void lookAndFeelPackageChanged(const Package &package);

protected:
    void setShell(const QString &name);
    void setShellPackage(const Package &package);

    void setLookAndFeel(const QString &name);
    void setLookAndFeelPackage(const Package &package);

private:
    Q_DECLARE_PRIVATE(Mantle)
    MantlePrivate *const d_ptr;
};

} // namespace Hawaii

#endif // MANTLE_H
