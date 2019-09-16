#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    if (m_image == nullptr)
        return;

    int index = ui->comboBox_gap->currentIndex();
    int w = static_cast<int>(SIGNGLE_WIDTH * 2 - m_offset[index].m_right - m_offset[index + 1].m_left);
    w = (w + 3) / 4 * 4;
    int hh = m_image->height();
    int h = hh + static_cast<int>(qAbs(m_offset[index].m_top - m_offset[index + 1].m_top));

    int w_l = static_cast<int>(SIGNGLE_WIDTH - m_offset[index].m_right);
    int w_r = static_cast<int>(SIGNGLE_WIDTH - m_offset[index + 1].m_left);

    unsigned char* data = new unsigned char[static_cast<size_t>(w * h)];
    unsigned char* src_ptr1 = m_image->bits() + index * SIGNGLE_WIDTH;
    unsigned char* src_ptr2 = m_image->bits() + (index + 1) * SIGNGLE_WIDTH + m_offset[index + 1].m_left;
    unsigned char* dst_ptr1;
    unsigned char* dst_ptr2;
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
    if (!m_image)
    {
        return;
    }

    updateImage();
}

void MainWindow::on_btn_l_l_clicked()
{

}

void MainWindow::on_btn_l_ll_clicked()
{

}

void MainWindow::on_btn_l_r_clicked()
{

}

void MainWindow::on_btn_l_rr_clicked()
{

}

void MainWindow::on_btn_l_u_clicked()
{

}

void MainWindow::on_btn_l_uu_clicked()
{

}

void MainWindow::on_btn_l_d_clicked()
{

}

void MainWindow::on_btn_l_dd_clicked()
{

}

void MainWindow::on_btn_r_l_clicked()
{

}

void MainWindow::on_btn_r_ll_clicked()
{

}

void MainWindow::on_btn_r_r_clicked()
{

}

void MainWindow::on_btn_r_rr_clicked()
{

}

void MainWindow::on_btn_r_u_clicked()
{

}

void MainWindow::on_btn_r_uu_clicked()
{

}

void MainWindow::on_btn_r_d_clicked()
{

}

void MainWindow::on_btn_r_dd_clicked()
{

}

void MainWindow::on_btn_dir_black_clicked()
{

}

void MainWindow::on_btn_path_white_clicked()
{

}

void MainWindow::on_btn_export_correct_clicked()
{

}
