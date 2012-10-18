#ifndef HISTORYLISTVIEW_H
#define HISTORYLISTVIEW_H

#include <QListView>
#include <stack>
#include <QString>

class historyListView : public QListView
{
Q_OBJECT
public:
    explicit historyListView( bool left, QWidget *parent = 0 );
    ~historyListView();
    void addHistoryItem(const QString &path);
    QString getTop();
    void forward();
    void back();
    std::stack<QString> forwardStack;
signals:

public slots:

private:
    bool mleft;
};

#endif // HISTORYLISTVIEW_H
