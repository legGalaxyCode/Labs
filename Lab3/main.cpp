#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>

using namespace std;

static const int M = 10;
static const int K = 5;
static const double P = 0.2; //probability
vector<bool> used;

unsigned int find_comps(vector<vector<int>> &graph);
int random_n(vector<int> &r);
bool is_all_burned(vector<bool> &u);

int main() {
	srand(time(NULL));

	const int N = pow(10, 6)/ M; //vertex
	const int E = K*N; //edge
	int c = 0; //edge counter
	int s = 0; //start
	vector<vector<int>> graph(N);
	used.resize(N);
	//соединяю все вершины с одной(0)
	for (int i = 1; i < N; i++) {
		int temp = 0;
		graph[temp].push_back(i);
		graph[i].push_back(temp);
		c++;
	} 
	//соединяю вершины между собой пока не E ребер
	while (c != E) {
		int u, v;
		u = rand() % (N-1) + 1;
		v = rand() % (N-1) + 1;
		if (v == u) {
			while (v != u) {
				v = rand() % (N-1) + 1;
			}
		}
		graph[u].push_back(v);
		graph[v].push_back(u);
		c++;
	}
	//bfs
	queue<int> q;
	q.push(s);
	vector<int> d(N), p(N);
	used[s] = true;//burned
	p[s] = -1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (size_t i=0; i < graph[v].size(); ++i) {
			int to = graph[v][i];
			if (!used[to]) {
				used[to] = true;
				q.push(to);
				d[to] = d[v] + 1;
				p[to] = v;
			}
		}
	}
	unsigned int comp = find_comps(graph);
	cout << "Components: " << comp << endl;
	q = {}; used = {};//clear
	used.resize(N);
	//вынос рандома из ф-ии
	vector<int> rand_arr;
	int r_var = 10;
	int np = P*10;
	for (int i = 0; i <= r_var; i++) {
		if (i < np) {
			rand_arr.push_back(0);
		} else if (i > np) {
			rand_arr.push_back(1);
		}
	}
	if (rand() % 10 < 2) //p=0.2
	//вынос окончен
	//bfs with probability
	//absolutely new way
	//помещаем 0 вершину, она связана со всеми
	//пока все элементы в used не равны true
	//сначала помещаем
	//затем убираем, пока все не true
	//сделать вектор для хранения вершин true на цикле
	bool is_b = is_all_burned(used); //1
	while (is_b) { //обобщить теперь под s и добавить исключение вершин
		for (int v = 0; v < N; ++v) { //сделать переменную temp для s, затем q.pop()
			if (used[v] != true) {
				q.push(v);
				int temp = v;
				q.pop();
				used[v] = true; // burned
				for (unsigned int i = 0; i < graph[temp].size(); ++i) {
					int to = graph[temp][i];
					if (used[to] == false && random_n(rand_arr) == 0) { // without random much faster
						used[to] = true;
						q.push(to);
						}
					}
				is_b = is_all_burned(used);
		 	}
		 	else {
		 		q.pop();
		 	}
		}
	}
	cout << "Queue size: " << q.size() << endl;
	cout << "Time: " << clock()/1000000.0 << endl;
	return 0;
}

unsigned int find_comps(vector<vector<int>> &graph) {
	queue<int> Q;
	vector<int> distance(graph.size(), -1);
	vector<int> prevVer(graph.size(), -1);

	unsigned int count = 0;
	for (unsigned int start = 0; start < graph.size(); start++) {
		if (distance[start] == -1) {
			distance[start] = 0;
			Q.push(start);
			while (Q.size()) {
				int u = Q.front();
				Q.pop();
				for (unsigned int j = 0; j < graph[u].size(); j++) {
					int v = graph[u][j];
					if (distance[v] == -1) {
						distance[v] = distance[u] + 1;
						prevVer[v] = u;
						Q.push(v);
					}
				}
			}

		count++;	
		}
	}

	return count;
}

int random_n(vector<int> &r) {
	int ra = rand() % 10;
	return r.at(ra);
}

bool is_all_burned(vector<bool> &u) {
	bool temp = false;
	for (vector<bool>::iterator it = u.begin(); it != u.end(); ++it) {
		if (*it == 0) { //if not burned still exist
			temp = 1;
			break;
		}
	}
	return temp; //0 - good, 1 - bad;
}