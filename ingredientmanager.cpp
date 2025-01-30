#include "ingredientmanager.hpp"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

IngredientManager *IngredientManager::instance = nullptr;

void IngredientManager::Create(const QString &filename)
{
    if (!instance)
        instance = new IngredientManager(filename);
}

void IngredientManager::Destroy()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

IngredientManager* IngredientManager::getInstance()
{
    return instance;
}

void IngredientManager::saveIngredients(const QList<Ingredient> &ingredients) const
{
    QJsonArray jsonArray;
    for (const Ingredient &ingredient : ingredients)
        jsonArray.append(ingredient.toJson());

    QJsonDocument doc(jsonArray);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.close();
    }
}

QList<Ingredient> IngredientManager::loadIngredients()
{
    QList<Ingredient> ingredients;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        lastId=0;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray array = doc.array();
        for (const auto &value : array)
        {
            ingredients.append(Ingredient::fromJson(value.toObject()));
            lastId++;
        }

        file.close();
    }
    return ingredients;
}

void IngredientManager::appendIngredient(const Ingredient &ingredient)
{
    QList<Ingredient> ingredients = loadIngredients();
    ingredients.append(ingredient);
    saveIngredients(ingredients);
}

Ingredient IngredientManager::getIngredient(int id)
{
    QList<Ingredient> ingredients = loadIngredients();
    for (const Ingredient &ingredient : ingredients)
    {
        if (ingredient.getId() == id)
            return ingredient;
    }
    return Ingredient(-1, "", 0); // Brak składnika
}

bool IngredientManager::updateIngredient(const Ingredient &updatedIngredient)
{
    QList<Ingredient> ingredients = loadIngredients();
    for (int i = 0; i < ingredients.size(); ++i)
    {
        if (ingredients[i].getId() == updatedIngredient.getId())
        {
            ingredients[i] = updatedIngredient;
            saveIngredients(ingredients);
            return true;
        }
    }
    return false;
}
