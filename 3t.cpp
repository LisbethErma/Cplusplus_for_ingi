#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>

class PhoneBookApp : public QWidget {
    Q_OBJECT

public:
    PhoneBookApp(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Телефонная книга");
        setFixedSize(600, 400);

        // Подключение к базе данных
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("phonebook.db");

        if (!db.open()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных");
            exit(1);
        }

        // Создание таблицы, если она не существует
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS contacts (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, phone TEXT)");

        // Инициализация интерфейса
        QVBoxLayout *layout = new QVBoxLayout(this);

        QHBoxLayout *formLayout = new QHBoxLayout;
        nameEdit = new QLineEdit;
        nameEdit->setPlaceholderText("Имя");
        phoneEdit = new QLineEdit;
        phoneEdit->setPlaceholderText("Телефон");
        formLayout->addWidget(nameEdit);
        formLayout->addWidget(phoneEdit);
        layout->addLayout(formLayout);

        QPushButton *addButton = new QPushButton("Добавить контакт");
        layout->addWidget(addButton);

        QPushButton *deleteButton = new QPushButton("Удалить выбранный контакт");
        layout->addWidget(deleteButton);

        // Модель и таблица для отображения контактов
        model = new QSqlTableModel(this, db);
        model->setTable("contacts");
        model->select();

        QTableView *tableView = new QTableView;
        tableView->setModel(model);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->horizontalHeader()->setStretchLastSection(true);
        layout->addWidget(tableView);

        // Соединения для кнопок
        connect(addButton, &QPushButton::clicked, this, &PhoneBookApp::addContact);
        connect(deleteButton, &QPushButton::clicked, [=]() {
            QModelIndexList selection = tableView->selectionModel()->selectedRows();
            for (const QModelIndex &index : selection) {
                model->removeRow(index.row());
            }
            model->submitAll();
        });
    }

private slots:
    void addContact() {
        QString name = nameEdit->text().trimmed();
        QString phone = phoneEdit->text().trimmed();

        if (name.isEmpty() || phone.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля");
            return;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO contacts (name, phone) VALUES (:name, :phone)");
        query.bindValue(":name", name);
        query.bindValue(":phone", phone);

        if (!query.exec()) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить контакт");
        } else {
            model->select();
            nameEdit->clear();
            phoneEdit->clear();
        }
    }

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PhoneBookApp phoneBookApp;
    phoneBookApp.show();

    return app.exec();
}

#include "phonebook.moc"
