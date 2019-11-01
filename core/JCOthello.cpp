#include <ics46/factory/DynamicFactory.hpp>
#include "JCOthello.hpp"
// host: ron-cadillac.ics.uci.edu port:4603
ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI,jaredac1::JCOthello,"Madhatter Othello AI (Required)");
jaredac1::JCOthello::JCOthello(){}
jaredac1::JCOthello::~JCOthello(){}
std::pair<int,int> jaredac1::JCOthello::chooseMove(const OthelloGameState& state){
    std::vector<std::pair<int,int>> moves =findMoves(state);
    int max=0;
    int current_move=0;
    int index=0;
    for(int i=0;i<moves.size();i++){
    	std::unique_ptr<OthelloGameState> new_board=state.clone();
    	new_board->makeMove(moves[i].first,moves[i].second);
    	current_move=search(*new_board,4, 1);
    	if (current_move>max){
    		max=current_move;
    		index=i;
    	}
    }
	return moves[index];
}
int jaredac1::JCOthello::search(OthelloGameState& state, int d, int myturn){
	int best=1;
	if (d==0)
		return calculate(state);
	else{
		if (myturn==1){
			std::vector<std::pair<int,int>> m=findMoves(state);
			std::unique_ptr<OthelloGameState> xwanted=state.clone();
			best=0;
			for (int i=0;i<m.size();++i){
				std::unique_ptr<OthelloGameState> bCopy=state.clone();
				bCopy->makeMove(m[i].first,m[i].second);
				int board=search(*bCopy,d-1,0);
				best=std::max(best,board); 
			}
		}
		else{
			std::vector<std::pair<int,int>> n=findMoves(state);
			std::unique_ptr<OthelloGameState> ywanted=state.clone();
			best=1000;
			for (int i=0;i<n.size();++i){
				std::unique_ptr<OthelloGameState> bCopy=state.clone();
				bCopy->makeMove(n[i].first,n[i].second);
				int board=search(*bCopy,d-1,1);
				best=std::min(best,board); 
			}
		}
	}
	return best;
}
int jaredac1::JCOthello::calculate(const OthelloGameState& state){
	std::vector<std::pair<int,int>> corner_spots{std::pair<int,int>(0,0),
										std::pair<int,int>(state.board().width()-1,0),
										std::pair<int,int>(state.board().width()-1,state.board().height()-1),
										std::pair<int,int>(0,state.board().height()-1)};
	std::vector<std::pair<int,int>> Xspots{std::pair<int,int>(1,0),
										std::pair<int,int>(0,1),
										//std::pair<int,int>(1,1),

										std::pair<int,int>(state.board().width()-2,0),
										std::pair<int,int>(state.board().width()-1,1),
										//std::pair<int,int>(state.board().width()-2,1),

										std::pair<int,int>(state.board().width()-1,state.board().height()-2),
										std::pair<int,int>(state.board().width()-2,state.board().height()-1),
										//std::pair<int,int>(state.board().width()-2,state.board().height()-2),

										//std::pair<int,int>(1,state.board().height()-2),
										std::pair<int,int>(1,state.board().height()-1),
										std::pair<int,int>(0,state.board().height()-2)};   
	std::vector<std::pair<int,int>> mov=findMoves(state);
	int coins=0;/*owned tiles*/
	int moves=mov.size();/*possible future moves*/
	int corners=0;/*count corners owned and add*/
	int x_squares=0;/*next to corners bad position unless the corner is owned*/

	if (state.isBlackTurn()){
		coins=state.blackScore()-state.whiteScore();
		for(int i=0;i<corner_spots.size();++i){
			if (state.board().cellAt(corner_spots[i].first,corner_spots[i].second)==OthelloCell::black)
				++corners;
			else if(state.board().cellAt(corner_spots[i].first,corner_spots[i].second)==OthelloCell::white)
				corners-=2;
		}
		if (corners>2)
			corners*=3;
		for (int i=0; i<Xspots.size();++i){
			if(state.board().cellAt(Xspots[i].first,Xspots[i].second)==OthelloCell::black)
				x_squares-=2;
			else if(state.board().cellAt(Xspots[i].first,Xspots[i].second)==OthelloCell::white)
				x_squares++;
		}
	}
	else{
		coins=state.whiteScore()-state.blackScore();
		for(int i=0;i<corner_spots.size();++i){
			if (state.board().cellAt(corner_spots[i].first,corner_spots[i].second)==OthelloCell::white)
				++corners;
			else if(state.board().cellAt(corner_spots[i].first,corner_spots[i].second)==OthelloCell::black)
				corners-=2;
		}
		if (corners>2)
			corners*=3;
		for (int i=0; i<Xspots.size();++i){
			if(state.board().cellAt(Xspots[i].first,Xspots[i].second)==OthelloCell::white)
				x_squares-=2;
			else if(state.board().cellAt(Xspots[i].first,Xspots[i].second)==OthelloCell::black)
				x_squares+=1;
		}
	}
	for (int item=0;item<mov.size();++item){
			if (std::find(Xspots.begin(),Xspots.end(),mov[item])==Xspots.end()){
				if (mov[item].first==0 || mov[item].first==state.board().width()-1)
					moves+=2;
				if (mov[item].second==0 || mov[item].second==state.board().height()-1)
					moves+=2;
			}
		}
	return (coins+moves+corners+x_squares);
}
std::vector<std::pair<int,int>> jaredac1::JCOthello::findMoves(const OthelloGameState& state){
	std::vector<std::pair<int,int>> spots;
	for (int x=0;x<state.board().width();++x){
    	for (int y=0;y<state.board().height();++y){
    		if(state.isValidMove(x,y)){
    			spots.push_back(std::pair<int,int>(x,y));
    		}
    	}
	}
	return spots;
}