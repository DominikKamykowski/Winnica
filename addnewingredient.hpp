#ifndef ADDNEWINGREDIENT_HPP
#define ADDNEWINGREDIENT_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

class AddNewIngredient : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewIngredient(QDialog *parent = nullptr);
    void addIngredient();
    void editIngredient(const int id, const QString& name, int quantity);

private:
    void createView();

    QVBoxLayout* mainLayout = nullptr;
    QSpinBox* idSpinBox = nullptr;
    QLineEdit* nameEdit = nullptr;
    QDoubleSpinBox* quantitySpinBox = nullptr;
    QPushButton* saveButton = nullptr;
    QPushButton* cancelButton = nullptr;
    int editingIngredientId = -1;
    int editId = 0;
    void saveClicked();
    void discardClicked();

    QString editingName = ""; // Pusty, jeśli dodajemy nowy składnik
};

#endif // ADDNEWINGREDIENT_HPP
