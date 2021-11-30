#include "main.h"
#include <iostream>
#include <bitset>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;



string MsgToBin(string message)
{
	string BinMsg = "";
	for (char& _char : message)
	{
		BinMsg += bitset<8>(_char).to_string();
	}

	return BinMsg;
}

string BinToPad(string message)
	{
	
	int length_val = MsgToBin(message).size();
	int k_val = 512 - ((length_val + 65) % 512);
	string zero = "";
	for (int i = 0; i < k_val; i++)
	{
		zero += "0";
	}
	string length = bitset<64>(length_val).to_string();
	string Pad = MsgToBin(message) + "1" + zero + length;

	return Pad;
	}

unsigned int ROT(int n, unsigned int x)
{
	return (x >> n) | (x << (32 - n));
}

unsigned int sig0(unsigned int x)
{
	return ROT(7, x) ^ ROT(18, x) ^ (x >> 3);
}

unsigned int sig1(unsigned int x)
{
	return ROT(17, x) ^ ROT(19, x) ^ (x >> 10);
}

unsigned int SIG0(unsigned int x)
{
	return ROT(2, x) ^ ROT(13, x) ^ ROT(22,x);
}

unsigned int SIG1(unsigned int x)
{
	return ROT(6, x) ^ ROT(11, x) ^ ROT(25, x);
}

unsigned int CH(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (~x & z);
}

unsigned int MAJ(unsigned int x, unsigned int y, unsigned int z)
{
	return (x & y) ^ (x & z) ^ (y & z);
}


string SHA256(string bits)
{
	string B[32];
	string word = "";

	unsigned int A[16];

	for (int h = 0; h < 16; h++)
	{
		word = bits.substr(h * 32, 32);
		A[h] = stoul(word, 0, 2);
	}

	unsigned int K[] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
			0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
			0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
			0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
			0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
			0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
			0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

	unsigned int H[] = {
		0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

	unsigned int W[64];
	for (int t = 0; t < 16; t++)
	{
		W[t] = A[t];
	}
	for (int t = 16; t < 64; t++)
	{
		W[t] = (sig1(W[t - 2]) + W[t - 7] + sig0(W[t - 15]) + W[t - 16]);
	}

	unsigned int a = H[0];
	unsigned int b = H[1];
	unsigned int c = H[2];
	unsigned int d = H[3];
	unsigned int e = H[4];
	unsigned int f = H[5];
	unsigned int g = H[6];
	unsigned int h = H[7];

	cout << "\n\nStep\ta\t\tb\t\tc\t\td\t\te\t\tf\t\tg\t\th\n\nInit\t";
	cout << hex << setfill('0') << setw(8) << a;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << b;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << c;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << d;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << e;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << f;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << g;
	cout << "\t";
	cout << hex << setfill('0') << setw(8) << h;
	cout << "\n";

	for (int t = 0; t < 64; t++)
	{
		unsigned int T1 = (h + SIG1(e) + CH(e, f, g) + K[t] + W[t]);
		unsigned int T2 = (SIG0(a) + MAJ(a, b, c));
		h = g;
		g = f;
		f = e;
		e = (d + T1);
		d = c;
		c = b;
		b = a;
		a = (T1 + T2);

		cout << "t=" << dec << t;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << a;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << b;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << c;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << d;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << e;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << f;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << g;
		cout << "\t";
		cout << hex << setfill('0') << setw(8) << h;
		cout << "\n";
	}

	H[0] = (H[0] + a);
	H[1] = (H[1] + b);
	H[2] = (H[2] + c);
	H[3] = (H[3] + d);
	H[4] = (H[4] + e);
	H[5] = (H[5] + f);
	H[6] = (H[6] + g);
	H[7] = (H[7] + h);

	return bitset<32>(H[0]).to_string()+ bitset<32>(H[1]).to_string()+ bitset<32>(H[2]).to_string()+ bitset<32>(H[3]).to_string()+ bitset<32>(H[4]).to_string()+ bitset<32>(H[5]).to_string()+ bitset<32>(H[6]).to_string()+ bitset<32>(H[7]).to_string();
}


int main(){
	string Msg;
	string Bin;
	string Hex;
	string Pad;
	string hash;
	unsigned int hashd;

	cout << "Enter your message: ";
	getline(cin, Msg);

	Bin = MsgToBin(Msg);

	cout << "\nBinary of Message: " + Bin + "\n";

	system("pause");

	cout << "\nHexadecimal of Input: ";

	int r = Msg.size();

	for (int i = 0; i < r; i++)
	{
		int character = int(Msg[i]);
		cout << hex << character;
	}

	cout << "\n";

	system("pause");

	Pad = BinToPad(Msg);

	cout << "\nPadded Binary Input: " + Pad + "\n";

	system("pause");

	hash = SHA256(Pad);

	cout << "\nBinary Hash Output: " + hash + "\n";

	system("pause");

	cout << "\nHexadecimal Hash Output: ";

	for (int i = 0; i < 64; i++)
	{
		string part = hash.substr(i * 4, 4);
		unsigned int hex_bit = stoul(part, 0, 2);
		cout << hex << hex_bit;
	}

	cout << "\n";

	system("pause");

	return 0;
}
