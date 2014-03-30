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

#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <hawaii/package.h>

namespace Hawaii {

class PluginLoaderPrivate;

class HAWAII_EXPORT PluginLoader
{
public:
    enum PluginType {
        BackgroundPlugin = 0,
        ElementPlugin = 1,
        ContainmentPlugin = 2,
        ShellPlugin = 3,
        LookAndFeelPlugin = 4,
        PreferencesPlugin = 5,
        CustomPlugin = 0x0100
    };

    PluginLoader();
    ~PluginLoader();

    static PluginLoader *instance();

    Package loadPackage(PluginType type);

    QStringList listPlugins(PluginType type);

private:
    Q_DECLARE_PRIVATE(PluginLoader)
    PluginLoaderPrivate *const d_ptr;
};

} // namespace Hawaii

#endif // PLUGINLOADER_H
