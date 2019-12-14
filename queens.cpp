#include <iostream>
#include <vector>

using namespace std;

#define Q 1 // queen
#define E 0 // empty

struct Pos {
	int x;
	int y;
};

void print(vector<vector<int>> &board){
	for(int y = 0; y < board.size(); y++){
		for(int x = 0; x < board[y].size(); x++){
			if(board[y][x] == Q)
				cout << 'Q';
			else
				cout << '.';
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

Pos next_pos(Pos pos, const int size){
	if(pos.x == size-1){
		pos.x = 0;
		pos.y++;
	}else{
		pos.x++;
	}
	return pos;
}

bool valid_hor(vector<vector<int>> &board, Pos q){
	for(int x = 0; x < board[q.y].size(); x++){
		if(q.x != x && board[q.y][x] == Q){
			return false;
		}
	}
	return true;
}

bool valid_ver(vector<vector<int>> &board, Pos q){
	for(int y = 0; y < board.size(); y++){
		if(q.y != y && board[y][q.x] == Q){
			return false;
		}
	}
	return true;
}

bool valid_dia(vector<vector<int>> &board, Pos q){
	const int N = board.size();

	int c = q.x + q.y;
	for(int y = 0; y < N; y++){
		for(int x = 0; x < N; x++){
			if(x + y == c && x != q.x && y != q.y && board[y][x] == Q){
				return false;
			}
		}
	}

	c = N-1-q.x + q.y;
	for(int y = 0; y < N; y++){
		for(int x = 0; x < N; x++){
			if(N-1-x + y == c && x != q.x && y != q.y && board[y][x] == Q){
				return false;
			}
		}
	}

	return true;
}

bool valid_board(vector<vector<int>> &board, Pos q){
	return valid_hor(board, q) && valid_ver(board, q) && valid_dia(board, q);
}

void solve(vector<vector<int>> &board, Pos pos, int placed){
	const int N = board.size();

	if(placed == N){
		print(board);
		return;	
	}
	if(pos.y == N)
		return;
	
	// try with queen
	board[pos.y][pos.x] = Q;
	if(valid_board(board, pos))	
		solve(board, {0,pos.y+1}, placed+1);
	// try without queen
	board[pos.y][pos.x] = E;
	solve(board, next_pos(pos, N), placed);
}

int main(int argc, char* argv[]){
	int N = 8;

	if(argc > 1)
		N = atoi(argv[1]);

	vector<vector<int>> board(N, vector<int>(N));

	solve(board, {0,0}, 0);

	return 0;
}
