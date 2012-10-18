#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QtGui>
#include <QWidget>
#include <QTextEdit>
#include <QString>
#include "Speech.h"
#include <vector>
#include <string>

  class Notepad: public QWidget
          {
              Q_OBJECT

         public:
             Notepad();


         private slots:
             void quit();
             void readFromFile(QString);
             void moveCursorDown();
             void moveCursorUp();
             void fontUp();
             void fontDown();
             
         private:
             QTextEdit *textEdit;
             QPushButton *quitButton;
             QPushButton *loadButton;
             QPushButton *downButton;
             QPushButton *upButton;
             QPushButton *fontUpButton;
             QPushButton *fontDownButton;
             QLabel *pathDisp;
             QPushButton *createButton(const QString &text, const char *member);
             
         };


#endif // NOTEPAD_H

