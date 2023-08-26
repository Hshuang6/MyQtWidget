#pragma once

#include <QObject>
#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget* parent = nullptr);

    void updateProgress();

protected:
    void paintEvent(QPaintEvent* event) override;
    int progress;

};