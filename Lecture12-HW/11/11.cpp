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
	/* 교수님 코드 수정하다가 포기 으악
	int count = 0;

	chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();

	int delay_time_ms = 0;

	this_thread::sleep_for(chrono::milliseconds(1000));

	while (count < 10)
	{
		//시작시간과 끝시간
		prev_end = end;
		end = chrono::steady_clock::now();

		//시간차 구하기
		chrono::steady_clock::duration diff = end - prev_end; // 1500
		delay_time_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
		delay_time_ms = delay_time_ms-(delay_time_ms - 1000);
		//1000
		//1500
		//1000
		//1500 - 500
		//diff - (diff-1000)

		//출력

		cout << count++ << "   dur:" << delay_time_ms << endl;

		//슬립
		this_thread::sleep_for(chrono::milliseconds(delay_time_ms));

	}
	*/


	/* 내 코드
	int count = 0;
	int delay_time_ms = 0;
	int a = 1;
	//chrono::steady_clock::time_point start = chrono::steady_clock::now();
	
	chrono::steady_clock::time_point end;
	chrono::steady_clock::time_point prev_end;
	
	end = chrono::steady_clock::now();
	this_thread::sleep_for( chrono::milliseconds(1000));
	// >
	while (count < 10)
	{
		prev_end = end;
		end = chrono::steady_clock::now();
		chrono::steady_clock::duration diff = end - prev_end ;
		delay_time_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
		cout << count++ <<" , " << delay_time_ms << endl;
		this_thread::sleep_for( chrono::milliseconds(1000));
	}
	*/

	


	/*
	int count = 0;
	int delay_time_ms = 0;

	chrono::steady_clock::time_point start = chrono::steady_clock::now();
	chrono::steady_clock::time_point prev_end = chrono::steady_clock::now();
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	while (count < 10)
	{
		//delay_time_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();
		int ms = chrono::duration_cast<chrono::milliseconds>(end - prev_end).count();
		cout << count <<" , " << ms << endl;
		prev_end = end;
		this_thread::sleep_for(chrono::milliseconds(1000));
		end = chrono::steady_clock::now();
		count++;
		//chrono::steady_clock::duration diff = end - prev_end;
	}


	//0.01초를 while 주기로 만들기.
	int count = 0;
	chrono::steady_clock::time_point while_start = chrono::steady_clock::now();
	while (count < 1000)
	{
		count++;
		cout << count << endl;
		this_thread::sleep_for(chrono::milliseconds(10)); //1000 = 1 , 0.01 =10
	}
	chrono::steady_clock::time_point while_end = chrono::steady_clock::now();
	int ms = chrono::duration_cast<chrono::milliseconds>(while_end - while_start).count();
	cout << "총걸린시간 : " << ms << endl;
	*/


