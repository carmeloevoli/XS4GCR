#ifndef INCLUDE_INTERPOLATOR_H_
#define INCLUDE_INTERPOLATOR_H_

template<class T>
class Interpolator {
public:
	/*
	 *  Linear interpolation
	 *  @param target the target point in [0,1]
	 *  @param v a pointer to an array of size 2 containing the two values
	 *  @return linear interpolation at target
	 *  @see https://en.wikipedia.org/wiki/Linear_interpolation
	 */
	inline static T Linear(T target, T *v) {
		return (T) (target * (v[1]) + (T(1) - target) * (v[0]));
	}

	/*
	 *  BiLinear interpolation
	 *  @param target a 2D point (X,Y)
	 *  @param v an array of size 4 containing values clockwise around the square starting from bottom left
	 *  @return bilinear interpolation at target
	 *  @see https://en.wikipedia.org/wiki/Bilinear_interpolation
	 */
	inline static T Bilinear(T *target, T *v) {
		// v[0] = f_00, v[1] = f_01, v[2] = f_11, v[3] = f_10
		T value = v[0] * (T(1) - target[0]) * (T(1) - target[1]);
		value += v[1] * (T(1) - target[0]) * target[1];
		value += v[2] * target[0] * target[1];
		value += v[3] * target[0] * (T(1) - target[1]);
		return value;
		//return + v[3] * target[0] * (1. - target[1]) + v[1] * (1 - target[0]) * target[1] + v[2] * target[0] * target[1];
		//T v_prime[2] = { Linear(target[1], &(v[0])), Linear(target[1], &(v[2])) };
		//return Linear(target[0], v_prime);
	}

	/*inline static T Trilinear(T *target, T *v) {
	 T v_prime[2] = { Bilinear(&(target[0]), &(v[0])), Bilinear(&(target[1]), &(v[4])) };
	 return Linear(target[2], v_prime);
	 }*/
};

#endif /* INCLUDE_INTERPOLATOR_H_ */
