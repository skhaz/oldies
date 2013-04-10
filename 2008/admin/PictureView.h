
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _PictureView_h
#define _PictureView_h

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QByteArray>
#include <QBuffer>

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

#include "ui_PictureView.h"
#include "Global.h"



class PictureView : public QDialog, private Ui_PictureView
{
	public:
		PictureView(QWidget* parent = 0);

	signals:
		void dataChanged();

	public slots:
		void setParam(const ParameterList& param);

	protected slots:
		void submitClicked();
		void importClicked();
		void exportClicked();

	private:
		Q_OBJECT

		QFile file;
		QSqlQuery query;
		QLabel* label;
};

#endif

