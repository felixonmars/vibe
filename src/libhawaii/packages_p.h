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

#ifndef PACKAGES_P_H
#define PACKAGES_P_H

#include "packagestructure.h"

namespace Hawaii {

class BasePackage : public PackageStructure
{
public:
    void initializePackage(Package *package);
};

class MainScriptPackage : public PackageStructure
{
public:
    void initializePackage(Package *package);

protected:
    void pathChanged(Package *package);
};

class BackgroundPackage : public MainScriptPackage
{
public:
    void initializePackage(Package *package);
};

class ElementPackage : public MainScriptPackage
{
public:
    void initializePackage(Package *package);
};

class ContainmentPackage : public MainScriptPackage
{
public:
    void initializePackage(Package *package);
};

class ShellPackage : public BasePackage
{
public:
    void initializePackage(Package *package);
};

class LookAndFeelPackage : public BasePackage
{
public:
    void initializePackage(Package *package);
};

class PreferencesPackage : public MainScriptPackage
{
public:
    void initializePackage(Package *package);
};

} // namespace Hawaii

#endif // PACKAGES_P_H
