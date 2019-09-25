#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "previewdialog.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QImage>
#include <QSettings>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_image(nullptr)
{
    ui->setupUi(this);
    initUI();
    initOffset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    ui->graphicsView->setScene(new QGraphicsScene());

    QStringList list;
    for (int i = 1; i < CHANNEL_NUM; i++)
    {
        list.append(QStringLiteral("拼缝") + QString::number(i) + "(Gap " + QString::number(i) + ")");
    }
    ui->comboBox_gap->addItems(list);
}

void MainWindow::initOffset()
{
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_offset[i].m_left = 0;
        m_offset[i].m_top = 0;
        m_offset[i].m_right = 0;
    }
}

void MainWindow::updateImage()
{
    if (m_image == nullptr) return;

    int index = ui->comboBox_gap->currentIndex();
    int w = static_cast<int>(SIGNGLE_WIDTH * 2 - m_offset[index].m_right - m_offset[index + 1].m_left);
    w = (w + 3) / 4 * 4;
    int hh = m_image->height();
    int h = hh + static_cast<int>(qAbs(m_offset[index].m_top - m_offset[index + 1].m_top));

    int w_l = static_cast<int>(SIGNGLE_WIDTH - m_offset[index].m_right);
    int w_r = static_cast<int>(SIGNGLE_WIDTH - m_offset[index + 1].m_left);

    uchar* data = new uchar[static_cast<size_t>(w * h)];
    uchar* src_ptr1 = m_image->bits() + index * SIGNGLE_WIDTH;
    uchar* src_ptr2 = m_image->bits() + (index + 1) * SIGNGLE_WIDTH + m_offset[index + 1].m_left;
    uchar* dst_ptr1;
    uchar* dst_ptr2;
    if (m_offset[index].m_top > m_offset[index + 1].m_top)
    {
        dst_ptr1 = data;
        dst_ptr2 = data + w_l + static_cast<uint>((m_offset[index].m_top - m_offset[index + 1].m_top) * w);
    }
    else
    {
        dst_ptr1 = data + static_cast<uint>((m_offset[index + 1].m_top - m_offset[index].m_top) * w);
        dst_ptr2 = data + w_l;
    }

    for (int i = 0; i < hh; i++)
    {
        memcpy(dst_ptr1, src_ptr1, static_cast<uint>(w_l));
        memcpy(dst_ptr2, src_ptr2, static_cast<uint>(w_r));
        dst_ptr1 += w;
        dst_ptr2 += w;

        src_ptr1 += SIGNGLE_WIDTH * CHANNEL_NUM;
        src_ptr2 += SIGNGLE_WIDTH * CHANNEL_NUM;
    }

    QImage img(data, w, h, QImage::Format_Indexed8);
    ui->graphicsView->scene()->clear();
    ui->graphicsView->scene()->setSceneRect(img.rect());
    ui->graphicsView->scene()->addPixmap(QPixmap::fromImage(img));
    int v = (ui->graphicsView->horizontalScrollBar()->maximum() - ui->graphicsView->horizontalScrollBar()->minimum() - w_r + w_l) / 2;
    ui->graphicsView->horizontalScrollBar()->setValue(v);

    delete [] data;
}

void MainWindow::h_offset(bool isLeft, int offset)
{
    int index = ui->comboBox_gap->currentIndex();
    if (isLeft)
    {
        if (static_cast<int>(m_offset[index].m_right) + offset < 0)
        {
            m_offset[index].m_right = 0;
        }
        else
        {
            m_offset[index].m_right += static_cast<uint>(offset);
        }
    }
    else
    {
        if (static_cast<int>(m_offset[index + 1].m_left) + offset < 0)
        {
            m_offset[index + 1].m_left = 0;
        }
        else
        {
            m_offset[index + 1].m_left += static_cast<uint>(offset);
        }
    }
    updateImage();
}

void MainWindow::v_offset(bool isLeft, int offset)
{
    int index = ui->comboBox_gap->currentIndex();
    int top[CHANNEL_NUM];
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        top[i] = static_cast<int>(m_offset[i].m_top);
    }

    if (isLeft)
    {
        for (int i = 0; i <= index; i++)
        {
            top[i] += offset;
        }
    }
    else
    {
        for (int i = index; i < (CHANNEL_NUM - 1); i++)
        {
            top[i + 1] += offset;
        }
    }

    int min = top[0];
    for (int i = 1; i < CHANNEL_NUM; i++)
    {
        if (min > top[i])
        {
            min = top[i];
        }
    }
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        top[i] -= min;
    }

    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_offset[i].m_top = top[i];
    }
    updateImage();
}

void MainWindow::on_btn_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Images (*.bmp)"));
    if (filename.isEmpty())
    {
        return;
    }

    if (m_image)
    {
        delete m_image;
    }

    m_image = new QImage(filename);
    if (m_image->width() != SIGNGLE_WIDTH * CHANNEL_NUM)
    {
        delete m_image;
        m_image = nullptr;
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("图像宽度不为7632，请重新选择图像"));
        return;
    }
    initOffset();
    updateImage();
}

void MainWindow::on_btn_import_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CONFIG (config.ini)"));

    if (filename.isEmpty())
    {
        return;
    }
    QSettings setting(filename, QSettings::IniFormat);

    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_offset[i].m_top = setting.value("channel" + QString::number(i) + "/top").toInt();
        m_offset[i].m_left = setting.value("channel" + QString::number(i) + "/left").toInt();
        m_offset[i].m_right = setting.value("channel" + QString::number(i) + "/right").toInt();
    }

    updateImage();
}

void MainWindow::on_btn_preview_clicked()
{
    if (m_image == nullptr) return;

    ImageProcess process(m_image->bits(), m_image->width(), m_image->height());
    ImageProcess montage;
    process.montage(m_offset, montage);

    QImage dst(montage.bits(), montage.width(), montage.height(), QImage::Format_Grayscale8);
    PreviewDialog dialog(&dst, this);
    dialog.exec();
}

void MainWindow::on_btn_export_clicked()
{
    QSettings setting("config.ini", QSettings::IniFormat);
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        setting.setValue("channel" + QString::number(i) + "/top", m_offset[i].m_top);
        setting.setValue("channel" + QString::number(i) + "/left", m_offset[i].m_left);
        setting.setValue("channel" + QString::number(i) + "/right", m_offset[i].m_right);
    }

    QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("拼接数据导出完成。"));
}

void MainWindow::on_comboBox_gap_currentIndexChanged(int index)
{
    (void)index;
    if (!m_image) return;

    updateImage();
}

void MainWindow::on_btn_l_l_clicked()
{
	if (m_image == nullptr) return;
	h_offset(true, -1);
}

void MainWindow::on_btn_l_ll_clicked()
{
	if (m_image == nullptr) return;
	h_offset(true, -10);
}

void MainWindow::on_btn_l_r_clicked()
{
	if (m_image == nullptr) return;
	h_offset(true, 1);
}

void MainWindow::on_btn_l_rr_clicked()
{
	if (m_image == nullptr) return;
	h_offset(true, 10);
}

void MainWindow::on_btn_l_u_clicked()
{
	if (m_image == nullptr) return;
	v_offset(true, 1);
}

void MainWindow::on_btn_l_uu_clicked()
{
	if (m_image == nullptr) return;
	v_offset(true, 10);
}

void MainWindow::on_btn_l_d_clicked()
{
	if (m_image == nullptr) return;
	v_offset(true, -1);
}

void MainWindow::on_btn_l_dd_clicked()
{
	if (m_image == nullptr) return;
	v_offset(true, -10);
}

void MainWindow::on_btn_r_l_clicked()
{
	if (m_image == nullptr) return;
	h_offset(false, 1);
}

void MainWindow::on_btn_r_ll_clicked()
{
	if (m_image == nullptr) return;
	h_offset(false, 10);
}

void MainWindow::on_btn_r_r_clicked()
{
	if (m_image == nullptr) return;
	h_offset(false, -1);
}

void MainWindow::on_btn_r_rr_clicked()
{
	if (m_image == nullptr) return;
	h_offset(false, -10);
}

void MainWindow::on_btn_r_u_clicked()
{
	if (m_image == nullptr) return;
	v_offset(false, 1);
}

void MainWindow::on_btn_r_uu_clicked()
{
	if (m_image == nullptr) return;
	v_offset(false, 10);
}

void MainWindow::on_btn_r_d_clicked()
{
	if (m_image == nullptr) return;
	v_offset(false, -1);
}

void MainWindow::on_btn_r_dd_clicked()
{
	if (m_image == nullptr) return;
	v_offset(false, -10);
}

void MainWindow::on_btn_dir_black_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开图像(Open File)"), "", QStringLiteral("Images (*.bmp)"));
	if (filename.isEmpty()) return;

	ui->lineEdit1->setText(filename);
}

void MainWindow::on_btn_path_white_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开图像(Open File)"), "", QStringLiteral("Images (*.bmp)"));
	if (filename.isEmpty()) return;

	ui->lineEdit2->setText(filename);
}

void MainWindow::on_btn_export_correct_clicked()
{
	QImage img1(ui->lineEdit1->text());
	QImage img2(ui->lineEdit2->text());

    const size_t length = static_cast<size_t>(SIGNGLE_WIDTH * CHANNEL_NUM);
    if (img1.width() != length || img2.width() != length)
	{
        QMessageBox::warning(this, QStringLiteral("提示(warninng)"), QStringLiteral("图像宽度不为") + QString::number(length) + QStringLiteral("，请重新选择图像"));
		return;
	}

    uchar* black = new uchar[static_cast<size_t>(img1.width())];
    uchar* white = new uchar[static_cast<size_t>(img2.width())];

	getCorrectData(img1.bits(), img1.width(), img1.height(), black);
	getCorrectData(img2.bits(), img2.width(), img2.height(), white);

    int aver_black = 0, aver_white = 0;
    for (size_t i = 0; i < length; ++i)
    {
        aver_black += black[i];
        aver_white += white[i];
    }
    aver_black /= length;
    aver_white /= length;

    if (ui->checkBox_black->isChecked())
    {
        uchar half_aver_white = static_cast<uchar>(aver_white / 2);

        for (size_t i = 0; i < length; ++i)
            if (white[i] < half_aver_white)
                white[i] = black[i] = 0;
    }

    if (ui->checkBox_white->isChecked())
    {
        uchar double_aver_black = static_cast<uchar>(min(aver_black * 2, 255));

        for (size_t i = 0; i < length; ++i)
            if (black[i] > double_aver_black)
                white[i] = black[i] = 255;
    }

	saveCorrectData("correctData.dat", reinterpret_cast<const char*>(black), reinterpret_cast<const char*>(white));

    QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("数据导出完成"));

	delete[] black;
	delete[] white;
}

void MainWindow::getCorrectData(uchar* src, int width, int height, uchar* dst)
{
	for (int x = 0; x < width; x++)
	{
		long total = 0;
		for (int y = 0; y < height; y++)
		{
			total += src[y * width + x];
		}
        dst[x] = static_cast<uchar>(total / height);
	}
}

void MainWindow::saveCorrectData(const QString& filename, const char* black, const char* white, size_t length)
{
	QFile file(filename);
	file.open(QIODevice::WriteOnly);

	QDataStream out(&file);
	out.writeBytes(black, length);
	out.writeBytes(white, length);
	file.close();
}

void MainWindow::on_checkBox_black_clicked(bool checked)
{
    if (checked)
        ui->checkBox_white->setChecked(false);
}

void MainWindow::on_checkBox_white_clicked(bool checked)
{
    if (checked)
        ui->checkBox_black->setChecked(false);
}
