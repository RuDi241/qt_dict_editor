#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QTableWidget>
#include <customtablewidgetitem.h>

class CustomTableWidget : public QTableWidget
{
public:
    CustomTableWidget(QWidget*);
    bool Exist(const QString&);
    QTableWidgetItem* Find(const QString&);
    void EditItem (const QString&, QTableWidgetItem*);
    void AddNewItem(QTableWidgetItem*, QTableWidgetItem*);
    bool canCallChangeEvent;
private:
    int findPosition(const QString&);
};

#endif // CUSTOMTABLEWIDGET_H
