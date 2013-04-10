
/*
 *
 *
 *
 *
 *
 */

#include "MainWindow.h"



MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
, workspace(new QWorkspace(this))
, fileMenu(0)
, fileToolBar(0)
, exitAction(0)
, optionAction(0)
, editMenu(0)
, editToolBar(0)
, cutAction(0)
, copyAction(0)
, pasteAction(0)
, helpMenu(0)
, aboutAction(0)
{
	setWindowTitle(Utf8("Adminstração"));
	statusBar();

	setCentralWidget(workspace);

	optionAction = new QAction(Utf8("Op&ções"), this);
	optionAction->setIcon(QIcon(":/media/icon/wrench_orange.png"));
	optionAction->setShortcut(tr("CTRL+SHIFT+O"));
	optionAction->setStatusTip(Utf8("Opções"));

	vacuumAction = new QAction(Utf8("Vacuum"), this);
	vacuumAction->setIcon(QIcon(":/media/icon/database_refresh.png"));
	vacuumAction->setStatusTip(Utf8("Vacuum"));
	connect(vacuumAction, SIGNAL(triggered()), SLOT(slotVacuum()));

	databaseSubMenu = new QMenu(this);
	databaseSubMenu->setTitle("Banco de Dados");
	databaseSubMenu->setIcon(QIcon(":/media/icon/database.png"));
	databaseSubMenu->addAction(vacuumAction);

	exitAction = new QAction("S&air", this);
	exitAction->setIcon(QIcon(":/media/icon/door_out.png"));
	exitAction->setShortcut(tr("CTRL+Q"));
	exitAction->setStatusTip("Sai do programa");
	connect(exitAction, SIGNAL(triggered()), SLOT(close()));

	QMenuBar* menu = menuBar();
	fileMenu = menu->addMenu("&Arquivo");
	fileMenu->addAction(optionAction);
	fileMenu->addMenu(databaseSubMenu);
	fileMenu->addAction(exitAction);

	fileToolBar = addToolBar("&Arquivo");
	fileToolBar->addAction(optionAction);
	fileToolBar->addAction(exitAction);

	cutAction = new QAction("Recor&tar", this);
	cutAction->setIcon(QIcon(":/media/icon/cut_red.png"));
	cutAction->setShortcut(tr("CTRL+X"));
	cutAction->setStatusTip("Recortar");

	copyAction = new QAction("C&opiar", this);
	copyAction->setIcon(QIcon(":/media/icon/page_copy.png"));
	copyAction->setShortcut(tr("CTRL+C"));
	copyAction->setStatusTip("Copiar");

	pasteAction = new QAction("Co&lar", this);
	pasteAction->setIcon(QIcon(":/media/icon/page_paste.png"));
	pasteAction->setShortcut(tr("CTRL+V"));
	pasteAction->setStatusTip("Colar");

	editMenu = menu->addMenu("E&ditar");
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	editToolBar = addToolBar("E&ditar");
	editToolBar->addAction(cutAction);
	editToolBar->addAction(copyAction);
	editToolBar->addAction(pasteAction);

	materiaPrimaAction = new QAction(Utf8("Máteria Prima"), this);
	materiaPrimaAction->setIcon(QIcon(":/media/icon/brick.png"));
	materiaPrimaAction->setStatusTip(Utf8("Cadastro e/ou consulta de máterias prima"));
	connect(materiaPrimaAction, SIGNAL(triggered()), SLOT(slotMateriaPrima()));

	especieAction = new QAction(Utf8("Espécie de Material"), this);
	especieAction->setIcon(QIcon());
	especieAction->setStatusTip(Utf8("Cadastro e/ou consulta de espécies de materias"));
	connect(especieAction, SIGNAL(triggered()), SLOT(slotEspecie()));

	materialAction = new QAction(Utf8("Material"), this);
	materialAction->setIcon(QIcon());
	materialAction->setStatusTip(Utf8("Cadastro e/ou consulta de material"));
	connect(materialAction, SIGNAL(triggered()), SLOT(slotMaterial()));


	estoqueMenu = menu->addMenu("Ca&dastro");
	estoqueMenu->addAction(materiaPrimaAction);
	estoqueMenu->addAction(especieAction);
	estoqueMenu->addAction(materialAction);

	estoqueToolBar = addToolBar("E&stoque");
	estoqueToolBar->addAction(materiaPrimaAction);

	aboutAction = new QAction("Sob&re", this);
	aboutAction->setIcon(QIcon(":/media/icon/help.png"));
	aboutAction->setShortcut(tr("CTRL+A"));
	aboutAction->setStatusTip("");

	helpMenu = menu->addMenu("A&juda");
	helpMenu->addAction(aboutAction);

/*
	Programa* p = new Programa(this);
	ParameterList param;
	param["mode"] = "edit";
	param["cod"] = "1";
	*/
//	p->setParam(param);
//	workspace->addWindow(p);
//	p->show();

	ParameterList param;
	param["mode"] = "edit";
	param["cod"] = "1";
/*
	Peca* c = new Peca(this);
	c->setParam(param);
	workspace->addWindow(c);
	c->show();
*/ 
	PecaView* p = new PecaView(this);
	workspace->addWindow(p);
	p->show();

	Orcamento* o = new Orcamento(this);
	workspace->addWindow(o);

	param["mode"] = "edit";
	param["cod"] = "1";
	o->setParam(param);
	o->show();
}

void MainWindow::slotVacuum()
{
	QProgressDialog progress("Executando o vacuum...", "Abortar", 0, 100, this);
	progress.setWindowModality(Qt::WindowModal);
	progress.show();
}

void MainWindow::slotMateriaPrima()
{
	MateriaPrimaView* materiaPrimaView = new MateriaPrimaView(this);
	workspace->addWindow(materiaPrimaView);
	materiaPrimaView->show();
}

void MainWindow::slotEspecie()
{
	EspecieView* especieView = new EspecieView(this);
	workspace->addWindow(especieView);
	especieView->show();
}

void MainWindow::slotMaterial()
{
	MaterialView* materialView = new MaterialView(this);
	workspace->addWindow(materialView);
	materialView->show();
}

