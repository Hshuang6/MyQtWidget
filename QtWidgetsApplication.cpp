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

	setWindowTitle(QString::fromLocal8Bit("�������-������-8.26"));
}

QtWidgetsApplication::~QtWidgetsApplication()
{
}

void QtWidgetsApplication::IniUI()
{
	//��������������������ʼ������������������������//
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

	//����������������������ҳ�桪��������������//
	connect(m_ui->action, &QAction::triggered, this, [=]
		{
			Dialog* newDialog = new Dialog(this);
			newDialog->show();
		});

	//������������������״̬����ʼ������������������//
	QLabel* leftLabel;
	QLabel* rightLabel1;
	QLabel* rightLabel2;
	// ���������ı�ǩ
	leftLabel = new QLabel("lift1");
	m_ui->statusBar->addWidget(leftLabel);
	// �����Ҷ���ı�ǩ
	rightLabel1 = new QLabel("right1");
	m_ui->statusBar->addPermanentWidget(rightLabel1);
	rightLabel2 = new QLabel("right2");
	m_ui->statusBar->addPermanentWidget(rightLabel2);

	//����������������������ʼ������������������//
	m_ui->tableWidget->setRowCount(8);
	m_ui->tableWidget->setColumnCount(5);
	//���ñ�ͷ
	QStringList headerLabels;
	headerLabels << "1" << "2" << "3" << "4" << "5";
	m_ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
	// ���������
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 5; ++col)
		{
			QTableWidgetItem* item = new QTableWidgetItem(QString("%1,%2").arg(row + 1).arg(col + 1));
			item->setTextAlignment(Qt::AlignCenter);
			m_ui->tableWidget->setItem(row, col, item);
		}
	}
	// ����Ӧ�иߺ��п�
	m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(m_ui->pushButton, &QPushButton::clicked, this, [=]
		{
			static bool sorted = false;
			sorted = !sorted;
			if (sorted)
			{
				m_ui->tableWidget->sortItems(0, Qt::DescendingOrder);
				m_ui->pushButton->setText(QStringLiteral("����"));
			}
			else
			{
				m_ui->tableWidget->sortItems(0, Qt::AscendingOrder);
				m_ui->pushButton->setText(QStringLiteral("����"));
			}
		});

	//����������������������ͼ��ʼ������������������//
	QStandardItemModel* model = new QStandardItemModel(m_ui->treeView);
	model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("���"));


	// ������ݵ�ģ��
	for (int row = 0; row < 8; ++row)
	{
		//һ���ڵ�
		QList<QStandardItem*> items1;
		QStandardItem* item1 = new QStandardItem(QString::number(row + 1));
		items1.append(item1);
		model->appendRow(items1);
		for (int col = 0; col < 5; ++col)
		{
			//�����ڵ�
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
			// �����ӽڵ�����
			QModelIndex rootIndex = model->indexFromItem(model->invisibleRootItem());
			for (int row = 0; row < model->rowCount(rootIndex); ++row) {
				QModelIndex itemIndex = model->index(row, 0, rootIndex);
				traverseAndProcessNode(model->itemFromIndex(itemIndex));
			}
		});
	connect(m_ui->pushButton_delete, &QPushButton::clicked, this, [=]
		{
			// ɾ���ӽڵ��е�ż����
			QModelIndex rootIndex = model->indexFromItem(model->invisibleRootItem());
			for (int row = 0; row < model->rowCount(rootIndex); ++row) {
				QModelIndex itemIndex = model->index(row, 0, rootIndex);
				QStandardItem* item = model->itemFromIndex(itemIndex);
				deleteEvenRows(item);
			}
		});

	MyWidget* myWidget = new MyWidget(this);
	m_ui->verticalLayout->addWidget(myWidget);

	//������������������TCP��ʼ������������������//
	//�ͻ���
	m_ui->textEdit->setReadOnly(true);
	tcpSocket = new QTcpSocket(this);
	timer = new QTimer(this);
	tcpSocket->connectToHost(QHostAddress::LocalHost, 6666); // �˿�
	connect(m_ui->pushButton_start, &QPushButton::clicked, this, [=]
		{
			static bool sorted = false;
			sorted = !sorted;
			if (sorted)
			{
				m_ui->pushButton_start->setText(QStringLiteral("ֹͣ"));
				timer->start(500); // ÿ500ms����һ��
			}
			else
			{
				m_ui->pushButton_start->setText(QStringLiteral("��ʼ"));
				timer->stop();
			}

		});
	connect(timer, &QTimer::timeout, this, [=]
		{
			QString textToSend = "Sent: " + QString::number(ran());
			QByteArray send_data = textToSend.toUtf8();
			tcpSocket->write(send_data);
			tcpSocket->flush();
			// ��ʾ�������ݣ�������

			m_ui->textEdit->append(textToSend);
		});
	connect(tcpSocket, &QTcpSocket::connected, this, [=]
		{
			m_ui->textEdit->append("ClientSuccess");
		});


	//�����
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

	//����������������������ļ�����������������//
	connect(m_ui->pushButton_hello, &QPushButton::clicked, this, [=]
		{
			QString q_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
			std::string filename = q_dir.toLocal8Bit().toStdString() + "\\" + "hello" + ".txt";
			std::ofstream lout(filename);
			std::fstream file(filename, std::ios::out);//���
			for (int i = 0; i < 500; i++)
			{
				std::fstream f;
				f.open(filename, std::ios_base::out | std::ios_base::app);
				f << "��ã����ļ���" << std::endl;
				f.close();
			}
			m_ui->label->setText(QStringLiteral("hello�ļ���ӳɹ�"));
		});

	//���������������������ݿ���ɾ���򡪡�������������//
	// ���ˮƽ��ͷ��ǩ
	QStringList horizontalHeaderLabels;
	horizontalHeaderLabels << "index" << "1" << "2" << "3";
	QStandardItemModel* header_model = new QStandardItemModel;
	header_model->setHorizontalHeaderLabels(horizontalHeaderLabels);
	// ��ģ������ͼ����
	m_ui->tableView->setModel(header_model);
	// ���ر�ͷ
	m_ui->tableView->verticalHeader()->setVisible(false);
	// ����Ӧ�иߺ��п�
	m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


	// ����һ�����ݿ�����
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("db/mytestdb.sqlite");
	db.setConnectOptions("QSQLITE_OPEN_URI;QSQLITE_ENABLE_SHARED_CACHE=1;UTF8=1"); // ��������ѡ��

	// �����ݿ�
	if (db.open())
	{
		m_ui->label->setText(QStringLiteral("���ݿ����ӳɹ�"));
		connect(m_ui->pushButton_insert, &QPushButton::clicked, this, [=]
			{

				// ִ�д�����Ĳ���
				QSqlQuery query;
				QString tableName = "databast_table_1";
				if (db.tables().contains(tableName))
				{
					if (query.exec("DROP TABLE " + tableName))
					{
						m_ui->label->setText(QStringLiteral("��ɾ�����ڵı�"));
					}
					else
					{
						m_ui->label->setText(QStringLiteral("ɾ����ʧ��"));
					}
				}

				QString createTableQuery = "CREATE TABLE " + tableName + " (No INTEGER, Random1 INTEGER, Random2 INTEGER, Random3 INTEGER)";
				if (query.exec(createTableQuery)) {
					m_ui->label->setText(QStringLiteral("���ݿ��1��ӳɹ�"));

					// ����100������
					srand(QTime::currentTime().msec()); // ��ʼ�����������
					for (int i = 0; i < 1000; i++) {
						int random1 = QRandomGenerator::global()->bounded(3001); // ����0��3000�������
						int random2 = QRandomGenerator::global()->bounded(3001);
						int random3 = QRandomGenerator::global()->bounded(3001);

						QString insertQuery = QString("INSERT INTO %1 (No, Random1, Random2, Random3) VALUES (%2, %3, %4, %5)")
							.arg(tableName).arg(i + 1).arg(random1).arg(random2).arg(random3);

						if (!query.exec(insertQuery)) {
							m_ui->label->setText(QStringLiteral("��������ʧ��"));
							break;
						}
						myWidget->updateProgress();
						m_ui->progressBar->setValue((i + 1) / 10);//���ý�����
						this->update();
					}
					m_ui->label->setText(QStringLiteral("�������ݳɹ�"));
				}
				else {
					m_ui->label->setText(QStringLiteral("���ݿ��1���ʧ��"));
				}
			});
		//sort
		connect(m_ui->pushButton_sort, &QPushButton::clicked, this, [=]
			{
				// ִ�б���������Ĳ���
				QSqlQuery query;
				QString tableName = "databast_table_1";

				if (db.tables().contains(tableName))
				{
					QList<QList<QVariant>> rows; // ���ڴ洢Ҫ������е��б�

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
							// ���²���
							int i = 0;
							for (const QList<QVariant>& row : rows)
							{
								QString insertQuery = QString("INSERT INTO %1 (No, Random1, Random2, Random3) VALUES (%2, %3, %4, %5)")
									.arg(tableName).arg(row[0].toInt()).arg(row[1].toInt())
									.arg(row[2].toInt()).arg(row[3].toInt());

								if (!query.exec(insertQuery)) {
									m_ui->label->setText(QStringLiteral("��������ʧ��"));
									break;
								}
								myWidget->updateProgress();
								m_ui->progressBar->setValue((i + 1) / 10);//���ý�����
								this->update();
								i++;
							}
							m_ui->label->setText(QStringLiteral("��������ɹ�"));
						}
						else
						{
							m_ui->label->setText(QStringLiteral("��ձ�����ʧ��"));
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
					// �ҵ������в���ӡ����
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

							// �������е�ģ����
							header_model->insertRow(header_model->rowCount(), newRowItems);
						}
					}

					// ɾ��ż����
					QString deleteQuery = "DELETE FROM " + tableName + " WHERE Random3 % 2 = 0";
					query.exec(deleteQuery);
				}
			});
	}
	else
	{
		m_ui->label->setText(QStringLiteral("���ݿ�����ʧ��"));
	}
}

int QtWidgetsApplication::ran()
{
	// ����һ�������
	std::random_device rd;
	std::mt19937 gen(rd());
	// ����������ֲ���Χ
	std::uniform_int_distribution<int> distribution(1, 50);
	// ���������
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
		int newValue = item->text().toInt(); // ��ȡ�ڵ����ݲ�ת��Ϊ����

		if (newValue <= 25)
		{
			newValue = 0; // ���С�ڵ���25����ֵ��Ϊ0
			item->setText(QString::number(newValue)); // ���½ڵ�����
		}
	}

	int rowCount = item->rowCount();
	for (int i = 0; i < rowCount; ++i)
	{
		QStandardItem* childItem = item->child(i);
		traverseAndProcessNode(childItem, false); // ������һ���ڵ�
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
		if (row % 2 != 0) // �����ż����
		{
			QStandardItem* itemToRemove = parentItem->takeRow(row).at(0);
			delete itemToRemove; // �ͷ��ڴ�
		}
	}

	int rowCount = parentItem->rowCount();
	for (int i = 0; i < rowCount; ++i)
	{
		QStandardItem* childItem = parentItem->child(i);
		deleteEvenRows(childItem);
	}
}