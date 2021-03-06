
#include "Sudoku.h"
#include "NormalizedCentralMomentsRecognizer.h"
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;

Sudoku::Sudoku(void)
{
}


Sudoku::~Sudoku(void)
{
	delete digit_recognizer;
}

void Sudoku::Run(void)
{
	string file_name;
	cout << "Filename: ";
	cin >> file_name;
	cv::Mat input_img = image_acquirer.AcquireImage(file_name.c_str());
	image_processing.ImageLoad(input_img);

	digit_recognizer = new NormalizedCentralMomentsRecognizer();
	digit_recognizer->SetMode(DEFAULT_MODE);

	std::vector<SudokuCellImg> extractd_cell_imgs = image_processing.Run();
	digit_recognizer->LoadInput(extractd_cell_imgs);

	std::vector<SudokuCell> v = digit_recognizer->Run();
	while(sudoku_solver.LoadInput(v) == false) {
		digit_recognizer->SetMode(TRAINING_MODE);
		v = digit_recognizer->Run();
	}
	std::vector<SudokuCell> solution = sudoku_solver.Run();
	cv::Mat extracted_sudoku = image_processing.GetSudoku();
	solution_sender.LoadSolution(solution);
	solution_sender.ImageLoad(extracted_sudoku);
	solution_sender.Run();

	cv::waitKey(0);
}
