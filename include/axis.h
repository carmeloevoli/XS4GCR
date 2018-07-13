#ifndef INCLUDE_AXIS_H_
#define INCLUDE_AXIS_H_

#include <cmath>

namespace DRAGON2 {

template<typename T>
class log_axis {
public:
	log_axis() :
			min_value(0), max_value(0), size(0) {
		ratio = 0;
	}
	log_axis(T min_, T max_, size_t size_) {
		set(min_, max_, size_);
	}
	void set_size(size_t size_) {
		size = size_;
	}
	void set_range(T min_, T max_) {
		min_value = min_;
		max_value = max_;
		if (size > 1)
			ratio = pow(max_value / min_value, 1 / (T) (size - 1));
	}
	void set(T min_, T max_, size_t size_) {
		set_size(size_);
		set_range(min_, max_);
	}
	size_t get_size() const {
		return size;
	}
	size_t get_idx(const T& value) const {
		return floor(std::log(value / min_value) / std::log(ratio));
	}
	T at(const size_t& i) const {
		return min_value * pow(ratio, (T) i);
	}
	T get_min() const {
		return min_value;
	}
	T get_max() const {
		return max_value;
	}
	T get_ratio() const {
		return ratio;
	}
	virtual ~log_axis() {
	}
protected:
	T min_value;
	T max_value;
	T ratio;
	size_t size;
};

} // namespace DRAGON2

#endif /* INCLUDE_AXIS_H_ */
