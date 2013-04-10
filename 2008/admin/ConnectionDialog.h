
/*
 *
 *
 *
 *
 *
 */

#ifndef _ConnectionDialog_h
#define _ConnectionDialog_h

#include <QWidget>
#include <QDialog>
#include <QStringList>
#include <QSqlDatabase>

#include "ui_ConnectionDialog.h"



class ConnectionDialog : public QDialog, private Ui_ConnectionDialog 
{
	public:
		ConnectionDialog(QWidget* parent = 0);

	private:
		Q_OBJECT
};

#endif

