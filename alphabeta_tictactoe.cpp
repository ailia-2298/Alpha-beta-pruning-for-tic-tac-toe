#include<iostream>
#include<vector>
using namespace std;
struct node {
	int arr[3][3] = { {-1,-1,-1},{-1,-1,-1},{-1,-1,-1} };
	int depth;
	int alpha, beta;
	int in, jn;
};
node max_board;
void printArray(node &cur) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << cur.arr[i][j] << "\t";
		cout << endl;
	}
	cout << "Alpha: " << cur.alpha << endl;
	cout << "Beta: " << cur.beta << endl;
	cout << "Depth: " << cur.depth << endl << endl;
}

bool is_root(node &cur) {
	if (cur.depth == 0 && cur.alpha == -10000 && cur.beta == 10000)
		return true;
	else false;
}

bool matrixIsFull(node &cur) {
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++)
			if (cur.arr[i][j] == -1)		
				return false;
	return true;
}

bool rowisEmpty(int matrix[3][3], int i) {
	bool empty = false;
	int value;
	value = matrix[i][0];	
	for (int j = 1; j < 3; j++) {
		if (matrix[i][j] == value && value == -1)	
			empty = true;
		else {
			empty = false;
			break;
		}
	}
	return empty;
}

bool checkrow(int matrix[3][3]) {
	bool check = false;
	for (int i = 0; i < 3; i++) {
		int c = 1, d = 1;		
		if (!rowisEmpty(matrix,i)) {	
			int value = matrix[i][0];		
			for (int j = 1; j < 3; j++) {
				if (matrix[i][j] == value && value == 0)	
					c++;
				else if (matrix[i][j] == value && value == 1)
					d++;
			}
			if (c == 3 || d == 3) {	
				check = true;
				return check;
			}
		}
		else				
			check = false;
	}
	return check;
}

bool colisEmpty(int matrix[3][3], int i) {
	bool empty = false;
	int value;
	value = matrix[0][i];			
	for (int j = 1; j < 3; j++) {
		if (matrix[j][i] == value && value == -1)	
			empty = true;
		else {
			empty = false;
			break;
		}
	}
	return empty;
}

bool checkcols(int matrix[3][3]) {
	bool check = false;
	for (int i = 0; i < 3; i++) {
		int c = 1, d = 1;						
		if (!colisEmpty(matrix,i)) {				
			int value = matrix[0][i];					
			for (int j = 1; j < 3; j++) {
				if (matrix[j][i] == value && value == 0)	
					c++;
				else if (matrix[j][i] == value && value == 1)
					d++;
			}
			if (c == 3 || d == 3) {			
				check = true;
				return check;
			}
		}
		else							
			check = false;
	}
	return check;
}

bool checkdiagonalone(int matrix[3][3]) {
	int value = matrix[0][0], c = 1, d = 1;					
	for (int i = 1; i < 3; i++) {
		if (matrix[i][i] == value && value == 0)		
			c++;
		else if (matrix[i][i] == value && value == 1)		
			d++;
		else												
			return false;
	}
	if (c == 3 || d == 3)								
		return true;
	return false;
}

bool checkdiagonaltwo(int matrix[3][3]) {
	int value = matrix[0][3 - 1], c = 1, d = 1;			
	for (int i = 3 - 1 - 1, j = 1; i <= 0, j < 3; i--, j++) {
		if (matrix[j][i] == value && value == 0)		
			c++;
		else if (matrix[j][i] == value && value == 1)	
			d++;
		else				
			return false;
	}
	if (c == 3 || d == 3)
		return true;
	return false;
}

bool is_leaf(node cur) {
	//if (cur.depth == plydepth)
	//return true;
	if (matrixIsFull(cur))
		return true;
	if (checkrow(cur.arr) == true || checkcols(cur.arr) == true || checkdiagonalone(cur.arr) == true || checkdiagonaltwo(cur.arr) == true) {
		return true;
	}
	return false;
}

bool is_max_node(node cur) {
	if (cur.depth % 2 == 0)
		return true;
	return false;
}

bool is_min_node(node cur) {
	if (cur.depth % 2 != 0)
		return true;
	return false;
}

void copyArray(int A[3][3], int B[3][3]) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			A[i][j] = B[i][j];
}

void printmine(vector<node> &myvector) {
	for (unsigned int i = 0; i < myvector.size(); i++) {
		printArray(myvector[i]);
	}
	/*while (!myvector.empty()) {
		printArray(myvector[0]);
		myvector.erase(myvector.begin());
	}*/
}

void Children(node cur,vector<node> &myvector) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (cur.arr[i][j] == -1) {
				node arr2;
				copyArray(arr2.arr, cur.arr);
				arr2.depth = cur.depth + 1;
				arr2.alpha = cur.alpha;
				arr2.beta = cur.beta;
				if (cur.depth % 2 == 0)
					arr2.arr[i][j] = 1;
				else
					arr2.arr[i][j] = 0;
				arr2.in = i;
				arr2.jn = j;
				myvector.push_back(arr2);
			}
		}
	}
}

int heuristic(node cur) {
	int h_value=0;
	if (is_max_node(cur)) {
		if (cur.arr[0][0] == 0)
			h_value = h_value + 3;
		if (cur.arr[0][2] == 0)
			h_value = h_value + 3;
		if (cur.arr[2][0] == 0)
			h_value = h_value + 3;
		if (cur.arr[2][2] == 0)
			h_value = h_value + 3;
		if (cur.arr[0][1] == 0)
			h_value = h_value + 2;
		if (cur.arr[1][0] == 0)
			h_value = h_value + 2;
		if (cur.arr[1][2] == 0)
			h_value = h_value + 2;
		if (cur.arr[2][1] == 0)
			h_value = h_value + 2;
		if (cur.arr[1][1] == 0)
			h_value = h_value + 4;
		if (cur.arr[0][0] == 1)
			h_value = h_value - 3;
		if (cur.arr[0][2] == 1)
			h_value = h_value - 3;
		if (cur.arr[2][0] == 1)
			h_value = h_value - 3;
		if (cur.arr[2][2] == 1)
			h_value = h_value - 3;
		if (cur.arr[0][1] == 1)
			h_value = h_value - 2;
		if (cur.arr[1][0] == 1)
			h_value = h_value - 2;
		if (cur.arr[1][2] == 1)
			h_value = h_value - 2;
		if (cur.arr[2][1] == 1)
			h_value = h_value - 2;
		if (cur.arr[1][1] == 1)
			h_value = h_value - 4;
	}
	else if (is_min_node(cur)) {
		if (cur.arr[0][0] == 0)
			h_value = h_value - 3;
		if (cur.arr[0][2] == 0)
			h_value = h_value - 3;
		if (cur.arr[2][0] == 0)
			h_value = h_value - 3;
		if (cur.arr[2][2] == 0)
			h_value = h_value - 3;
		if (cur.arr[0][1] == 0)
			h_value = h_value - 2;
		if (cur.arr[1][0] == 0)
			h_value = h_value - 2;
		if (cur.arr[1][2] == 0)
			h_value = h_value - 2;
		if (cur.arr[2][1] == 0)
			h_value = h_value - 2;
		if (cur.arr[1][1] == 0)
			h_value = h_value - 4;
		if (cur.arr[0][0] == 1)
			h_value = h_value + 3;
		if (cur.arr[0][2] == 1)
			h_value = h_value + 3;
		if (cur.arr[2][0] == 1)
			h_value = h_value + 3;
		if (cur.arr[2][2] == 1)
			h_value = h_value + 3;
		if (cur.arr[0][1] == 1)
			h_value = h_value + 2;
		if (cur.arr[1][0] == 1)
			h_value = h_value + 2;
		if (cur.arr[1][2] == 1)
			h_value = h_value + 2;
		if (cur.arr[2][1] == 1)
			h_value = h_value + 2;
		if (cur.arr[1][1] == 1)
			h_value = h_value - 4;
	}
	return h_value;
}

int alpha_beta_pruning(node cur) {
	/*if (is_root(cur)) {
		cur.alpha = -10000;
		cur.beta = 10000;
	}*/
	if (is_leaf(cur)) {
		return heuristic(cur);
	}
	if (cur.alpha > cur.beta) {
		if (is_max_node(cur))
			return cur.alpha;
		else
			return cur.beta;
	}
	if (is_max_node(cur)) {
		//cout << "Max\n\n";
		int max = cur.alpha;
		vector<node> myvector;
		Children(cur,myvector);
		for (unsigned int i = 0; i < myvector.size() ; i++) {
			node n = myvector[i];
			int val = alpha_beta_pruning(myvector[i]);
			if (max < val) {
				max = val;
				cur.alpha = max;
				if (is_root(myvector[i])) {
					copyArray(max_board.arr, myvector[i].arr);
					max_board.alpha = myvector[i].alpha;
					max_board.beta = myvector[i].beta;
					max_board.depth = myvector[i].depth;
					max_board.in = myvector[i].in;
					max_board.jn = myvector[i].jn;
				}
			}
			/*if (is_root(myvector[i])) {
				cout << "Value: " << val << endl;
				printArray(myvector[i]);
			}*/
		}
		return cur.alpha;
		//printmine(myvector);
	}
	if (is_min_node(cur)) {
		//cout << "Min\n\n";
		int min = cur.beta;
		vector<node> myvector;
		Children(cur, myvector);
		for (int i = 0; i < myvector.size(); i++) {
			int val = alpha_beta_pruning(myvector[i]);
			if (min > val) {
				min = val;
				cur.beta = min;
			}
		}
		return cur.beta;
		//printmine(myvector);
	}
}
//player 0  //computer 1
int main() {

	node a;
	a.arr[0][0] = 0;    a.arr[0][1] = 1;    a.arr[0][2] = -1;
	a.arr[1][0] = -1;    a.arr[1][1] = 1;    a.arr[1][2] = -1;
	a.arr[2][0] = 0;    a.arr[2][1] = 0;    a.arr[2][2] = -1;
	a.depth = 0;
	a.alpha = -10000;
	a.beta = 10000;

	cout << "initial state: " << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << a.arr[i][j] << "\t";
		cout << endl;
	}

	//printArray(a);
	//cout << "Alpha beta pruning value: " << alpha_beta_pruning(a) << endl;
	alpha_beta_pruning(a);

	cout << "\nBest move: " << endl;
	a.arr[max_board.in][max_board.jn] = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << a.arr[i][j] << "\t";
		cout << endl;
	}

	return 0;
}