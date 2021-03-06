/***************************************************************************
                         qgsinbuiltlocatorfilters.h
                         --------------------------
    begin                : May 2017
    copyright            : (C) 2017 by Nyall Dawson
    email                : nyall dot dawson at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSINBUILTLOCATORFILTERS_H
#define QGSINBUILTLOCATORFILTERS_H

#include "qgslocatorfilter.h"
class QAction;

class QgsLayerTreeLocatorFilter : public QgsLocatorFilter
{
    Q_OBJECT

  public:

    QgsLayerTreeLocatorFilter( QObject *parent = nullptr );
    virtual QString name() const override { return QStringLiteral( "layertree" ); }
    virtual QString displayName() const override { return tr( "Project Layers" ); }
    virtual Priority priority() const override { return Highest; }
    QString prefix() const override { return QStringLiteral( "l" ); }

    void fetchResults( const QString &string, const QgsLocatorContext &context, QgsFeedback *feedback ) override;
    void triggerResult( const QgsLocatorResult &result ) override;

};

class QgsLayoutLocatorFilter : public QgsLocatorFilter
{
    Q_OBJECT

  public:

    QgsLayoutLocatorFilter( QObject *parent = nullptr );
    virtual QString name() const override { return QStringLiteral( "layouts" ); }
    virtual QString displayName() const override { return tr( "Project Layouts" ); }
    virtual Priority priority() const override { return Highest; }
    QString prefix() const override { return QStringLiteral( "pl" ); }

    void fetchResults( const QString &string, const QgsLocatorContext &context, QgsFeedback *feedback ) override;
    void triggerResult( const QgsLocatorResult &result ) override;

};

class QgsActionLocatorFilter : public QgsLocatorFilter
{
    Q_OBJECT

  public:

    QgsActionLocatorFilter( const QList<QWidget *> &parentObjectsForActions, QObject *parent = nullptr );
    virtual QString name() const override { return QStringLiteral( "actions" ); }
    virtual QString displayName() const override { return tr( "Actions" ); }
    virtual Priority priority() const override { return Lowest; }
    QString prefix() const override { return QStringLiteral( "." ); }

    void fetchResults( const QString &string, const QgsLocatorContext &context, QgsFeedback *feedback ) override;
    void triggerResult( const QgsLocatorResult &result ) override;
  private:

    QList< QWidget * > mActionParents;

    void searchActions( const QString &string, QWidget *parent, QList< QAction *> &found );

};

#endif // QGSINBUILTLOCATORFILTERS_H


