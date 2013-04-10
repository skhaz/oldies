
/*
 *
 *
 *
 *
 *
 *
 */

#include "MateriaPrimaDetail.h"



MateriaPrimaDetail::MateriaPrimaDetail(QWidget* parent)
: QDialog(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);

	setupUi(this);

	connect(tipoComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(formulaIndexChanged(int)));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

bool MateriaPrimaDetail::validate(QLineEdit* lineEdit)
{
	QString text = lineEdit->text();
	const QValidator* validator = lineEdit->validator();

	if (validator)
	{
		int pos;
		if (validator->validate(text, pos) != QValidator::Acceptable)
			return false;
	}

	if (text.isEmpty())
	{
		return false;
	}

	return true;
}

void MateriaPrimaDetail::setParam(const ParameterList& param)
{
	formulaTitleLabel->hide();
	formulaLabel->hide();
	label1->hide();
	label2->hide();
	lineEdit1->hide();
	lineEdit2->hide();

	nomeEdit->clear();
	tipoComboBox->setCurrentIndex(-1);
	precoEdit->clear();

	if (param["mode"] != "new")
	{
		disconnect(pushButton, SIGNAL(clicked()), this, SLOT(newClicked()));
		connect(pushButton, SIGNAL(clicked()), this, SLOT(editClicked()));
		pushButton->setText("&Salvar");
		query.prepare("UPDATE materiaprima SET nome = :nome, preco_por_kilo = :preco_por_kilo, tipo = :tipo WHERE cod_materiaprima = :cod");
		query.bindValue(":cod", param["cod"].toULongLong());

		QSqlQuery sql;
		sql.prepare("SELECT nome, tipo, preco_por_kilo FROM materia_prima WHERE cod_materiaprima=:cod_materia_prima");
		sql.bindValue("cod_materia_prima", param["cod"].toULongLong());

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				QString::fromUtf8("Erro na consulta\1%1").arg(query.lastError().text()));
		}

		else
		{
			sql.last();

			nomeEdit->setText(sql.value(0).toString());
			tipoComboBox->setCurrentIndex(sql.value(1).toInt());
			precoEdit->setText(sql.value(2).toString());
		}

		if (param["mode"] == "view")
		{
			setWindowTitle(QString::fromUtf8("Visualizando registro [%1]").arg(sql.value(0).toString()));

			nomeEdit->setReadOnly(true);
			precoEdit->setReadOnly(true);
			pushButton->hide();
			cancelButton->setText("Fe&char");
		} else {
			setWindowTitle(QString::fromUtf8("Editando registro [%1]").arg(sql.value(0).toString()));
		}
	}

	else
	{
		setWindowTitle(QString::fromUtf8("Novo registro"));
		disconnect(pushButton, SIGNAL(clicked()), this, SLOT(editClicked()));
		connect(pushButton, SIGNAL(clicked()), this, SLOT(newClicked()));
		pushButton->setText("&Inserir");
		query.prepare("INSERT INTO materiaprima (nome, preco_por_kilo, tipo) VALUES (:nome, :preco_por_kilo, :tipo)");
	}
}

void MateriaPrimaDetail::newClicked()
{
	if (!validate(nomeEdit) && !validate(precoEdit))
	{
		QMessageBox::warning(this, "Admin",
			QString::fromUtf8("Há campos vazios"));
	}

	else
	{
		query.bindValue(":nome", nomeEdit->text());
		query.bindValue(":tipo", tipoComboBox->currentIndex());
		query.bindValue(":preco_por_kilo", precoEdit->text());

		if (!query.exec())
		{
			QMessageBox::warning(this, "Admin",
				QString::fromUtf8("Houve um erro ao inserir\1%1").arg(query.lastError().text()));
		}

		ParameterList param;
		param["mode"] = "new";
		setParam(param);

		emit dataChanged();
	}
}

void MateriaPrimaDetail::editClicked()
{
	query.bindValue(":nome", nomeEdit->text());
	query.bindValue(":tipo", tipoComboBox->currentIndex());
	query.bindValue(":preco_por_kilo", precoEdit->text());

	if (!query.exec())
	{
		QMessageBox::warning(this, "Admin",
			QString::fromUtf8("Houve um erro ao inserir\1%1").arg(query.lastError().text()));
	}

	ParameterList param;
	param["mode"] = "new";
	setParam(param);

	emit dataChanged();
}

void MateriaPrimaDetail::formulaIndexChanged(int index)
{
	switch(index)
	{
		case TIPO_REDONDO:
			formulaTitleLabel->hide();
			formulaLabel->hide();
			label1->hide();
			label2->hide();
			lineEdit1->hide();
			lineEdit2->hide();

			formulaTitleLabel->show();
			formulaLabel->setText("D² * 0.00025");
			formulaLabel->show();
			label1->setText("D: ");
			label1->show();
			lineEdit1->show();

			tipo = TIPO_REDONDO;
			break;

		case TIPO_QUADRADO:
			formulaTitleLabel->hide();
			formulaLabel->hide();
			label1->hide();
			label2->hide();
			lineEdit1->hide();
			lineEdit2->hide();

			formulaTitleLabel->show();
			formulaLabel->setText("(D² * T) * 0.00025");
			formulaLabel->show();
			label1->setText("D: ");
			label1->show();
			lineEdit1->show();

			label2->setText("T: ");
			label2->show();
			lineEdit2->show();

			tipo = TIPO_QUADRADO;
			break;

		case TIPO_SEXTAVADO:
			break;
	}
}

