#include <iostream>
#include <string>
using namespace std;

class InvalidTemperatureException : public exception {
public:
  virtual const char* what() const throw() {
    return "Error: Input value invalid (non-numeric).";
  }
};

class InvalidConversionException : public exception {
public:
  virtual const char* what() const throw() {
    return "Error: Invalid option chosen";
  }
};

class TemperatureOutOfRangeException : public exception {
public:
  virtual const char* what() const throw() {
    return "Error: Input value out of bounds";
  }
};

int FToC(int F) { return (F - 32) * (5/9); }

int CToF(int C) { return (C * (9/5)) + 32; }

bool validateF(int F) {
  if (F < -459.67 || F > 1000) return false;
  else return true;
}

bool validateC(int C) {
  if (C < -273.15 || C > 1000) return false;
  else return true;
}

int main() {
  int value = 0;
  try {
    string input;
    cin >> input;
    try {
      value = stoi(input);
    } catch (std::invalid_argument& ia) {
      throw InvalidTemperatureException();
    }
  } catch (InvalidTemperatureException& ite) {
    cout << ite.what() << endl;
    return 1;
  }

  int direction = 0;
  try {
    cout << "Choose conversion direction:\n1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius\n";
    cin >> direction;
    if (!(direction == 1 || direction == 2)) throw InvalidConversionException();
  } catch (InvalidConversionException& ice) {
    cout << ice.what() << endl;
    return 1;
  }

  int result = 0;
  if (direction == 1) {
    result = CToF(value);
    try {
      if (!validateF(result)) throw TemperatureOutOfRangeException();
    } catch (TemperatureOutOfRangeException& toore) {
      cout << toore.what() << endl;
      return 1;
    }
  } else if (direction == 2){
    result = FToC(value);
    try {
      if (!validateC(result)) throw TemperatureOutOfRangeException();
    } catch (TemperatureOutOfRangeException& toore) {
      cout << toore.what() << endl;
      return 1;
    }
  }
  cout << result;
}