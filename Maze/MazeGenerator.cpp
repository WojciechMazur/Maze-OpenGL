#include "MazeGenerator.h"

Point2D<size_t>* Maze::MazeGenerator::finishPosition = NULL;
Array2D<Maze::EObject>* Maze::MazeGenerator::tilesMap = nullptr;

Maze::MazeGenerator::MazeGenerator(size_t _rows, size_t _collumns)
{
	srand(time(NULL));
	if (_rows % 2==0) _rows--;
	if (_collumns % 2==0) _collumns++;
	rows = _rows;
	collumns = _collumns;
	tilesMap = new Array2D<EObject>(rows, collumns);
	vistiedTiles = new Array2D<bool>(rows, collumns);
	currentPosition = new Point2D<size_t>(rows / 2-1 , collumns / 2-1 );
	startPosition = currentPosition;
	finishPosition =  new Point2D<size_t>(rows - 2, collumns - 2);
	preGenerationInit();
}

Maze::MazeGenerator::~MazeGenerator()
{
	delete tilesMap;
	delete vistiedTiles;
}

void Maze::MazeGenerator::setObject(EObject object, size_t row, size_t collumn)
{
	try {
		*this->tilesMap->operator()(row, collumn) = object;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}

void Maze::MazeGenerator::setObject(EObject object, Point2D<size_t> position)
{

	if( this->tilesMap->operator()(position.x, position.y) !=nullptr)
		*this->tilesMap->operator()(position.x, position.y) =object;
	else
		std::cout << "nullptr throwed from operator() pos:" << position.x << ", " << position.y << std::endl;

}

void Maze::MazeGenerator::print()
{
	try {
		std::cout << "\n\tMap of generated 2D maze\n\n";
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		Point2D<size_t> position(0, 0);
		for (size_t i = 0; i < this->rows; i++)
		{
			for (size_t j = 0; j < this->collumns; j++)
			{
				position = Point2D<size_t>(i, j);
				if (!*this->vistiedTiles->operator[](&position))
					SetConsoleTextAttribute(hConsole, 7);
				else
					SetConsoleTextAttribute(hConsole, 121);
				switch (*this->tilesMap->operator[](&position))
				{
				case WALL:
					std::cout << " #";
					break;
				case SPACE:
					std::cout << "  ";
					break;
				case START:
					std::cout << " S";
					break;
				case FINISH:
					std::cout << " F";
					break;
				default:
					std::cout << " !";
					break;
				}
			}
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, 7);
		std::cout <<"\n\n\n" ;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}


bool Maze::MazeGenerator::isMovePossibleInDirection(EDirection moveDirection) const
{
	try {
		Point2D<size_t> predictedPostion(*currentPosition);

		predictedPostion += moveDirection;

		if (*this->vistiedTiles->operator[](&predictedPostion) == false)
		{
			predictedPostion += moveDirection;
			if (*this->vistiedTiles->operator[](&predictedPostion) == false)
				return true;
		}
		return false;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}

bool Maze::MazeGenerator::isAnyMovePossible() const
{
	for(int i=0; i<4; i++)
		if(this->isMovePossibleInDirection(static_cast<Maze::EDirection>(i))==true)
			return true;
	return false;
}

void Maze::MazeGenerator::preGenerationInit()
{
	try {
		for (size_t i = 0; i < this->rows; i++)
		{
			this->setObject(WALL, i, 0);
			this->setVisited(i, 0);
			this->setObject(WALL, i, collumns - 1);
			this->setVisited(i, collumns - 1);
		}
		for (size_t i = 0; i < this->collumns; i++)
		{
			this->setObject(WALL, 0, i);
			this->setVisited(0, i);
			this->setObject(WALL, rows - 1, i);
			this->setVisited(rows - 1, i);
		}
		this->setObject(START, *currentPosition);
		this->setObject(FINISH, rows - 2, collumns - 2);
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}

void Maze::MazeGenerator::setVisited(Point2D<size_t>* position) 
{
	try {
		*this->vistiedTiles->operator[](position) = true;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
}

void Maze::MazeGenerator::setVisited(size_t row, size_t collumn)
{
	try {
		*this->vistiedTiles->operator()(row, collumn) = true;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
	}

void Maze::MazeGenerator::setVisited()
{
	try {
		if (this->vistiedTiles->operator[](currentPosition) != nullptr)
			*this->vistiedTiles->operator[](currentPosition) = true;
	}
	catch (std::out_of_range e) {
		std::cout << e.what() << std::endl;
	}
	}

void Maze::MazeGenerator::generate()
{
	std::stack < Point2D<size_t>> backTracker;
	backTracker.push(*currentPosition);
	EDirection newDirection;
	//Check is any move posible
	//system("cls");
	while (!backTracker.empty()) {
		*currentPosition = backTracker.top();
		backTracker.pop();
		while (this->isAnyMovePossible()) {
			//Sleep(100);
			//system("cls");
			//this->print();
			this->setObject(Maze::SPACE, *currentPosition);

			//Seek for new possible direction
			do {
				newDirection = static_cast<EDirection>(rand() % 4);
			} while (!isMovePossibleInDirection(newDirection));

			for (int i = 0; i < 2; i++) {
				*currentPosition += newDirection;
				setObject(Maze::SPACE, *currentPosition);
				setVisited(currentPosition);
			}
			if (*currentPosition == *finishPosition)
				break;
			backTracker.push(*currentPosition);
		}
	}
}

size_t Maze::MazeGenerator::getSizeRows()
{
	return rows;
}

size_t Maze::MazeGenerator::getSizeCollumns()
{
	return collumns;
}

Array2D<Maze::EObject>* Maze::MazeGenerator::getTilesMap()
{
	return tilesMap;
}

Point2D<size_t>* Maze::MazeGenerator::getCurrentPosition()
{
	return currentPosition;
}

Array2D<Maze::EObject>* Maze::MazeGenerator::getMazeTiles()
{
	return tilesMap;
}
