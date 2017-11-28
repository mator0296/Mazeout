#ifndef MAZE
#define MAZE 
#include <Define.h>
#include <recursiveBackTracker.h>
class Maze{
	public:
		pair<int,int> enemysCord;
		pair<int,int> playerCord;
		Maze(){}

		void initMaze(int mapSize){
			this->mapSize = mapSize;
			InitMap();
			InitGraph();

		};
		
		~Maze(){

			this->Clean();
		};
		char** getMaze(){return map;}
		Graph* getGraph(){return graphMap;}
		

		void PrintMaze(){
			for(int i = 0; i< (2*this->mapSize) + 1 ; i++){
				for (int j = 0; j < (2*this->mapSize) + 1 ; ++j){
					cout << this->map[i][j] ;
				}
				cout << endl;
			}
		}

		

		void MakeMaze(){
			initRecursiveBackTracker(this->map, this->graphMap);
		}

		DynList<pair<int,int> > CordPath(pair<int,int> start, pair<int,int> End){
			//cout << "star(" << start.first << ',' << start.second << ')' << endl;
			//cout << "end(" << End.first << ',' << End.second << ')' << endl;

			auto ArcStart = cordToArc(start, this->graphMap);
			auto ArcEnd = cordToArc(End, this->graphMap);
			auto list = arcToCord(this->makeBriefPath(ArcStart.first, ArcEnd.first), this->graphMap);
			//cout << "first(" << list.get_first().first << ',' << list.get_first().second << ')' << endl;
			if(ArcStart.second == 1)
				if(list.get_first().second > start.second)
					list.remove_first();
				else 
					if(list.get(1).second == start.second and  list.get(1).first == start.first)
						list.remove_first();
					else
						list.insert(start);
			else if(ArcStart.second == 2)
				if(list.get_first().first > start.first)
					list.remove_first();
				else 
					if(list.get(1).second == start.second and  list.get(1).first == start.first)
						list.remove_first();
					else
						list.insert(start);



			if(ArcEnd.second ==1 )
				if(list.get_last().second < End.second)
					list.append(End);
			else if(ArcEnd.second ==2 )
					if(list.get_last().first < End.first)
						list.append(End);	

			return list;
		}

		

		void makeDepth(void(*visit)(Arc*)){
			resetRecorridos();

			Depth(visit, this->graphMap->get_first_arc(), this->graphMap);

		}

		void makeBrief(void(*visit)(Arc*)){
			resetRecorridos();
			brief(visit, this->graphMap->get_first_arc(), this->graphMap);

		}

		void makeDepthPath(){
			resetRecorridos();
			Arc *aux;
			for (Graph::Arc_Iterator it(*this->graphMap); it.has_curr(); it.next()){
				aux = it.get_curr();
			}
			DynList<Arc*> path;
			
			
			DepthPath(this->graphMap->get_first_arc(),aux,this->graphMap, path);
			path.insert(this->graphMap->get_first_arc());
			/*path.for_each([](Arc *a){

				cout << a->get_info().info << endl;
			});*/

		}

		DynList<Arc*>*  makeBriefPath(Arc *start, Arc *Destino){
			resetRecorridos();
				
			
			return briefPath(start,Destino,this->graphMap);
			/*path->for_each([](Arc *a){

				cout << a->get_info().info << endl;
			});*/
			
		}

		void Clean(){

			for(int i = 0; i < (2*this->mapSize) + 1 ; i++){
				delete [] this->map[i];
			}
			delete[] this->map;
			clear_graph(*this->graphMap);
		}

		
	private:
		Graph *graphMap;
		char **map;
		int mapSize;

		void InitMap(){
			this->map = new char *[2*(this->mapSize)+1];
		    for(int i = 0; i < (2*(this->mapSize)+1) ;i++)   {
		      this->map[i] = new char[2*(this->mapSize)+1];
		    }
			for(int i = 0; i< (2*this->mapSize) + 1 ; i++){
				for (int j = 0; j < (2*this->mapSize) + 1 ; ++j){
					if((i == 0 || i == (2*this->mapSize) || i%2 + 1 == 1 || j == ( 2*this->mapSize) || j == 0  || j%2 + 1 == 1) ){
						this->map[i][j] = 'X';

					}else{
						this->map[i][j] = ' ';
					}
				}

			}

		}

		void InitGraph(){
			this->graphMap = new Graph();
			for (int i = 0; i < this->mapSize; ++i){
				this->graphMap->insert_node(i);
				
			}
			for (Graph::Node_Iterator it(*this->graphMap); it.has_curr(); it.next()){
				for (Graph::Node_Iterator it2(*this->graphMap); it2.has_curr(); it2.next()){
					ostringstream info ;
					info << "Arco de " <<  it.get_curr()->get_info() << " hacia " <<  it2.get_curr()->get_info();
					//cout << "info " << info.str() << endl;
					arcData data(info.str());
					this->graphMap->insert_arc(it.get_curr(), it2.get_curr(), data );
					enemysCord.first = 2*it2.get_curr()->get_info();
					enemysCord.second = 2*it.get_curr()->get_info();
				}
			}

		}

		void resetRecorridos(){
			resetGraphAvalible(this->graphMap);
		}

	
};


#endif