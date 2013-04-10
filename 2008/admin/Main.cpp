
/*
 *
 *
 *
 *
 *
 */

#include "MainWindow.h"

#include <QMutex>
#include <QWaitCondition>
#include <QProgressBar>



int main(int argc, char** argv)
{
	Application app(argc, argv);

	QPixmap pixmap("splash.png");
	SplashScreen splash(pixmap);

	QProgressBar* p = new QProgressBar(&splash);
	p->setAlignment(Qt::AlignHCenter);

	splash.show();
	app.processEvents();

	QMutex mutex;
	QWaitCondition sleep;

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(10);
	mutex.unlock();

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(20);
	mutex.unlock();


	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(30);
	mutex.unlock();


	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(40);
	mutex.unlock();


	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(50);
	mutex.unlock();


	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(60);
	mutex.unlock();

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(70);
	mutex.unlock();

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(80);
	mutex.unlock();

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(90);
	mutex.unlock();

	mutex.lock();
	sleep.wait(&mutex, 200);
	p->setValue(100);
	mutex.unlock();



	MainWindow window;
	window.showMaximized();
	splash.finish(&window);

	return app.exec();
}

