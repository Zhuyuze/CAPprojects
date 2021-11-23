/* On my honor, I have neither given nor received unauthorized aid on this assignment */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int binaryStringToInt(string s) {
	int output = 0;
	for (int i = 0; i < (s.size() == 33? 32: s.size()); i++) {
		if (s[i] == '1') output += 1 << ((s.size() == 33? 32: s.size()) - i - 1);
	}
	return output;
}


int binaryStringToShortInt(string s) {
	short output = 0;
	for (int i = 0; i < 16; i++) {
		if (s[i] == '1') output += 1 << (16 - i - 1);
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
	map<int, pair<string,string>> commandStore;
	string temp = "";
	int counter = 260;
	while (getline(input, temp)) { // decode command
		//input >> temp;
		temp = temp.substr(0, 32);
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
			outputD << temp << "\t" << to_string(counter) << "\t" << command << endl;
			commandStore[counter] = pair<string,string>(temp, command);
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
			command = "ADDI R" + to_string(binaryStringToInt(r1)) + ", R" + to_string(binaryStringToInt(r2)) + ", #"+ to_string(binaryStringToShortInt(im)); // binaryStringToInt to binaryStringToShortInt
			
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
		commandStore[counter] = pair<string,string>(temp, command);
		outputD << commandStore[counter].first << "\t" << to_string(counter) << "\t" << commandStore[counter].second << endl;
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
	
	
	
	
	
	
	
	
	
	
	
	
	// SIMULATION
	int R[32] = {0};
	int toWrite[32];
	for (int i = 0; i < 32; i++) toWrite[i] = 0;
	int RAW[32];
	for (int i = 0; i < 32; i++) RAW[i] = 0;
	bool WAR[32];
	for (int i = 0; i < 32; i++) WAR[i] = false;
	int IF[2] = {0}, B1[8] = {0}, B2[2] = {0}, B3[2] = {0}, B4[2] = {0}, B5 = 0, B6 = 0, B7 = 0, B8 = 0, B9 = 0, B10 = 0;
	string sB6, sB8, sB10;
	bool isWB, isHazard;
	for (int i = 0; i < 32; i++) R[i] = 0;	
	int ct = 0;
	int i = 260;
	while (1) { // execute commandStore[i].second != "BREAK"
		ct++;
		//if(ct > 100) break;
		int tw8 = -1, tw6 = -1, tw10 = -1;
		int RAW6 = -1, RAW8 = -1, RAW10 = -1;
		int WAR81 = -1, WAR82 = -1, WAR61 = -1, WAR62 = -1, WAR101 = -1, WAR102 = -1;
		
		
		// SW & LW
		if (B8 != 0) { // LW
			string temp = commandStore[B8].first;
			string opcode = temp.substr(0, 6);
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string offset = temp.substr(16, 16);
			R[binaryStringToInt(r2)] = D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]];
			tw8 = binaryStringToInt(r2);
			RAW8 = binaryStringToInt(r2);
			//WAR81 = binaryStringToInt(r1);
			WAR[binaryStringToInt(r1)] = false;
			B8 = 0;
			isWB = true;
		}
		if (B5 != 0) {
			string temp = commandStore[B5].first;
			string opcode = temp.substr(0, 6);
			if (opcode == "000100") { // SW
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string offset = temp.substr(16, 16);
				D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]] = R[binaryStringToInt(r2)];
				//WAR[binaryStringToInt(r1)] = false;
				//WAR[binaryStringToInt(r2)] = false;
				//WAR81 = binaryStringToInt(r1);
				//WAR82 = binaryStringToInt(r2);
			} else {
				B8 = B5;
				string temp = commandStore[B8].first;
				string opcode = temp.substr(0, 6);
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string offset = temp.substr(16, 16);
				//R[binaryStringToInt(r2)] = D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]];
				sB8 = to_string(D[binaryStringToInt(offset) + R[binaryStringToInt(r1)]]) + ", R" + to_string(binaryStringToInt(r2));
			}
			B5 = 0;
		}
		if (B2[0] != 0) {
			B5 = B2[0];
			B2[0] = B2[1];
			B2[1] = 0;
		}
		
		
		
		
		
		
		
		
		// others
		if (B6 != 0) {
			string temp = commandStore[B6].first;
			//cout << temp << "!!!";
			string opcode = temp.substr(0, 6);
			if (opcode == "001000") { // ADD
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
				if (R[binaryStringToInt(r2)] >= 0) {// > to >=
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
			}
			tw6 = binaryStringToInt(temp.substr(6, 5));
			RAW6 = binaryStringToInt(temp.substr(6, 5));
			//WAR61 = binaryStringToInt(temp.substr(11, 5));
			//WAR[binaryStringToInt(temp.substr(11, 5))] = false;
			//if (opcode != "010000" && opcode != "010001" && opcode != "010010") WAR62 = binaryStringToInt(temp.substr(16, 5));
			//if (opcode != "010000" && opcode != "010001" && opcode != "010010") WAR[binaryStringToInt(temp.substr(16, 5))] = false;
			isWB = true;
			B6 = 0;	
		}
		if (B3[0] != 0) {
			B6 = B3[0];
			B3[0] = B3[1];
			B3[1] = 0;
			int result;
			string temp = commandStore[B6].first;
			
			string opcode = temp.substr(0, 6);
			
			if (opcode == "001000") { // ADD
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				result = R[binaryStringToInt(r2)] + R[binaryStringToInt(r3)];
			} else if (opcode == "001001") { // SUB
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				result = R[binaryStringToInt(r2)] - R[binaryStringToInt(r3)];
			} else if (opcode == "001010") { // AND
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				result = R[binaryStringToInt(r2)] & R[binaryStringToInt(r3)];
			} else if (opcode == "001011") { // OR
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				result = R[binaryStringToInt(r2)] | R[binaryStringToInt(r3)];
			} else if (opcode == "001100") { // SRL
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				if (R[binaryStringToInt(r2)] >= 0) {// > to >=
					result = R[binaryStringToInt(r2)] >> binaryStringToInt(r3);
				} else {
					if (binaryStringToInt(r3) == 0) {
						result = R[binaryStringToInt(r2)];
					} else {
						result = R[binaryStringToInt(r2)] >> 1;
						result -= (1 << 31);
						result = R[binaryStringToInt(r1)] >> (binaryStringToInt(r3) - 1);
					}
				}	
			} else if (opcode == "001101") { // SRA
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string r3 = temp.substr(16, 5);
				result = R[binaryStringToInt(r2)] >> binaryStringToInt(r3);	
			} else if (opcode == "010000") { // ADDI
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string im = temp.substr(16, 16);
				result = R[binaryStringToInt(r2)] + binaryStringToShortInt(im);
			} else if (opcode == "010001") { // ANDI
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string im = temp.substr(16, 16);
				result = R[binaryStringToInt(r2)] & binaryStringToShortInt(im);
			} else if (opcode == "010010") { // ORI
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				string im = temp.substr(16, 16);
				result = R[binaryStringToInt(r2)] | binaryStringToShortInt(im);
			}
			
			sB6 = to_string(result) + ", R" + to_string(binaryStringToInt(temp.substr(6, 5)));
			
		}
		
		
		
		
		
		
		
		
		
		
		
		// MUL
		if (B10 != 0) {
			string temp = commandStore[B10].first;
			string opcode = temp.substr(0, 6);
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] * R[binaryStringToInt(r3)];
			tw10 = binaryStringToInt(r1);
			RAW10 = binaryStringToInt(r1);
			//WAR[binaryStringToInt(r2)] = false;
			//WAR[binaryStringToInt(r3)] = false;
			//WAR101 = binaryStringToInt(r2);
			//WAR102 = binaryStringToInt(r3);
			B10 = 0;
			isWB = true;
		}
		if (B9 != 0) {
			B10 = B9;
			B9 = 0;
			string temp = commandStore[B10].first;
			string opcode = temp.substr(0, 6);
			string r1 = temp.substr(6, 5);
			string r2 = temp.substr(11, 5);
			string r3 = temp.substr(16, 5);
			//R[binaryStringToInt(r1)] = R[binaryStringToInt(r2)] * R[binaryStringToInt(r3)];
			sB10 = to_string(R[binaryStringToInt(r2)] * R[binaryStringToInt(r3)]) + ", R" + to_string(binaryStringToInt(r1));
			
		}
		if (B7 != 0) {
			B9 = B7;
			B7 = 0;
		}
		if (B4[0] != 0) {
			B7 = B4[0];
			B4[0] = B4[1];
			B4[1] = 0;
		}
		
		
		// IS
		if (B1[0] != 0) {
			bool toRead[32];
			for (int i = 0; i < 32; i++) toRead[i] = false;
			
			
			int po = 0;
			while (po < 8 && B1[po] != 0) po++;
			
			int c1 = 2, c2 = 2, c3 = 2;
			if (B2[0] != 0) c1 = 0;
			if (B3[0] != 0) c2 = 0;
			if (B4[0] != 0) c3 = 0;
			int cp = 0;
			for (int j = 0; j < 6; j++) {
				if (cp >= po) break;
				string temp = commandStore[B1[cp]].first;
				string opcode = temp.substr(0, 6);
				if (c1 > 0 && (opcode == "000100" || opcode == "000101")) { // SW & LW
					// to do: hazard prevention
					string r1 = temp.substr(6, 5);
					string r2 = temp.substr(11, 5);
					if (B3[0] != 0 || B4[0] != 0 || B7 != 0 || B9 != 0 || B6 != 0 || B10 != 0) {
						cp++;
						continue;
					}
					
					
					if (opcode == "000100") { //SW, read r1 & r2, RAW
						if (RAW[binaryStringToInt(r1)] != 0 || RAW[binaryStringToInt(r2)] != 0) break;
					} else {
						if (RAW[binaryStringToInt(r1)] != 0) break; // LW, only read r1
						if (RAW[binaryStringToInt(r2)] != 0) break; // LW, WAW
					}
					
					
					if (opcode == "000101") { // LW, WAR
						if (toRead[binaryStringToInt(r2)]) break;
					}
					
					
					
					B2[2-c1] = B1[cp];
					toRead[binaryStringToInt(r1)] = true;
					toRead[binaryStringToInt(r2)] = true;
					if (opcode == "000101") {
						RAW[binaryStringToInt(temp.substr(11,5))]++;
						//WAR[binaryStringToInt(temp.substr(6,5))] = false;
						WAR81 = binaryStringToInt(temp.substr(6,5));
					} else {
						WAR81 = binaryStringToInt(temp.substr(6,5));
						WAR82 = binaryStringToInt(temp.substr(11,5));
						//WAR[binaryStringToInt(temp.substr(11,5))] = false;
						//WAR[binaryStringToInt(temp.substr(6,5))] = false;
					}
					
					for (int k = cp; k < po - 1; k++) B1[k] = B1[k+1];
					for (int k = po-1; k < 8; k++) B1[k] = 0;
					po--;
					c1--;
				} else if (c2 > 0 && opcode != "001110") { // others
					//cout << commandStore[B1[cp]].second;
					if (opcode == "010000" || opcode == "010001" || opcode == "010010" || opcode == "001100"|| opcode == "001101") {
						string r2 = temp.substr(11, 5);
						if (RAW[binaryStringToInt(r2)] != 0) break;//RAW
					} else {
						string r2 = temp.substr(11, 5);
						string r3 = temp.substr(16, 5);
						if (RAW[binaryStringToInt(r2)] != 0 || RAW[binaryStringToInt(r3)] != 0) break;
					}
					string r1 = temp.substr(6, 5);
					
					if (RAW[binaryStringToInt(r1)] != 0) break; //WAW
					//cout << isHazard << endl;
					//cout << toRead[binaryStringToInt(r1)] << endl;
					
					if (isHazard) {
						isHazard = false;
						break;
					}
					
					
					if (toRead[binaryStringToInt(r1)]) break;// WAR
					
					
					
					// to do: hazard prevention
					
					
					if (cp > 0) {
						for (int k = 0; k < cp; k++) {
							string ttemp = commandStore[B1[k]].first;
							string topcode = ttemp.substr(0, 6);
							if (topcode == "000100" || topcode == "000101") {
								string r1 = ttemp.substr(6, 5);
								string r2 = ttemp.substr(11, 5);
								string r3 = temp.substr(6, 5);
								if (r1 == r3 || r2 == r3) {
									isHazard = true;
									break;
								}
							} else {
								if (opcode == "010000" || opcode == "010001" || opcode == "010010") {
									string r1 = ttemp.substr(11, 5);
									string r3 = temp.substr(6, 5);
									if (r1 == r3) {
										isHazard = true;
										break;
									}
								} else {
									string r1 = ttemp.substr(11, 5);
									string r2 = ttemp.substr(16, 5);
									string r3 = temp.substr(6, 5);
									if (r1 == r3 || r2 == r3) {
										isHazard = true;
										break;
									}
								}	
							}
						}
						
					}
					if (isHazard) break;
					
					//cout << commandStore[B1[cp]].second;
					B3[2-c2] = B1[cp];
					RAW[binaryStringToInt(temp.substr(6,5))]++;
					if (opcode == "010000" || opcode == "010001" || opcode == "010010" || opcode == "001100"|| opcode == "001101") {
						toRead[binaryStringToInt(temp.substr(11,5))] = true;
						WAR61 = binaryStringToInt(temp.substr(11,5));
						//WAR[binaryStringToInt(temp.substr(11,5))] = false;
					} else {
						toRead[binaryStringToInt(temp.substr(11,5))] = true;
						toRead[binaryStringToInt(temp.substr(16,5))] = true;
						WAR61 = binaryStringToInt(temp.substr(11,5));
						WAR62 = binaryStringToInt(temp.substr(16,5));
						//WAR[binaryStringToInt(temp.substr(11,5))] = false;
						//WAR[binaryStringToInt(temp.substr(16,5))] = false;
					}
					
					
					for (int k = cp; k < po - 1; k++) B1[k] = B1[k+1];
					for (int k = po-1; k < 8; k++) B1[k] = 0;
					po--;
					c2--;
				} else if (c3 > 0 && opcode == "001110") { // MUL
					string r1 = temp.substr(6, 5);
					string r2 = temp.substr(11, 5);
					string r3 = temp.substr(16, 5);
					if (RAW[binaryStringToInt(r2)] != 0 || RAW[binaryStringToInt(r3)] != 0) break; //RAW
					
					if (isHazard) {
						isHazard = false;
						break;
					}
					if (RAW[binaryStringToInt(r1)] != 0) break; //WAW
					if (toRead[binaryStringToInt(r1)]) break; //WAR
					
					
					if (cp > 0) {
						for (int k = 0; k < cp; k++) {
							string ttemp = commandStore[B1[k]].first;
							string topcode = ttemp.substr(0, 6);
							if (topcode == "000100" || topcode == "000101") {
								string r1 = ttemp.substr(6, 5);
								string r2 = ttemp.substr(11, 5);
								string r3 = temp.substr(6, 5);
								if (r1 == r3 || r2 == r3) {
									isHazard = true;
									break;
								}
							} else {
								if (opcode == "010000" || opcode == "010001" || opcode == "010010") {
									string r1 = ttemp.substr(11, 5);
									string r3 = temp.substr(6, 5);
									if (r1 == r3) {
										isHazard = true;
										break;
									}
								} else {
									string r1 = ttemp.substr(11, 5);
									string r2 = ttemp.substr(16, 5);
									string r3 = temp.substr(6, 5);
									if (r1 == r3 || r2 == r3) {
										isHazard = true;
										break;
									}
								}	
							}
						}
						
					}
					if (isHazard) break;
					
					
					
					
					
					if (B2[0] != 0) {
						string temp = commandStore[B2[0]].first;
						string opcode = temp.substr(0, 6);
						if (opcode == "000101") {
							break;
						}
					}
					if (B2[1] != 0) {
						string temp = commandStore[B2[1]].first;
						string opcode = temp.substr(0, 6);
						if (opcode == "000101") {
							break;
						}
					}
					if (B5 != 0) {
						string temp = commandStore[B5].first;
						string opcode = temp.substr(0, 6);
						if (opcode == "000101") {
							break;
						}
					}
					if (B8 != 0) {
						string temp = commandStore[B8].first;
						string opcode = temp.substr(0, 6);
						if (opcode == "000101") {
							break;
						}
					}
					//if (isWB) break;
					
					B4[2-c3] = B1[cp];
					RAW[binaryStringToInt(temp.substr(6,5))]++;
					toRead[binaryStringToInt(temp.substr(11,5))] = true;
					toRead[binaryStringToInt(temp.substr(16,5))] = true;
					WAR101 = binaryStringToInt(temp.substr(11,5));
					WAR102 = binaryStringToInt(temp.substr(16,5));
					//WAR[binaryStringToInt(temp.substr(11,5))] = false;
					//WAR[binaryStringToInt(temp.substr(16,5))] = false;
					for (int k = cp; k < po - 1; k++) B1[k] = B1[k+1];
					for (int k = po-1; k < 8; k++) B1[k] = 0;
					po--;
					c3--;
				}
			}
		}
		
		
		
		
		// IF
		if (IF[0] == 0) {
			int po = 0;
			while (po < 8 && B1[po] != 0) po++;
			bool fuck = false;
			for (int j = 0; j < 4; j++) {
				string temp = commandStore[i].first;
				string opcode = temp.substr(0, 6);
				
				if (temp == "00011000000000000000000000000000") { // find break
					fuck = true;
					break;
				}
				if (opcode == "000000") {
					IF[1] = i;
					string t = temp.substr(6, 26);
					t = t + "00";
					i = binaryStringToInt(t);
					break;
				}
				if (opcode == "000001" || opcode =="000010" || opcode == "000011") {
					IF[0] = i;
					break;
				}
				
				
				//update toWrite
				if (opcode == "000100");
				else if (opcode == "000101") {
					toWrite[binaryStringToInt(temp.substr(11,5))]++;
				} else {
					toWrite[binaryStringToInt(temp.substr(6,5))]++;
				}
				
				//////////////////////////////////
				if (opcode == "000100" || opcode == "000101") { // SW & LW
					// to do: hazard prevention
					string r1 = temp.substr(6, 5);
					string r2 = temp.substr(11, 5);
					if (opcode == "000100") {
						WAR[binaryStringToInt(r1)] = true;
						WAR[binaryStringToInt(r2)] = true;
					} else WAR[binaryStringToInt(r1)] = true;
					
				} else if (opcode != "001110") { // others
					if (opcode == "010000" || opcode == "010001" || opcode == "010010"){
						string r1 = temp.substr(6, 5);
						string r2 = temp.substr(11, 5);
						if (r1 == r2);
						else WAR[binaryStringToInt(temp.substr(11,5))] = true;
					} else {
						string r1 = temp.substr(6, 5);
						string r2 = temp.substr(11, 5);
						string r3 = temp.substr(16, 5);
						if (r1 == r2 || r1 == r3);
						else {
							WAR[binaryStringToInt(temp.substr(11,5))] = true;
							WAR[binaryStringToInt(temp.substr(16,5))] = true;
						}
					}
				} else if (opcode == "001110") { // MUL
					string r1 = temp.substr(6, 5);
					string r2 = temp.substr(11, 5);
					string r3 = temp.substr(16, 5);
					if (r1 == r2 || r1 == r3);
					else {
						WAR[binaryStringToInt(temp.substr(11,5))] = true;
						WAR[binaryStringToInt(temp.substr(16,5))] = true;
					}
				}
				//////////////////////////////////
				
				
				B1[po] = i;
				po++;
				i += 4;
			}
			if (fuck) {
				ct--;
				break;
			}
		} else if (B1[0] == 0) { // to do: distinct panalty
			string temp = commandStore[IF[0]].first;
			string opcode = temp.substr(0, 6);
			if (opcode == "000001") { // BEQ
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				if (toWrite[binaryStringToInt(r1)] != 0 || toWrite[binaryStringToInt(r2)] != 0);
				else {
					string offset = temp.substr(16, 16);
					offset = offset + "00";
					if (R[binaryStringToInt(r1)] == R[binaryStringToInt(r2)]) {
						i = i + 4 + binaryStringToInt(offset);
					} else i += 4;
					IF[1] = IF[0];
					IF[0] = 0;
				}
				
			} else if (opcode =="000010") { // BNE
				string r1 = temp.substr(6, 5);
				string r2 = temp.substr(11, 5);
				//cout << toWrite[binaryStringToInt(r1)] << toWrite[binaryStringToInt(r2)];
				if (toWrite[binaryStringToInt(r1)] != 0 || toWrite[binaryStringToInt(r2)] != 0);
				else {
					string offset = temp.substr(16, 16);
					offset = offset + "00";
					if (R[binaryStringToInt(r1)] != R[binaryStringToInt(r2)]) {
						i = i + 4 + binaryStringToInt(offset);
					} else i += 4;
					IF[1] = IF[0];
					IF[0] = 0;
				}
				
			} else if (opcode == "000011") { // BGTZ
				string r1 = temp.substr(6, 5);
				if (toWrite[binaryStringToInt(r1)] != 0);
				else {
					string offset = temp.substr(16, 16);
					offset = offset + "00";
					if (R[binaryStringToInt(r1)] > 0) {
						i = i + 4 + binaryStringToInt(offset);
					} else i += 4;
					IF[1] = IF[0];
					IF[0] = 0;
				}
			}
			
		}
		//cout << toWrite[2];
		
		/*
		if (opcode == "000100") { // SW
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
			if (R[binaryStringToInt(r2)] >= 0) {// > to >=
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
		*/
		cout << "--------------------" << endl;
		cout << "Cycle " << ct << ":" << endl;
		cout << endl;
		cout << "IF:" << endl; 
		cout << "\tWaiting:";
		if (IF[0] != 0) cout << " [" << commandStore[IF[0]].second << "]";
		cout << endl;
		cout << "\tExecuted:";
		if (IF[1] != 0) cout << " [" << commandStore[IF[1]].second << "]";
		cout << endl;
		cout << "Buf1:" << endl;
		for (int k = 0; k < 8; k++) {
			cout << "\tEntry " << k << ":";
			if (B1[k] != 0) cout << " [" << commandStore[B1[k]].second << "]";
			cout << endl;
		}
		cout << "Buf2:" << endl;
		for (int k = 0; k < 2; k++) {
			cout << "\tEntry " << k << ":";
			if (B2[k] != 0) cout << " [" << commandStore[B2[k]].second << "]";
			cout << endl;
		}
		cout << "Buf3:" << endl;
		for (int k = 0; k < 2; k++) {
			cout << "\tEntry " << k << ":";
			if (B3[k] != 0) cout << " [" << commandStore[B3[k]].second << "]";
			cout << endl;
		}
		cout << "Buf4:" << endl;
		for (int k = 0; k < 2; k++) {
			cout << "\tEntry " << k << ":";
			if (B4[k] != 0) cout << " [" << commandStore[B4[k]].second << "]";
			cout << endl;
		}
		cout << "Buf5:";
		if (B5 != 0) cout << " [" << commandStore[B5].second << "]";
		cout << endl;
		cout << "Buf6:";
		if (sB6 != "") cout << " [" << sB6 << "]";
		cout << endl;
		cout << "Buf7:";
		if (B7 != 0) cout << " [" << commandStore[B7].second << "]";
		cout << endl;
		cout << "Buf8:";
		if (sB8 != "") cout << " [" << sB8 << "]";
		cout << endl;
		cout << "Buf9:";
		if (B9 != 0) cout << " [" << commandStore[B9].second << "]";
		cout << endl;
		cout << "Buf10:";
		if (sB10 != "") cout << " [" << sB10 << "]";
		cout << endl;
		cout << endl;
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
		//cout << endl;
		
		
		
		
		
		
		outputS << "--------------------" << endl;
		outputS << "Cycle " << ct << ":" << endl;
		outputS << endl;
		outputS << "IF:" << endl; 
		outputS << "\tWaiting:";
		if (IF[0] != 0) outputS << " [" << commandStore[IF[0]].second << "]";
		outputS << endl;
		outputS << "\tExecuted:";
		if (IF[1] != 0) outputS << " [" << commandStore[IF[1]].second << "]";
		outputS << endl;
		outputS << "Buf1:" << endl;
		for (int k = 0; k < 8; k++) {
			outputS << "\tEntry " << k << ":";
			if (B1[k] != 0) outputS << " [" << commandStore[B1[k]].second << "]";
			outputS << endl;
		}
		outputS << "Buf2:" << endl;
		for (int k = 0; k < 2; k++) {
			outputS << "\tEntry " << k << ":";
			if (B2[k] != 0) outputS << " [" << commandStore[B2[k]].second << "]";
			outputS << endl;
		}
		outputS << "Buf3:" << endl;
		for (int k = 0; k < 2; k++) {
			outputS << "\tEntry " << k << ":";
			if (B3[k] != 0) outputS << " [" << commandStore[B3[k]].second << "]";
			outputS << endl;
		}
		outputS << "Buf4:" << endl;
		for (int k = 0; k < 2; k++) {
			outputS << "\tEntry " << k << ":";
			if (B4[k] != 0) outputS << " [" << commandStore[B4[k]].second << "]";
			outputS << endl;
		}
		outputS << "Buf5:";
		if (B5 != 0) outputS << " [" << commandStore[B5].second << "]";
		outputS << endl;
		outputS << "Buf6:";
		if (sB6 != "") outputS << " [" << sB6 << "]";
		outputS << endl;
		outputS << "Buf7:";
		if (B7 != 0) outputS << " [" << commandStore[B7].second << "]";
		outputS << endl;
		outputS << "Buf8:";
		if (sB8 != "") outputS << " [" << sB8 << "]";
		outputS << endl;
		outputS << "Buf9:";
		if (B9 != 0) outputS << " [" << commandStore[B9].second << "]";
		outputS << endl;
		outputS << "Buf10:";
		if (sB10 != "") outputS << " [" << sB10 << "]";
		outputS << endl;
		outputS << endl;
		outputS << "Registers" << endl;
		outputS << "R00:\t" << R[0] << "\t" << R[1] << "\t" << R[2] << "\t" << R[3] << "\t" << R[4] << "\t" << R[5] << "\t" << R[6] << "\t" << R[7] << endl;
		outputS << "R08:\t" << R[8] << "\t" << R[9] << "\t" << R[10] << "\t" << R[11] << "\t" << R[12] << "\t" << R[13] << "\t" << R[14] << "\t" << R[15] << endl;
		outputS << "R16:\t" << R[16] << "\t" << R[17] << "\t" << R[18] << "\t" << R[19] << "\t" << R[20] << "\t" << R[21] << "\t" << R[22] << "\t" << R[23] << endl;
		outputS << "R24:\t" << R[24] << "\t" << R[25] << "\t" << R[26] << "\t" << R[27] << "\t" << R[28] << "\t" << R[29] << "\t" << R[30] << "\t" << R[31] << endl;
		outputS << endl;
		outputS << "Data" << endl;
		for (int j = mark; j < counter; j += 32) {
			outputS << j << ":\t";
			for (int k = 0; k < 8; k++) outputS << D[j + 4 * k] << "\t";
			outputS << endl;
		}
		
		
		

		if (tw8 != -1) toWrite[tw8]--;
		if (tw6 != -1) toWrite[tw6]--;
		if (tw10 != -1) toWrite[tw10]--;
		
		if (RAW6 != -1) RAW[RAW6]--;
		if (RAW10 != -1) RAW[RAW10]--;
		if (RAW8 != -1) RAW[RAW8]--;
		
		if (WAR81 != -1) WAR[WAR81] = false;
		if (WAR82 != -1) WAR[WAR82] = false;
		if (WAR61 != -1) WAR[WAR61] = false;
		if (WAR62 != -1) WAR[WAR62] = false;
		if (WAR101 != -1) WAR[WAR101] = false;
		if (WAR102 != -1) WAR[WAR102] = false;
		
		IF[1] = 0;
		sB8 = "";
		sB6 = "";
		sB10 = "";
		isWB = false;
	}
	ct++;
	//BREAK
	cout << "--------------------" << endl;
	cout << "Cycle " << ct << ":" << endl;
	cout << endl;
	cout << "IF:" << endl; 
	cout << "\tWaiting: ";
	if (IF[0] != 0) cout << "[" << commandStore[IF[0]].second << "]";
	cout << endl;
	cout << "\tExecuted: [BREAK]";
	cout << endl;
	cout << "Buf1:" << endl;
	for (int k = 0; k < 8; k++) {
		cout << "\tEntry " << k << ":";
		if (B1[k] != 0) cout << "[" << commandStore[B1[k]].second << "]";
		cout << endl;
	}
	cout << "Buf2:" << endl;
	for (int k = 0; k < 2; k++) {
		cout << "\tEntry " << k << ":";
		if (B2[k] != 0) cout << "[" << commandStore[B2[k]].second << "]";
		cout << endl;
	}
	cout << "Buf3:" << endl;
	for (int k = 0; k < 2; k++) {
		cout << "\tEntry " << k << ":";
		if (B3[k] != 0) cout << "[" << commandStore[B3[k]].second << "]";
		cout << endl;
	}
	cout << "Buf4:" << endl;
	for (int k = 0; k < 2; k++) {
		cout << "\tEntry " << k << ":";
		if (B4[k] != 0) cout << "[" << commandStore[B4[k]].second << "]";
		cout << endl;
	}
	cout << "Buf5:";
	if (B5 != 0) cout << "[" << commandStore[B5].second << "]";
	cout << endl;
	cout << "Buf6:";
	if (B6 != 0) cout << "[" << commandStore[B6].second << "]";
	cout << endl;
	cout << "Buf7:";
	if (B7 != 0) cout << "[" << commandStore[B7].second << "]";
	cout << endl;
	cout << "Buf8:";
	if (B8 != 0) cout << "[" << commandStore[B8].second << "]";
	cout << endl;
	cout << "Buf9:";
	if (B9 != 0) cout << "[" << commandStore[B9].second << "]";
	cout << endl;
	cout << "Buf10:";
	if (B10 != 0) cout << "[" << commandStore[B10].second << "]";
	cout << endl;
	cout << endl;
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
	//cout << endl;
	
	
	
	outputS << "--------------------" << endl;
	outputS << "Cycle " << ct << ":" << endl;
	outputS << endl;
	outputS << "IF:" << endl; 
	outputS << "\tWaiting: ";
	if (IF[0] != 0) outputS << "[" << commandStore[IF[0]].second << "]";
	outputS << endl;
	outputS << "\tExecuted: [BREAK]";
	outputS << endl;
	outputS << "Buf1:" << endl;
	for (int k = 0; k < 8; k++) {
		outputS << "\tEntry " << k << ":";
		if (B1[k] != 0) outputS << "[" << commandStore[B1[k]].second << "]";
		outputS << endl;
	}
	outputS << "Buf2:" << endl;
	for (int k = 0; k < 2; k++) {
		outputS << "\tEntry " << k << ":";
		if (B2[k] != 0) outputS << "[" << commandStore[B2[k]].second << "]";
		outputS << endl;
	}
	outputS << "Buf3:" << endl;
	for (int k = 0; k < 2; k++) {
		outputS << "\tEntry " << k << ":";
		if (B3[k] != 0) outputS << "[" << commandStore[B3[k]].second << "]";
		outputS << endl;
	}
	outputS << "Buf4:" << endl;
	for (int k = 0; k < 2; k++) {
		outputS << "\tEntry " << k << ":";
		if (B4[k] != 0) outputS << "[" << commandStore[B4[k]].second << "]";
		outputS << endl;
	}
	outputS << "Buf5:";
	if (B5 != 0) outputS << "[" << commandStore[B5].second << "]";
	outputS << endl;
	outputS << "Buf6:";
	if (B6 != 0) outputS << "[" << commandStore[B6].second << "]";
	outputS << endl;
	outputS << "Buf7:";
	if (B7 != 0) outputS << "[" << commandStore[B7].second << "]";
	outputS << endl;
	outputS << "Buf8:";
	if (B8 != 0) outputS << "[" << commandStore[B8].second << "]";
	outputS << endl;
	outputS << "Buf9:";
	if (B9 != 0) outputS << "[" << commandStore[B9].second << "]";
	outputS << endl;
	outputS << "Buf10:";
	if (B10 != 0) outputS << "[" << commandStore[B10].second << "]";
	outputS << endl;
	outputS << endl;
	outputS << "Registers" << endl;
	outputS << "R00:\t" << R[0] << "\t" << R[1] << "\t" << R[2] << "\t" << R[3] << "\t" << R[4] << "\t" << R[5] << "\t" << R[6] << "\t" << R[7] << endl;
	outputS << "R08:\t" << R[8] << "\t" << R[9] << "\t" << R[10] << "\t" << R[11] << "\t" << R[12] << "\t" << R[13] << "\t" << R[14] << "\t" << R[15] << endl;
	outputS << "R16:\t" << R[16] << "\t" << R[17] << "\t" << R[18] << "\t" << R[19] << "\t" << R[20] << "\t" << R[21] << "\t" << R[22] << "\t" << R[23] << endl;
	outputS << "R24:\t" << R[24] << "\t" << R[25] << "\t" << R[26] << "\t" << R[27] << "\t" << R[28] << "\t" << R[29] << "\t" << R[30] << "\t" << R[31] << endl;
	outputS << endl;
	outputS << "Data" << endl;
	for (int j = mark; j < counter; j += 32) {
		outputS << j << ":\t";
		for (int k = 0; k < 8; k++) outputS << D[j + 4 * k] << "\t";
		outputS << endl;
	}
	
	return 0;
}
