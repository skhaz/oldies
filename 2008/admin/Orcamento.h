
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Orcamento_h
#define _Orcamento_h

#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QString>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>

#include "Global.h"
#include "ui_Orcamento.h"



class Orcamento : public QDialog, private Ui_Orcamento
{
	public:
		Orcamento(QWidget* parent = 0);

	signals:
		void dataChanged();

	public slots:
		void setParam(const ParameterList& param);

	protected slots:
		void submitClicked();

	private:
		Q_OBJECT

		QSqlQuery query;
};

#endif

