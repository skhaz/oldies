
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _Peca_h
#define _Peca_h

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>

#include "Global.h"
#include "PictureView.h"
#include "MateriaPrima.h"
#include "Programa.h"
#include "ui_Peca.h"



class Peca : public QDialog, private Ui_Peca
{
	public:
		Peca(QWidget* parent = 0);

	signals:
		void dataChanged();

	public slots:
		void setParam(const ParameterList& param);

	protected slots:
		void submitClicked();

		void addMaterialClicked();
		void removeMaterialClicked();
		void addDesenhoClicked();
		void removeDesenhoClicked();
		void addProgramaClicked();
		void removeProgramaClicked();

		void newMaterialClicked();

		void materialViewClicked();
		void desenhoViewClicked();
		void programaViewClicked();

		void populate();

	private:
		Q_OBJECT

		QSqlQuery query;

		QSqlQueryModel* materiaisModel;
		QSqlQueryModel* programasModel;
		QSqlQueryModel* desenhosModel;

		int cod_peca;
};

#endif

