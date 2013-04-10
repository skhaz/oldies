
#
#
#

TEMPLATE = app

TARGET = admin

DESTDIR = output

CONFIG += console warn_on

OBJECTS_DIR = tmp/obj
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc

QT += sql

SOURCES += \
	Main.cpp \
	SqlComboBox.cpp \
	Logger.cpp \
	Application.cpp \
	MainWindow.cpp \
	AbstractItemView.cpp \
	FilterWidget.cpp \
	MateriaPrimaView.cpp \
	MateriaPrima.cpp \
	MaterialView.cpp \
	Material.cpp \
	EspecieView.cpp \
	Especie.cpp \
	Programa.cpp \
	PictureView.cpp \
	PecaView.cpp \
	Peca.cpp \
	Orcamento.cpp \
	SplashScreen.cpp

HEADERS += \
	SqlComboBox.h \
	Logger.h \
	Application.h \
	MainWindow.h \
	AbstractItemView.h \
	FilterWidget.h \
	MateriaPrimaView.h \
	MateriaPrima.h \
	MaterialView.h \
	Material.h \
	EspecieView.h \
	Especie.h \
	Programa.h \
	PictureView.h \
	PecaView.h \
	Peca.h \
	Orcamento.h \
	SplashScreen.h

RESOURCES += \
	Media.qrc

FORMS += \
	forms/AbstractItemView.ui \
	forms/MateriaPrima.ui \
	forms/Material.ui \
	forms/Especie.ui \
	forms/Programa.ui \
	forms/PictureView.ui \
	forms/Peca.ui \
	forms/Orcamento.ui

win32 {
	RC_FILE = admin.rc
}

