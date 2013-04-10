
/*
 *
 *
 *
 *
 *
 */

#include "SplashScreen.h"



SplashScreen::SplashScreen(QPixmap const& pixmap, Qt::WindowFlags flags)
: QSplashScreen(pixmap, flags)
{
}

void SplashScreen::paintEvent(QPaintEvent* event)
{
	QSplashScreen::paintEvent(event);
}

