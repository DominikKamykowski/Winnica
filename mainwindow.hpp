#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "Dane/ordermanager.hpp"
#include "addneworder.hpp"
#include "addnewingredient.hpp"
#include "addnewassortment.hpp"
#include "assortmentmanager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openAddNewAssortmentDialog();
    void refreshAssortmentTable();

private:
    Ui::MainWindow *ui;
    QMenu * plik = nullptr;
    QMenu * print = nullptr;
    QAction * printOrders = nullptr, *printDrinks = nullptr, *printIngredients = nullptr;

    void prepareOrderTableWidget();
    void prepareAssortmentTableWidget();
    void cellClicked(int row, int column);
    OrderManager* orderManager = nullptr;

    AddNewOrder * newOrderDialog = nullptr;
    void addOrderClicked();
    void editOrderClicked();
    void orderSaved();
    void changeOrderStatusPrepared();
    void changeOrderStatusShipped();
    void changeOrderStatusReceived();
    void printOrderClicked();
    void printOrder(int id);

    AddNewIngredient* newIngredientDialog = nullptr;
    AddNewAssortment* addNewAssortmentDialog = nullptr;
    AssortmentManager* assortmentManager = nullptr;

    void addIngredientClicked();
    void editIngredientClicked();
    void ingredientSaved();

};
#endif // MAINWINDOW_HPP
