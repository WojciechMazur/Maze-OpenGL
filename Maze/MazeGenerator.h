#pragma once
#include "Array2D.h"
#include "Point2D.h"
#include <Windows.h>
#include <stack>
#include <time.h>

class MultiTextSphere;

namespace Maze {

	enum EObject {
		WALL, SPACE, START, FINISH
	};

	enum EDirection {
		UP, RIGHT, DOWN, LEFT
	};

	class MazeGenerator
	{
	public:
		MazeGenerator(size_t rows, size_t collumns);
		~MazeGenerator();
		void setObject(EObject object, size_t row, size_t collumn);
		void setObject(EObject object, Point2D<size_t> position);
		void print();
		void setVisited(Point2D<size_t>* position);
		void setVisited(size_t row, size_t collumn);
		void setVisited();
		void generate();
		size_t getSizeRows();
		size_t getSizeCollumns();
		Array2D<EObject>* getTilesMap();
		Point2D<size_t>* getCurrentPosition();
		static Array2D<Maze::EObject>* getMazeTiles();
	private:
		void preGenerationInit();
		bool isAnyMovePossible()const;
		bool isMovePossibleInDirection(EDirection direction) const;

	private:
		size_t rows, collumns;
		static Array2D<EObject>* tilesMap;
		Array2D<bool>* vistiedTiles;
		Point2D<size_t>* currentPosition;

	public:
		Point2D<size_t>* startPosition;
		static Point2D<size_t>* finishPosition;
	
	friend class MultiTextSphere;
	friend class SceneManager;;
	friend class Camera;
	};

}

