#ifndef CUSTOMTABLEWIDGETITEM_H
#define CUSTOMTABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <QDebug>

class CustomTableWidgetItem : public QTableWidgetItem
{
public:
    CustomTableWidgetItem(const QString&);
    bool operator< (const QTableWidgetItem &other) const;
};

#endif // CUSTOMTABLEWIDGETITEM_H
