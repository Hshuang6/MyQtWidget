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

    // 绘制第一个圆环
    painter.setBrush(Qt::red); // 设置圆环颜色为蓝色
    painter.drawEllipse(QPointF(centerX - 110, centerY), ringRadius, ringRadius);

    // 绘制第二个圆环
    painter.setBrush(Qt::green); // 设置圆环颜色为绿色
    painter.drawEllipse(QPointF(centerX, centerY), ringRadius, ringRadius);

    // 绘制第三个圆环
    painter.setBrush(Qt::yellow); // 设置圆环颜色为黄色
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