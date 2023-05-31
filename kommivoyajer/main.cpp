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
    GraphWidget2(QWidget* parent = nullptr) : QWidget(parent) {}

    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);

        // Пример графа с весами ребер
        std::vector<std::vector<int>> graph = {
            {0, 3, 6, 1, 6, 14},
            {3, 0, 10, 34, 0, 1},
            {6, 10, 0, 11, 3, 0},
            {1, 34, 11, 0, 6, 4},
            {6, 0, 3, 6, 0, 9},
            {14, 1, 0, 4, 9, 0}
        };

        auto result = solveTravelingSalesmanProblem(graph);
        int minDistance = result.first;
        std::vector<int> minPath = result.second;

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
            if (i < int(minPath.size()) - 1) {
                pathText += " -> ";
            }
        }
        painter.drawText(QRectF(50, 280, 300, 30), Qt::AlignLeft, pathText);
    }
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GraphWidget2 graphWidget2;
    QVBoxLayout mainLayout2;
    mainLayout2.addWidget(&graphWidget2);
    QWidget window2;
    window2.setLayout(&mainLayout2);
    window2.setWindowTitle("Traveling Salesman Problem");
    window2.setFixedSize(600,550);
    window2.show();

    return app.exec();
}

