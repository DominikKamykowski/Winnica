#include "addnewingredient.hpp"
#include "Dane/ingredient.hpp"
#include "ingredientmanager.hpp"

AddNewIngredient::AddNewIngredient(QDialog* parent)
    : QDialog(parent)
{
    createView();
    connect(saveButton, &QPushButton::clicked, this, &AddNewIngredient::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddNewIngredient::discardClicked);
}

void AddNewIngredient::createView()
{
    mainLayout = new QVBoxLayout(this);
    nameEdit = new QLineEdit(this);
    quantitySpinBox = new QDoubleSpinBox(this);
    quantitySpinBox->setRange(0, 1000);
    saveButton = new QPushButton("Zapisz", this);
    cancelButton = new QPushButton("Anuluj", this);

    mainLayout->addWidget(new QLabel("Nazwa składnika", this));
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(new QLabel("Ilość", this));
    mainLayout->addWidget(quantitySpinBox);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);
}

void AddNewIngredient::addIngredient()
{
    editingIngredientId = -1;
    nameEdit->clear();
    quantitySpinBox->setValue(0);
    show();
}

void AddNewIngredient::editIngredient(const QString& name, int quantity)
{
    editingIngredientId = 1;
    editingName = name;
    nameEdit->setText(name);
    quantitySpinBox->setValue(quantity);
    show();
}

void AddNewIngredient::saveClicked()
{
    if (nameEdit->text().isEmpty()) {
        nameEdit->setStyleSheet("border: 1px solid red");
        return;
    }
    auto manager = IngredientManager::getInstance();

    Ingredient newIngredient(
        manager->getNextId(),
        nameEdit->text(),
        quantitySpinBox->value()
        );

    if (editingIngredientId == -1) {
        manager->appendIngredient(newIngredient);
    }
    else // Edycja istniejącego zamówienia
    {
        manager->updateIngredient(newIngredient);
    }
    accept();

}

void AddNewIngredient::discardClicked()
{
    editingIngredientId = -1; // Resetuj tryb
    reject(); // Anuluj zmiany
}
