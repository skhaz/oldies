
/*
 *
 *
 *
 *
 *
 *
 */

#include "EspecieView.h"



EspecieView::EspecieView(QWidget* parent)
: AbstractItemView(parent)
, model(new QSqlTableModel(this))
{
	setWindowTitle(QString::fromUtf8("Espécie"));

	filterEdit->hide();

	model->setTable("materialespecie");
	//model->setQuery("select * from materialespecie");

	tableView->setModel(model);

	model->setHeaderData(0, Qt::Horizontal, QString::fromUtf8("Cod"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromUtf8("Espécie"));

	tableView->setColumnWidth(0, 50);
	tableView->setColumnWidth(1, 500);

	if (!model->select())
	{
		QMessageBox::warning(this, "Admin",
			QString::fromUtf8("Erro ao executar a requisição\n%1").arg(model->lastError().text()) );
	}

	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
}

void EspecieView::newClicked()
{
	Especie* detail = new Especie(this);
	connect(detail, SIGNAL(dataChanged()), SLOT(select()));

	ParameterList param;
	param["mode"] = "new";

	detail->setParam(param);
	detail->show();
}

void EspecieView::editClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Especie* detail = new Especie(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_materialespecie").toString();
		param["mode"] = "edit";

		detail->setParam(param);
		detail->show();
	}
}

void EspecieView::viewClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Especie* detail = new Especie(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_materialespecie").toString();
		param["mode"] = "edit";

		detail->setParam(param);
		detail->show();
	}
}

void EspecieView::deleteClicked()
{
	if (tableView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = model->record(tableView->currentIndex().row());
	int cod = record.value("cod_materialespecie").toInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			QString::fromUtf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome), QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QString detailedText;

		QSqlQuery sql;
		sql.prepare("delete from materialespecie where cod_materialespecie = :cod");
		sql.bindValue(":cod", cod);

		if (!sql.exec())
		{
			QSqlQuery query1;
			query1.prepare("select nome from materiaprima where cod_materialespecie = :cod");
			query1.bindValue(":cod", cod);

			if (query1.exec())
			{
				while (query1.next()) {
					detailedText.append(query1.value(query1.record().indexOf("nome")).toString());
					detailedText.append("\n");
				}
			}

			QSqlQuery query2;
			query2.prepare("delete from materiaprima where cod_materialespecie = :cod");
			query2.bindValue(":cod", cod);

			QMessageBox messageBox;
			messageBox.setWindowTitle("Admin");
			messageBox.setText(QString::fromUtf8(
					"Existe alguma matéria prima sendo referenciada por este material (veja em detalhes)\n"
					"tentar uma exclusão em cadeia forçada?"
				));
			messageBox.setDetailedText(detailedText);
			messageBox.setIcon(QMessageBox::Critical);
			messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

			switch(messageBox.exec())
			{
				case QMessageBox::Yes:
						query2.exec();
						sql.exec();
					break;

				default:
					break;
			}
		}

		model->select();
	}

}

void EspecieView::printClicked()
{	
}

void EspecieView::closeClicked()
{
}

void EspecieView::select()
{
	model->select();
}

