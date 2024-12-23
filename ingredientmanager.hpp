#ifndef INGREDIENTMANAGER_HPP
#define INGREDIENTMANAGER_HPP

#include <QList>
#include <QString>
#include "Dane/ingredient.hpp"

class IngredientManager
{
public:
    static void Create(const QString &filename);
    static void Destroy();
    static IngredientManager* getInstance();

    void saveIngredients(const QList<Ingredient> &ingredients) const;
    QList<Ingredient> loadIngredients();
    void appendIngredient(const Ingredient &ingredient);
    Ingredient getIngredient(int id);
    bool updateIngredient(const Ingredient &updatedIngredient);

    void resetIngredients() {
        ingredients.clear();
        lastId = 0;
    }

    int getNextId() {
        return ++lastId; // Zwiększanie i zwracanie ID
    }

private:
    QList<Ingredient> ingredients;
    int lastId = 0; // Ostatnie wygenerowane ID

    static IngredientManager *instance;
    QString filename;

    IngredientManager(const QString &filename) : filename(filename) {}
};

#endif // INGREDIENTMANAGER_HPP
