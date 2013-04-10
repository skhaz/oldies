
/*
 *
 *
 *
 *
 *
 *
 */

#include "Material.h"



Material::Material(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(cancelClicked()));
}

void Material::setParam(const ParameterList& param)
{
	query.clear();
	codigoEdit->clear();
	nomeEdit->clear();
	densidadeEdit->clear();
	submitButton->show();
	cancelButton->setText("&Cancelar");

	if (param["mode"] != "new")
	{
		int cod = param["cod"].toInt();
		query.prepare(
				" update material set nome = :nome, densidade = :densidade "
				" where cod_material = :cod_material "
			);

		codigoEdit->setText(param["cod"]);
		submitButton->setText("&Gravar");

		query.bindValue(":cod_material", cod);

		QSqlQuery sql;
		sql.prepare("select cod_material, nome, densidade from material where cod_material = :cod_material limit 1");
		sql.bindValue(":cod_material", cod);

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro na consulta\n%1").arg(sql.lastError().text()));
		}

		else
		{
			sql.first();

			codigoEdit->setText(sql.value(sql.record().indexOf("cod_material")).toString());
			nomeEdit->setText(sql.value(sql.record().indexOf("nome")).toString());

			double valor = sql.value(sql.record().indexOf("densidade")).toDouble();
			densidadeEdit->setValue(/*QString("%L1").arg(valor, 0, 'f', 2)*/ valor);
		}

		if (param["mode"] == "view")
		{
			cancelButton->setText("&Fechar");
			submitButton->hide();
			nomeEdit->setEnabled(false);
			densidadeEdit->setEnabled(false);
		}
	}

	else
	{
		query.prepare("insert into material (nome, densidade) values (:nome, :densidade)");
		submitButton->setText("&Inserir");
		nomeEdit->setFocus(Qt::MouseFocusReason);
	}
}

void Material::cancelClicked()
{
	// Check if editing

	QMessageBox messageBox;
	messageBox.setWindowTitle("Admin");
	messageBox.setText(Utf8("Tem certeza que deseja cancelar a edição?"));
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

void Material::submitClicked()
{
	if (nomeEdit->hasAcceptableInput() && densidadeEdit->hasAcceptableInput())
	{
		query.bindValue(":nome", nomeEdit->text());
		query.bindValue(":densidade", densidadeEdit->value());

		if (!query.exec())
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Houve um erro ao inserir\n%1").arg(query.lastError().text()));
		}

		emit dataChanged();

		ParameterList param;
		param["mode"] = "new";
		setParam(param);
	}

	else
	{
		QMessageBox::warning(this, "Admin",
				Utf8("Os dados inseridos são invalidos ou incompletos"));
	}
}

