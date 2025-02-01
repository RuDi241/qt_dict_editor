#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define YELLOW 100,100,0
#define WHITE 255,255,255

#include <QMainWindow>
#include <QTableWidget>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QTcpSocket>
#include <QtNetwork>
#include <chrono>
#include <thread>
#include "customtablewidgetitem.h"
#include "customtablewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionOpen_triggered();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_actionAdd_row_triggered();
    void on_actionSave_triggered();
    void on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);
    void on_tableWidget_itemChanged(QTableWidgetItem *item);
    //svoid on_actionadd10000000lines_triggered();
    //void on_actionconnect_triggered();

private:
    Ui::MainWindow *ui;
    QTableWidgetItem* searchResultItem;
    QString prevValue;
    QString fileName;
    bool IsSaving;
    void receiveData();
};
#endif // MAINWINDOW_H
