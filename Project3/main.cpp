#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QMap>
#include <QVector>
#include <QString>
#include <QPair>
#include <QFont>
#include <QFrame>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <limits>
#include <algorithm>

using namespace std;

struct MissionPlace {
    QString name;
    QString description;
    int x;
    int y;
};

struct Edge {
    int to;
    int distance;
    int danger;
};

class MissionGraph {
private:
    QVector<MissionPlace> places;
    QVector<QVector<Edge>> adj;

public:
    MissionGraph() {
    addPlace("공항", "Los Santos 남서쪽에 위치한 국제공항입니다. 빠른 이동 수단을 확보하기 좋은 지역입니다.", 260, 650);
    addPlace("해변", "도시 서쪽 해안가 지역입니다. 추격을 피하거나 우회 경로로 이동하기 좋은 지역입니다.", 235, 555);
    addPlace("항구", "Los Santos 남동쪽에 위치한 항구입니다. 화물 이동과 탈출 미션에 자주 사용되는 지역입니다.", 410, 660);
    addPlace("도심", "Los Santos 중심부입니다. 은행, 경찰서, 차고지로 이어지는 주요 교차점입니다.", 350, 545);
    addPlace("은행", "도심에 위치한 고위험 미션 장소입니다. 보상이 크지만 경찰 위험도가 높습니다.", 390, 515);
    addPlace("경찰서", "도심 동쪽에 위치한 경찰 거점입니다. 이동 시 위험도가 높은 지역입니다.", 455, 540);
    addPlace("차고지", "도시 북쪽 진입부에 있는 차량 보관 장소입니다. 미션 준비에 적합합니다.", 315, 470);
    addPlace("아지트", "도시 외곽과 도심을 연결하는 플레이어 거점입니다. 대부분의 미션 경로가 이곳에서 시작됩니다.", 300, 410);
    addPlace("산악지역", "맵 북쪽 중앙에 위치한 Mount Chiliad 산악 지형입니다. 이동 거리는 길지만 우회 경로로 사용할 수 있습니다.", 355, 145);
    addPlace("군사기지", "서쪽 해안 위쪽의 Fort Zancudo 군사 지역입니다. 위험도는 높지만 특수 장비 획득이 가능합니다.", 150, 300);
    addPlace("사막마을", "Alamo Sea 근처의 Sandy Shores 지역입니다. 북부와 동부 지역을 연결하는 중간 지점입니다.", 455, 310);
    addPlace("북부마을", "북서쪽 해안의 Paleto Bay 지역입니다. 산악지역과 해안도로를 연결합니다.", 315, 80);
    addPlace("동부마을", "동쪽 외곽의 Grapeseed 인근 지역입니다. 사막마을과 산업시설 사이의 경유지입니다.", 535, 295);
    addPlace("발전소", "동남쪽 산업 시설 지역입니다. 항구와 동부 외곽을 연결하는 지점입니다.", 530, 455);

    addEdge("아지트", "차고지", 3, 2);
    addEdge("차고지", "도심", 4, 3);
    addEdge("도심", "은행", 2, 5);
    addEdge("은행", "경찰서", 2, 8);
    addEdge("도심", "경찰서", 4, 7);
    addEdge("도심", "항구", 5, 4);
    addEdge("해변", "도심", 4, 3);
    addEdge("해변", "공항", 3, 2);
    addEdge("공항", "항구", 5, 3);
    addEdge("군사기지", "해변", 6, 6);
    addEdge("군사기지", "산악지역", 6, 8);
    addEdge("군사기지", "아지트", 5, 5);
    addEdge("산악지역", "북부마을", 4, 4);
    addEdge("산악지역", "사막마을", 5, 3);
    addEdge("사막마을", "동부마을", 3, 3);
    addEdge("동부마을", "발전소", 4, 4);
    addEdge("발전소", "항구", 5, 5);
    addEdge("발전소", "경찰서", 4, 6);
    addEdge("아지트", "사막마을", 5, 2);
    addEdge("차고지", "해변", 4, 3);
    addEdge("은행", "발전소", 6, 6);
}

    void addPlace(QString name, QString description, int x, int y) {
        MissionPlace p;
        p.name = name;
        p.description = description;
        p.x = x;
        p.y = y;
        places.push_back(p);
        adj.push_back(QVector<Edge>());
    }

    int indexOf(QString name) const {
        for (int i = 0; i < places.size(); i++) {
            if (places[i].name == name) return i;
        }
        return -1;
    }

    void addEdge(QString from, QString to, int distance, int danger) {
        int a = indexOf(from);
        int b = indexOf(to);
        if (a == -1 || b == -1) return;

        adj[a].push_back({b, distance, danger});
        adj[b].push_back({a, distance, danger});
    }

    QVector<MissionPlace> getPlaces() const {
        return places;
    }

    QVector<QVector<Edge>> getAdj() const {
        return adj;
    }

    QString getDescription(QString name) const {
        int idx = indexOf(name);
        if (idx == -1) return "장소 정보를 찾을 수 없습니다.";
        return places[idx].description;
    }

    QPair<QString, int> dijkstra(QString startName, QString endName, QString mode) const {
        int n = places.size();
        int start = indexOf(startName);
        int target = indexOf(endName);

        if (start == -1 || target == -1) {
            return {"장소 선택이 올바르지 않습니다.", 0};
        }

        const int INF = numeric_limits<int>::max() / 4;
        QVector<int> dist(n, INF);
        QVector<int> prev(n, -1);
        QVector<bool> visited(n, false);

        dist[start] = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            int best = INF;

            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < best) {
                    best = dist[i];
                    u = i;
                }
            }

            if (u == -1) break;
            visited[u] = true;

            for (const Edge& e : adj[u]) {
                int weight;

                if (mode == "최단 거리") {
                    weight = e.distance;
                } else if (mode == "최소 위험도") {
                    weight = e.danger;
                } else {
                    weight = e.distance + e.danger;
                }

                int v = e.to;
                int nd = dist[u] + weight;

                if (nd < dist[v]) {
                    dist[v] = nd;
                    prev[v] = u;
                }
            }
        }

        if (dist[target] == INF) {
            return {"경로를 찾을 수 없습니다.", 0};
        }

        QVector<int> path;
        for (int cur = target; cur != -1; cur = prev[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        QString result;
        for (int i = 0; i < path.size(); i++) {
            result += places[path[i]].name;
            if (i != path.size() - 1) result += " → ";
        }

        return {result, dist[target]};
    }

    QString getGraphText() const {
        QString text;
        text += "[그래프 데이터 구조]\n\n";
        text += "노드: 맵 위의 주요 장소\n";
        text += "간선: 장소 사이의 이동 가능한 도로\n";
        text += "가중치: 거리 / 위험도\n\n";

        for (int i = 0; i < places.size(); i++) {
            text += places[i].name + " : ";
            for (const Edge& e : adj[i]) {
                text += places[e.to].name;
                text += "(거리 " + QString::number(e.distance);
                text += ", 위험도 " + QString::number(e.danger) + ") ";
            }
            text += "\n";
        }

        return text;
    }
};

class MapWidget : public QWidget {
private:
    MissionGraph* graph;
    QPixmap mapImage;
    QString selectedPlace;

public:
    MapWidget(MissionGraph* g, QWidget* parent = nullptr) : QWidget(parent), graph(g) {
        setMinimumSize(650, 720);

        QStringList candidates;
        candidates << "gta5map.png" << "gta5map.jpg" << "gta5map.jpeg" << "gta5map.bmp";

        for (const QString& file : candidates) {
            if (QFile::exists(file)) {
                mapImage.load(file);
                break;
            }
        }
    }

    void setSelectedPlace(QString name) {
        selectedPlace = name;
        update();
    }

protected:
    void paintEvent(QPaintEvent*) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect mapRect = rect();

        if (!mapImage.isNull()) {
            painter.drawPixmap(mapRect, mapImage);
        } else {
            painter.fillRect(mapRect, QColor(25, 42, 65));
            painter.setPen(Qt::white);
            painter.drawText(rect(), Qt::AlignCenter,
                             "gta5map 이미지 파일을 찾을 수 없습니다.\n"
                             "main.cpp와 같은 위치에 gta5map.jpg 또는 gta5map.png를 넣으세요.");
        }

        QVector<MissionPlace> places = graph->getPlaces();
        QVector<QVector<Edge>> adj = graph->getAdj();

        double sx = width() / 650.0;
        double sy = height() / 720.0;

        painter.setPen(QPen(QColor(180, 220, 255), 3));

        for (int i = 0; i < places.size(); i++) {
            for (const Edge& e : adj[i]) {
                if (i < e.to) {
                    QPoint p1(places[i].x * sx, places[i].y * sy);
                    QPoint p2(places[e.to].x * sx, places[e.to].y * sy);
                    painter.drawLine(p1, p2);
                }
            }
        }

        for (const MissionPlace& p : places) {
            int px = p.x * sx;
            int py = p.y * sy;

            if (p.name == selectedPlace) {
                painter.setBrush(QColor(255, 220, 80));
                painter.setPen(QPen(Qt::black, 2));
                painter.drawEllipse(QPoint(px, py), 12, 12);
            } else {
                painter.setBrush(QColor(50, 170, 255));
                painter.setPen(QPen(Qt::white, 2));
                painter.drawEllipse(QPoint(px, py), 9, 9);
            }

            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 9, QFont::Bold));
            painter.drawText(px + 12, py - 8, p.name);
        }
    }
};

class MainWindow : public QMainWindow {
private:
    MissionGraph graph;
    MapWidget* mapWidget;
    QComboBox* startCombo;
    QComboBox* endCombo;
    QComboBox* modeCombo;
    QTextEdit* resultText;
    QLabel* placeInfoLabel;

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("오픈월드 도시 맵 기반 미션 경로 탐색 프로그램");
        resize(1100, 760);

        QWidget* central = new QWidget(this);
        setCentralWidget(central);

        QHBoxLayout* mainLayout = new QHBoxLayout(central);

        QGroupBox* mapBox = new QGroupBox("가상 도시 미션 맵");
        QVBoxLayout* mapLayout = new QVBoxLayout(mapBox);

        mapWidget = new MapWidget(&graph);
        mapLayout->addWidget(mapWidget);

        QGroupBox* panelBox = new QGroupBox("미션 경로 탐색");
        QVBoxLayout* panelLayout = new QVBoxLayout(panelBox);

        QLabel* title = new QLabel("Mission Route Finder");
        QFont titleFont;
        titleFont.setPointSize(18);
        titleFont.setBold(true);
        title->setFont(titleFont);
        title->setAlignment(Qt::AlignCenter);

        QLabel* subTitle = new QLabel("맵의 장소를 그래프 노드로 저장하고, 도로를 간선으로 저장한 경로 탐색 프로그램");
        subTitle->setWordWrap(true);
        subTitle->setAlignment(Qt::AlignCenter);

        startCombo = new QComboBox();
        endCombo = new QComboBox();
        modeCombo = new QComboBox();

        QVector<MissionPlace> places = graph.getPlaces();
        for (const MissionPlace& p : places) {
            startCombo->addItem(p.name);
            endCombo->addItem(p.name);
        }

        startCombo->setCurrentText("아지트");
        endCombo->setCurrentText("은행");

        modeCombo->addItem("최단 거리");
        modeCombo->addItem("최소 위험도");
        modeCombo->addItem("미션 추천");

        QPushButton* searchButton = new QPushButton("경로 찾기");
        QPushButton* graphButton = new QPushButton("그래프 데이터 보기");

        placeInfoLabel = new QLabel("출발지 또는 도착지를 선택하면 장소 정보가 표시됩니다.");
        placeInfoLabel->setWordWrap(true);
        placeInfoLabel->setFrameShape(QFrame::StyledPanel);
        placeInfoLabel->setMinimumHeight(90);

        resultText = new QTextEdit();
        resultText->setReadOnly(true);
        resultText->setMinimumHeight(260);
        resultText->setText("출발지와 목적지를 선택한 뒤 [경로 찾기] 버튼을 누르세요.");

        QObject::connect(startCombo, &QComboBox::currentTextChanged, [=](const QString& name) {
            mapWidget->setSelectedPlace(name);
            placeInfoLabel->setText("<b>" + name + "</b><br>" + graph.getDescription(name));
        });

        QObject::connect(endCombo, &QComboBox::currentTextChanged, [=](const QString& name) {
            placeInfoLabel->setText("<b>" + name + "</b><br>" + graph.getDescription(name));
        });

        QObject::connect(searchButton, &QPushButton::clicked, [=]() {
            QString start = startCombo->currentText();
            QString end = endCombo->currentText();
            QString mode = modeCombo->currentText();

            if (start == end) {
                QMessageBox::information(this, "알림", "출발지와 목적지가 같습니다.");
                return;
            }

            QPair<QString, int> answer = graph.dijkstra(start, end, mode);

            QString unit;
            if (mode == "최단 거리") unit = "km 기준 점수";
            else if (mode == "최소 위험도") unit = "위험도 점수";
            else unit = "종합 점수";

            QString output;
            output += "[미션 경로 탐색 결과]\n\n";
            output += "출발지: " + start + "\n";
            output += "목적지: " + end + "\n";
            output += "탐색 기준: " + mode + "\n\n";
            output += "추천 경로:\n";
            output += answer.first + "\n\n";
            output += "총 비용: " + QString::number(answer.second) + " (" + unit + ")\n\n";

            output += "[사용 자료구조]\n";
            output += "그래프 - 인접 리스트\n\n";

            output += "[사용 알고리즘]\n";
            output += "Dijkstra 최단 경로 알고리즘\n";

            resultText->setText(output);

            QMessageBox::information(this, "탐색 완료", "미션 경로 탐색이 완료되었습니다.");
        });

        QObject::connect(graphButton, &QPushButton::clicked, [=]() {
            resultText->setText(graph.getGraphText());
        });

        panelLayout->addWidget(title);
        panelLayout->addWidget(subTitle);
        panelLayout->addSpacing(10);

        panelLayout->addWidget(new QLabel("출발지"));
        panelLayout->addWidget(startCombo);

        panelLayout->addWidget(new QLabel("목적지"));
        panelLayout->addWidget(endCombo);

        panelLayout->addWidget(new QLabel("탐색 기준"));
        panelLayout->addWidget(modeCombo);

        panelLayout->addWidget(searchButton);
        panelLayout->addWidget(graphButton);

        panelLayout->addSpacing(10);
        panelLayout->addWidget(new QLabel("장소 정보"));
        panelLayout->addWidget(placeInfoLabel);

        panelLayout->addWidget(new QLabel("실행 결과"));
        panelLayout->addWidget(resultText);

        mainLayout->addWidget(mapBox, 2);
        mainLayout->addWidget(panelBox, 1);

        mapWidget->setSelectedPlace("아지트");
        placeInfoLabel->setText("<b>아지트</b><br>" + graph.getDescription("아지트"));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}