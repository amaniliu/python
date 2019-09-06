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

	// 创建信号量
	QSystemSemaphore semaphore("PythonZ1200Semaphore", 1);
	// 启用信号量，禁止其他实例通过共享内存一起工作
	semaphore.acquire(); 

#ifndef Q_OS_WIN32
	// 在linux / unix 程序异常结束共享内存不会回收
	// 在这里需要提供释放内存的接口，就是在程序运行的时候如果有这段内存 先清除掉
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
		// 否则申请一字节内存
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
