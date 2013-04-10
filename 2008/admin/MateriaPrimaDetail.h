
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _MateriaPrimaDetail_h
#define _MateriaPrimaDetail_h

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QDoubleValidator>

#include <QSqlQuery>
#include <QSqlError>

#include "Global.h"

#include "AbstractItemView.h"
#include "ui_MateriaPrimaDetail.h"



class MateriaPrimaDetail : public QDialog, private Ui_MateriaPrimaDetail
{
	public:
		MateriaPrimaDetail(QWidget* parent = 0);

		void setParam(const ParameterList& param);

	protected:
		bool validate(QLineEdit* lineEdit);

	protected slots:

		void newClicked();
		void editClicked();
		void formulaIndexChanged(int index);

	signals:
		void dataChanged();

	private:
		Q_OBJECT

		enum
		{
			TIPO_REDONDO = 0,
			TIPO_QUADRADO,
			TIPO_SEXTAVADO
		};

		int tipo;
		QSqlQuery query;
};

#endif

