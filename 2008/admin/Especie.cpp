
/*
 *
 *
 *
 *
 *
 *
 */

#include "Especie.h"



Especie::Especie(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(cancelClicked())); 
}

void Especie::setParam(const ParameterList& param)
{
	query.clear();
	codigoEdit->clear();
	nomeEdit->clear();
	submitButton->show();
	cancelButton->setText("&Cancelar");

	if (param["mode"] != "new")
	{
		int cod = param["cod"].toInt();
		query.prepare(
				" update materialespecie set nome = :nome "
				" where cod_materialespecie = :cod_materialespecie "
			);

		codigoEdit->setText(param["cod"]);
		submitButton->setText("&Gravar");

		query.bindValue(":cod_materialespecie", cod);

		QSqlQuery sql;
		sql.prepare("select cod_materialespecie, nome from materialespecie where cod_materialespecie = :cod_materialespecie limit 1");
		sql.bindValue(":cod_materialespecie", cod);

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				QString::fromUtf8("Erro na consulta\n%1").arg(sql.lastError().text()));
		}

		else
		{
			sql.first();

			codigoEdit->setText(sql.value(sql.record().indexOf("cod_materialespecie")).toString());
			nomeEdit->setText(sql.value(sql.record().indexOf("nome")).toString());
		}

		if (param["mode"] == "view")
		{
			cancelButton->setText("&Fechar");
			submitButton->hide();
			nomeEdit->setEnabled(false);
		}
	}

	else
	{
		query.prepare("insert into materialespecie (nome) values (:nome)");
		submitButton->setText("&Inserir");
		nomeEdit->setFocus(Qt::MouseFocusReason);
	}
}

void Especie::cancelClicked()
{
	// Check if editing

	QMessageBox messageBox;
	messageBox.setWindowTitle("Admin");
	messageBox.setText(QString::fromUtf8("Tem certeza que deseja cancelar a edição?"));
	messageBox.setIcon(QMessageBox::Question);
	messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

	switch(messageBox.exec())
	{
		case QMessageBox::Yes:
			close();
			break;

		default:
			break;
	}
}

void Especie::submitClicked()
{
	if (nomeEdit->hasAcceptableInput())
	{
		query.bindValue(":nome", nomeEdit->text());

		if (!query.exec())
		{
			QMessageBox::warning(this, "Admin",
				QString::fromUtf8("Houve um erro ao inserir\n%1").arg(query.lastError().text()));
		}

		emit dataChanged();

		ParameterList param;
		param["mode"] = "new";
		setParam(param);
	}

	else
	{
		QMessageBox::warning(this, "Admin",
				QString::fromUtf8("Os dados inseridos são invalidos ou incompletos"));
	}
}


