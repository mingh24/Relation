#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qstack.h>
#include "ui_mainWindow.h"
#include "relation.h"

#define MAXNUM 10
#define X1 120		// Left abscissa of the pixmap
#define X2 650		// Right abscissa of the pixmap	

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	void reinitPixmap();
	void displayOriginalMatrix(const Relation r);
	void showMessageBox(const QString title, const QString text);
	void paintEvent(QPaintEvent* event);
	void drawOriginalNodes(const int dimension);
	void drawResultNodes(const int dimension);
	void drawHasseNodes(const int dimension, const int* result);
	void drawTopoNodes(const int dimension, const int* result);
	void drawLines(const int dimension, const int* result);

public slots:
	void on_equivClosureBtn_clicked();
	void on_equivClassesBtn_clicked();
	void on_hasseBtn_clicked();
	void on_topoBtn_clicked();

public:
	MainWindow(QWidget* parent = Q_NULLPTR);

private:
	Ui::MainWindowClass ui;
	string filePath;
	QString fileName;
	QPixmap pixmap;
	QFont font;
	QPen linePen;
	QBrush circularBrush;
	QPoint positions[2 * MAXNUM];
};
