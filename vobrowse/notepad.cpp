#include "notepad.h"
using namespace std;

Notepad::Notepad()
{
    textEdit = new QTextEdit();
    textEdit->setReadOnly(true);
    pathDisp= new QLabel();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(textEdit, 1,0,1,10);
    layout->addWidget(pathDisp, 0,0,1,3);
    setLayout(layout);

    setWindowTitle(tr("Text Reader"));


    textEdit->setFontPointSize(14);

    resize(900,600);

    textEdit->moveCursor(QTextCursor::Start);
    textEdit->ensureCursorVisible();
    textEdit->setCursorWidth(5);
    textEdit->append(QString::number(textEdit->height()));

    int i;
    for(i=0;i<5;i++) textEdit->moveCursor(QTextCursor::Down);



}

void Notepad::quit()
{
   if(( QMessageBox::question(
                this,
                tr("Quit?"),
                tr("Do you really want to quit the Notepad?"),
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No
                ) == QMessageBox::Yes
            )) qApp->quit();
}

QPushButton *Notepad::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void Notepad::readFromFile(QString fileName)
{
    Speech::instance()->stop();
    pathDisp->setText("FileName:" + fileName);
    QFile file(fileName);
    textEdit->setText("");
    vector<string> filecontent;
    if (file.open(QIODevice::ReadOnly))
    {
        QString line;
        QTextStream in(&file);
        while (!in.atEnd())
        {
            line = in.readLine();
            textEdit->append(line);
            filecontent.push_back(line.toLocal8Bit().data());
        }
    }
    Speech::instance()->sayList(filecontent, 1);
    textEdit->verticalScrollBar()->setValue((textEdit->verticalScrollBar()->minimum() + textEdit->verticalScrollBar()->maximum())/2);
    textEdit->selectAll();
    textEdit->setFontPointSize(12);
    textEdit->moveCursor(QTextCursor::Right);
    this->show();
}

void Notepad::moveCursorDown()
{
    int i;
    for(i = 0; i < 15; i++)
    {
        textEdit->moveCursor(QTextCursor::Down);
    }
}

void Notepad::moveCursorUp()
{
     int i;
    for(i=0;i<15;i++)
    {
        textEdit->moveCursor(QTextCursor::Up);
    }
}

void Notepad::fontUp()
{
    textEdit->selectAll();
    textEdit->setFontPointSize(textEdit->fontPointSize()+1);
    textEdit->moveCursor(QTextCursor::Right);
}

void Notepad::fontDown()
{
    textEdit->selectAll();
    if(textEdit->fontPointSize()>4) textEdit->setFontPointSize(textEdit->fontPointSize()-1);
    textEdit->moveCursor(QTextCursor::Right);
}

