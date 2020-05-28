#include <bits/stdc++.h>

using namespace std;

vector<string> instructions;
unordered_map<string, string> opcodes;
unordered_map<string, string> aRegs;
unordered_map<string, string> naRegs;
unordered_set<string> isAd;

string compile(string &);
string hex_to_bin(string &);
string bin_to_hex(string);
void fill();

int main(int argc, char const *argv[]) {
  fill();
  ifstream infile("data.txt");
  ofstream outfile("out.txt");
  string line;
  while (getline(infile, line)) {
    outfile << compile(line) << endl;
  }
  infile.close();
  outfile.close();
  return 0;
}

string compile(string &jx) {
  string res = "";
  string opstr = jx.substr(0, jx.find_first_of(' '));
  res += opcodes[opstr];
  jx = jx.substr(jx.find_first_of(' ') + 1, jx.size());
  if (isAd.find(opstr) == isAd.end()) { // instr is not address referenced
    res += naRegs[jx.substr(0, jx.find_first_of(' '))];
    jx = jx.substr(jx.find_first_of(' ') + 1, jx.size());
    if (jx.size() > 2) {
      res += naRegs[jx.substr(0, jx.find_first_of(' '))];
      jx = jx.substr(jx.find_first_of(' ') + 1, jx.size());
    }
    res += naRegs[jx];
    while (res.size() < 16) {
      res += "0";
    }
    return bin_to_hex(res.substr(0, 8)) + " " + bin_to_hex(res.substr(8, 15));
  } else {
    res += aRegs[jx.substr(0, jx.find_first_of(' '))];
    jx = jx.substr(jx.find_first_of(' ') + 1, jx.size());
    res += jx[0] == 'I' ? '0' : '1';
    if (jx[0] == 'D') {
      return "00 " + bin_to_hex(res);
    } else {
      return jx.substr(jx.find_first_of(' ') + 3, jx.size()) + " " +
             bin_to_hex(res);
    }
  }
}

string hex_to_bin(string &k) {
  int i = 0;
  string res = "";
  while (k[i]) {
    switch (toupper(k[i++])) {
    case '0':
      res += "0000";
      break;
    case '1':
      res += "0001";
      break;
    case '2':
      res += "0010";
      break;
    case '3':
      res += "0011";
      break;
    case '4':
      res += "0100";
      break;
    case '5':
      res += "0101";
      break;
    case '6':
      res += "0110";
      break;
    case '7':
      res += "0111";
      break;
    case '8':
      res += "1000";
      break;
    case '9':
      res += "1001";
      break;
    case 'A':
      res += "1010";
      break;
    case 'B':
      res += "1011";
      break;
    case 'C':
      res += "1100";
      break;
    case 'D':
      res += "1101";
      break;
    case 'E':
      res += "1110";
      break;
    case 'F':
      res += "1111";
      break;
    }
  }
  return res;
}

string bin_to_hex(string k) {
  int i = 0;
  string res = "";
  while (i + 4 < k.size() + 2) {
    string tok = k.substr(i, i + 4);
    if (tok == "0000") {
      res += "0";
    } else if (tok == "0001") {
      res += "1";
    } else if (tok == "0010") {
      res += "2";
    } else if (tok == "0011") {
      res += "3";
    } else if (tok == "0100") {
      res += "4";
    } else if (tok == "0101") {
      res += "5";
    } else if (tok == "0110") {
      res += "6";
    } else if (tok == "0111") {
      res += "7";
    } else if (tok == "1000") {
      res += "8";
    } else if (tok == "1001") {
      res += "9";
    } else if (tok == "1010") {
      res += "A";
    } else if (tok == "1011") {
      res += "B";
    } else if (tok == "1100") {
      res += "C";
    } else if (tok == "1101") {
      res += "D";
    } else if (tok == "1110") {
      res += "E";
    } else if (tok == "1111") {
      res += "F";
    }
    i += 4;
  }
  return res;
}

void fill() {
  isAd.insert("LD");
  isAd.insert("ST");
  isAd.insert("BRA");
  isAd.insert("BEQ");
  isAd.insert("BNE");
  isAd.insert("CALL");
  opcodes["LD"] = "00000";
  opcodes["ST"] = "00001";
  opcodes["MOV"] = "00010";
  opcodes["PSH"] = "00011";
  opcodes["PUL"] = "00100";
  opcodes["ADD"] = "00101";
  opcodes["SUB"] = "00110";
  opcodes["DEC"] = "00111";
  opcodes["INC"] = "01000";
  opcodes["AND"] = "01001";
  opcodes["OR"] = "01010";
  opcodes["NOT"] = "01011";
  opcodes["LSL"] = "01100";
  opcodes["LSR"] = "01101";
  opcodes["BRA"] = "01110";
  opcodes["BEQ"] = "01111";
  opcodes["BNE"] = "10000";
  opcodes["CALL"] = "10001";
  opcodes["RET"] = "10010";
  aRegs["R0"] = "00";
  aRegs["R1"] = "01";
  aRegs["R2"] = "10";
  aRegs["R3"] = "11";
  naRegs["R0"] = "000";
  naRegs["R1"] = "001";
  naRegs["R2"] = "010";
  naRegs["R3"] = "011";
  naRegs["PC"] = "100";
  naRegs["PC"] = "101";
  naRegs["AR"] = "110";
  naRegs["SP"] = "111";
}