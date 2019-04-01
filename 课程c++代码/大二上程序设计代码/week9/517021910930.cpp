#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void gameOfLife(vector<vector<int>>& board) {
		vector<vector<int>> newboard(board);
		int m = board.size();
		int n = board[0].size();
		for (int i = 0; i < board.size(); i++)
			for (int j = 0; j < board[0].size(); j++)
			{
				int livecount = 0;
				for (int k = -1; k<2; k++)
					for (int l = -1; l < 2; l++)
					{
						if (k || l)
						{
							if (i + k >= 0 && i + k < m&&j + l >= 0 && j + l < n)
								livecount += board[i + k][j + l]; 
						}
					}
				if (board[i][j] == 0)
				{
					if (livecount == 3)
						newboard[i][j] = 1;
					else
						newboard[i][j] = 0;
				}
				else
				{
					if (livecount == 2 || livecount == 3)
						newboard[i][j] = 1;
					else
						newboard[i][j] = 0;
				}
			}
		board = newboard;
	}
};
