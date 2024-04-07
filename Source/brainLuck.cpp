#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

#define MAX_POS 30000

class tiny {
public:
    int value = 0;

    tiny() {}
    tiny(int num) {
        if (num > 255)
            value = 0;
        else if (num < 0)
            value = 255;
        else
            value = num;
    }

    void operator++(int) {
        value++;

        if (value > 255)
            value = 0;
    }
    void operator--(int) {
        value--;

        if (value < 0)
            value = 255;
    }
};

std::string brainLuck(const std::string &code, const std::string &input) {
  std::string result = "";
  
  std::vector<tiny> arr(MAX_POS);
  int it = 0, itForIn = 0;
  
  std::map<int, int> dists;
  
  for (int i = 0, j = 0; i < code.size(); i++) {
    switch (code[i]) {
        case '>':
          it++;
          break;
        case '<':
          it--;
          break;
        case '+':
          arr[it]++;
          break;
        case '-':
          arr[it]--;
          break;
        case '.':
          result += (char)arr[it].value;
          break;
        case ',':
          arr[it].value = (int)input[itForIn];
          itForIn++;
          break;
        case '[':
          j++;
          
          if (dists[i] == 0) {
            for (int k = i + 1; ; k++) {
                if (code[k] == '[')
                    j++;
                else if (code[k] == ']')
                    j--;

                if (j == 0) {
                    dists[k] = i;
                    dists[i] = k;
                    break;
                }
            }
            
            if (arr[it].value == 0)
              i = dists[i];
          }
          else if (arr[it].value == 0)
            i = dists[i];
          
            break;
        case ']':
            if (arr[it].value != 0)
                i = dists[i];
            break;
        }
    }

    return result;
}

int main(int argc, char *args[]) {
    std::string result = args[2], code;
    std::ifstream file;

    file.open(args[1]);

    while (std::getline(file, code) && file.is_open()) 
        result = brainLuck(code, result);
    
    file.close();

    std::cout << result;
}