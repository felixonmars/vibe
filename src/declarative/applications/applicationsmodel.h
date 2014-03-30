/****************************************************************************
 * This file is part of libhawaii.
 *
 * Copyright (C) 2012-2014 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef APPLICATIONSMODEL_H
#define APPLICATIONSMODEL_H

#include <QtCore/QSet>
#include <QtCore/QAbstractListModel>
#include <QtCore/QSortFilterProxyModel>
#include <QtQml/QQmlComponent>

#include <hawaii/appinfo.h>

class QFileSystemWatcher;

class ApplicationsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CommentRole,
        IconNameRole,
        CategoriesRole
    };

    ApplicationsModel(QObject *parent = 0);
    ~ApplicationsModel();

    QHash<int, QByteArray> roleNames() const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

public Q_SLOTS:
    void populate();

    Hawaii::AppInfo *get(int index);
    void launch(int index);

private:
    QList<Hawaii::AppInfo *> m_apps;
    QFileSystemWatcher *m_watcher;
    QSet<QString> m_categories;

    void cleanupCategories();

private Q_SLOTS:
    void directoryChanged(const QString &path);
};

class ApplicationsModelSorted : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ApplicationsModelSorted(QObject *parent = 0);
    ~ApplicationsModelSorted();

private:
    ApplicationsModel *m_model;
};

QML_DECLARE_TYPE(ApplicationsModel)
QML_DECLARE_TYPE(ApplicationsModelSorted)

#endif // APPLICATIONSMODEL_H
