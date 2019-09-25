#include "previewdialog.h"
#include "ui_previewdialog.h"

PreviewDialog::PreviewDialog(QImage* img, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviewDialog)
{
    ui->setupUi(this);
    ui->view->setScroll(ui->horizontalScrollBar, ui->verticalScrollBar);
    this->setWindowFlags(Qt::Dialog | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    if (img != nullptr)
        ui->view->addImage(img);
}

PreviewDialog::~PreviewDialog()
{
    delete ui;
}

void PreviewDialog::on_btn_zoomin_clicked()
{
    ui->view->zoomIn();
}

void PreviewDialog::on_btn_zoomout_clicked()
{
    ui->view->zoomOut();
}

void PreviewDialog::on_btn_zoomorign_clicked()
{
    ui->view->zoomOrigin();
}

void PreviewDialog::on_btn_zoomfit_clicked()
{
    ui->view->zoomAdjust();
}
