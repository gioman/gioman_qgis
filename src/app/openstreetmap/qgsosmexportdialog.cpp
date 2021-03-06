/***************************************************************************
  qgsosmexportdialog.cpp
  --------------------------------------
  Date                 : February 2013
  Copyright            : (C) 2013 by Martin Dobias
  Email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsosmexportdialog.h"

#include "qgsosmdatabase.h"

#include "qgsdatasourceuri.h"
#include "qgsproject.h"
#include "qgsvectorlayer.h"
#include "qgssettings.h"

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>

QgsOSMExportDialog::QgsOSMExportDialog( QWidget *parent )
  : QDialog( parent )
  , mDatabase( new QgsOSMDatabase )
{
  setupUi( this );

  connect( btnBrowseDb, &QAbstractButton::clicked, this, &QgsOSMExportDialog::onBrowse );
  connect( buttonBox, &QDialogButtonBox::accepted, this, &QgsOSMExportDialog::onOK );
  connect( buttonBox, &QDialogButtonBox::rejected, this, &QgsOSMExportDialog::onClose );
  connect( editDbFileName, &QLineEdit::textChanged, this, &QgsOSMExportDialog::updateLayerName );
  connect( radPoints, &QAbstractButton::clicked, this, &QgsOSMExportDialog::updateLayerName );
  connect( radPolylines, &QAbstractButton::clicked, this, &QgsOSMExportDialog::updateLayerName );
  connect( radPolygons, &QAbstractButton::clicked, this, &QgsOSMExportDialog::updateLayerName );
  connect( btnLoadTags, &QAbstractButton::clicked, this, &QgsOSMExportDialog::onLoadTags );
  connect( btnSelectAll, &QAbstractButton::clicked, this, &QgsOSMExportDialog::onSelectAll );
  connect( btnDeselectAll, &QAbstractButton::clicked, this, &QgsOSMExportDialog::onDeselectAll );

  mTagsModel = new QStandardItemModel( this );
  mTagsModel->setHorizontalHeaderLabels( QStringList() << tr( "Tag" ) << tr( "Count" ) << tr( "Not null" ) );
  viewTags->setModel( mTagsModel );
}

QgsOSMExportDialog::~QgsOSMExportDialog()
{
  delete mDatabase;
}


void QgsOSMExportDialog::onBrowse()
{
  QgsSettings settings;
  QString lastDir = settings.value( QStringLiteral( "osm/lastDir" ), QDir::homePath() ).toString();

  QString fileName = QFileDialog::getOpenFileName( this, QString(), lastDir, tr( "SQLite databases (*.db)" ) );
  if ( fileName.isNull() )
    return;

  settings.setValue( QStringLiteral( "osm/lastDir" ), QFileInfo( fileName ).absolutePath() );
  editDbFileName->setText( fileName );
}

void QgsOSMExportDialog::updateLayerName()
{
  QString baseName = QFileInfo( editDbFileName->text() ).baseName();

  QString layerType;
  if ( radPoints->isChecked() )
    layerType = QStringLiteral( "points" );
  else if ( radPolylines->isChecked() )
    layerType = QStringLiteral( "polylines" );
  else
    layerType = QStringLiteral( "polygons" );
  editLayerName->setText( QStringLiteral( "%1_%2" ).arg( baseName, layerType ) );
}


bool QgsOSMExportDialog::openDatabase()
{
  mDatabase->setFileName( editDbFileName->text() );

  if ( !mDatabase->open() )
  {
    QMessageBox::critical( this, QString(), tr( "Unable to open database:\n%1" ).arg( mDatabase->errorString() ) );
    return false;
  }

  return true;
}


void QgsOSMExportDialog::onLoadTags()
{
  if ( !openDatabase() )
    return;

  QApplication::setOverrideCursor( Qt::WaitCursor );

  QList<QgsOSMTagCountPair> pairs = mDatabase->usedTags( !radPoints->isChecked() );
  mDatabase->close();

  mTagsModel->setColumnCount( 3 );
  mTagsModel->setRowCount( pairs.count() );

  for ( int i = 0; i < pairs.count(); ++i )
  {
    const QgsOSMTagCountPair &p = pairs[i];
    QStandardItem *item = new QStandardItem( p.first );
    item->setCheckable( true );
    mTagsModel->setItem( i, 0, item );

    QStandardItem *item2 = new QStandardItem();
    item2->setData( p.second, Qt::DisplayRole );
    mTagsModel->setItem( i, 1, item2 );

    QStandardItem *item3 = new QStandardItem();
    item3->setData( "Not null", Qt::DisplayRole );
    item3->setCheckable( true );
    mTagsModel->setItem( i, 2, item3 );
  }

  viewTags->resizeColumnToContents( 0 );
  viewTags->sortByColumn( 1, Qt::DescendingOrder );

  QApplication::restoreOverrideCursor();
}


void QgsOSMExportDialog::onOK()
{
  if ( !openDatabase() )
    return;

  QgsOSMDatabase::ExportType type;
  if ( radPoints->isChecked() )
    type = QgsOSMDatabase::Point;
  else if ( radPolylines->isChecked() )
    type = QgsOSMDatabase::Polyline;
  else
    type = QgsOSMDatabase::Polygon;

  buttonBox->setEnabled( false );
  QApplication::setOverrideCursor( Qt::WaitCursor );

  QStringList tagKeys;
  QStringList notNullTagKeys;

  for ( int i = 0; i < mTagsModel->rowCount(); ++i )
  {
    QStandardItem *item = mTagsModel->item( i, 0 );
    if ( item->checkState() == Qt::Checked )
      tagKeys << item->text();

    QStandardItem *item2 = mTagsModel->item( i, 2 );
    if ( item2->checkState() == Qt::Checked )
      notNullTagKeys << item->text();
  }

  bool res = mDatabase->exportSpatiaLite( type, editLayerName->text(), tagKeys, notNullTagKeys );

  // load the layer into canvas if that was requested
  if ( chkLoadWhenFinished->isChecked() )
  {
    QgsDataSourceUri uri;
    uri.setDatabase( editDbFileName->text() );
    uri.setDataSource( QString(), editLayerName->text(), QStringLiteral( "geometry" ) );
    QgsVectorLayer *vlayer = new QgsVectorLayer( uri.uri(), editLayerName->text(), QStringLiteral( "spatialite" ) );
    if ( vlayer->isValid() )
      QgsProject::instance()->addMapLayer( vlayer );
  }

  QApplication::restoreOverrideCursor();
  buttonBox->setEnabled( true );

  if ( res )
  {
    QMessageBox::information( this, tr( "OpenStreetMap export" ), tr( "Export has been successful." ) );
  }
  else
  {
    QMessageBox::critical( this, tr( "OpenStreetMap export" ), tr( "Failed to export OSM data:\n%1" ).arg( mDatabase->errorString() ) );
  }

  mDatabase->close();
}

void QgsOSMExportDialog::onClose()
{
  reject();
}

void QgsOSMExportDialog::onSelectAll()
{
  for ( int i = 0; i < mTagsModel->rowCount(); ++i )
  {
    mTagsModel->item( i, 0 )->setCheckState( Qt::Checked );
  }
}

void QgsOSMExportDialog::onDeselectAll()
{
  for ( int i = 0; i < mTagsModel->rowCount(); ++i )
  {
    mTagsModel->item( i, 0 )->setCheckState( Qt::Unchecked );
  }
}
