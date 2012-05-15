#pragma once

#include <opencv2\core\core.hpp>
#include <boost\optional.hpp>
#include <boost\serialization\nvp.hpp>

class DigitExtractor
{
public:
	DigitExtractor(void);
	~DigitExtractor(void);

	boost::optional<cv::Mat> ExtractDigit(unsigned int col, unsigned int row,
										  unsigned int thresh);
	void LoadImage(cv::Mat& img);

	inline bool GetAdjustFlag(void) { return adjust_flag_; }
	inline void SetAdjustFlag(bool adjust_flag) { adjust_flag_ = adjust_flag; }
	inline int GetBlockSize(void) { return block_size_; }
	inline void SetBlockSize(int blockSize) { block_size_ = blockSize; }
	inline double GetC(void) { return c_; }
	inline void SetC(double c) { c_ = c; }
	inline int GetPercentage(void) { return percentage_; }
	inline void SetPercentage(int percentage) { percentage_ = percentage; }
	inline int GetN(void) { return n_; }
	inline void SetN(int n) { n_ = n; }

private:
	void Preprocess(cv::Mat* img);
	void SetDefaultParameters(void);
	bool Load(void);
	bool Save(void);

	cv::Mat input_img;
	cv::Mat cell_img;
	cv::Mat tmp_img;
	int cell_width;
	int cell_height;
	int cell_area;
	bool ready_flag;

	//parameters
	std::string file_name_;
	bool adjust_flag_;
	int block_size_;      
	double c_;	       
	int percentage_;
	int n_;

	friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
		using boost::serialization::make_nvp;
		ar & make_nvp("block_size", block_size_)
		   & make_nvp("c", c_)
		   & make_nvp("percentage", percentage_)
		   & make_nvp("n", n_);
    }
};

