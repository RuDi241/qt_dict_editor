#include "customtablewidget.h"

CustomTableWidget::CustomTableWidget(QWidget* widget)
    : QTableWidget(widget)
{
    canCallChangeEvent = true;
}
bool CustomTableWidget::Exist(const QString& query) {
    if(Find(query) != nullptr) return true;
    return false;
}
QTableWidgetItem* CustomTableWidget::Find(const QString& query) {
    int l = 0, r = this->rowCount()-1, m;
    while(l <= r) {
        m = (l + r)/2;
        if(this->item(m,0)->text() == query)
            return this->item(m,0);
        else if(this->item(m,0)->text() < query) l = m + 1;
        else r = m - 1;
    }
    return nullptr;
}
void CustomTableWidget::AddNewItem(QTableWidgetItem* itemPtr0, QTableWidgetItem* itemPtr1) {
    canCallChangeEvent = false;
    int pos = findPosition(itemPtr0->text());
    setRowCount(rowCount() + 1);
    for(int i = rowCount() - 2; i > pos; --i) {
        setItem(i + 1, 0, takeItem(i,0));
        setItem(i + 1, 1, takeItem(i,1));
    }
    setItem(pos, 0, itemPtr0);
    setItem(pos, 1, itemPtr1);
    canCallChangeEvent = true;
}
void CustomTableWidget::EditItem(const QString &itemText, QTableWidgetItem* itemPtr) {
    canCallChangeEvent = false;
    int pos = findPosition(itemText);
    int ipos = itemPtr->row();
    itemPtr->setText(itemText);
    if(ipos == pos) return;
    auto column1 = takeItem(itemPtr->row(),1);
    itemPtr = takeItem(itemPtr->row(), itemPtr->column());
    if(ipos < pos) {
        pos--;
        for(int i = ipos + 1;i <= pos ; ++i) {
            setItem(i - 1, 0, takeItem(i,0));
            setItem(i - 1, 1, takeItem(i,1));
        }
    } else {
        //pos++;
        for(int i = pos ;i >= ipos - 1; --i) {
            setItem(i + 1, 0, takeItem(i,0));
            setItem(i + 1, 1, takeItem(i,1));
        }
    }
    setItem(pos, 0, itemPtr);
    setItem(pos, 1, column1);
    canCallChangeEvent = true;
}
int CustomTableWidget::findPosition(const QString& query) {
    int l = 0, r = this->rowCount()-1, m;
    while(l <= r) {
        m = (l + r)/2;
        if(this->item(m,0)->text() < query) l = m + 1;
        else r = m - 1;
    }
    return l;
}
