#pragma once

#include "ImageAcquirer.h"
#include "ImageProcessing.h"
#include "DigitRecognizerInterface.h"
#include "SudokuSolver.h"
#include "SolutionSender.h"

class Sudoku
{
public:
	Sudoku(void);
	~Sudoku(void);
	
	void Run(void);

private:
	ImageAcquirer image_acquirer;
	ImageProcessing image_processing;
	DigitRecognizerInterface* digit_recognizer;
	SudokuSolver sudoku_solver;
	SolutionSender solution_sender;

};

