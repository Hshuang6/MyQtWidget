#include "QtWidgetsApplication.h"
#include "dialog.h"
#include <QToolButton>
#include <QLabel>
#include <random>
#include< QFileDialog>
//#include <MyWidget.h>
#include "MyWidget.h"
#include <fstream>
#include <string>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>



QtWidgetsApplication::QtWidgetsApplication(QWidget* parent)
	: QMainWindow(parent),
	m_ui(new Ui::QtWidgetsApplicationClass)
{
	m_ui->setupUi(this);
	IniUI();

	setWindowTitle(QString::fromLocal8Bit("界面程序-胡滨鸿-8.26"));
}

QtWidgetsApplication::~QtWidgetsApplication()
{
}

void QtWidgetsApplication::IniUI()
{
	//—————————初始化工具栏————————//
	QToolButton* button1 = new QToolButton();
	button1->setIcon(QIcon("image/Tempaccount_circle_Green.png"));
	button1->setToolTip("1");
	QToolButton* button2 = new QToolButton();
	button2->setIcon(QIcon("image/Tempbuild_circle_Green.png"));
	button2->setToolTip("2");
	QToolButton* button3 = new QToolButton();
	button3->setIcon(QIcon("image/Tempcheck_circle_Green.png"));
	button3->setToolTip("3");
	QToolButton* button4 = new QToolButton();
	button4->setIcon(QIcon("image/Tempplay_circle_filled_Green.png"));
	button4->setToolTip("4");
	QToolButton* button5 = new QToolButton();
	button5->setIcon(QIcon("image/Tempsupervised_user_circle_Green_Red.png"));
	button5->setToolTip("5");
	m_ui->mainToolBar->addWidget(button1);
	m_ui->mainToolBar->addWidget(button2);
	m_ui->mainToolBar->addWidget(button3);
	m_ui->mainToolBar->addWidget(button4);
	m_ui->mainToolBar->addWidget(button5);
	connect(button1, &QToolButton::clicked, this, [=]
		{
			m_ui->listWidget->addItem(QStringLiteral("1"));
		});
	connect(button2, &QToolButton::clicked, this, [=]
		{
			m_ui->listWidget->addItem(QStringLiteral("2"));
		});
	connect(button3, &QToolButton::clicked, this, [=]
		{
			m_ui->listWidget->addItem(QStringLiteral("3"));
		});
	connect(button4, &QToolButton::clicked, this, [=]
		{
			m_ui->listWidget->addItem(QStringLiteral("4"));
		});
	connect(button5, &QToolButton::clicked, this, [=]
		{
			m_ui->listWidget->addItem(QStringLiteral("5"));
		});
	connect(m_ui->pushButton_clear, &QPushButton::clicked, this, [=]
		{
			m_ui->listWidget->clear();
		});

	//—————————打开新页面————————//
	connect(m_ui->action, &QAction::triggered, this, [=]
		{
			Dialog* newDialog = new Dialog(this);
			newDialog->show();
		});

	//—————————状态栏初始化————————//
	QLabel* leftLabel;
	QLabel* rightLabel1;
	QLabel* rightLabel2;
	// 创建左对齐的标签
	leftLabel = new QLabel("lift1");
	m_ui->statusBar->addWidget(leftLabel);
	// 创建右对齐的标签
	rightLabel1 = new QLabel("right1");
	m_ui->statusBar->addPermanentWidget(rightLabel1);
	rightLabel2 = new QLabel("right2");
	m_ui->statusBar->addPermanentWidget(rightLabel2);

	//—————————表格初始化————————//
	m_ui->tableWidget->setRowCount(8);
	m_ui->tableWidget->setColumnCount(5);
	//设置表头
	QStringList headerLabels;
	headerLabels << "1" << "2" << "3" << "4" << "5";
	m_ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
	// 填充表格内容
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			QTableWidgetItem* item = new QTableWidgetItem(QString("%1,%2").arg(row + 1).arg(col + 1));
			item->setTextAlignment(Qt::AlignCenter);
			m_ui->tableWidget->setItem(row, col, item);
		}
	}
	// 自适应行高和列宽
	m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(m_ui->pushButton, &QPushButton::clicked, this, [=]
		{
			static bool sorted = false;
			sorted = !sorted;
			if (sorted)
			{
				m_ui->tableWidget->sortItems(0, Qt::DescendingOrder);
				m_ui->pushButton->setText(QStringLiteral("正序"));
			}
			else
			{
				m_ui->tableWidget->sortItems(0, Qt::AscendingOrder);
				m_ui->pushButton->setText(QStringLiteral("倒序"));
			}
		});

	//—————————树形图初始化————————//
	QStandardItemModel* model = new QStandardItemModel(m_ui->treeView);
	model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("序号"));


	// 添加数据到模型
	for (int row = 0; row < 8; ++row)
	{
		//一级节点
		QList<QStandardItem*> items1;
		QStandardItem* item1 = new QStandardItem(QString::number(row + 1));
		items1.append(item1);
		model->appendRow(items1);
		for (int col = 0; col < 5; ++col)
		{
			//二级节点
			QList<QStandardItem*> items2;
			QStandardItem* item2 = new QStandardItem(QString::number(ran()));
			items2.append(item2);
			item1->appendRow(items2);
		}
	}
	m_ui->treeView->setModel(model);
	m_ui->treeView->setAlternatingRowColors(true);

	connect(m_ui->pushButton_zero, &QPushButton::clicked, this, [=]
		{
			// 遍历子节点内容
			QModelIndex rootIndex = model->indexFromItem(model->invisibleRootItem());
			for (int row = 0; row < model->rowCount(rootIndex); ++row) {
				QModelIndex itemIndex = model->index(row, 0, rootIndex);
				traverseAndProcessNode(model->itemFromIndex(itemIndex));
			}
		});
	connect(m_ui->pushButton_delete, &QPushButton::clicked, this, [=]
		{
			// 删除子节点中的偶数行
			QModelIndex rootIndex = model->indexFromItem(model->invisibleRootItem());
			for (int row = 0; row < model->rowCount(rootIndex); ++row) {
				QModelIndex itemIndex = model->index(row, 0, rootIndex);
				QStandardItem* item = model->itemFromIndex(itemIndex);
				deleteEvenRows(item);
			}
		});

	MyWidget* myWidget = new MyWidget(this);
	m_ui->verticalLayout->addWidget(myWidget);

	//—————————TCP初始化————————//
	//客户端
	m_ui->textEdit->setReadOnly(true);
	tcpSocket = new QTcpSocket(this);
	timer = new QTimer(this);
	tcpSocket->connectToHost(QHostAddress::LocalHost, 6666); // 端口
	connect(m_ui->pushButton_start, &QPushButton::clicked, this, [=]
		{
			static bool sorted = false;
			sorted = !sorted;
			if (sorted)
			{
				m_ui->pushButton_start->setText(QStringLiteral("停止"));
				timer->start(500); // 每500ms发送一次
			}
			else
			{
				m_ui->pushButton_start->setText(QStringLiteral("开始"));
				timer->stop();
			}

		});
	connect(timer, &QTimer::timeout, this, [=]
		{
			QString textToSend = "Sent: " + QString::number(ran());
			QByteArray send_data = textToSend.toUtf8();
			tcpSocket->write(send_data);
			tcpSocket->flush();
			// 显示发送内容，并换行

			m_ui->textEdit->append(textToSend);
		});
	connect(tcpSocket, &QTcpSocket::connected, this, [=]
		{
			m_ui->textEdit->append("ClientSuccess");
		});


	//服务端
	m_ui->textEdit_2->setReadOnly(true);
	tcpServer = new QTcpServer(this);
	tcpServer->hasPendingConnections();
	if (tcpServer->listen(QHostAddress::LocalHost, 6666))
	{
		connect(tcpServer, &QTcpServer::newConnection, this, [=]
			{
				m_ui->textEdit_2->append("ServerSuccess");
				QTcpSocket* socket = tcpServer->nextPendingConnection();
				connect(socket, &QTcpSocket::readyRead, this, [=]
					{
						QString recv_text = QString::fromUtf8(socket->readAll());
						m_ui->textEdit_2->append(recv_text);
					});
			});
	}

	//—————————你好文件————————//
	connect(m_ui->pushButton_hello, &QPushButton::clicked, this, [=]
		{
			QString q_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
			std::string filename = q_dir.toLocal8Bit().toStdString() + "\\" + "hello" + ".txt";
			std::ofstream lout(filename);
			std::fstream file(filename, std::ios::out);//清空
			for (int i = 0; i < 500; i++)
			{
				std::fstream f;
				f.open(filename, std::ios_base::out | std::ios_base::app);
				f << "你好，“文件”" << std::endl;
				f.close();
			}
			m_ui->label->setText(QStringLiteral("hello文件添加成功"));
		});

	//—————————数据库增删排序————————//
	// 添加水平表头标签
	QStringList horizontalHeaderLabels;
	horizontalHeaderLabels << "index" << "1" << "2" << "3";
	QStandardItemModel* header_model = new QStandardItemModel;
	header_model->setHorizontalHeaderLabels(horizontalHeaderLabels);
	// 将模型与视图关联
	m_ui->tableView->setModel(header_model);
	// 隐藏表头
	m_ui->tableView->verticalHeader()->setVisible(false);
	// 自适应行高和列宽
	m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


	// 创建一个数据库连接
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("db/mytestdb.sqlite");
	db.setConnectOptions("QSQLITE_OPEN_URI;QSQLITE_ENABLE_SHARED_CACHE=1;UTF8=1"); // 设置连接选项

	// 打开数据库
	if (db.open())
	{
		m_ui->label->setText(QStringLiteral("数据库链接成功"));
		connect(m_ui->pushButton_insert, &QPushButton::clicked, this, [=]
			{

				// 执行创建表的操作
				QSqlQuery query;
				QString tableName = "databast_table_1";
				if (db.tables().contains(tableName))
				{
					if (query.exec("DROP TABLE " + tableName))
					{
						m_ui->label->setText(QStringLiteral("已删除存在的表"));
					}
					else
					{
						m_ui->label->setText(QStringLiteral("删除表失败"));
					}
				}

				QString createTableQuery = "CREATE TABLE " + tableName + " (No INTEGER, Random1 INTEGER, Random2 INTEGER, Random3 INTEGER)";
				if (query.exec(createTableQuery)) {
					m_ui->label->setText(QStringLiteral("数据库表1添加成功"));

					// 插入100条数据
					srand(QTime::currentTime().msec()); // 初始化随机数种子
					for (int i = 0; i < 1000; i++) {
						int random1 = QRandomGenerator::global()->bounded(3001); // 生成0到3000的随机数
						int random2 = QRandomGenerator::global()->bounded(3001);
						int random3 = QRandomGenerator::global()->bounded(3001);

						QString insertQuery = QString("INSERT INTO %1 (No, Random1, Random2, Random3) VALUES (%2, %3, %4, %5)")
							.arg(tableName).arg(i + 1).arg(random1).arg(random2).arg(random3);

						if (!query.exec(insertQuery)) {
							m_ui->label->setText(QStringLiteral("插入数据失败"));
							break;
						}
						myWidget->updateProgress();
						m_ui->progressBar->setValue((i + 1) / 10);//设置进度条
						this->update();
					}
					m_ui->label->setText(QStringLiteral("插入数据成功"));
				}
				else {
					m_ui->label->setText(QStringLiteral("数据库表1添加失败"));
				}
			});
		//sort
		connect(m_ui->pushButton_sort, &QPushButton::clicked, this, [=]
			{
				// 执行遍历和排序的操作
				QSqlQuery query;
				QString tableName = "databast_table_1";

				if (db.tables().contains(tableName))
				{
					QList<QList<QVariant>> rows; // 用于存储要排序的行的列表

					QString selectQuery = "SELECT * FROM " + tableName;
					if (query.exec(selectQuery))
					{
						while (query.next())
						{
							QList<QVariant> row;
							for (int i = 0; i < 4; ++i)
							{
								row.append(query.value(i));
							}
							rows.append(row);
						}
						std::sort(rows.begin(), rows.end(), [](const QList<QVariant>& a, const QList<QVariant>& b)
							{
								return a[2].toInt() > b[2].toInt();
							});
						QString clearQuery = "DELETE FROM " + tableName;
						if (query.exec(clearQuery))
						{
							// 重新插入
							int i = 0;
							for (const QList<QVariant>& row : rows)
							{
								QString insertQuery = QString("INSERT INTO %1 (No, Random1, Random2, Random3) VALUES (%2, %3, %4, %5)")
									.arg(tableName).arg(row[0].toInt()).arg(row[1].toInt())
									.arg(row[2].toInt()).arg(row[3].toInt());

								if (!query.exec(insertQuery)) {
									m_ui->label->setText(QStringLiteral("插入数据失败"));
									break;
								}
								myWidget->updateProgress();
								m_ui->progressBar->setValue((i + 1) / 10);//设置进度条
								this->update();
								i++;
							}
							m_ui->label->setText(QStringLiteral("重新排序成功"));
						}
						else
						{
							m_ui->label->setText(QStringLiteral("清空表数据失败"));
						}
					}
				}
			});
		//delete
		connect(m_ui->pushButton_delete2, &QPushButton::clicked, this, [=]
			{
				QSqlQuery query;
				QString tableName = "databast_table_1";

				if (db.tables().contains(tableName))
				{
					// 找到奇数行并打印内容
					QString selectQuery = "SELECT * FROM " + tableName + " WHERE Random3 % 2 = 1";
					if (query.exec(selectQuery))
					{
						while (query.next())
						{
							QList<QStandardItem*> newRowItems;
							QStandardItem* item1 = new QStandardItem(query.value(0).toString());
							QStandardItem* item2 = new QStandardItem(query.value(1).toString());
							QStandardItem* item3 = new QStandardItem(query.value(2).toString());
							QStandardItem* item4 = new QStandardItem(query.value(3).toString());
							newRowItems << item1 << item2 << item3 << item4;

							// 插入新行到模型中
							header_model->insertRow(header_model->rowCount(), newRowItems);
						}
					}

					// 删除偶数行
					QString deleteQuery = "DELETE FROM " + tableName + " WHERE Random3 % 2 = 0";
					query.exec(deleteQuery);
				}
			});
	}
	else
	{
		m_ui->label->setText(QStringLiteral("数据库链接失败"));
	}
}

int QtWidgetsApplication::ran()
{
	// 创建一个随机数
	std::random_device rd;
	std::mt19937 gen(rd());
	// 定义随机数分布范围
	std::uniform_int_distribution<int> distribution(1, 50);
	// 生成随机数
	int random_number = distribution(gen);
	return random_number;
}

void QtWidgetsApplication::traverseAndProcessNode(QStandardItem* item, bool skipFirstNode)
{
	if (!item)
	{
		return;
	}

	if (!skipFirstNode || item->parent() != nullptr)
	{
		int newValue = item->text().toInt(); // 获取节点内容并转换为整数

		if (newValue <= 25)
		{
			newValue = 0; // 如果小于等于25，将值设为0
			item->setText(QString::number(newValue)); // 更新节点内容
		}
	}

	int rowCount = item->rowCount();
	for (int i = 0; i < rowCount; ++i)
	{
		QStandardItem* childItem = item->child(i);
		traverseAndProcessNode(childItem, false); // 跳过第一个节点
	}
}

void QtWidgetsApplication::deleteEvenRows(QStandardItem* parentItem)
{
	if (!parentItem)
	{
		return;
	}

	for (int row = parentItem->rowCount() - 1; row >= 0; --row)
	{
		if (row % 2 != 0) // 如果是偶数行
		{
			QStandardItem* itemToRemove = parentItem->takeRow(row).at(0);
			delete itemToRemove; // 释放内存
		}
	}

	int rowCount = parentItem->rowCount();
	for (int i = 0; i < rowCount; ++i)
	{
		QStandardItem* childItem = parentItem->child(i);
		deleteEvenRows(childItem);
	}
}