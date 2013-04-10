
/*
 *
 *
 *
 *
 *
 *
 */

#include "MateriaPrima.h"



MateriaPrima::MateriaPrima(QWidget* parent)
: QDialog(parent)
{
	setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

	connect(tipoCombo, SIGNAL(currentIndexChanged(int)), SLOT(tipoIndexChanged(int)));
	connect(doubleSpinBox1, SIGNAL(valueChanged(double)), SLOT(tipoIndexChanged()));
	connect(doubleSpinBox2, SIGNAL(valueChanged(double)), SLOT(tipoIndexChanged()));
	connect(doubleSpinBox3, SIGNAL(valueChanged(double)), SLOT(tipoIndexChanged()));
	connect(doubleSpinBox4, SIGNAL(valueChanged(double)), SLOT(tipoIndexChanged()));
	connect(doubleSpinBox5, SIGNAL(valueChanged(double)), SLOT(tipoIndexChanged()));
	connect(materialCombo, SIGNAL(currentIndexChanged(int)), SLOT(materialIndexChanged(int)));
	connect(materialCombo, SIGNAL(currentIndexChanged(int)), SLOT(tipoIndexChanged()));
	connect(materialCombo, SIGNAL(currentIndexChanged(int)), SLOT(buildMaterialString()));
	connect(tipoCombo, SIGNAL(currentIndexChanged(int)), SLOT(buildMaterialString()));
	connect(especieCombo, SIGNAL(currentIndexChanged(int)), SLOT(buildMaterialString()));
	connect(doubleSpinBox1, SIGNAL(valueChanged(double)), SLOT(buildMaterialString()));
	connect(doubleSpinBox2, SIGNAL(valueChanged(double)), SLOT(buildMaterialString()));
	connect(doubleSpinBox3, SIGNAL(valueChanged(double)), SLOT(buildMaterialString()));
	connect(doubleSpinBox4, SIGNAL(valueChanged(double)), SLOT(buildMaterialString()));
	connect(doubleSpinBox5, SIGNAL(valueChanged(double)), SLOT(buildMaterialString()));
	connect(qualidadeEdit, SIGNAL(textChanged(const QString&)), SLOT(buildMaterialString()));
	connect(submitButton, SIGNAL(clicked()), SLOT(submitClicked()));
	connect(cancelButton, SIGNAL(clicked()), SLOT(cancelClicked()));
	connect(materialCombo, SIGNAL(currentIndexChanged(int)), SLOT(calculaPesoLinear()));
	connect(doubleSpinBox1, SIGNAL(valueChanged(double)), SLOT(calculaPesoLinear()));
	connect(doubleSpinBox2, SIGNAL(valueChanged(double)), SLOT(calculaPesoLinear()));
	connect(doubleSpinBox3, SIGNAL(valueChanged(double)), SLOT(calculaPesoLinear()));
	connect(doubleSpinBox4, SIGNAL(valueChanged(double)), SLOT(calculaPesoLinear()));
	connect(doubleSpinBox5, SIGNAL(valueChanged(double)), SLOT(calculaPesoLinear()));
}

void MateriaPrima::setParam(const ParameterList& param)
{
	formulaLabel->hide();
	densidadeLabel->hide();
	nomeEdit->clear();
	materialCombo->clear();
	especieCombo->clear();
	qualidadeEdit->clear();
	tipoCombo->clear();
	precoSpin->clear();

	submitButton->show();

	tipoCombo->addItem("Redondo");
	tipoCombo->addItem("Quadrado");
	tipoCombo->addItem("Sextavado");
	tipoCombo->addItem("Tubos Redondos");
	tipoCombo->addItem("Cantoeira");
	tipoCombo->setCurrentIndex(-1);

	materialCombo->setQuery("select cod_material, nome from material");
	especieCombo->setQuery("select cod_materialespecie, nome from materialespecie");

	query.clear();

	if (param["mode"] != "new")
	{
		submitButton->setText("&Gravar");

		int cod = param["cod"].toInt();
		QSqlQuery sql;

		query.prepare(
				" update materiaprima set nome = :nome, cod_material = :cod_material, "
				" tipo = :tipo, cod_materialespecie = :cod_materialespecie,           "
				" qualidade = :qualidade, preco = :preco, pesolinear = :pesolinear,   "
				" var1 = :var1, var2 = :var2, var3 = :var3, var4 = :var4,             "
				" var5 = :var5 where cod_materiaprima = :cod                          "
			);

		sql.prepare(
				" select nome, cod_material, tipo, cod_materialespecie,          "
				" qualidade, preco, pesolinear, var1, var2, var3, var4, var5     "
				" from materiaprima where cod_materiaprima = :cod limit 1        "
			);

		query.bindValue(":cod", cod);
		sql.bindValue(":cod", cod);

		if (!sql.exec())
		{
			QMessageBox::warning(this, "Admin",
				Utf8("Erro na consulta\n%1").arg(sql.lastError().text()));
		}

		else
		{
			sql.first();

			nomeEdit->setText(sql.value(sql.record().indexOf("nome")).toString());
			qualidadeEdit->setText(sql.value(sql.record().indexOf("qualidade")).toString());

			materialCombo->setCurrentIndex(materialCombo->findData(
					sql.value(sql.record().indexOf("cod_material")).toInt()));

			especieCombo->setCurrentIndex(especieCombo->findData(
					sql.value(sql.record().indexOf("cod_materialespecie")).toInt()));

			tipoCombo->setCurrentIndex(sql.value(sql.record().indexOf("tipo")).toInt());

			precoSpin->setValue(sql.value(sql.record().indexOf("preco")).toDouble());

			doubleSpinBox1->setValue(sql.value(sql.record().indexOf("var1")).toDouble());
			doubleSpinBox2->setValue(sql.value(sql.record().indexOf("var2")).toDouble());
			doubleSpinBox3->setValue(sql.value(sql.record().indexOf("var3")).toDouble());
			doubleSpinBox4->setValue(sql.value(sql.record().indexOf("var4")).toDouble());
			doubleSpinBox5->setValue(sql.value(sql.record().indexOf("var5")).toDouble());
		}

		if (param["mode"] == "view")
		{
			submitButton->hide();

			doubleSpinBox1->setEnabled(false);
			doubleSpinBox2->setEnabled(false);
			doubleSpinBox3->setEnabled(false);
			doubleSpinBox4->setEnabled(false);
			doubleSpinBox5->setEnabled(false);
			nomeEdit->setEnabled(false);
			qualidadeEdit->setEnabled(false);
			precoSpin->setEnabled(false);

			tipoCombo->setEnabled(false);
			especieCombo->setEnabled(false);
			materialCombo->setEnabled(false);
		}
	}

	else
	{
		nomeEdit->setFocus(Qt::MouseFocusReason);
		submitButton->setText("&Inserir");

		query.prepare(
				" insert into materiaprima (nome, cod_material, tipo, cod_materialespecie, qualidade,              "
				" preco, pesolinear, var1, var2, var3, var4, var5) values (:nome, :cod_material,                   "
				" :tipo, :cod_materialespecie, :qualidade, :preco, :pesolinear, :var1, :var2, :var3, :var4, :var5) "
			);
	}
}

void MateriaPrima::buildMaterialString()
{
	QString buffer;

	QString material(materialCombo->currentText().toUpper());

	material.replace(QRegExp(Utf8("[ÁÀÂÃÄ]")), "A");
	material.replace(QRegExp(Utf8("[ÉÈÊË]")), "E");
	material.replace(QRegExp(Utf8("[ÍÌÎÏ]")), "I");
	material.replace(QRegExp(Utf8("[ÓÒÔÕÖ]")), "O");
	material.replace(QRegExp(Utf8("[ÚÙÛÜ]")), "U");
	material.replace(Utf8("Ç"), "C");
	material.truncate(10);

	if (material.isEmpty())
	{
	}

	else {
		buffer.append(material);
		buffer.append(" ");
	}

	QString tipo(tipoCombo->currentText().toUpper());

	tipo.replace(QRegExp(Utf8("[ÁÀÂÃÄ]")), "A");
	tipo.replace(QRegExp(Utf8("[ÉÈÊË]")), "E");
	tipo.replace(QRegExp(Utf8("[ÍÌÎÏ]")), "I");
	tipo.replace(QRegExp(Utf8("[ÓÒÔÕÖ]")), "O");
	tipo.replace(QRegExp(Utf8("[ÚÙÛÜ]")), "U");
	tipo.replace(Utf8("Ç"), "C");
	tipo.truncate(5);

	if (tipo.isEmpty())
	{
	}

	else {
		buffer.append(tipo);
		buffer.append(" ");
	}

	QString especie(especieCombo->currentText().toUpper());

	especie.replace(QRegExp(Utf8("[ÁÀÂÃÄ]")), "A");
	especie.replace(QRegExp(Utf8("[ÉÈÊË]")), "E");
	especie.replace(QRegExp(Utf8("[ÍÌÎÏ]")), "I");
	especie.replace(QRegExp(Utf8("[ÓÒÔÕÖ]")), "O");
	especie.replace(QRegExp(Utf8("[ÚÙÛÜ]")), "U");
	especie.replace(Utf8("Ç"), "C");
	especie.truncate(4);

	if (especie.isEmpty())
	{
	}

	else {
		buffer.append(especie);
		buffer.append(" ");
	}

	QString qualidade(qualidadeEdit->text().toUpper());
	qualidade.replace(QRegExp(Utf8("[ÁÀÂÃÄ]")), "A");
	qualidade.replace(QRegExp(Utf8("[ÉÈÊË]")), "E");
	qualidade.replace(QRegExp(Utf8("[ÍÌÎÏ]")), "I");
	qualidade.replace(QRegExp(Utf8("[ÓÒÔÕÖ]")), "O");
	qualidade.replace(QRegExp(Utf8("[ÚÙÛÜ]")), "U");
	qualidade.replace(Utf8("Ç"), "C"); 

	if (qualidade.isEmpty())
	{
	}

	else {
		buffer.append(qualidade);
		buffer.append(" ");
	}

	QLocale locale;

	if (doubleSpinBox1->value() != 0)
			buffer.append(QString("%1%2").arg(locale.toString(doubleSpinBox1->value())).arg(
				doubleSpinBox2->value() != 0 ? "x" : ""));

	if (doubleSpinBox2->value() != 0)
			buffer.append(QString("%1%2").arg(locale.toString(doubleSpinBox2->value())).arg(
				doubleSpinBox3->value() != 0 ? "x" : ""));

	if (doubleSpinBox3->value() != 0)
			buffer.append(QString("%1%2").arg(locale.toString(doubleSpinBox3->value())).arg(
				doubleSpinBox4->value() != 0 ? "x" : ""));

	if (doubleSpinBox4->value() != 0)
			buffer.append(QString("%1%2").arg(locale.toString(doubleSpinBox4->value())).arg(
				doubleSpinBox5->value() != 0 ? "x" : ""));

	if (doubleSpinBox5->value() != 0)
			buffer.append(QString("%1").arg(locale.toString(
				doubleSpinBox4->value())));

	nomeEdit->setText(buffer);
}

void MateriaPrima::submitClicked()
{
	if (qualidadeEdit->text().isEmpty())
	{
		QMessageBox::warning(this, "Admin",
				Utf8("A Qualidade informada é inválida ou vazia"));
	}

	else if (precoSpin->value() == 0)
	{
		QMessageBox::warning(this, "Admin",
				Utf8("O campo preço está vazio"));
	}

	else
	{
		query.bindValue(":nome", nomeEdit->text());
		query.bindValue(":cod_material", materialCombo->itemData(materialCombo->currentIndex()).toInt());
		query.bindValue(":tipo", tipoCombo->currentIndex());
		query.bindValue(":cod_materialespecie", especieCombo->itemData(especieCombo->currentIndex()).toInt());
		query.bindValue(":qualidade", qualidadeEdit->text());
		query.bindValue(":preco", precoSpin->value());
		query.bindValue(":pesolinear", 0);
		query.bindValue(":var1", doubleSpinBox1->value());
		query.bindValue(":var2", doubleSpinBox2->value());
		query.bindValue(":var3", doubleSpinBox3->value());
		query.bindValue(":var4", doubleSpinBox4->value());
		query.bindValue(":var5", doubleSpinBox5->value());

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
}

void MateriaPrima::cancelClicked()
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

void MateriaPrima::materialIndexChanged(int index)
{
	index != -1 ? densidadeLabel->show() : densidadeLabel->hide();

	QSqlQuery sql;
	sql.prepare("select densidade from material where cod_material = :cod");
	sql.bindValue(":cod", materialCombo->itemData(index).toInt());

	if (!sql.exec()) {
		// TODO: Erro
	}

	else
	{
		sql.last();
		QString densidade;
		densidade.sprintf("%2.4f", sql.value(sql.record().indexOf("densidade")).toDouble());
		densidadeLabel->setText(densidade);
	}
}

void MateriaPrima::tipoIndexChanged(int index)
{
	if (index != 0)
	{
		pictureLabel->setPixmap(QPixmap());

		doubleSpinBox1->setValue(0);
		doubleSpinBox2->setValue(0);
		doubleSpinBox3->setValue(0);
		doubleSpinBox4->setValue(0);
		doubleSpinBox5->setValue(0);

		doubleSpinBox1->hide();
		doubleSpinBox2->hide();
		doubleSpinBox3->hide();
		doubleSpinBox4->hide();
		doubleSpinBox5->hide();

		label1->hide();
		label2->hide();
		label3->hide();
		label4->hide();
		label5->hide();
	}		
			
	else {
		index = tipoCombo->currentIndex();
	}

	QColor colorkey(255, 0, 255);
	QPixmap pixmap;
	QString formula;
	QLocale locale;

	switch (index)
	{
		case 0:
			if (QPixmapCache::find("redondo", pixmap))
			{
			}

			else {
				pixmap.load(":/media/geo/redondo.png");
				pixmap = pixmap.createMaskFromColor(colorkey.rgb());
				QPixmapCache::insert("redondo", pixmap);
			}

			pictureLabel->setPixmap(pixmap);

			formula = QString("(%1 * %1 * 3,1416 * %2) / 4.000").arg(
							doubleSpinBox1->value() != 0 ? locale.toString(doubleSpinBox1->value()) : "D").arg(
								densidadeLabel->text().toDouble());

			formulaLabel->show();
			label1->setText("D");
			label1->show();
			doubleSpinBox1->show();
			break;

		case 1:
			if (QPixmapCache::find("barra", pixmap))
			{
			}

			else {
				pixmap.load(":/media/geo/barra.png");
				pixmap = pixmap.createMaskFromColor(colorkey.rgb());
				QPixmapCache::insert("barra", pixmap);
			}

			pictureLabel->setPixmap(pixmap);

			formula = QString("(%1 * %1 * %2) / 1.000").arg(
					doubleSpinBox1->value() != 0 ? locale.toString(doubleSpinBox1->value()) : "D").arg(
						densidadeLabel->text().toDouble());

			label1->setText("D");
			label1->show();
			doubleSpinBox1->show();
			break;

		case 2:
			if (QPixmapCache::find("sextavado", pixmap))
			{
			}

			else {
				pixmap.load(":/media/geo/sextavado.png");
				pixmap = pixmap.createMaskFromColor(colorkey.rgb());
				QPixmapCache::insert("sextavado", pixmap);
			}

			pictureLabel->setPixmap(pixmap);

			formula = QString("(%1 * %1 * 3 * %3) / 3.460").arg(
					doubleSpinBox1->value() != 0 ? locale.toString(doubleSpinBox1->value()) : "D").arg(
						densidadeLabel->text().toDouble());

			label1->show();
			label1->setText("D");
			doubleSpinBox1->show();
			break;

		case 3:
			if (QPixmapCache::find("tuboredondo", pixmap))
			{
			}

			else {
				pixmap.load(":/media/geo/tuboredondo.png");
				pixmap = pixmap.createMaskFromColor(colorkey.rgb());
				QPixmapCache::insert("tuboredondo", pixmap);
			}

			pictureLabel->setPixmap(pixmap);

			formula = QString("(%1 * %1 * 3,1416) - (%2 * %2 * 3,1416) * %3 / 4.000").arg(
							doubleSpinBox1->value() != 0 ? locale.toString(doubleSpinBox1->value()) : "De").arg(
								doubleSpinBox2->value() != 0 ? locale.toString(doubleSpinBox2->value()) : "Di").arg(
								densidadeLabel->text().toDouble());

			formulaLabel->show();
			label1->show();
			label1->setText("De");
			doubleSpinBox1->show();
			label2->show();
			label2->setText("Di");
			doubleSpinBox2->show();
			break;

		case 4:
			label1->show();
			doubleSpinBox1->show();
			label2->show();
			doubleSpinBox2->show();
			label3->show();
			doubleSpinBox3->show();
			label4->show();
			doubleSpinBox4->show();
			break;

		default:
			break;
	}

	formulaLabel->setText(formula);
}

void MateriaPrima::calculaPesoLinear()
{
	double densidade = densidadeLabel->text().toDouble();
	float diametro = doubleSpinBox1->value();
	double linear = (diametro * diametro * 3.1416f * densidade) / 4000;

	linearLabel->setText(QString("%1 KG/m").arg(linear));
}

