#ifndef FILTERWHEEL_HPP
#define FILTERWHEEL_HPP


class FilterWheel  {
	private:

	public:
	
		void SeppLoganMatrixFilter(cv::Mat& Matrix);
		double SeppLoganMatrixFilterFunction(double value);
};

#endif // FILTERWHEEL_HPP

