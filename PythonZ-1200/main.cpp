#include "mainwindow.h"
#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings setting("setting.ini", QSettings::IniFormat);
    QString language = setting.value("settings/language").toString();
    QTranslator qtTranslator;
    if (language == "cn")
        qtTranslator.load("cn", ":/language");
    else
        qtTranslator.load("en", ":/language");
    a.installTranslator(&qtTranslator);

	// �����ź���
	QSystemSemaphore semaphore("PythonZ1200Semaphore", 1);
	// �����ź�������ֹ����ʵ��ͨ�������ڴ�һ����
	semaphore.acquire(); 

#ifndef Q_OS_WIN32
	// ��linux / unix �����쳣���������ڴ治�����
	// ��������Ҫ�ṩ�ͷ��ڴ�Ľӿڣ������ڳ������е�ʱ�����������ڴ� �������
	QSharedMemory nix_fix_shared_memory("PythonZ1200");
	if (nix_fix_shared_memory.attach())
	{
		nix_fix_shared_memory.detach();
	}
#endif
	QSharedMemory sharedMemory("PythonZ1200");
	bool isRunning = sharedMemory.attach();
	if (isRunning)
	{
        QMessageBox::warning(nullptr, QObject::tr("warnning"), QObject::tr("There is already a program running."));
	}
	else
	{
		// ��������һ�ֽ��ڴ�
		sharedMemory.create(1);
	}
	semaphore.release();

	if (isRunning)
	{
		return 1;
	}

	MainWindow w;
	w.show();
    return a.exec();
}
