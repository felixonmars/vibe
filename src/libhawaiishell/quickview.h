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

#ifndef QUICKVIEW_H
#define QUICKVIEW_H

#include <QtQuick/QQuickView>

#include <hawaiishell/hawaiishell.h>
#include <hawaiishell/mantle.h>

namespace Hawaii {

class Containment;
class QuickViewPrivate;

class HAWAIISHELL_EXPORT QuickView : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(Hawaii::Types::FormFactor formFactor READ formFactor WRITE setFormFactor NOTIFY formFactorChanged)
    Q_PROPERTY(Hawaii::Types::Location location READ location WRITE setLocation NOTIFY locationChanged)
    Q_PROPERTY(bool immutable READ isImmutable WRITE setImmutable NOTIFY immutableChanged)
    Q_PROPERTY(bool configuring READ isConfiguring WRITE setConfiguring NOTIFY configuringChanged)
    Q_PROPERTY(QRectF screenGeometry READ screenGeometry NOTIFY screenGeometryChanged)
public:
    /*!
     * Constructor.
     * \param mantle the mantle for this view
     * \param parent the QWindow this view is parented to
     */
    QuickView(Mantle *mantle, QWindow *parent = 0);

    /*!
     * Destructor.
     */
    virtual ~QuickView();

    /*!
     * \return the mantle for this view.
     */
    Mantle *mantle() const;

    /*!
     * \return the containment for this view.
     */
    Containment *containment() const;

    /*!
     * Sets the containment for this view.
     * The containment will influence the \a formFactor and
     * \a location properties.
     *
     * \param containment the containment for this view
     *
     * \sa formFactor()
     * \sa location()
     */
    void setContainment(Containment *containment);

    /*!
     * \return the form factor of this view.
     */
    Hawaii::Types::FormFactor formFactor() const;

    /*!
     * Sets the form factor of this view.
     * \param formFactor the form factor of the view
     */
    void setFormFactor(Types::FormFactor value);

    /*!
     * \return the location of this view.
     */
    Hawaii::Types::Location location() const;

    /*!
     * Sets the location of this view.
     * \param location the location of the view
     */
    void setLocation(Types::Location value);

    /*!
     * \return whether the view is immutable or not.
     */
    bool isImmutable() const;

    /*!
     * Makes the view immutable or not.
     * Immutable views cannot be configured by the user.
     * \param value whether the view is immutable or not
     */
    void setImmutable(bool value);

    /*!
     * \return whether this view is in configuration mode.
     */
    bool isConfiguring() const;

    /*!
     * Enable or disable the configuration mode.
     * \param value whether configuration mode is enabled or not.
     */
    void setConfiguring(bool value);

    /*!
     * \return the geometry of the screen where this view is located.
     */
    QRectF screenGeometry() const;

protected:
    /*!
     * Shows the configuration window for this view.
     * This method must be implemented by custom views to create and
     * set configuration windows up.
     */
    virtual void showConfigurationWindow();

    /*!
     * Hide the configuration window for this view.
     * This method must be implemented by custom views to hide and
     * destroy the configuration window when it's not needed anymore.
     */
    virtual void hideConfigurationWindow();

Q_SIGNALS:
    /*!
     * Emitted when the containment is changed.
     */
    void containmentChanged();

    /*!
     * Emitted when the form factor is changed.
     * \param formFactor the new form factorof the view
     */
    void formFactorChanged(Hawaii::Types::FormFactor formFactor);

    /*!
     * Emitted when the location is changed.
     * \param location the new location of the view
     */
    void locationChanged(Hawaii::Types::Location location);

    /*!
     * Emitted when the view becomes immutable or it's no longer
     * immutable.
     * \param newValue whether the view is immutable
     */
    void immutableChanged(bool newValue);

    /*!
     * Emitted when the configuration mode is enabled or disabled.
     * \param newValue whether the view is now in configuration mode or not.
     */
    void configuringChanged(bool newValue);

    /*!
     * Emitted when the screen geometry is changed.
     * \param geometry the new screen geometry
     */
    void screenGeometryChanged(const QRect &geometry);

private:
    Q_DECLARE_PRIVATE(QuickView)
    QuickViewPrivate *const d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_configuringChanged(bool value))
};

} // namespace Hawaii

#endif // QUICKVIEW_H
