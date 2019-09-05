#include "mainwindow.h"
#include <QApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
		QMessageBox::warning(nullptr, QStringLiteral("��ʾ"), QStringLiteral("������ͬ�ĳ����������У�"));
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
