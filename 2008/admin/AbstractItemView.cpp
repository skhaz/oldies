
/*
 *
 *
 *
 *
 *
 *
 */

#include "AbstractItemView.h"



AbstractItemView::AbstractItemView(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	connect(newButton, SIGNAL(clicked()), SLOT(newClicked()));
	connect(editButton, SIGNAL(clicked()), SLOT(editClicked()));
	connect(viewButton, SIGNAL(clicked()), SLOT(viewClicked()));
	connect(deleteButton, SIGNAL(clicked()), SLOT(deleteClicked()));
	connect(printButton, SIGNAL(clicked()), SLOT(printClicked()));
	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
	connect(tableView, SIGNAL(doubleClicked(QModelIndex)), SLOT(viewClicked()));
}

