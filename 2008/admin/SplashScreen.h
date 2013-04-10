
/*
 *
 *
 *
 *
 *
 */

#ifndef _SplashScreen_h
#define _SplashScreen_h

#include <QSplashScreen>
#include <QPixmap>
#include <QWidget>
#include <QProgressBar>



class SplashScreen : public QSplashScreen
{
	public:
		SplashScreen(QPixmap const& pixmap = QPixmap(), Qt::WindowFlags flags = 0);

	protected:
		virtual void paintEvent(QPaintEvent* event);

	private:

};

#endif

