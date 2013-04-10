
/*
 *
 *
 *
 *
 *
 */


#ifndef _MainWindow_h
#define _MainWindow_h

#include <QWidget>
#include <QString>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QWorkspace>
#include <QImage>
#include <QPalette>
#include <QBrush>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QLatin1Char>
#include <QProgressDialog>

#include "Application.h"

#include "MateriaPrimaView.h"
#include "MaterialView.h"
#include "EspecieView.h"
#include "PecaView.h"

#include "Orcamento.h"
#include "Peca.h"
#include "Programa.h"
#include "PictureView.h"



class MainWindow : public QMainWindow
{
	public:
		MainWindow(QWidget* parent = 0);
		
	protected slots:
		void slotVacuum();

		void slotMateriaPrima();
		void slotEspecie();
		void slotMaterial();

	private:
		Q_OBJECT
		
		QWorkspace* workspace;

		QMenu* fileMenu;
		QToolBar* fileToolBar;
		QAction* exitAction;
		QAction* optionAction;
		QAction* vacuumAction;
		QMenu* databaseSubMenu;

		QMenu* editMenu;
		QToolBar* editToolBar;
		QAction* cutAction;
		QAction* copyAction;
		QAction* pasteAction;

		QMenu* estoqueMenu;
		QAction* materiaPrimaAction;
		QAction* especieAction;
		QAction* materialAction;
		QToolBar* estoqueToolBar;
		QMenu* helpMenu;
		QAction* aboutAction;
};

#endif

