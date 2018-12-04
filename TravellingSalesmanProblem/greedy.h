int N, r, c;

int recFunc();
int getRow();
int getCol();
void randMap(int map[r][c]);
void printMap(int map[r][c]);
int tsp(int city, int arr[r][c], int vis[r]);//get nearest city for "r", c = #columns
void mincost(int city, int arr[r][c], int completed[r], bool graph);


