#include "addnewassortment.hpp"
#include "Dane/assortment.hpp"
#include "assortmentmanager.hpp"

AddNewAssortment::AddNewAssortment(QDialog* parent)
    : QDialog(parent)
{
    createView();
    connect(saveButton, &QPushButton::clicked, this, &AddNewAssortment::saveClicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddNewAssortment::discardClicked);
}

void AddNewAssortment::createView()
{
    mainLayout = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    factoryNumberEdit = new QLineEdit(this);
    ingredientsEdit = new QTextEdit(this);
    quantitySpinBox = new QSpinBox(this);
    quantitySpinBox->setRange(0, 1000);
    saveButton = new QPushButton("Zapisz", this);
    cancelButton = new QPushButton("Anuluj", this);

    mainLayout->addWidget(new QLabel("Nazwa asortymentu", this));
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(new QLabel("Numer fabryczny", this));
    mainLayout->addWidget(factoryNumberEdit);
    mainLayout->addWidget(new QLabel("Składniki (oddzielone przecinkami)", this));
    mainLayout->addWidget(ingredientsEdit);
    mainLayout->addWidget(new QLabel("Ilość", this));
    mainLayout->addWidget(quantitySpinBox);
    mainLayout->addWidget(saveButton);
    mainLayout->addWidget(cancelButton);
}

void AddNewAssortment::addAssortment()
{
    editingAssortmentId = -1;
    nameEdit->clear();
    factoryNumberEdit->clear();
    ingredientsEdit->clear();
    quantitySpinBox->setValue(0);
    show();
}

void AddNewAssortment::editAssortment(int id, const QString& name, const QString& factoryNumber, const QStringList& ingredients, int quantity)
{
    editingAssortmentId = id;
    nameEdit->setText(name);
    factoryNumberEdit->setText(factoryNumber);
    ingredientsEdit->setPlainText(ingredients.join(", "));
    quantitySpinBox->setValue(quantity);
    show();
}

void AddNewAssortment::saveClicked()
{
    if (nameEdit->text().isEmpty() || factoryNumberEdit->text().isEmpty()) {
        nameEdit->setStyleSheet("border: 1px solid red");
        factoryNumberEdit->setStyleSheet("border: 1px solid red");
        return;
    }

    auto manager = AssortmentManager::getInstance();

    QStringList ingredientList = ingredientsEdit->toPlainText().split(",", Qt::SkipEmptyParts);
    for (QString& ingredient : ingredientList) {
        ingredient = ingredient.trimmed();
    }

    Assortment newAssortment(
        editingAssortmentId == -1 ? manager->getNextId() : editingAssortmentId,
        nameEdit->text(),
        factoryNumberEdit->text(),
        ingredientList.toVector(),
        quantitySpinBox->value()
        );

    if (editingAssortmentId == -1) {
        manager->appendAssortment(newAssortment);
    } else {
        manager->updateAssortment(newAssortment);
    }
    accept();
}

void AddNewAssortment::discardClicked()
{
    editingAssortmentId = -1; // Resetuj tryb
    reject(); // Anuluj zmiany
}
