#include "customtablewidgetitem.h"

CustomTableWidgetItem::CustomTableWidgetItem(const QString& string) : QTableWidgetItem(std::move(string)) {};
bool CustomTableWidgetItem::operator< (const QTableWidgetItem &other) const
     {
         return (this->text() < other.text());
     }
