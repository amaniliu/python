#include "settingDialog.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QImage>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include "stdlib.h"
#include "correctDialog.h"

#define SIGNGLE_WIDTH 1272
#define CHANNEL_NUM 6

SettingDialog::SettingDialog(QWidget* parent)
: m_image(0)
{
    initUi();
    initOffset();
}

void SettingDialog::initUi()
{
    m_btn_open = new QToolButton;
    m_btn_open->setFixedHeight(50);
    m_btn_open->setText(QStringLiteral("打开图片\n(Open File)"));

    m_btn_import = new QToolButton;
    //m_btn_import->setFixedSize(80, 50);
    m_btn_import->setFixedHeight(50);
    m_btn_import->setText(QStringLiteral("导入现有规则\n(Import Existing Rule)"));

    m_btn_save = new QToolButton;
    m_btn_save->setFixedHeight(50);
    m_btn_save->setText(QStringLiteral("导出规则\n (Export Rule)"));

    m_cb_channel = new QComboBox;
    QStringList list;
    for (int i = 1; i < CHANNEL_NUM; i++)
    {
        list.append(QStringLiteral("拼缝") + QString::number(i) + "(Gap " + QString::number(i) + ")");
    }
    m_cb_channel->addItems(list);

    m_scene = new QGraphicsScene;
    m_view = new QGraphicsView(m_scene);
    m_view->horizontalScrollBar()->setVisible(false);

    m_correctDialog = new CorrectDialog;

    QHBoxLayout* layout_btn = new QHBoxLayout;
    layout_btn->addWidget(m_btn_open);
    layout_btn->addWidget(m_btn_import);
    layout_btn->addWidget(m_btn_save);
    layout_btn->addWidget(m_cb_channel);

    QGroupBox* groupBox = new QGroupBox(QStringLiteral("(Joint)"));
    groupBox->setLayout(layout_btn);

    QHBoxLayout* layout_toolBar = new QHBoxLayout;
    layout_toolBar->addWidget(groupBox);
    layout_toolBar->addWidget(m_correctDialog);
    //layout_btn->addWidget(m_correctDialog);
    layout_toolBar->addStretch();

    m_btn_l_l = new QToolButton;
    m_btn_l_l->setText(QStringLiteral("<"));
    m_btn_l_ll = new QToolButton;
    m_btn_l_ll->setText(QStringLiteral("《"));
    m_btn_l_r = new QToolButton;
    m_btn_l_r->setText(QStringLiteral(">"));
    m_btn_l_rr = new QToolButton;
    m_btn_l_rr->setText(QStringLiteral("》"));
    m_btn_l_u = new QToolButton;
    m_btn_l_u->setText(QStringLiteral("︿"));
    m_btn_l_uu = new QToolButton;
    m_btn_l_uu->setText(QStringLiteral("︽"));
    m_btn_l_d = new QToolButton;
    m_btn_l_d->setText(QStringLiteral("﹀"));
    m_btn_l_dd = new QToolButton;
    m_btn_l_dd->setText(QStringLiteral("︾"));

    m_btn_r_l = new QToolButton;
    m_btn_r_l->setText(QStringLiteral("<"));
    m_btn_r_ll = new QToolButton;
    m_btn_r_ll->setText(QStringLiteral("《"));
    m_btn_r_r = new QToolButton;
    m_btn_r_r->setText(QStringLiteral(">"));
    m_btn_r_rr = new QToolButton;
    m_btn_r_rr->setText(QStringLiteral("》"));
    m_btn_r_u = new QToolButton;
    m_btn_r_u->setText(QStringLiteral("︿"));
    m_btn_r_uu = new QToolButton;
    m_btn_r_uu->setText(QStringLiteral("︽"));
    m_btn_r_d = new QToolButton;
    m_btn_r_d->setText(QStringLiteral("﹀"));
    m_btn_r_dd = new QToolButton;
    m_btn_r_dd->setText(QStringLiteral("︾"));

    QGridLayout* layout_btns1 = new QGridLayout;
    layout_btns1->addWidget(m_btn_l_uu, 0, 3, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_u, 1, 3, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_ll, 2, 1, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_l, 2, 2, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_r, 2, 4, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_rr, 2, 5, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_d, 3, 3, Qt::AlignCenter);
    layout_btns1->addWidget(m_btn_l_dd, 4, 3, Qt::AlignCenter);
    QGridLayout* layout_btns2 = new QGridLayout;
    layout_btns2->addWidget(m_btn_r_uu, 0, 3, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_u, 1, 3, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_ll, 2, 1, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_l, 2, 2, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_r, 2, 4, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_rr, 2, 5, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_d, 3, 3, Qt::AlignCenter);
    layout_btns2->addWidget(m_btn_r_dd, 4, 3, Qt::AlignCenter);

    QHBoxLayout* layout_btns = new QHBoxLayout;
    layout_btns->addStretch();
    layout_btns->addLayout(layout_btns1);
    layout_btns->addSpacing(50);
    layout_btns->addLayout(layout_btns2);
    layout_btns->addStretch();

    QVBoxLayout* layout_main = new QVBoxLayout;
    layout_main->addLayout(layout_toolBar, 0);
    layout_main->addWidget(m_view, 1);
    layout_main->addLayout(layout_btns, 0);

    this->setLayout(layout_main);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle(QStringLiteral("У(Adjust Tool)"));

    connect(m_cb_channel, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));

    connect(m_btn_open, SIGNAL(clicked()), this, SLOT(btn_open()));
    connect(m_btn_import, SIGNAL(clicked()), this, SLOT(btn_improt()));
    connect(m_btn_save, SIGNAL(clicked()), this, SLOT(btn_save()));

    connect(m_btn_l_l, SIGNAL(clicked()), this, SLOT(btn_l_l()));
    connect(m_btn_l_ll, SIGNAL(clicked()), this, SLOT(btn_l_ll()));
    connect(m_btn_l_r, SIGNAL(clicked()), this, SLOT(btn_l_r()));
    connect(m_btn_l_rr, SIGNAL(clicked()), this, SLOT(btn_l_rr()));
    connect(m_btn_l_u, SIGNAL(clicked()), this, SLOT(btn_l_u()));
    connect(m_btn_l_uu, SIGNAL(clicked()), this, SLOT(btn_l_uu()));
    connect(m_btn_l_d, SIGNAL(clicked()), this, SLOT(btn_l_d()));
    connect(m_btn_l_dd, SIGNAL(clicked()), this, SLOT(btn_l_dd()));

    connect(m_btn_r_l, SIGNAL(clicked()), this, SLOT(btn_r_l()));
    connect(m_btn_r_ll, SIGNAL(clicked()), this, SLOT(btn_r_ll()));
    connect(m_btn_r_r, SIGNAL(clicked()), this, SLOT(btn_r_r()));
    connect(m_btn_r_rr, SIGNAL(clicked()), this, SLOT(btn_r_rr()));
    connect(m_btn_r_u, SIGNAL(clicked()), this, SLOT(btn_r_u()));
    connect(m_btn_r_uu, SIGNAL(clicked()), this, SLOT(btn_r_uu()));
    connect(m_btn_r_d, SIGNAL(clicked()), this, SLOT(btn_r_d()));
    connect(m_btn_r_dd, SIGNAL(clicked()), this, SLOT(btn_r_dd()));
}

SettingDialog::~SettingDialog()
{
    if (m_image)
    {
        delete m_image;
    }
}

void SettingDialog::initOffset()
{
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        m_offset[i].m_left = 0;
        m_offset[i].m_top = 0;
        m_offset[i].m_right = 0;
    }
}

void SettingDialog::btn_open()
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
        m_image = 0;
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("图像宽度不为7632，请重新选择图像"));
        return;
    }
    initOffset();
    updateImage();
}

void SettingDialog::btn_save()
{
    QSettings setting("config.ini", QSettings::IniFormat);
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        setting.setValue("channel" + QString::number(i) + "/top", m_offset[i].m_top);
        setting.setValue("channel" + QString::number(i) + "/left", m_offset[i].m_left);
        setting.setValue("channel" + QString::number(i) + "/right", m_offset[i].m_right);
    }

    QMessageBox::information(0, QStringLiteral("提示"), QStringLiteral("拼接数据导出完成。"));
}

void SettingDialog::h_offset(bool isLeft, int offset)
{
    int index = m_cb_channel->currentIndex();
    if (isLeft)
    {
        if ((int)m_offset[index].m_right + offset < 0)
        {
            m_offset[index].m_right = 0;
        }
        else
        {
            m_offset[index].m_right += offset;
        }
    }
    else
    {
        if ((int)m_offset[index + 1].m_left + offset < 0)
        {
            m_offset[index + 1].m_left = 0;
        }
        else
        {
            m_offset[index + 1].m_left += offset;
        }
    }
    updateImage();
}

void SettingDialog::v_offset(bool isLeft, int offset)
{
    int index = m_cb_channel->currentIndex();
    int top[CHANNEL_NUM];
    for (int i = 0; i < CHANNEL_NUM; i++)
    {
        top[i] = m_offset[i].m_top;
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

void SettingDialog::updateImage()
{
    if (!m_image)
    {
        return;
    }
    int index = m_cb_channel->currentIndex();
    int w = SIGNGLE_WIDTH * 2 - m_offset[index].m_right - m_offset[index + 1].m_left;
    w = (w + 3) / 4 * 4;
    int hh = m_image->height();
    int h = hh + abs((int)m_offset[index].m_top - (int)m_offset[index + 1].m_top);

    int w_l = SIGNGLE_WIDTH - m_offset[index].m_right;
    int w_r = SIGNGLE_WIDTH - m_offset[index + 1].m_left;

    unsigned char* data = new unsigned char[w * h];
    unsigned char* src_ptr1 = m_image->bits() + index * SIGNGLE_WIDTH;
    unsigned char* src_ptr2 = m_image->bits() + (index + 1) * SIGNGLE_WIDTH + m_offset[index + 1].m_left;
    unsigned char* dst_ptr1;
    unsigned char* dst_ptr2;
    if (m_offset[index].m_top > m_offset[index + 1].m_top)
    {
        dst_ptr1 = data;
        dst_ptr2 =data + w_l + (m_offset[index].m_top - m_offset[index + 1].m_top) * w;
    }
    else
    {
        dst_ptr1 = data + (m_offset[index + 1].m_top - m_offset[index].m_top) * w;
        dst_ptr2 = data + w_l;
    }

    for (int i = 0; i < hh; i++)
    {
        memcpy(dst_ptr1, src_ptr1, w_l);
        memcpy(dst_ptr2, src_ptr2, w_r);
        dst_ptr1 += w;
        dst_ptr2 += w;

        src_ptr1 += SIGNGLE_WIDTH * CHANNEL_NUM;
        src_ptr2 += SIGNGLE_WIDTH * CHANNEL_NUM;
    }

    QImage img(data, w, h, QImage::Format_Indexed8);
    m_scene->clear();
    m_scene->setSceneRect(img.rect());
    m_scene->addPixmap(QPixmap::fromImage(img));
    int v = (m_view->horizontalScrollBar()->maximum() - m_view->horizontalScrollBar()->minimum() - w_r + w_l) / 2;
    m_view->horizontalScrollBar()->setValue(v);

    delete [] data;
}

void SettingDialog::btn_l_l()
{
    if (!m_image)
    {
        return;
    }

    h_offset(true, -1);
}

void SettingDialog::btn_l_ll()
{
    if (!m_image)
    {
        return;
    }

    h_offset(true, -10);
}

void SettingDialog::btn_l_u()
{
    if (!m_image)
    {
        return;
    }
    v_offset(true, 1);
}

void SettingDialog::btn_l_uu()
{
    if (!m_image)
    {
        return;
    }
    v_offset(true, 10);
}

void SettingDialog::btn_l_r()
{
    if (!m_image)
    {
        return;
    }

    h_offset(true, 1);
}

void SettingDialog::btn_l_rr()
{
    if (!m_image)
    {
        return;
    }

    h_offset(true, 10);
}

void SettingDialog::btn_l_d()
{
    if (!m_image)
    {
        return;
    }

    v_offset(true, -1);
}

void SettingDialog::btn_l_dd()
{
    if (!m_image)
    {
        return;
    }

    v_offset(true, -10);
}

void SettingDialog::btn_r_l()
{
    if (!m_image)
    {
        return;
    }

    h_offset(false, 1);
}

void SettingDialog::btn_r_ll()
{
    if (!m_image)
    {
        return;
    }

    h_offset(false, 10);
}

void SettingDialog::btn_r_u()
{
    if (!m_image)
    {
        return;
    }

    v_offset(false, 1);
}

void SettingDialog::btn_r_uu()
{
    if (!m_image)
    {
        return;
    }
    v_offset(false, 10);

}

void SettingDialog::btn_r_r()
{
    if (!m_image)
    {
        return;
    }

    h_offset(false, -1);
}

void SettingDialog::btn_r_rr()
{
    if (!m_image)
    {
        return;
    }

    h_offset(false, -10);
}

void SettingDialog::btn_r_d()
{
    if (!m_image)
    {
        return;
    }

    v_offset(false, -1);
}

void SettingDialog::btn_r_dd()
{
    if (!m_image)
    {
        return;
    }

    v_offset(false, -10);
}

void SettingDialog::indexChanged(int)
{
    if (!m_image)
    {
        return;
    }

    updateImage();
}

void SettingDialog::btn_improt()
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
