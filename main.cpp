#include <iostream>
#include <gmpxx.h>
#include <sstream>
#include <vector>

#define NUMBER_OF_SECTIONS 10 // cause const i = 0, 1 .. 10

void printAsDecimal(mpq_class num, int d);

int getSectionNumber (mpq_class value);

mpq_class getTermValue(int index);

int main(int argc, char **argv) {
    
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    std::string dStr(argv[1]);
    std::stringstream dStream(dStr);
    int d;
    dStream >> d;
    mpf_set_default_prec(d * 4);
    
    std::vector<mpq_class> inputNumbers;
    inputNumbers.reserve(16777216);
    
    // ---------------
    // chi-kwadrat
    // ---------------
    
    int sections[NUMBER_OF_SECTIONS]; // Y[i]
    for(int i = 0; i < NUMBER_OF_SECTIONS; i++) sections[i] = 0;
    
    mpq_class current;
    while (std::cin >> current) {
        inputNumbers.push_back(current);
        sections[getSectionNumber(current)]++;
    }
    
    mpq_class sum = 0;
    for(int i = 0; i < NUMBER_OF_SECTIONS; i++) {
        mpq_class expectedValue((getTermValue(i+1) - getTermValue(i)) * inputNumbers.size()); //np[i]
        mpq_class diff(expectedValue - sections[i]); //np[i] - Y[i]
        mpq_class value(diff.get_num()*diff.get_num()*expectedValue.get_den(), //(np[i] - Y[i])^2 / np[i]
                        diff.get_den()*diff.get_den()*expectedValue.get_num());
        sum += value;
    }
    
    printAsDecimal(sum, d);
    
    // ---------------
    // Kolmogorow
    // ---------------
    
    std::sort(inputNumbers.begin(), inputNumbers.end());
    mpq_class KnPlus(0); //TODO is possible minus ?
    mpq_class KnMinus(0);
    for(int i = 0; i < inputNumbers.size(); i++) {
        
        mpq_class tmpPlus (i+1,inputNumbers.size()); // tmpPlus = j/n
        tmpPlus -= inputNumbers[i]; // tmpPlus = j/n - F(x)
        if(tmpPlus > KnPlus) KnPlus = tmpPlus;
        
        mpq_class tmpMinus (-i,inputNumbers.size()); // tmpMinus = -(j-1)/n
        tmpMinus += inputNumbers[i]; // tmpMinus = -(j-1)/n + F(x) = F(x) - (j-1)/n
        if(tmpMinus > KnMinus) KnMinus = tmpMinus;
    }
    
    printAsDecimal(KnPlus, d);
    printAsDecimal(KnMinus, d);
    
    return 0;
}



mpq_class getTermValue(int index) {
    return mpq_class(index*index,100);
}

int getSectionNumber (mpq_class value) {
    
    int index = 0;
    for(int i = 0; i <= NUMBER_OF_SECTIONS; i++) {
        if(value >= getTermValue(i)) index = i;
        else return index;
    }
    return index;
}

void printAsDecimal(mpq_class num, int d) {
    mpz_class integer(num);
    mpq_class fraction = num - integer;
    if (fraction < 0) {
        fraction = -fraction;
    }
    std::string strFraction = "";
    for (int i = 1; i <= d; i++) {
        if (fraction == 0) {
            break;
        }
        fraction *= 10;
        mpz_class temp(fraction);
        fraction -= temp;
        strFraction += temp.get_str();
    }
    std::cout << integer.get_str();
    if (strFraction != "") {
        std::cout << '.';
        for (int i = strFraction.size() - 1; i >= 0; i--) {
            if (strFraction[i] == '0')
                strFraction.erase(i);
            else
                break;
        }
        std::cout << strFraction;
    }
    std::cout << std::endl;
}
