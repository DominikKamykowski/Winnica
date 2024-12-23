#ifndef ORDERPRINTER_HPP
#define ORDERPRINTER_HPP

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include "Dane/order.hpp"

class OrderPrinter
{
public:
    explicit OrderPrinter(const QString &outputDirectory = "./");
    bool printOrderToPdf(const Order &order, const QString &defaultFileName = "Zamowienie.pdf");

private:
    QString outputDirectory;
};

#endif // ORDERPRINTER_HPP
