#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    searchResultItem = nullptr;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionOpen_triggered()
{
    ui->tableWidget->canCallChangeEvent = false;
    fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Dictionary (*.dic)");
    QFile file(fileName);
    if(!file.open(QFile::OpenModeFlag::Text | QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", "File has not been opened!");
        file.close();
        return;
    }
    QStringList list0;
    QStringList list1;
    QTextStream in(&file);
    while(!in.atEnd()) {
        list0.push_back(in.readLine());
        list1.push_back(in.readLine());
    }
    file.close();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    QPair<int, int> columnsWidth;
    for(int i = 0; i < std::max(list0.size(), list1.size()); i++) {
        ui->tableWidget->AddNewItem(new CustomTableWidgetItem(list0[i]), new CustomTableWidgetItem(list1[i]));
        columnsWidth.first = std::max(list0[i].size()*7, columnsWidth.first);
        columnsWidth.second = std::max(list1[i].size()*7, columnsWidth.second);
    }
    ui->tableWidget->setColumnWidth(0, columnsWidth.first);
    ui->tableWidget->setColumnWidth(1, columnsWidth.second);
    ui->lineEdit->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionAdd_row->setEnabled(true);
    IsSaving = false;
    ui->tableWidget->canCallChangeEvent = true;
}
void MainWindow::on_lineEdit_textChanged(const QString& query)
{
    if(searchResultItem != nullptr) searchResultItem->setSelected(false);
    searchResultItem = ui->tableWidget->Find(query);
    if(searchResultItem != nullptr) {
        ui->tableWidget->scrollToItem(searchResultItem);
        searchResultItem->setSelected(true);
    }
}
void MainWindow::on_actionAdd_row_triggered()
{
    if(ui->tableWidget->Exist("")) return;
    ui->tableWidget->canCallChangeEvent = false;
    ui->tableWidget->AddNewItem(new CustomTableWidgetItem(""), new CustomTableWidgetItem(""));
    ui->tableWidget->scrollToTop();
    ui->tableWidget->canCallChangeEvent = true;
}
void MainWindow::on_actionSave_triggered()
{
    if(IsSaving) return;
    QFile file(fileName);
    if(!file.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Warning!", "File has not been saved!");
        return;
    }
    IsSaving = true;
    ui->tableWidget->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    QTextStream out(&file);
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        out << ui->tableWidget->item(i,0)->text() << '\n'
            << ui->tableWidget->item(i,1)->text() << '\n';
        out.flush();
    }
    file.close();
    IsSaving = false;
}
/*
void MainWindow::on_actionadd10000000lines_triggered()
{
    ui->tableWidget->canCallChangeEvent = false;
    int l = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 100);
    for(int i = l; i < ui->tableWidget->rowCount(); ++i) {
        ui->tableWidget->AddNewItem(new CustomTableWidgetItem("Привет, Мир!" + QString::number(i)),
                new CustomTableWidgetItem("Привет, Мир!" + QString::number(i)));
    }
    ui->tableWidget->canCallChangeEvent = true;
}
*/
void MainWindow::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    prevValue = current->text();
}
void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(!ui->tableWidget->canCallChangeEvent || item->column() != 0) return;
    QString temp = item->text();
    ui->tableWidget->canCallChangeEvent = false;
    item->setText(prevValue);
    if(!ui->tableWidget->Exist(temp)) {
        ui->tableWidget->EditItem(temp, item);
    }
    ui->tableWidget->canCallChangeEvent = true;
}

/*
void MainWindow::receiveData() {
    QTcpSocket socket;
    socket.connectToHost("63.209.35.135", 5217);
    QString s;
    if(socket.waitForConnected(3000)) {
        std::cout << "Connected!" << std::endl;
        int i = 0x02;
        socket.write((const char*) &i, sizeof(i));
        socket.waitForBytesWritten(1000);
        socket.waitForReadyRead(3000);
        QDataStream stream(&socket);
        QString data =
        QStringList data;
        bool inString = false;
        QString numBuffer = "";
        int inputsExpected = 1000000000;
        while(inputsExpected > 0)
        {
            if(!socket.bytesAvailable()) continue;
            if(inString) {
                QString c = socket.read(1);
                if(c[0] == '\013')
                {
                    inString = false;
                    inputsExpected--;
                }
                else
                    data.last().append(c);
            } else
            {
                QString c = socket.read(1);
                if(c[0] == '\013')
                {
                    inString = true;
                    data.push_back("");
                    if(numBuffer.size() != 0)
                    {
                        inputsExpected = numBuffer.toInt();
                    }
                }
                else {
                    numBuffer.append(c);
                }
            }
        }
        socket.close();
    } else {
      std::cout << "Not connected!" << std::endl;
    }
}
*/
/*
void MainWindow::on_actionconnect_triggered()
{
    //receiveData();
}
*/
