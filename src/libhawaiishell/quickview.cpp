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

#include <QtCore/QPointer>
#include <QtGui/QScreen>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickItem>

#include "containment.h"
#include "qmlobject.h"
#include "quickview.h"

namespace Hawaii {

/*
 * QuickViewPrivate
 */

class QuickViewPrivate
{
    Q_DECLARE_PUBLIC(QuickView)
public:
    QuickViewPrivate(QuickView *view);

    Mantle *mantle;
    QPointer<Containment> containment;

    void initialize();

    void _q_configuringChanged(bool value);

protected:
    QuickView *const q_ptr;
};

QuickViewPrivate::QuickViewPrivate(QuickView *view)
    : q_ptr(view)
{
}

void QuickViewPrivate::initialize()
{
    Q_Q(QuickView);

    // Transparent color
    q->setColor(Qt::transparent);

    // Set custom window type
    q->setFlags(Qt::BypassWindowManagerHint);

    // Create platform window
    q->create();

    // View is sized by the root object
    q->setResizeMode(QQuickView::SizeViewToRootObject);
}

void QuickViewPrivate::_q_configuringChanged(bool value)
{
    Q_Q(QuickView);

    // Views inheriting QuickView will have to override these methods
    // implementing their window setup code
    if (value)
        q->showConfigurationWindow();
    else
        q->hideConfigurationWindow();
}

/*
 * QuickView
 */

QuickView::QuickView(Mantle *mantle, QWindow *parent)
    : QQuickView(mantle->engine(), parent)
    , d_ptr(new QuickViewPrivate(this))
{
    Q_D(QuickView);
    d->mantle = mantle;
    d->initialize();
}

QuickView::~QuickView()
{
    delete d_ptr;
}

Mantle *QuickView::mantle() const
{
    Q_D(const QuickView);
    return d->mantle;
}

Containment *QuickView::containment() const
{
    Q_D(const QuickView);
    return d->containment.data();
}

void QuickView::setContainment(Containment *containment)
{
    Q_D(QuickView);

    if (d->containment.data() == containment)
        return;

    Types::FormFactor oldFormFactor = formFactor();
    Types::Location oldLocation = location();

    if (d->containment) {
        disconnect(d->containment.data(), nullptr, this, nullptr);

        QObject *oldItem = d->containment.data()->property("_graphicObject").value<QObject *>();
        if (oldItem)
            oldItem->setParent(d->containment.data());
    }

    d->containment = containment;

    if (oldFormFactor != formFactor())
        Q_EMIT formFactorChanged(formFactor());
    if (oldLocation != location())
        Q_EMIT locationChanged(location());

    Q_EMIT containmentChanged();

    if (containment) {
        connect(containment, &Containment::locationChanged,
                this, &QuickView::locationChanged);
        connect(containment, &Containment::formFactorChanged,
                this, &QuickView::formFactorChanged);
        connect(containment, &Containment::immutableChanged,
                this, &QuickView::immutableChanged);
        connect(containment, SIGNAL(configuringChanged(bool)),
                this, SLOT(_q_configuringChanged(bool)));

        QQuickItem *item = qobject_cast<QQuickItem *>(d->containment.data()->property("_graphicObject").value<QObject *>());
        if (item) {
            item->setProperty("width", width());
            item->setProperty("height", height());
            item->setParentItem(rootObject());

            if (rootObject())
                rootObject()->setProperty("containment", QVariant::fromValue(item));
        }
    }
}

Hawaii::Types::FormFactor QuickView::formFactor() const
{
    Q_D(const QuickView);

    if (!d->containment)
        return Types::Plane;
    return d->containment.data()->formFactor();
}

void QuickView::setFormFactor(Types::FormFactor value)
{
    Q_D(QuickView);

    if (formFactor() != value)
        d->containment.data()->setFormFactor(value);
}

Hawaii::Types::Location QuickView::location() const
{
    Q_D(const QuickView);

    if (!d->containment)
        return Types::Desktop;
    return d->containment.data()->location();
}

void QuickView::setLocation(Types::Location value)
{
    Q_D(QuickView);

    if (location() != value)
        d->containment.data()->setLocation(value);
}

bool QuickView::isImmutable() const
{
    Q_D(const QuickView);

    if (!d->containment)
        return true;
    return d->containment.data()->isImmutable();
}

void QuickView::setImmutable(bool value)
{
    Q_D(QuickView);

    if (isImmutable() != value)
        d->containment.data()->setImmutable(value);
}

bool QuickView::isConfiguring() const
{
    Q_D(const QuickView);

    if (!d->containment)
        return false;
    return d->containment.data()->isConfiguring();
}

void QuickView::setConfiguring(bool value)
{
    Q_D(QuickView);

    if (isConfiguring() != value)
        d->containment.data()->setConfiguring(value);
}

void QuickView::showConfigurationWindow()
{
}

void QuickView::hideConfigurationWindow()
{
}

} // Hawaii namespace

#include "moc_quickview.cpp"
