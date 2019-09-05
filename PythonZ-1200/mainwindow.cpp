﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../usbDevice/usbdevice.h"
#include "assistant.h"

#include <QSettings>
#include <QButtonGroup>
#include <QFileDialog>
#include <QGraphicsScene>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <QImage>
#include <QDateTime>
#include <QMessageBox>

#define SINGLE_WIDTH 1272
#define COUNTOF_CHANNEL 6

using namespace std;

static Assistant m_assistant;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_image(nullptr),
    m_imageProcess(nullptr)
{
    ui->setupUi(this);
    initUI();

    QButtonGroup* btnGroup1 = new QButtonGroup(this);
    btnGroup1->addButton(ui->radio_bmp);
    btnGroup1->addButton(ui->radio_jpg);

    QButtonGroup* btnGroup2 = new QButtonGroup(this);
    btnGroup2->addButton(ui->radio_black);
    btnGroup2->addButton(ui->radio_white);

    initSettings();
    initUsbDevice();
    getCorrectData();
	getMontageData();
}

MainWindow::~MainWindow()
{
    saveSettings();
    stop_scan();
    close_usb();
    delete ui;
    if (m_image)
    {
        delete m_image;
        m_image = nullptr;
    }

    if (m_imageProcess)
    {
        delete m_imageProcess;
        m_imageProcess = nullptr;
    }
}

void MainWindow::on_btn_start_clicked()
{
    ui->btn_start->setEnabled(false);
    start_scan();
    ui->btn_stop->setEnabled(true);
    ui->lbl_status->setText(QStringLiteral("正在扫描(Scanning)"));
}

void MainWindow::on_btn_stop_clicked()
{
    ui->btn_stop->setEnabled(false);
    stop_scan();
    ui->lbl_status->setText(QStringLiteral("停止扫描(Stop)"));
}

void MainWindow::on_btn_save_clicked()
{
#if 1
    if (!m_image)
    {
        return;
    }
    QString filename = QFileDialog::getSaveFileName(this, QStringLiteral("保存图像"), "", tr("BITMAP (*.bmp);;JPEG(*.jpg)"));
    if (m_image->format() == QImage::Format_Indexed8)
    {
        for (int i = 0; i < 256; i++)
        {
            m_image->setColor(i, qRgb(i, i, i));
        }
    }
    m_image->save(filename);
#else

    QImage img("..\\bin\\debug\\1.jpg");
    showImage(img.bits(), img.byteCount());
#endif
}

void MainWindow::on_btn_zoomIn_clicked()
{
	ui->view->zoomIn();
}

void MainWindow::on_btn_zoomOut_clicked()
{
	ui->view->zoomOut();
}

void MainWindow::on_btn_original_clicked()
{
	ui->view->zoomOrigin();
}

void MainWindow::on_btn_adjust_clicked()
{
	ui->view->zoomAdjust();
}

void MainWindow::on_btn_dir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, QStringLiteral("保存路径"));

    if (dir.isEmpty())
    {
        return;
    }

    ui->lineEdt_dir->setText(dir);
}

void MainWindow::on_check_doubleExposure_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        set_exposure(false);
    }
    else if(arg1 == 2)
    {
        set_exposure(true);
    }
}

void MainWindow::on_hslider_optimize_valueChanged(int value)
{
    ui->lbl_optimize->setText(QStringLiteral("优化") + QString::number(value) + QStringLiteral("%"));
}

void MainWindow::on_spin_h_edit_finished()
{
    ui->spin_scale_h->setValue(ui->spin_plan_h->value() / ui->spin_actual_h->value());
}

void MainWindow::on_spin_v_edit_finished()
{
    ui->spin_scale_v->setValue(ui->spin_plan_v->value() / ui->spin_actual_v->value());
}

void MainWindow::on_check_montage_toggled(bool checked)
{
    if (!checked)
    {
        ui->check_contour->setChecked(false);
    }
}

void MainWindow::on_check_contour_toggled(bool checked)
{
    if (checked)
    {
        ui->check_montage->setChecked(true);
    }
}

bool MainWindow::nativeEvent(const QByteArray& eventType, void* message, long * result)
{
    (void)result;
    if (eventType != "windows_generic_MSG")
    {
        return false;
    }
    MSG* msg = static_cast<MSG*>(message);
    Device_Status ds = device_status(msg->message, msg->wParam, reinterpret_cast<void*>(msg->lParam));
    if (ds == connected)
    {
        initUsbDevice();
    }
    else if (ds == removed)
    {
        close_usb();
        ui->lbl_status->setText(QStringLiteral("设备未连接(Device is unconnected)"));
        ui->btn_start->setEnabled(false);
        ui->btn_stop->setEnabled(false);
    }
    return false;
}

void MainWindow::initUsbDevice()
{
    bool b = open_usb(MainWindow::callback_getPicInfo, MainWindow::callback_reciveMsg);
    if (b)
    {
        ui->lbl_status->setText(QStringLiteral("设备已连接(Device is connected)"));
        ui->btn_start->setEnabled(true);
        ui->btn_stop->setEnabled(false);
        ui->check_doubleExposure->setChecked(false);
    }
    else
    {
        ui->lbl_status->setText(QStringLiteral("设备未连接(Device is unconnected)"));
        ui->btn_start->setEnabled(false);
        ui->btn_stop->setEnabled(false);
    }
}

void MainWindow::initUI()
{
	ui->view->setScroll(ui->horizontalScrollBar, ui->verticalScrollBar);
    connect(ui->spin_plan_h, SIGNAL(editingFinished()), this, SLOT(on_spin_h_edit_finished()));
    connect(ui->spin_actual_h, SIGNAL(editingFinished()), this, SLOT(on_spin_h_edit_finished()));
    connect(ui->spin_plan_v, SIGNAL(editingFinished()), this, SLOT(on_spin_v_edit_finished()));
    connect(ui->spin_actual_v, SIGNAL(editingFinished()), this, SLOT(on_spin_v_edit_finished()));

    connect(&m_assistant, SIGNAL(sendpic(unsigned char*, long)), this, SLOT(showImage(unsigned char*, long)));
    connect(&m_assistant, SIGNAL(sendmsg(int)), this, SLOT(reciveMsg(int)));
}

void MainWindow::initSettings()
{
    QSettings setting("setting.ini", QSettings::IniFormat);
    ui->check_correct->setChecked(setting.value("settings/correct").toBool());
    ui->check_montage->setChecked(setting.value("settings/montage").toBool());
    ui->check_doubleExposure->setChecked(setting.value("settings/doubleExposure").toBool());
    ui->check_contour->setChecked(setting.value("settings/canny").toBool());
    ui->check_autoSave->setChecked(setting.value("settings/saveAuto").toBool());
    ui->lineEdt_dir->setText(setting.value("settings/dir").toString());
    ui->hslider_optimize->setValue(setting.value("settings/optimize").toInt());
    ui->spin_plan_h->setValue(setting.value("settings/scale_x1").toDouble());
    ui->spin_plan_v->setValue(setting.value("settings/scale_y1").toDouble());
    ui->spin_actual_h->setValue(setting.value("settings/scale_x2").toDouble());
    ui->spin_actual_v->setValue(setting.value("settings/scale_y2").toDouble());
    ui->spin_scale_h->setValue(setting.value("settings/scale_x").toDouble());
    ui->spin_scale_v->setValue(setting.value("settings/scale_y").toDouble());

    if (setting.value("settings/background").toBool())
    {
        ui->radio_black->setChecked(true);
    }
    else
    {
        ui->radio_white->setChecked(true);
    }
    if (setting.value("settings/save_format").toBool())
    {
        ui->radio_bmp->setChecked(true);
    }
    else
    {
        ui->radio_jpg->setChecked(true);
    }

    setLineCount(setting.value("settings/lineCount").toInt());
}

void MainWindow::saveSettings()
{
    QSettings setting("setting.ini", QSettings::IniFormat);
    setting.setValue("settings/correct", ui->check_correct->isChecked());
    setting.setValue("settings/montage", ui->check_montage->isChecked());
    setting.setValue("settings/doubleExposure", ui->check_doubleExposure->isChecked());
    setting.setValue("settings/canny", ui->check_contour->isChecked());
    setting.setValue("settings/saveAuto", ui->check_autoSave->isChecked());
    setting.setValue("settings/background", ui->radio_black->isChecked());
    setting.setValue("settings/save_format", ui->radio_bmp->isChecked());
    setting.setValue("settings/dir", ui->lineEdt_dir->text());
    setting.setValue("settings/optimize", ui->hslider_optimize->value());
    setting.setValue("settings/scale_x", ui->spin_scale_h->value());
    setting.setValue("settings/scale_y", ui->spin_scale_v->value());
    setting.setValue("settings/scale_x1", ui->spin_plan_h->value());
    setting.setValue("settings/scale_y1", ui->spin_plan_v->value());
    setting.setValue("settings/scale_x2", ui->spin_actual_h->value());
    setting.setValue("settings/scale_y2", ui->spin_actual_v->value());
}

void MainWindow::getCorrectData()
{
    ifstream f("correctData.dat", ios::binary | ios::in);

    if (!f.is_open())
    {
        f.close();
        return;
    }

    unsigned char* m_buffer_black = new unsigned char[SINGLE_WIDTH * COUNTOF_CHANNEL];
    unsigned char* m_buffer_white = new unsigned char[SINGLE_WIDTH * COUNTOF_CHANNEL];

    f.read(reinterpret_cast<char*>(m_buffer_black), SINGLE_WIDTH * COUNTOF_CHANNEL);
    f.read(reinterpret_cast<char*>(m_buffer_white), SINGLE_WIDTH * COUNTOF_CHANNEL);

    f.close();

    if (m_imageProcess != nullptr)
    {
        delete m_imageProcess;
    }
    m_imageProcess = new ImageProcess;
    m_imageProcess->setCorrectData(m_buffer_black, m_buffer_white, SINGLE_WIDTH * COUNTOF_CHANNEL);

    delete [] m_buffer_black;
    delete [] m_buffer_white;
}

void MainWindow::getMontageData()
{
	QSettings setting("config.ini", QSettings::IniFormat);

	for (int i = 0; i < COUNTOF_CHANNEL; i++)
	{
		offsets[i].m_top = setting.value("channel" + QString::number(i) + "/top").toInt();
		offsets[i].m_left = setting.value("channel" + QString::number(i) + "/left").toInt();
		offsets[i].m_right = setting.value("channel" + QString::number(i) + "/right").toInt();
	}
}

void MainWindow::callback_getPicInfo(unsigned char* buffer, long length)
{
    m_assistant.sendPicInfo(buffer, length);
}

void MainWindow::callback_reciveMsg(int msg)
{
    m_assistant.sendMessage(msg);
}

void MainWindow::showImage(unsigned char* buffer, long length)
{
    unsigned char* new_buffer = new unsigned char[static_cast<unsigned int>(length)];
    memcpy(new_buffer, buffer, static_cast<unsigned int>(length));
    int width = single_width() * count_of_channel();
    int height = length / width;
    if (m_image)
    {
		delete[] m_image->bits();
        delete m_image;
        m_image = nullptr;
    }

    m_imageProcess->setWidth(width);
    m_imageProcess->setHeight(height);
    m_imageProcess->setData(new_buffer);
    m_imageProcess->setBiXPelsPerMeter(8859);
    m_imageProcess->setBiYPelsPerMeter(8859);
    if (ui->check_correct->isChecked())
    {
        m_imageProcess->correct();
    }

	ui->view->addPolygons(QVector<QVector<QPointF>>());
    if (ui->check_montage->isChecked())
    {
		ImageProcess newImg;
		m_imageProcess->montage(offsets, newImg);
		delete[] m_imageProcess->bits();

        if (newImg.bits() == nullptr)
        {
            ui->btn_start->setEnabled(true);
            return;
        }

		ImageProcess zoomImage;
		newImg.zoom(ui->spin_scale_h->value(), ui->spin_scale_v->value(), zoomImage);

		unsigned char* buffer = new unsigned char[static_cast<unsigned int>(zoomImage.width() * zoomImage.height())];
		memcpy(buffer, zoomImage.bits(), static_cast<unsigned int>(zoomImage.width() * zoomImage.height()));
        m_image = new QImage(buffer, zoomImage.width(), zoomImage.height(), QImage::Format_Indexed8);

        if (ui->check_contour->isChecked())
        {
            int thre = ui->radio_black->isChecked() ? 80 : 160;

            vector<vector<HTS_Point>> contours;
			QVector<QVector<QPointF>> polygons;
            zoomImage.findContour(contours, thre, 400, ui->radio_black->isChecked(), ui->hslider_optimize->value());

            for (size_t i = 0, length = contours.size(); i < length; ++i)
            {
                QVector<QPointF> points;
                for (size_t j = 0, total = contours[i].size(); j < total; ++j)
                {
                    points.append(QPointF(contours[i][j].x, contours[i][j].y));
                }
				polygons.append(points);
            }
			ui->view->addPolygons(polygons);
        }
    }
    else
    {
		ImageProcess zoomImg;
		m_imageProcess->zoom(ui->spin_scale_h->value(), ui->spin_scale_v->value(), zoomImg);
		delete[] m_imageProcess->bits();
        unsigned char* buffer = new unsigned char[static_cast<size_t>(zoomImg.width() * zoomImg.height())];
        memcpy(buffer, zoomImg.bits(), static_cast<size_t>(zoomImg.width() * zoomImg.height()));
        m_image = new QImage(buffer, zoomImg.width(), zoomImg.height(), QImage::Format_Indexed8);
        m_image->setDotsPerMeterX(zoomImg.getBiXPelsPerMeter());
        m_image->setDotsPerMeterY(zoomImg.getBiYPelsPerMeter());
    }
	ui->view->addImage(m_image);
    if (ui->check_autoSave->isChecked())
    {
        for (int i = 0; i < 256; i++)
        {
            m_image->setColor(i, qRgb(i, i, i));
        }
        QString foramt;
        if (ui->radio_bmp->isChecked())
        {
            foramt = ".bmp";
        }
        else
        {
            foramt = ".jpg";
        }
        m_image->setDotsPerMeterX(150);
        QDir dir(ui->lineEdt_dir->text());
        if  (dir.exists())
        {
            m_image->save(ui->lineEdt_dir->text() + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + foramt);
        }
        else
        {
            QMessageBox::warning(this, QStringLiteral("提示"), ui->lineEdt_dir->text() + QStringLiteral("不存在，无法保存图像。"), QMessageBox::Yes);
        }
    }

    if (is_open())
    {
        ui->btn_start->setEnabled(true);
        ui->btn_save->setEnabled(true);
    }
    ui->btn_zoomIn->setEnabled(true);
    ui->btn_zoomOut->setEnabled(true);
    ui->btn_adjust->setEnabled(true);
    ui->btn_original->setEnabled(true);
    ui->lbl_status->setText(QStringLiteral("扫描完成(Finished)"));
}

void MainWindow::reciveMsg(int msg)
{	if (msg == 0)
    {
        on_btn_start_clicked();
    }
    else if (msg == 1)
    {
        on_btn_stop_clicked();
    }
}