
/*
 *
 *
 *
 *
 *
 *
 */

#ifndef _AbstractItemView_h
#define _AbstractItemView_h

#include <QWidget>
#include <QDialog>

#include "ui_AbstractItemView.h"



class AbstractItemView : public QDialog, public Ui_AbstractItemView
{
	public:
		explicit AbstractItemView(QWidget* parent = 0);

	protected slots:
		virtual void newClicked() = 0;
		virtual void editClicked() = 0;
		virtual void viewClicked() = 0;
		virtual void deleteClicked() = 0;
		virtual void printClicked() = 0;

	private:
		Q_OBJECT
};

#endif

