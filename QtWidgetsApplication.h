#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication.h"
#include <QtWidgets/QTreeView>
#include <QStandardItemModel>
#include <QtNetwork>
#include <QTimer>

class QtWidgetsApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget* parent = nullptr);
    ~QtWidgetsApplication();

    void IniUI();

    int ran();

    void traverseAndProcessNode(QStandardItem* item, bool skipFirstNode = true);

    void deleteEvenRows(QStandardItem* parentItem);
private slots:


private:
    Ui::QtWidgetsApplicationClass* m_ui;

    QTcpSocket* tcpSocket;
    QTcpServer* tcpServer;
    QTimer* timer;
};
