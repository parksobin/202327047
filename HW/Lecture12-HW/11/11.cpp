#include <iostream>
#include <chrono>
#include <thread> //sleep 이라는 함수 (잠깐 아무것도 안 하는 거)

using namespace std;
/*
chrono::steady_clock::time_point while_time;
chrono::steady_clock::time_point while_start = chrono::steady_clock::now();
chrono::steady_clock::time_point while_end;
int whiletime;
*/
chrono::steady_clock::time_point end = chrono::steady_clock::now();
int time()
{
	return 0;
}
int main()
{
	int count = 0;
	int delay_time_ms = 0;
	//chrono::steady_clock::time_point start = chrono::steady_clock::now();

	//chrono::steady_clock::duration diff;
	chrono::steady_clock::time_point end;
	chrono::steady_clock::time_point prev_end;

	end = chrono::steady_clock::now();
	this_thread::sleep_for(chrono::milliseconds(1000));
	// >
	while (count < 10)
	{
		prev_end = end;
		end = chrono::steady_clock::now();
		delay_time_ms = chrono::duration_cast<chrono::milliseconds>(end - prev_end).count();
		cout << count++ << " , " << delay_time_ms << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}



