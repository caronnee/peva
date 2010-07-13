#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <vector>
#include <QtGui/QMainWindow>
#include "ui_controlpanel.h"
#include "ui_instructions.h"

class controlPanel : public QMainWindow
{
	Q_OBJECT

		public slots:
			void mySet();
public:

	controlPanel(QWidget *parent = 0, Qt::WFlags flags = 0);
	~controlPanel();

private:
	QMainWindow * insWin;
	Ui::controlPanelClass ui;
	Ui::Instruction ins;
};

#endif // CONTROLPANEL_H
