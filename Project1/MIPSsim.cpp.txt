/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int binaryStringToInt(string s) {
	int output = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') output += 1 << (s.size() - i - 1);
	}
	return output;
}


int binaryStringToShortInt(string s) {
	short output = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') output += 1 << (s.size() - i - 1);
	}
	return output;
}


int main(int argc, char* argv[]) {
	string fileName = "sample.txt";
	if (argc > 1) fileName = argv[1];
	string dout = "disassembly.txt", sout = "simulation.txt";
	ifstream input;
	ofstream outputD, outputS;
	input.open(fileName.c_str(), ios::in);
	outputD.open(dout.c_str(), ios::out);
	outputS.open(sout.c_str(), ios::out);
	map<int, string> commandStore;
	map<int, string> disassemblyStore;
	string temp = "";
	int counter = 260;
	while (getline(input, temp)) { // decode command
		//input >> temp;
		string opcode = temp.substr(0, 6);
		string command = "";
		if (opcode == "000000") { // J
			string t = temp.substr(6, 26);
			t = t + "00";
			int num = binaryStringToInt(t);
			command = "J #" + to_string(num);

		} else if (opcode == "000001") { // BEQ
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			command = "BEQ R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #" + to_string(binaryStringToInt(offset));

		} else if (opcode =="000010") { // BNE
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			command = "BNE R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #" + to_string(binaryStringToInt(offset));
			
		} else if (opcode == "000011") { // BGTZ
			string r1 = temp.substr(6, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			command = "BGTZ R" + to_string(binaryStringToInt(r1)) + ", #" + to_string(binaryStringToInt(offset));
			
		} else if (opcode == "000100") { // SW
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			command = "SW R" + to_string(binaryStringToInt(r2)) + ", " + to_string(binaryStringToInt(offset)) + "(R" + to_string(binaryStringToInt(r1)) + ")";
			
		} else if (opcode == "000101") { // LW
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			command = "LW R" + to_string(binaryStringToInt(r2)) + ", " + to_string(binaryStringToInt(offset)) + "(R" + to_string(binaryStringToInt(r1)) + ")";
			
		} else if (opcode == "000110") { // BREAK
			command = "BREAK";
			disassemblyStore[counter] = command;
			outputD << temp << "\t" << to_string(counter) << "\t" << command << endl;
			counter += 4;
			break;
		} else if (opcode == "001000") { // ADD
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "ADD R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", R" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "001001") { // SUB
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "SUB R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", R" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "001010") { // AND
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "AND R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", R" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "001011") { // OR
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "OR R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", R" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "001100") { // SRL
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "SRL R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #" + to_string(binaryStringToInt(r3));
		} else if (opcode == "001101") { // SRA
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "SRA R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "001110") { // MUL
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			command = "MUL R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", R" + to_string(binaryStringToInt(r3));
			
		} else if (opcode == "010000") { // ADDI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			command = "ADDI R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #"+ to_string(binaryStringToInt(im));
			
		} else if (opcode == "010001") { // ANDI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			command = "ANDI R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #"+ to_string(binaryStringToInt(im));
			
		} else if (opcode == "010010") { // ORI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			command = "ORI R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #"+ to_string(binaryStringToInt(im));
			
		} else {
			cout << "no command!" << endl;
		}
		commandStore[counter] = temp;
		disassemblyStore[counter] = command;
		outputD << temp << "\t" << to_string(counter) << "\t" << command << endl;
		counter += 4;
	}
	map<int, int> D;
	int mark = counter;
	int numOfData = 0;
	while (getline(input, temp)) { // set memory
		//cout << binaryStringToInt(temp) << endl;
		//D[numOfData] = binaryStringToInt(temp);
		D[counter] = binaryStringToInt(temp);
		//cout << D[counter] << endl;
		outputD << temp << "\t" << to_string(counter) << "\t" << to_string(binaryStringToInt(temp)) << endl;
		counter += 4;
		numOfData++;
	}
	input.close();
	int R[32];
	for (int i = 0; i < 32; i++) R[i] = 0;	
	int ct = 0;
	for (int i = 260; i < mark; i += 4) { // execute
		ct++;
		temp = commandStore[i];
		string opcode = temp.substr(0, 6);
		int nexti = i;
		if (opcode == "000000") { // J
			string t = temp.substr(6, 26);
			t = t + "00";
			int num = binaryStringToInt(t);
			nexti = num - 4;
		} else if (opcode == "000001") { // BEQ
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			if (R[binaryStringToInt(r1)] == R[binaryStringToInt(r2)]) {
				nexti = i + binaryStringToInt(offset);
			}
		} else if (opcode =="000010") { // BNE
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			if (R[binaryStringToInt(r1)] != R[binaryStringToInt(r2)]) {
				nexti = i + binaryStringToInt(offset);
			}
		} else if (opcode == "000011") { // BGTZ
			string r1 = temp.substr(6, 5);
			string offset = temp.substr(16, 16);
			offset = offset + "00";
			if (R[binaryStringToInt(r1)] > 0) {
				nexti = i + binaryStringToInt(offset);
			}
		} else if (opcode == "000100") { // SW
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]] = R[binaryStringToInt(r2)];
		} else if (opcode == "000101") { // LW
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			R[binaryStringToInt(r2)] = D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]];
		} else if (opcode == "000110") { // BREAK
			break;
		} else if (opcode == "001000") { // ADD
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] + R[binaryStringToInt(r3)];
		} else if (opcode == "001001") { // SUB
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] - R[binaryStringToInt(r3)];
		} else if (opcode == "001010") { // AND
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] & R[binaryStringToInt(r3)];
		} else if (opcode == "001011") { // OR
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] | R[binaryStringToInt(r3)];
		} else if (opcode == "001100") { // SRL
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			if (R[binaryStringToInt(r2)] > 0) {
				R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] >> binaryStringToInt(r3);
			} else {
				if (binaryStringToInt(r3) == 0) {
					R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)];
				} else {
					R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] >> 1;
					R[binaryStringToInt(r1)] -= (1 << 31);
					R[binaryStringToInt(r1)] = R[binaryStringToInt(r1)] >> (binaryStringToInt(r3) - 1);
				}
			}	
		} else if (opcode == "001101") { // SRA
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] >> binaryStringToInt(r3);	
		} else if (opcode == "001110") { // MUL
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] * R[binaryStringToInt(r3)];
		} else if (opcode == "010000") { // ADDI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] + binaryStringToShortInt(im);
		} else if (opcode == "010001") { // ANDI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] & binaryStringToShortInt(im);
		} else if (opcode == "010010") { // ORI
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string im = temp.substr(16, 16);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] | binaryStringToShortInt(im);
		} else {
			//cout << "no command!" << endl;
		}
		/*
		cout << "--------------------" << endl;
		cout << "Cycle " << ct << ":\t" << i << "\t" << disassemblyStore[i] << endl << endl;
		cout << "Registers" << endl;
		cout << "R00:\t" << R[0] << "\t" << R[1] << "\t" << R[2] << "\t" << R[3] << "\t" << R[4] << "\t" << R[5] << "\t" << R[6] << "\t" << R[7] << endl;
		cout << "R08:\t" << R[8] << "\t" << R[9] << "\t" << R[10] << "\t" << R[11] << "\t" << R[12] << "\t" << R[13] << "\t" << R[14] << "\t" << R[15] << endl;
		cout << "R16:\t" << R[16] << "\t" << R[17] << "\t" << R[18] << "\t" << R[19] << "\t" << R[20] << "\t" << R[21] << "\t" << R[22] << "\t" << R[23] << endl;
		cout << "R24:\t" << R[24] << "\t" << R[25] << "\t" << R[26] << "\t" << R[27] << "\t" << R[28] << "\t" << R[29] << "\t" << R[30] << "\t" << R[31] << endl;
		cout << endl;
		cout << "Data" << endl;
		for (int j = mark; j < counter; j += 32) {
			cout << j << ":\t";
			for (int k = 0; k < 8; k++) cout << D[j + 4 * k] << "\t";
			cout << endl;
		}
		cout << endl;
		*/
		
		outputS << "--------------------" << endl;
		outputS << "Cycle " << ct << ":\t" << i << "\t" << disassemblyStore[i] << endl << endl;
		outputS << "Registers" << endl;
		outputS << "R00:\t" << R[0] << "\t" << R[1] << "\t" << R[2] << "\t" << R[3] << "\t" << R[4] << "\t" << R[5] << "\t" << R[6] << "\t" << R[7] << endl;
		outputS << "R08:\t" << R[8] << "\t" << R[9] << "\t" << R[10] << "\t" << R[11] << "\t" << R[12] << "\t" << R[13] << "\t" << R[14] << "\t" << R[15] << endl;
		outputS << "R16:\t" << R[16] << "\t" << R[17] << "\t" << R[18] << "\t" << R[19] << "\t" << R[20] << "\t" << R[21] << "\t" << R[22] << "\t" << R[23] << endl;
		outputS << "R24:\t" << R[24] << "\t" << R[25] << "\t" << R[26] << "\t" << R[27] << "\t" << R[28] << "\t" << R[29] << "\t" << R[30] << "\t" << R[31] << endl;
		outputS << endl;
		outputS << "Data" << endl;
		for (int j = mark; j < counter; j += 32) {
			outputS << j << ":";
			for (int k = 0; k < 8; k++) outputS << "\t" << D[j + 4 * k];
			outputS << endl;
		}
		if (disassemblyStore[i] != "BREAK") outputS << endl;
		
		i = nexti;
	}
	
	return 0;
}
