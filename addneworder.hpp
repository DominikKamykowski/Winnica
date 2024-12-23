#ifndef ADDNEWORDER_HPP
#define ADDNEWORDER_HPP

#include <QDialog>
#include <QObject>
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "qpushbutton.h"
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QCalendarWidget>
#include "Dane/order.hpp"
#include <QComboBox>
#include <QCheckBox>

class AddNewOrder : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewOrder(QDialog *parent = nullptr);
    void addOrder();
    void editOrder(const Order& order);


private:
    void createView();
    QVBoxLayout * main_layout = nullptr;

    //ID
    QHBoxLayout * ID_layout = nullptr;
    QLabel * id = new QLabel("ID",this);
    QSpinBox * id_spinbox = nullptr;

    //Numer
    QHBoxLayout * Nr_layout = nullptr;
    QLabel * lb_nr = new QLabel("Numer",this);
    QLineEdit * le_nr = nullptr;

    //Elementy
    QHBoxLayout * el_layout = nullptr;
    QLabel * lb_el = new QLabel("Elementy",this);
    QLineEdit * le_el = nullptr;

    //Data sporządzenia
    QHBoxLayout * createDate_layout = nullptr;
    QLabel * lb_createDate = new QLabel("Data utworzenia",this);
    QCalendarWidget * cal_createDate = nullptr;

    //Data nadania
    QHBoxLayout * sendDate_layout = nullptr;
    QLabel * lb_sendDate = nullptr;
    QCalendarWidget * cal_sendDate = nullptr;

    //Status
    QHBoxLayout * status_layout = nullptr;
    QComboBox * cb_status = nullptr;
    QLabel * lb_status = new QLabel("Status",this);

    //Data wysyłki
    QHBoxLayout * shippingDate_layout = nullptr;
    QCheckBox * cb_shippingDateEnabled= nullptr;
    // QLabel * lb_shippingDate = new QLabel("Data wysyłki",this);
    QCalendarWidget * cal_shippingDate = nullptr;

    //Data dostawy
    QHBoxLayout * deliveryDate_layout = nullptr;
    // QLabel * lb_deliveryDate = new QLabel("Data dostawy",this);
    QCheckBox * cb_deliveryDateEnabled = nullptr;
    QCalendarWidget * cal_deliveryDate = nullptr;

    //Nawigacja
    QHBoxLayout * nav_layout = nullptr;
    QPushButton* pb_save = new QPushButton("Zapisz",this);
    QPushButton* pb_discard = new QPushButton("Anuluj",this);
    void saveClicked();
    void discardClicked();

    int editingOrderId = -1;

};

#endif // ADDNEWORDER_HPP
