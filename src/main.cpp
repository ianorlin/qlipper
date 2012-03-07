/*
Qlipper - clipboard history manager
Copyright (C) 2012 Petr Vanek <petr@scribus.info>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <QtGui/QApplication>
#include <QtCore/QSettings>
#include <QtCore/QTranslator>
#include <QtCore/QTextCodec>
#include <QtDebug>

#include "qlippersystray.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    a.setApplicationName("qlipper");
    a.setApplicationVersion(QLIPPER_VERSION);
    a.setOrganizationDomain("qlipper.org");
    a.setOrganizationName("Qlipper");
    a.setWindowIcon(QIcon(":/icons/qlipper.png"));
    QSettings::setDefaultFormat(QSettings::IniFormat);

    // for QByteArray to QString constructors
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    a.setQuitOnLastWindowClosed(false);


    // potentially load translator
    QString fname(a.applicationName() + "." +  QLocale::system().name());
    qDebug() << fname;

#ifdef Q_WS_WIN
    QString location = a.applicationDirPath() + "/translations";
#elif defined Q_WS_MAC
    QString location = a.applicationDirPath() + "../Resources/translations";
#elif defined Q_WS_X11
    QString location = TRANSLATION_DIR;
#else
    // fallback
    QString location = a.applicationDirPath();
#endif

    QTranslator translator;

    if (translator.load(fname, location))
    {
        a.installTranslator(&translator);
    }
    else
    {
        qDebug() << "Translator is not loaded" << fname << location;
    }
    // end of translators


    QlipperSystray s;
    s.show();

    return a.exec();
}
