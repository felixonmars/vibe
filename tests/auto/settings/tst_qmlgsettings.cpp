/****************************************************************************
 * This file is part of Vibe.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtQuickTest/QtQuickTest>

// Can't use QUICK_TEST_MAIN because we need to
// set environment variables
int main(int argc, char **argv)
{
    qputenv("GSETTINGS_BACKEND", "memory");
    qputenv("GSETTINGS_SCHEMA_DIR", QByteArrayLiteral(TEST_DATADIR));
    return quick_test_main(argc, argv, "tst_qmlgsettings", QUICK_TEST_SOURCE_DIR);
}
