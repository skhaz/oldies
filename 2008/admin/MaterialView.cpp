
/*
 *
 *
 *
 *
 *
 *
 */

#include "MaterialView.h"


MaterialView::MaterialView(QWidget* parent)
: AbstractItemView(parent)
, model(new QSqlTableModel(this))
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(Utf8("Material"));

	filterEdit->hide();

	model->setTable("material");

	tableView->setModel(model);

	tableView->setColumnHidden(0, true);
	model->setHeaderData(1, Qt::Horizontal, Utf8("Nome"));
	model->setHeaderData(2, Qt::Horizontal, Utf8("Densidade"));
	tableView->setColumnWidth(1, 400);

	if (!model->select())
	{
		QMessageBox::warning(this, "Admin",
			Utf8("Erro ao executar a requisição\n%1").arg(model->lastError().text()));
	}

	connect(closeButton, SIGNAL(clicked()), SLOT(close()));
	connect(tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection&, QItemSelection&)),
		SIGNAL(selectionChanged(const QItemSelection&)));
}

void MaterialView::selectionChanged(const QItemSelection& index)
{
}

void MaterialView::newClicked()
{
	Material* detail = new Material(this);
	connect(detail, SIGNAL(dataChanged()), SLOT(select()));

	ParameterList param;
	param["mode"] = "new";

	detail->setParam(param);
	detail->show();
}

void MaterialView::editClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Material* detail = new Material(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_material").toString();
		param["mode"] = "edit";

		detail->setParam(param);
		detail->show();
	}
}

void MaterialView::viewClicked()
{
	if (tableView->currentIndex().row() >= 0)
	{
		QSqlRecord record = model->record(tableView->currentIndex().row());

		Material* detail = new Material(this);
		connect(detail, SIGNAL(dataChanged()), SLOT(select()));

		ParameterList param;
		param["cod"] = record.value("cod_material").toString();
		param["mode"] = "view";

		detail->setParam(param);
		detail->show();
	}
}

void MaterialView::deleteClicked()
{
	if (tableView->currentIndex().row() < 0)
	{
		return;
	}

	QSqlRecord record = model->record(tableView->currentIndex().row());
	uint cod = record.value("cod_material").toUInt();
	QString nome = record.value("nome").toString();

	QMessageBox messageBox(QMessageBox::Question, "Admin",
			Utf8("Confirma a exclusão do registro <b>%1</b>?").arg(nome), QMessageBox::Yes | QMessageBox::No, this);

	if (messageBox.exec() == QMessageBox::Yes)
	{
		QString detailedText;

		QSqlQuery sql;
		sql.prepare("delete from material where cod_material = :cod");
		sql.bindValue(":cod", cod);

		if (!sql.exec())
		{
			QSqlQuery query1;
			query1.prepare("select nome from materiaprima where cod_material = :cod");
			query1.bindValue(":cod", cod);
			if (query1.exec())
			{
				while (query1.next()) {
					detailedText.append(query1.value(query1.record().indexOf("nome")).toString());
					detailedText.append("\n");
				}
			}

			QSqlQuery query2;
			query2.prepare("delete from materiaprima where cod_material = :cod");
			query2.bindValue(":cod", cod);

			QMessageBox messageBox;
			messageBox.setWindowTitle("Admin");
			messageBox.setText(Utf8(
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

void MaterialView::printClicked()
{
}

void MaterialView::closeClicked()
{
}

void MaterialView::select()
{
	model->select();
}

