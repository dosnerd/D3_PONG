template <class T>
void Test::failIfDifferent(T value, T expected, std::string message){
	if (value != expected)
		fail(message);
}

template <class T>
void Test::failIfEqual(T value, T expected, std::string message){
	if (value == expected)
		fail(message);
}

template<class T>
void Test::log(T message) {
	std::lock_guard<std::mutex> lock(sLogMutex);
	std::cout << message << std::endl;
}
