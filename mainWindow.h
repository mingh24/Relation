#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include "ui_mainWindow.h"
#include "relation.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	string filePath;
	QString fileName;
	void displayOriginalMatrix(Relation r);
	void showMessageBox(QString title, QString text);
	void paintEvent(QPaintEvent* event);

public slots:
	void on_equivClosureBtn_clicked();
	void on_equivClassesBtn_clicked();
	void on_hasseBtn_clicked();
	void on_topoBtn_clicked();

public:
	MainWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
	QPixmap pixmap;
};
