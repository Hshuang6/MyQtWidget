#include "MyWidget.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>

MyWidget::MyWidget(QWidget* parent) 
    : QWidget(parent),
    progress(0)
{
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    int centerX = width() / 2;
    int centerY = height() / 2;
    int ringRadius = 50;

    // ���Ƶ�һ��Բ��
    painter.setBrush(Qt::red); // ����Բ����ɫΪ��ɫ
    painter.drawEllipse(QPointF(centerX - 110, centerY), ringRadius, ringRadius);

    // ���Ƶڶ���Բ��
    painter.setBrush(Qt::green); // ����Բ����ɫΪ��ɫ
    painter.drawEllipse(QPointF(centerX, centerY), ringRadius, ringRadius);

    // ���Ƶ�����Բ��
    painter.setBrush(Qt::yellow); // ����Բ����ɫΪ��ɫ
    painter.drawEllipse(QPointF(centerX + 110, centerY), ringRadius, ringRadius);

    int m_width = width() / 2;
    int m_height = 20;
    painter.setBrush(Qt::lightGray);
    painter.drawRect(centerX / 3, centerY + 100, m_width * 4 / 3, m_height);
    int progressBarWidth = static_cast<int>(m_width * 4 / 3 * (static_cast<double>(progress) / 1000.0));
    painter.setBrush(QColor(6, 176, 37));
    painter.drawRect(centerX / 3, centerY+100, progressBarWidth, m_height);
    painter.setPen(Qt::black);
    painter.drawText(QRect(centerX / 3 + m_width * 4 / 3+10, centerY + 100, 20, 20),
        Qt::AlignCenter, QString::number(progress/10) + "%");
}

void MyWidget::updateProgress()
{
    progress += 1; 
    if (progress > 1000)
        progress = 0;

    update(); 
}