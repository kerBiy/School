//
// Created by Alex Balta on 18.05.2024.
//

#include "MainWindow.hpp"

void MainWindow::setupLayout() {
    auto *centralWidget = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(centralWidget);

    model = new SongModel(service, this);
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto *formLayout = new QHBoxLayout;

    inputTitle = new QLineEdit(this);
    formLayout->addWidget(new QLabel("Title:"));
    formLayout->addWidget(inputTitle);

    inputArtist = new QLineEdit(this);
    formLayout->addWidget(new QLabel("Artist:"));
    formLayout->addWidget(inputArtist);

    inputGenre = new QLineEdit(this);
    formLayout->addWidget(new QLabel("Genre:"));
    formLayout->addWidget(inputGenre);

    btnAdd = new QPushButton("Add", this);
    btnDelete = new QPushButton("Delete", this);
    btnUpdate = new QPushButton("Update", this);

    formLayout->addWidget(btnAdd);
    formLayout->addWidget(btnDelete);
    formLayout->addWidget(btnUpdate);

    mainLayout->addWidget(tableView);
    mainLayout->addLayout(formLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::setupSignals() {
    connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
        const auto selected = tableView->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        const auto index = selected.first();
        inputTitle->setText(model->data(model->index(index.row(), 1)).toString());
        inputArtist->setText(model->data(model->index(index.row(), 2)).toString());
        inputGenre->setText(model->data(model->index(index.row(), 3)).toString());
    });

    connect(btnAdd, &QPushButton::clicked, this, [this]() {
        QString title = inputTitle->text();
        QString artist = inputArtist->text();
        QString genre = inputGenre->text();

        try {
            service.addSong(title.toStdString(), artist.toStdString(), genre.toStdString());
            model->updateModel();
            update();
        } catch (const ServiceException &e) {
            QMessageBox::warning(this, "Warning", e.what());
        }
    });

    connect(btnDelete, &QPushButton::clicked, this, [this]() {
        const auto selected = tableView->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        try {
            std::vector<int> ids;
            for (const auto index : selected) {
                const auto id = model->data(model->index(index.row(), 0)).toInt();
                ids.push_back(id);
            }

            for (const auto id : ids) {
                service.deleteSong(id);
            }

            model->updateModel();
            update();
        } catch (const ServiceException &e) {
            QMessageBox::warning(this, "Warning", e.what());
        }
    });

    connect(btnUpdate, &QPushButton::clicked, this, [this] {
        const auto selected = tableView->selectionModel()->selectedRows();

        if (selected.isEmpty()) return;

        const auto index = selected.first();
        const auto id = model->data(model->index(index.row(), 0)).toInt();

        QString title = inputTitle->text();
        QString artist = inputArtist->text();
        QString genre = inputGenre->text();

        try {
            service.updateSong(id, title.toStdString(), artist.toStdString(), genre.toStdString());
            model->updateModel();
            update();
        } catch (const ServiceException &e) {
            QMessageBox::warning(this, "Warning", e.what());
        }
    });
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const auto genreCounts = service.raportGenre();
    const int circleSpacing = 10;
    const int initialSize = 10;

    std::map<std::string, QColor> genreColors{
        {"pop", Qt::red},
        {"rock", Qt::green},
        {"folk", Qt::blue},
        {"disco", Qt::yellow}
    };

    for (const auto &[genre, count] : genreCounts) {
        QColor color = genreColors[genre];
        painter.setPen(color);

        for (int i = 0; i < count; ++i) {
            int radius = initialSize + i * circleSpacing;

            if (genre == "pop") {
                painter.drawEllipse(QPoint(0, 0), radius, radius);
            } else if (genre == "rock") {
                painter.drawEllipse(QPoint(width(), 0), radius, radius);
            } else if (genre == "folk") {
                painter.drawEllipse(QPoint(0, height()), radius, radius);
            } else if (genre == "disco") {
                painter.drawEllipse(QPoint(width(), height()), radius, radius);
            }
        }
    }
}
