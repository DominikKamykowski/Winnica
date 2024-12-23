#include "orderprinter.hpp"

OrderPrinter::OrderPrinter(const QString &outputDirectory)
    : outputDirectory(outputDirectory)
{
}

bool OrderPrinter::printOrderToPdf(const Order &order, const QString &defaultFileName)
{
    QString filePath = QFileDialog::getSaveFileName(
        nullptr,
        "Wybierz lokalizację do zapisu PDF",
        outputDirectory + "/" + defaultFileName,
        "PDF Files (*.pdf);;All Files (*)"
        );

    // Sprawdzamy, czy użytkownik wybrał plik
    if (filePath.isEmpty()) {
        QMessageBox::warning(nullptr, "Anulowano zapis", "Nie wybrano pliku do zapisu PDF.");
        return false;  // Anulowano zapis
    }

    // Inicjujemy QPdfWriter
    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);  // Ustawiamy wysoką rozdzielczość dla jakości wydruku

    QPainter painter(&pdfWriter);
    if (!painter.isActive()) {
        QMessageBox::critical(nullptr, "Błąd zapisu", "Nie można zapisać PDF.");
        return false;  // Zwracamy false, jeśli nie udało się rozpocząć pracy z painterem
    }

    // Ustawienia czcionki
    QFont titleFont("Arial", 16, QFont::Bold);
    QFont contentFont("Arial", 12);

    // Rysowanie nagłówka
    painter.setFont(titleFont);
    painter.drawText(50, 50, "Raport Zamówienia");

    // Rysowanie linii
    painter.drawLine(50, 70, 550, 70);

    // Ustawienia czcionki dla zawartości
    painter.setFont(contentFont);

    int y = 90; // Pozycja Y startowa dla tekstu
    int lineSpacing = 70; // Odstęp pomiędzy liniami tekstu

    // Drukowanie szczegółów zamówienia
    painter.drawText(50, y, "ID Zamówienia: " + QString::number(order.getId()));
    y += lineSpacing;
    painter.drawText(50, y, "Numer zakładowy: " + order.getFactoryNumber());
    y += lineSpacing;
    painter.drawText(50, y, "Elementy: " + order.getItems());
    y += lineSpacing;
    painter.drawText(50, y, "Data sporządzenia: " + order.getCreationDate().toString("yyyy-MM-dd"));
    y += lineSpacing;
    painter.drawText(50, y, "Data nadania: " + order.getShippingDate().toString("yyyy-MM-dd"));
    y += lineSpacing;
    painter.drawText(50, y, "Status: " + order.getStatusString());
    y += lineSpacing;
    painter.drawText(50, y, "Data dostarczenia: " + (order.getDeliveryDate().isValid() ? order.getDeliveryDate().toString("yyyy-MM-dd") : "Brak"));

    // Zakończenie pracy z painterem
    painter.end();

    return true;  // Zwracamy true, jeśli PDF został pomyślnie wygenerowany
}
