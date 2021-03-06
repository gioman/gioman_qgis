/***************************************************************************
                qgscrashdialog.h - QgsCrashDialog

 ---------------------
 begin                : 11.4.2017
 copyright            : (C) 2017 by Nathan Woodrow
 email                : woodrow.nathan@gmail.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSCRASHDIALOG_H
#define QGSCRASHDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QPushButton>

#include "ui_qgscrashdialog.h"
#include "qgis_app.h"
#include "qgspanelwidget.h"

/**
 * A dialog to show a nicer crash dialog to the user.
 */
class APP_EXPORT QgsCrashDialog : public QDialog, private Ui::QgsCrashDialog
{
    Q_OBJECT
  public:

    /**
     * A dialog to show a nicer crash dialog to the user.
     */
    QgsCrashDialog( QWidget *parent = nullptr );

    void setBugReport( const QString &reportData );

    static QString htmlToMarkdown( const QString &html );

  private slots:
    void showReportWidget();
    void createBugReport();

  private:
    QString mReportData;
};

#endif // QGSCRASHDIALOG_H
