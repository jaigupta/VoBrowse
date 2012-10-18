/*
The QeFeM project.
Copyright (C) 2010  Karim Pinter

This code is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QMovie>
#include "fmpanel.h"
//#include "mainwindow.h"
#include "utils.h"

class MainWindow;

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    ControlPanel( MainWindow* aMainW, FMPanel* aLeftPanel, FMPanel* aRightPanel );
    ~ControlPanel();
    QStringList getStatus();
    void disableButtons();
    void enableButtons();
    void stopAnimation();
    void startAnimation();
private slots:
    void bookmarkButtonClicked( bool checked );

#if defined(QEFEM_MAEMO_DEV)
    void exitButtonClicked( bool checked );
    void openButtonClicked( bool checked );
#endif
    void searchButtonClicked( bool /*checked*/ );
private:
    QLabel *animation;
    QMovie *movie;
    QHBoxLayout* commandLayout;
    QPushButton *bookmarkButton;
    QPushButton *searchButton;
#if defined(QEFEM_MAEMO_DEV)
    QPushButton *exitButton;
    QPushButton *openButton;
#endif
    FMPanel* leftPanel;
    FMPanel* rightPanel;
    MainWindow* mainW;
    bool statusOn;
};

#endif // CONTROLPANEL_H
