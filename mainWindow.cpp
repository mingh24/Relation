#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);
}

void MainWindow::displayOriginalMatrix(Relation r) {
	ui.originalTextBrowser->insertPlainText("The original adjacency matrix in " + fileName + " is: \n");
	for (int row = 0; row < r.getDimension(); ++row) {
		for (int column = 0; column < r.getDimension(); ++column)
			ui.originalTextBrowser->insertPlainText(QString::number(r(row, column)) + "   ");
		ui.originalTextBrowser->insertPlainText("\n");
	}
}

void MainWindow::showMessageBox(QString title, QString text) {
	QMessageBox msg(this);
	msg.setWindowTitle(title);
	msg.setText(text);
	msg.setIcon(QMessageBox::Warning);
	msg.setStandardButtons(QMessageBox::Ok);
	msg.exec();
}

void MainWindow::paintEvent(QPaintEvent * event) {
	QPainter Painter(this);
	pixmap.fill(Qt::blue);
	Painter.drawPixmap(0, 0, width(), height(), pixmap);
}

void MainWindow::on_equivClosureBtn_clicked() {
	ui.originalTextBrowser->setPlainText("");
	ui.newTextBrowser->setPlainText("");

	QString temp;
	if (NULL == (temp = QFileDialog::getOpenFileName(this, "Choose the adjacency matrix file", QDir::currentPath(), "txt files(*.txt)")))
		return;
	filePath = temp.toLocal8Bit();
	fileName = QFileInfo(temp).fileName();

	Relation r(filePath);
	displayOriginalMatrix(r);

	Relation rr = r.getEquivalenceClosure();
	ui.newTextBrowser->insertPlainText("The obtained adjacency matrix is: \n");
	for (int row = 0; row < rr.getDimension(); ++row) {
		for (int column = 0; column < rr.getDimension(); ++column)
			ui.newTextBrowser->insertPlainText(QString::number(rr(row, column)) + "   ");
		ui.newTextBrowser->insertPlainText("\n");
	}

	// TODO »­Í¼
}

void MainWindow::on_equivClassesBtn_clicked() {
	ui.originalTextBrowser->setPlainText("");
	ui.newTextBrowser->setPlainText("");

	QString temp;
	if (NULL == (temp = QFileDialog::getOpenFileName(this, "Choose the adjacency matrix file", QDir::currentPath(), "txt files(*.txt)")))
		return;
	filePath = temp.toLocal8Bit();
	fileName = QFileInfo(temp).fileName();

	Relation r(filePath);
	displayOriginalMatrix(r);

	if (r.isEquivalence()) {
		Relation rr = r.getEquivalenceClosure();
		int* result = rr.getEquivalenceClasses();

		ui.newTextBrowser->insertPlainText("The equivalence classes are: \n");

		int temp = 0;
		for (int i = 0; i < rr.getDimension(); ++i) {
			if (temp == rr.getDimension())
				break;
			ui.newTextBrowser->insertPlainText("{  ");
			for (int j = 0; j < rr.getDimension(); ++j) {
				if (result[j] == i) {
					ui.newTextBrowser->insertPlainText("Mod" + QString::number(j + 1) + "  ");
					++temp;
				}
			}
			ui.newTextBrowser->insertPlainText("}\n");
		}

		// TODO »­Í¼
	}
	else
		showMessageBox("Warning", "The relation is not an equivalence relation!");
}

void MainWindow::on_hasseBtn_clicked() {
	ui.originalTextBrowser->setPlainText("");
	ui.newTextBrowser->setPlainText("");

	QString temp;
	if (NULL == (temp = QFileDialog::getOpenFileName(this, "Choose the adjacency matrix file", QDir::currentPath(), "txt files(*.txt)")))
		return;
	filePath = temp.toLocal8Bit();
	fileName = QFileInfo(temp).fileName();

	Relation r(filePath);
	displayOriginalMatrix(r);

	if (r.isPartial()) {
		// TODO »­Í¼
	}
	else
		showMessageBox("Warning", "The relation is not a partial ordering relation");
}

void MainWindow::on_topoBtn_clicked() {
	ui.originalTextBrowser->setPlainText("");
	ui.newTextBrowser->setPlainText("");

	QString temp;
	if (NULL == (temp = QFileDialog::getOpenFileName(this, "Choose the adjacency matrix file", QDir::currentPath(), "txt files(*.txt)")))
		return;
	filePath = temp.toLocal8Bit();
	fileName = QFileInfo(temp).fileName();

	Relation r(filePath);
	displayOriginalMatrix(r);

	int* result = r.topologicallySorting();
	if (nullptr != result) {
		ui.newTextBrowser->insertPlainText("The topologically sorting result is: \n");
		for (int i = 0; i < r.getDimension() - 1; ++i)
			ui.newTextBrowser->insertPlainText("Mod" + QString::number(result[i] + 1) + "  ->  ");
		ui.newTextBrowser->insertPlainText("Mod" + QString::number(result[r.getDimension() - 1] + 1));

		// TODO »­Í¼
	}
	else
		showMessageBox("Warning", "There exists cycle in the graph!");
}
