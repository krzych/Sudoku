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

	inline int GetBlockSize(void) { return block_size_; }
	inline void SetBlockSize(int blockSize) { block_size_ = blockSize; }
	inline double GetC(void) { return c_; }
	inline void SetC(double c) { c_ = c; }
	inline int GetPercentage(void) { return percentage_; }
	inline void SetPercentage(int percentage) { percentage_ = percentage; }
	inline int GetN(void) { return n_; }
	inline void SetN(int n) { n_ = n; }
	inline int GetKernelSizeMorph(void) { return kernel_size_morph_; }
	inline void SetKernelSizeMorph(int kernel_size) { kernel_size_morph_ = kernel_size; }

	void ClearAdjustFlags(void);
	//void SetThresholdFlag(void) { ClearAdjustFlags(); threshold_flag = true; }
	//void SetFillBordersFlag(void) { ClearAdjustFlags(); fill_borders_flag = true; }
	//void SetNBlobsFlag(void) { ClearAdjustFlags(); n_blobs_flag = true; }
	//void SetBlobFlag(void) { ClearAdjustFlags(); blob_flag = true; }
	void SetAdjustFlag(void) { ClearAdjustFlags(); adjust_flag = true; }

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
	bool adjust_flag;

	//parameters
	std::string file_name_;
	int block_size_;      
	double c_;	       
	int percentage_;
	int n_;
	int kernel_size_morph_;

	friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
		using boost::serialization::make_nvp;
		ar & make_nvp("block_size", block_size_)
		   & make_nvp("c", c_)
		   & make_nvp("percentage", percentage_)
		   & make_nvp("n", n_)
		   & make_nvp("kernel_size_morph", kernel_size_morph_);
    }
};

