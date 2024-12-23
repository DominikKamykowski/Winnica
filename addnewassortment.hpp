#ifndef ADDNEWASSORTMENT_HPP
#define ADDNEWASSORTMENT_HPP

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>

class AddNewAssortment : public QDialog
{
    Q_OBJECT
public:
    explicit AddNewAssortment(QDialog *parent = nullptr);
    void addAssortment();
    void editAssortment(int id, const QString& name, const QString& factoryNumber, const QStringList& ingredients, int quantity);

private:
    void createView();

    QVBoxLayout* mainLayout = nullptr;
    QLineEdit* nameEdit = nullptr;
    QLineEdit* factoryNumberEdit = nullptr;
    QTextEdit* ingredientsEdit = nullptr;
    QSpinBox* quantitySpinBox = nullptr;
    QPushButton* saveButton = nullptr;
    QPushButton* cancelButton = nullptr;
    int editingAssortmentId = -1;

    void saveClicked();
    void discardClicked();
};

#endif // ADDNEWASSORTMENT_HPP
