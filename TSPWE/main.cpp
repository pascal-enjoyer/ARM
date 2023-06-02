#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QDebug>
#include <QPainter>
#include <QLabel>
#include <QtMath>
#include <vector>
#include <climits>
#include <algorithm> // Добавляем заголовочный файл algorithm для использования функции std::next_permutation

// Функция для решения задачи коммивояжера методом полного перебора
// Структура для представления состояния ветви
struct BranchState {
    int currentVertex; // Текущая вершина
    std::vector<int> path; // Пройденный путь
    int distance; // Текущее расстояние

    BranchState(int vertex, const std::vector<int>& p, int dist)
        : currentVertex(vertex), path(p), distance(dist) {}
};

// Функция для решения задачи коммивояжера методом ветвей и границ
std::pair<int, std::vector<int>> solveTravelingSalesmanProblem(const std::vector<std::vector<int>>& graph) {
    int n = graph.size(); // Количество вершин графа
    std::vector<int> vertexIndices(n);
    for (int i = 0; i < n; ++i) {
        vertexIndices[i] = i; // Индексы вершин
    }
    int minDistance = INT_MAX; // Минимальное расстояние
    std::vector<int> minPath; // Кратчайший путь

    std::vector<BranchState> branches; // Структура данных для хранения состояний ветвей
    // Инициализируем начальное состояние
    branches.emplace_back(vertexIndices[0], std::vector<int>{vertexIndices[0]}, 0);

    while (!branches.empty()) {
        // Извлекаем состояние ветви с наиболее перспективным расстоянием
        auto currentState = branches.back();
        branches.pop_back();

        // Проверяем, является ли текущее состояние допустимым (все вершины посещены)
        if (currentState.path.size() == n) {
            // Добавляем расстояние от последней вершины к исходной
            int finalDistance = currentState.distance + graph[currentState.currentVertex][vertexIndices[0]];
            if (finalDistance < minDistance) {
                minDistance = finalDistance;
                minPath = currentState.path;
                minPath.push_back(vertexIndices[0]);
            }
        } else {
            // Создаем и добавляем новые состояния ветвей
            for (int i = 1; i < n; ++i) {
                int nextVertex = vertexIndices[i]; // Следующая вершина

                // Проверяем, что вершина еще не посещена
                if (std::find(currentState.path.begin(), currentState.path.end(), nextVertex) == currentState.path.end()) {
                    int distanceToNext = graph[currentState.currentVertex][nextVertex];
                    if (distanceToNext != 0 && currentState.distance + distanceToNext < minDistance) {
                        std::vector<int> newPath = currentState.path;
                        newPath.push_back(nextVertex);

                        branches.emplace_back(nextVertex, newPath, currentState.distance + distanceToNext);
                    }
                }
            }
        }
    }

    return std::make_pair(minDistance, minPath);
}


class GraphWidget2 : public QWidget {
public:
    GraphWidget2(QWidget* parent = nullptr) : QWidget(parent) {
        connect(addVertexButton, &QPushButton::clicked, this, &GraphWidget2::addVertex);
        connect(removeVertexButton, &QPushButton::clicked, this, &GraphWidget2::removeVertex);
        connect(addEdgeButton, &QPushButton::clicked, this, &GraphWidget2::addEdge);
        connect(removeEdgeButton, &QPushButton::clicked, this, &GraphWidget2::removeEdge);
    }

    void addVertex() {
        bool ok;
        int vertexIndex = QInputDialog::getInt(this, tr("Add Vertex"), tr("Enter vertex index:"), 0, 0, INT_MAX, 1, &ok);
        if (ok) {
            int n = graph.size();
            for (int i = 0; i < n; ++i) {
                graph[i].push_back(0); // Добавляем нулевые веса для новой вершины
            }
            std::vector<int> newRow(n + 1, 0);
            graph.push_back(newRow); // Добавляем новую строку в матрицу смежности
            update();
        }
    }

    void removeVertex() {
        bool ok;
        int vertexIndex = QInputDialog::getInt(this, tr("Remove Vertex"), tr("Enter vertex index:"), 0, 0, INT_MAX, 1, &ok);
        if (ok && vertexIndex >= 0 && vertexIndex < graph.size()) {
            graph.erase(graph.begin() + vertexIndex); // Удаляем строку матрицы смежности
            for (auto& row : graph) {
                row.erase(row.begin() + vertexIndex); // Удаляем столбец матрицы смежности
            }
            update();
        }
    }

    void addEdge() {
        bool ok;
        int vertexIndex1 = QInputDialog::getInt(this, tr("Add Edge"), tr("Enter first vertex index:"), 0, 0, INT_MAX, 1, &ok);
        if (ok && vertexIndex1 >= 0 && vertexIndex1 < graph.size()) {
            int vertexIndex2 = QInputDialog::getInt(this, tr("Add Edge"), tr("Enter second vertex index:"), 0, 0, INT_MAX, 1, &ok);
            if (ok && vertexIndex2 >= 0 && vertexIndex2 < graph.size()) {
                int weight = QInputDialog::getInt(this, tr("Add Edge"), tr("Enter edge weight:"), 0, 0, INT_MAX, 1, &ok);
                if (ok) {
                    graph[vertexIndex1][vertexIndex2] = weight;
                    graph[vertexIndex2][vertexIndex1] = weight;
                    update();
                }
            }
        }
    }

    void removeEdge() {
        bool ok;
        int vertexIndex1 = QInputDialog::getInt(this, tr("Remove Edge"), tr("Enter first vertex index:"), 0, 0, INT_MAX, 1, &ok);
        if (ok && vertexIndex1 >= 0 && vertexIndex1 < graph.size()) {
            int vertexIndex2 = QInputDialog::getInt(this, tr("Remove Edge"), tr("Enter second vertex index:"), 0, 0, INT_MAX, 1, &ok);
            if (ok && vertexIndex2 >= 0 && vertexIndex2 < graph.size()) {
                graph[vertexIndex1][vertexIndex2] = 0;
                graph[vertexIndex2][vertexIndex1] = 0;
                update();
            }
        }
    }

    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.translate(300,220);

        // Рисуем вершины графа
        double R = 2 * M_PI / int(graph.size());
        int radius = 20;
        for (int i = 0; i < int(graph.size()); i++) {
            double x = qCos(i * R) * 200;
            double y = qSin(i * R) * 200;

            painter.drawEllipse(QPointF(x, y), radius, radius);
            painter.drawText(QRectF(x - radius, y - radius, radius * 2, radius * 2), Qt::AlignCenter, QString::number(i));
        }

        // Рисуем ребра графа
        for (int i = 0; i < int(graph.size()); ++i) {
            for (int j = i + 1; j < int(graph.size()); ++j) {
                if (graph[i][j] != 0) {
                    double x1 = qCos(i * R) * 200;
                    double y1 = qSin(i * R) * 200;
                    double x2 = qCos(j * R) * 200;
                    double y2 = qSin(j * R) * 200;
                    painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));

                    int weight = graph[i][j];
                    double dx = x2 - x1;
                    double dy = y2 - y1;
                    double vlen = qSqrt(dx * dx + dy * dy);
                    double dx2 = dy / vlen ;
                    double dy2 = -dx / vlen ;
                    painter.drawText(QRectF((x1 + x2) / 2 + dx2 , (y1 + y2) / 2 + dy2, 20, 10), Qt::AlignCenter, QString::number(weight));
                }
            }
        }

        // Выводим минимальное расстояние и путь
        painter.drawText(QRectF(50, 250, 300, 30), Qt::AlignLeft, "Min Distance: " + QString::number(minDistance));

        // Рисуем минимальный путь
        painter.setPen(Qt::red);
        for (int i = 0; i < int(minPath.size()) - 1; ++i) {
            int vertex1 = minPath[i];
            int vertex2 = minPath[i + 1];

            double x1 = qCos(vertex1 * R) * 200;
            double y1 = qSin(vertex1 * R) * 200;
            double x2 = qCos(vertex2 * R) * 200;
            double y2 = qSin(vertex2 * R) * 200;

            painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
        }
        QString pathText = "Min Path: ";
        for (int i = 0; i < int(minPath.size()); ++i) {
            pathText += QString::number(minPath[i]);
            if (i != int(minPath.size()) - 1) {
                pathText += " -> ";
            }
        }
        painter.drawText(QRectF(50, 280, 300, 30), Qt::AlignLeft, pathText);
    }
    QPushButton* addVertexButton = new QPushButton("Add Vertex");
    QPushButton* removeVertexButton = new QPushButton("Remove Vertex");
    QPushButton* addEdgeButton = new QPushButton("Add Edge");
    QPushButton* removeEdgeButton = new QPushButton("Remove Edge");
private:
    std::vector<std::vector<int>> graph; // Матрица смежности
    int minDistance; // Минимальное расстояние
    std::vector<int> minPath; // Кратчайший путь

    void update() {
        std::pair<int, std::vector<int>> result = solveTravelingSalesmanProblem(graph);
        minDistance = result.first;
        minPath = result.second;

        QWidget::update();
    }
};


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    GraphWidget2 graphWidget;
    graphWidget.setGeometry(100, 100, 600, 600);
    graphWidget.show();

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(graphWidget.addVertexButton);
    layout->addWidget(graphWidget.removeVertexButton);
    layout->addWidget(graphWidget.addEdgeButton);
    layout->addWidget(graphWidget.removeEdgeButton);

    QWidget widget;
    widget.setLayout(layout);
    widget.show();

    return app.exec();
}
