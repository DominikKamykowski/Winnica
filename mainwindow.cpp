#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Dane/order.hpp"
#include "Dane/ordermanager.hpp"
#include <QList>
#include <QDebug>
#include "orderprinter.hpp"
#include "ingredientmanager.hpp"
#include "assortmentmanager.hpp"
#include <QVector>
#include "Dane/assortment.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    newOrderDialog = new AddNewOrder();
    newIngredientDialog = new AddNewIngredient();
    // assortmentManager = new AssortmentManager();
    assortmentManager = AssortmentManager::getInstance();
    addNewAssortmentDialog = new AddNewAssortment();
    plik = new QMenu("Plik",this);
    print = new QMenu("Drukuj");
    printOrders = new QAction("Zamówienia");
    printDrinks = new QAction("Napoje");
    printIngredients = new QAction("Składniki");

    IngredientManager::Create("/home/dominik/Projekty/Projekt/ingredients.json");
    OrderManager::Create("/home/dominik/Projekty/Projekt/orders.json");
    orderManager = OrderManager::getInstance();

    print->addActions(QList<QAction*>{printOrders,printDrinks,printIngredients});
    plik->addMenu(print);
    menuBar()->addMenu(plik);
    prepareOrderTableWidget();
    prepareAssortmentTableWidget();

    ui->orderTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QObject::connect(ui->orderTableWidget,&QTableWidget::cellDoubleClicked,this,&MainWindow::cellClicked);
    QObject::connect(ui->pb_addNewOrder,&QPushButton::clicked,this,&MainWindow::addOrderClicked);
    QObject::connect(newOrderDialog,&QDialog::accepted,this,&MainWindow::orderSaved);
    QObject::connect(ui->pb_editOrder,&QPushButton::clicked,this,&MainWindow::editOrderClicked);
    QObject::connect(ui->pb_preparation,&QPushButton::clicked,this,&MainWindow::changeOrderStatusPrepared);
    QObject::connect(ui->pb_sended,&QPushButton::clicked,this,&MainWindow::changeOrderStatusShipped);
    QObject::connect(ui->pb_received,&QPushButton::clicked,this,&MainWindow::changeOrderStatusReceived);
    QObject::connect(ui->pb_printOrder,&QPushButton::clicked,this,&MainWindow::printOrderClicked);
    connect(ui->pb_addIngredient, &QPushButton::clicked, this, &MainWindow::addIngredientClicked);
    connect(ui->pb_editIngredient, &QPushButton::clicked, this, &MainWindow::editIngredientClicked);
    connect(newIngredientDialog, &QDialog::accepted, this, &MainWindow::ingredientSaved);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete addNewAssortmentDialog;
}

void MainWindow::prepareOrderTableWidget()
{
    ui->orderTableWidget->setColumnCount(7);
    ui->orderTableWidget->setHorizontalHeaderLabels({"ID", "Numer", "Zawartość", "Data sporządzenia", "Data nadania", "Status", "Data dostarczenia"});

    QList<Order> orders = orderManager->loadOrders();

    for (const Order &order : orders)
    {
        order.addToTable(ui->orderTableWidget);
    }

    ui->orderTableWidget->update();

    ui->ingredientTableWidget->setColumnCount(3);
    ui->ingredientTableWidget->setHorizontalHeaderLabels({"ID", "Składnik", "Ilość"});

    QList<Ingredient> ingredients = IngredientManager::getInstance()->loadIngredients();

    for (const Ingredient &ingredient : ingredients)
    {
        ingredient.addToTable(ui->ingredientTableWidget);
    }
    ui->ingredientTableWidget->update();

    // Przygotowanie tabeli asortymentów
    ui->assortmentTableWidget->setColumnCount(5);
    ui->assortmentTableWidget->setHorizontalHeaderLabels({"ID", "Nazwa", "Numer fabryczny", "Składniki", "Ilość"});

    refreshAssortmentTable();

    // Podłącz akcję otwierania okna dodawania nowego asortymentu
    connect(ui->addAssortmentButton, &QPushButton::clicked, this, &MainWindow::openAddNewAssortmentDialog);

    // Odśwież tabelę po zamknięciu dialogu dodawania/edycji
    connect(addNewAssortmentDialog, &AddNewAssortment::finished, this, &MainWindow::refreshAssortmentTable);
}


void MainWindow::prepareAssortmentTableWidget()
{
    // Konfiguracja tabeli dla asortymentu
    ui->assortmentTableWidget->setColumnCount(5);
    ui->assortmentTableWidget->setHorizontalHeaderLabels({"ID", "Nazwa", "Numer fabryczny", "Składniki", "Ilość"});

    // Pobieranie listy asortymentu z managera
    QList<Assortment> assortments = AssortmentManager::getInstance()->getAssortments();

    // Dodawanie danych do tabeli
    for (const Assortment &assortment : assortments)
    {
        int row = ui->assortmentTableWidget->rowCount();
        ui->assortmentTableWidget->insertRow(row);

        // Wypełnienie kolumn
        ui->assortmentTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(assortment.getId())));
        ui->assortmentTableWidget->setItem(row, 1, new QTableWidgetItem(assortment.getName()));
        ui->assortmentTableWidget->setItem(row, 2, new QTableWidgetItem(assortment.getFactoryNumber()));

        // Łączenie składników w jedną kolumnę
        QStringList ingredientsList = QStringList::fromVector(assortment.getIngredients());
        QString ingredientsString = ingredientsList.join(", ");
        ui->assortmentTableWidget->setItem(row, 3, new QTableWidgetItem(ingredientsString));

        ui->assortmentTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(assortment.getQuantity())));
    }

    // Aktualizacja widżetu tabeli
    ui->assortmentTableWidget->update();
}



void MainWindow::cellClicked(int row, int )
{
    newOrderDialog->editOrder(orderManager->getOrder(row));
}

void MainWindow::addOrderClicked()
{
    newOrderDialog->addOrder();
}

void MainWindow::editOrderClicked()
{
    if(ui->orderTableWidget->selectedItems().isEmpty())
    {
        ui->statusbar->showMessage("Brak wybranej pozycji do edycji",2000);
        return;
    }
    else
    {
        newOrderDialog->editOrder(orderManager->getOrder(ui->orderTableWidget->currentRow()));
    }
}

void MainWindow::orderSaved()
{
    QList<Order> orders = orderManager->loadOrders();

    ui->orderTableWidget->setRowCount(0);
    for (const Order &order : orders)
    {
        order.addToTable(ui->orderTableWidget);
    }
    ui->orderTableWidget->update();
}

void MainWindow::changeOrderStatusPrepared()
{
    if(ui->orderTableWidget->selectedItems().isEmpty())
    {
        ui->statusbar->showMessage("Brak wybranej pozycji do edycji",2000);
        return;
    }
    else
    {
        orderManager->updateOrderStatus(ui->orderTableWidget->currentRow(),Order::Status::Przygotowywane);
        orderSaved();
    }
}

void MainWindow::changeOrderStatusShipped()
{
    if(ui->orderTableWidget->selectedItems().isEmpty())
    {
        ui->statusbar->showMessage("Brak wybranej pozycji do edycji",2000);
        return;
    }
    if(orderManager->getOrder(ui->orderTableWidget->currentRow()).getStatusString().compare("Przygotowywane"))
    {
        ui->statusbar->showMessage("Nie można zmienić statusu paczki która nie jest przygotowana",2000);
        return;
    }
    else
    {
        orderManager->updateOrderStatus(ui->orderTableWidget->currentRow(),Order::Status::Nadane);
        orderSaved();
    }
}

void MainWindow::changeOrderStatusReceived()
{
    if(ui->orderTableWidget->selectedItems().isEmpty())
    {
        ui->statusbar->showMessage("Brak wybranej pozycji do edycji",2000);
        return;
    }
    if(orderManager->getOrder(ui->orderTableWidget->currentRow()).getStatusString().compare("Nadane"))
    {
        ui->statusbar->showMessage("Nie można zmienić statusu odebrania nie nadanego zamówienia",2000);
        return;
    }
    else
    {
        orderManager->updateOrderStatus(ui->orderTableWidget->currentRow(),Order::Status::Odebrane);
        orderSaved();
    }
}

void MainWindow::printOrderClicked()
{
    printOrder(ui->orderTableWidget->currentRow());
}

void MainWindow::printOrder(int id)
{
    OrderPrinter printer;
    bool success = printer.printOrderToPdf(orderManager->getOrder(id), "Order_12345.pdf");
}

void MainWindow::addIngredientClicked()
{
    newIngredientDialog->addIngredient();
}

void MainWindow::editIngredientClicked()
{
    if (ui->ingredientTableWidget->selectedItems().isEmpty())
    {
        ui->statusbar->showMessage("Nie wybrano składnika do edycji", 2000);
    }
    else {

            QString name = IngredientManager::getInstance()->getIngredient(ui->ingredientTableWidget->currentRow()+1).getName();
            int quantity = IngredientManager::getInstance()->getIngredient(ui->ingredientTableWidget->currentRow()+1).getStockQuantity();                // Pobierz ilość wybranego składnika
            newIngredientDialog->editIngredient(name, quantity);
    }
}

void MainWindow::ingredientSaved()
{
    ui->statusbar->showMessage("Składnik zapisany!", 2000);
    QList<Ingredient> ingredients = IngredientManager::getInstance()->loadIngredients();

    ui->ingredientTableWidget->setRowCount(0);
    for (const Ingredient &ingredient : ingredients)
    {
        ingredient.addToTable(ui->ingredientTableWidget);
    }
    ui->ingredientTableWidget->update();
}

void MainWindow::openAddNewAssortmentDialog()
{
    addNewAssortmentDialog->addAssortment();
}

void MainWindow::refreshAssortmentTable()
{
    ui->assortmentTableWidget->clearContents();
    ui->assortmentTableWidget->setRowCount(0); // Dodane czyszczenie wierszy
    QList<Assortment> assortments = assortmentManager->getAssortments();

    ui->assortmentTableWidget->setRowCount(assortments.size());
    int row = 0;
    for (const Assortment& assortment : assortments)
    {
        ui->assortmentTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(assortment.getId())));
        ui->assortmentTableWidget->setItem(row, 1, new QTableWidgetItem(assortment.getName()));
        ui->assortmentTableWidget->setItem(row, 2, new QTableWidgetItem(assortment.getFactoryNumber()));

        // Konwersja QVector<QString> na QStringList, aby użyć join
        QStringList ingredientsList = QStringList::fromVector(assortment.getIngredients());
        ui->assortmentTableWidget->setItem(row, 3, new QTableWidgetItem(ingredientsList.join(", ")));

        ui->assortmentTableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(assortment.getQuantity())));
        row++;
    }
    ui->assortmentTableWidget->update();
}



