#pragma once

#include <QDialog>
#include "ui_dialog.h"

class Dialog : public QDialog
{
	Q_OBJECT

public:
	Dialog(QWidget *parent = nullptr);
	~Dialog();

private:
	Ui::DialogClass ui;
};
