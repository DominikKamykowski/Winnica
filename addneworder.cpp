#include "addneworder.hpp"
#include "Dane/ordermanager.hpp"
#include "Dane/order.hpp"

AddNewOrder::AddNewOrder(QDialog *parent)
    : QDialog{parent}
{
    createView();
    QObject::connect(pb_save,&QPushButton::clicked, this, &AddNewOrder::saveClicked);
    QObject::connect(pb_discard,&QPushButton::clicked, this, &AddNewOrder::discardClicked);
}

void AddNewOrder::addOrder()
{
    editingOrderId = -1;
    id_spinbox->setValue(OrderManager::getInstance()->getLastOrderId() + 1);
    show();
}

void AddNewOrder::editOrder(const Order &order)
{
    editingOrderId = order.getId();
    show();

    id_spinbox->setValue(order.getId());
    le_nr->setText(order.getFactoryNumber());
    le_el->setText(order.getItems());
    cal_createDate->setSelectedDate(order.getCreationDate());
    cal_createDate->setEnabled(false);

    if (order.getShippingDate().isValid()) {
        cb_shippingDateEnabled->setChecked(true);
        cal_shippingDate->setSelectedDate(order.getShippingDate());
    } else {
        cb_shippingDateEnabled->setChecked(false);
    }

    if (order.getDeliveryDate().isValid()) {
        cb_deliveryDateEnabled->setChecked(true);
        cal_deliveryDate->setSelectedDate(order.getDeliveryDate());
    } else {
        cb_deliveryDateEnabled->setChecked(false);
    }

    cb_status->setCurrentIndex(order.getStatus());
}

void AddNewOrder::createView()
{
    this->setWindowTitle("Zamówienia");

    main_layout = new QVBoxLayout();
    this->setLayout(main_layout);

    //ID
    ID_layout = new QHBoxLayout();
    id_spinbox = new QSpinBox(this);
    id_spinbox->setEnabled(false);
    ID_layout->addWidget(id);
    ID_layout->addWidget(id_spinbox);
    main_layout->addLayout(ID_layout);

    //Numer
    Nr_layout = new QHBoxLayout();
    le_nr = new QLineEdit("Numer",this);
    Nr_layout->addWidget(lb_nr);
    Nr_layout->addWidget(le_nr);
    main_layout->addLayout(Nr_layout);

    //Elementy
    el_layout = new QHBoxLayout();
    le_el = new QLineEdit(this);
    el_layout->addWidget(lb_el);
    el_layout->addWidget(le_el);
    main_layout->addLayout(el_layout);

    //Data sporządzenia
    createDate_layout = new QHBoxLayout();
    cal_createDate = new QCalendarWidget(this);
    cal_createDate->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    createDate_layout->addWidget(lb_createDate);
    createDate_layout->addWidget(cal_createDate);
    main_layout->addLayout(createDate_layout);

    // Status
    status_layout = new QHBoxLayout();
    cb_status = new QComboBox(this);
    cb_status->addItems({"Nowe", "Przygotowywane", "Nadane", "Odebrane", "Zagubione"});
    status_layout->addWidget(lb_status);
    status_layout->addWidget(cb_status);
    main_layout->addLayout(status_layout);

    // Data wysyłki
    shippingDate_layout = new QHBoxLayout();
    cb_shippingDateEnabled = new QCheckBox("Ustaw datę wysyłki", this);
    cb_shippingDateEnabled->setChecked(false); // Domyślnie odznaczone
    cal_shippingDate = new QCalendarWidget(this);
    cal_shippingDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cal_shippingDate->setEnabled(false); // Kalendarz domyślnie wyłączony
    shippingDate_layout->addWidget(cb_shippingDateEnabled);
    shippingDate_layout->addWidget(cal_shippingDate);
    main_layout->addLayout(shippingDate_layout);

    // Połącz checkbox z kalendarzem
    connect(cb_shippingDateEnabled, &QCheckBox::toggled, cal_shippingDate, &QCalendarWidget::setEnabled);


    // Data dostawy
    deliveryDate_layout = new QHBoxLayout();
    cb_deliveryDateEnabled = new QCheckBox("Ustaw datę dostawy", this);
    cb_deliveryDateEnabled->setChecked(false); // Domyślnie odznaczone
    cal_deliveryDate = new QCalendarWidget(this);
    cal_deliveryDate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cal_deliveryDate->setEnabled(false); // Kalendarz domyślnie wyłączony
    deliveryDate_layout->addWidget(cb_deliveryDateEnabled);
    deliveryDate_layout->addWidget(cal_deliveryDate);
    main_layout->addLayout(deliveryDate_layout);

    // Połącz checkbox z kalendarzem
    connect(cb_deliveryDateEnabled, &QCheckBox::toggled, cal_deliveryDate, &QCalendarWidget::setEnabled);

    //Nav
    nav_layout =new QHBoxLayout();
    nav_layout->addWidget(pb_save);
    nav_layout->addWidget(pb_discard);
    main_layout->addLayout(nav_layout);
}

void AddNewOrder::saveClicked()
{
    if (le_el->text().isEmpty())
    {
        le_el->setStyleSheet("color: red");
        le_el->setText("Pole wymagane!");
        return;
    }
    if (le_nr->text().isEmpty())
    {
        le_nr->setStyleSheet("color: red");
        le_nr->setText("Pole wymagane!");
        return;
    }

    QDate shippingDate = cb_shippingDateEnabled->isChecked() ? cal_shippingDate->selectedDate() : QDate();
    QDate deliveryDate = cb_deliveryDateEnabled->isChecked() ? cal_deliveryDate->selectedDate() : QDate();

    OrderManager *manager = OrderManager::getInstance();

    Order newOrder(
        id_spinbox->value(),
        le_nr->text(),
        le_el->text(),
        cal_createDate->selectedDate(),
        static_cast<Order::Status>(cb_status->currentIndex()),
        shippingDate,
        deliveryDate
        );

    if (editingOrderId == -1) // Nowe zamówienie
    {
        manager->appendOrder(newOrder);
    }
    else // Edycja istniejącego zamówienia
    {
        manager->updateOrder(newOrder);
    }

    accept();
    cal_createDate->setEnabled(true);
}

void AddNewOrder::discardClicked()
{
    editingOrderId = -1; // Resetuj tryb
    hide();
}
