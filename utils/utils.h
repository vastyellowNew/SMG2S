//#include <random>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>

template<class T>
T random_unint(T min, T max)
{
/*
	std::default_random_engine e(time(NULL));
	std::uniform_real_distribution<T> u(min, max);
*/	
	return (min + static_cast<T>(max * rand() / static_cast<T>(RAND_MAX + 1)));

}

template<class S>
S factorial(S start, S end)
{
	S i;
	S value;

	if(start > end){
		value = 1;
	}
	else{
		value = start;
		for(i = start + 1; i <= end; i++){
			value *= i;
		}
	}

	return value;
}

template<class S>
std::map<S,S> nilpotent(S matrix_size, S degree)
{
	std::map<S,S> zeroPosition; //<index, zeros' postion in niplotent matrix >

	S i, j = 0;

	S size = (S) matrix_size / ( degree + 1 );

	printf("DEBUG >>> The zero array size for nilpotent matrix should be %d! \n", size);

	for(i=0;i<matrix_size-1;i++){
		i = i + degree;
		zeroPosition.insert(std::pair<S,S>(j,i));
		j++;
		if(i + degree > matrix_size-2) break;
	}

	return zeroPosition;

}

template<typename S>
struct Nilpotency
{
	S	diagPosition; //off-diagonal offset
	S	nbOne; //continuous 1 number of nilpotent matrix
	S   matrix_size; //matrix size

	Nilpotency()
	{
		diagPosition = 0;
		nbOne = 0;
		matrix_size = 0;
	};

	Nilpotency(S offset, S num, S size)
	{
		diagPosition = offset;
		nbOne = num;
		matrix_size = size;
	
	};

	~Nilpotency()
	{

	};

};

