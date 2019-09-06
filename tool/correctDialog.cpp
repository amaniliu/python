#include "correctDialog.h"
#include <fstream>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

CorrectDialog::CorrectDialog()
{
	initui();
}

void CorrectDialog::initui()
{
    QLabel* lbl1 = new QLabel(QStringLiteral("黑校正图像：(Black Image：)"));
    QLabel* lbl2 = new QLabel(QStringLiteral("白校正图像：(White Image：)"));

	m_lineEdit1 = new QLineEdit;
	m_lineEdit1->setReadOnly(true);
	m_lineEdit1->setFixedWidth(200);
	m_lineEdit2 = new QLineEdit;
	m_lineEdit2->setReadOnly(true);
	m_lineEdit2->setFixedWidth(200);

	m_dir1 = new QToolButton;
    m_dir1->setText(QStringLiteral("…"));
	m_dir2 = new QToolButton;
    m_dir2->setText(QStringLiteral("…"));

	m_correct = new QToolButton;
    m_correct->setText(QStringLiteral("导出校正数据\n(Export)"));
	m_correct->setEnabled(false);


	QHBoxLayout* layout1 = new QHBoxLayout;
	layout1->addWidget(lbl1);
	layout1->addWidget(m_lineEdit1);
	layout1->addWidget(m_dir1);

	QHBoxLayout* layout2 = new QHBoxLayout;
	layout2->addWidget(lbl2);
	layout2->addWidget(m_lineEdit2);
	layout2->addWidget(m_dir2);

	QVBoxLayout* layout_main = new QVBoxLayout;
	layout_main->addLayout(layout1);
	layout_main->addLayout(layout2);
	layout_main->addWidget(m_correct, 0, Qt::AlignRight);

	this->setLayout(layout_main);
    this->setTitle(QStringLiteral("校正工具(Adjust Tool)"));
	this->setFixedWidth(450);

	connect(m_dir1, SIGNAL(clicked()), this, SLOT(btn_dir1()));
	connect(m_dir2, SIGNAL(clicked()), this, SLOT(btn_dir2()));
	connect(m_correct, SIGNAL(clicked()), this, SLOT(btn_correct()));
	connect(m_lineEdit1, SIGNAL(textChanged(const QString&)), this, SLOT(getTextChanged(const QString&)));
	connect(m_lineEdit2, SIGNAL(textChanged(const QString&)), this, SLOT(getTextChanged(const QString&)));
}

void CorrectDialog::btn_dir1()
{
    QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开图像(Open File)"), "", QStringLiteral("Images (*.bmp)"));
	if (filename.isEmpty())
	{
		return;
	}

	m_lineEdit1->setText(filename);
}

void CorrectDialog::btn_dir2()
{
    QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开文件(Open File)"), "", QStringLiteral("Images (*.bmp)"));
	if (filename.isEmpty())
	{
		return;
	}

	m_lineEdit2->setText(filename);
}

void CorrectDialog::btn_correct()
{
	QImage img1(m_lineEdit1->text());
	QImage img2(m_lineEdit2->text());

	if (img1.width() != SIGNGLE_WIDTH * CHANNEL_NUM || img2.width() != SIGNGLE_WIDTH * CHANNEL_NUM)
	{
        QMessageBox::warning(this, QStringLiteral("提示(warninng)"), QStringLiteral("图像宽度不为") + QString::number(SIGNGLE_WIDTH * CHANNEL_NUM) + QStringLiteral("，请重新选择图像"));
		return;
	}

	unsigned char* black = new unsigned char[img1.width()];
	unsigned char* white = new unsigned char[img2.width()];

	getCorrectData(img1.bits(), img1.width(), img1.height(), black);
	getCorrectData(img2.bits(), img2.width(), img2.height(), white);

	saveCorrectData("correctData.dat", black, white);

    QMessageBox::information(0, QStringLiteral("提示"), QStringLiteral("数据导出完成"));

	delete [] black;
	delete [] white;
}

void CorrectDialog::getTextChanged(const QString& text)
{
	(void)text;
	if (m_lineEdit1->text().isEmpty() || m_lineEdit2->text().isEmpty())
	{
		m_correct->setEnabled(false);
	}
	else
	{
		m_correct->setEnabled(true);
	}
}

void CorrectDialog::getCorrectData(unsigned char* src, int width, int height, unsigned char* dst)
{
	for (int x = 0; x < width; x++)
	{
		long total = 0;
		for (int y = 0; y < height; y++)
		{
			total += src[y * width + x];
		}
		dst[x] = total / height;
	}
}

void CorrectDialog::saveCorrectData(const char* filename, unsigned char* const black, unsigned char* const white, int length)
{
	ofstream of(filename, ios::binary);

	of.write((char*)black, length);
	of.write((char*)white, length);

	of.close();
}
