#include <stdio.h>
#include <stdlib.h>

int compareStr(char*str1,char *str2){
    int i = 0;
    char* string1 = str1;
    char* string2 = str2;
    while((string1[i] !='\0')&&(string2[i] != '\0')){
        if (string1[i]!=string2[i]){
            return 0;
        }
        i++;
    }
    return 1;
}

float power(int base, int exponent){
    float answer = 1.0;
    if (exponent < 0){
        for (int i = 0; i < (-exponent); i++){
            answer *= (1.0/base);
        }
        
    }else{
    for (int i = 0; i < exponent; i++){
        answer *= base;
    }
    }
    return answer;
}

void serialize(char *strBinary) {
    unsigned int binary = 0;

    printf("Binary: %s\n",strBinary);
    for (int i = 31; i >= 0; i--) {
        if (strBinary[i] == '1') {
            binary = (binary | (1 << (31 - i)));
           
        }
    }
    
    unsigned int sign = (binary>>31)&1;
    unsigned int exponent = (0x7F800000&binary)>>23;
    int actualExponent=0;
    unsigned int mantissa = (0x7FFFFF&binary);
    float actualMantissa;

    if (exponent == 0){
        actualExponent = -126;
        actualMantissa = 0;
    }else{
        actualExponent = exponent - 127; 
        actualMantissa = 1.0;
    }




    for (int i = 0; i <= 22; i++){
        if (mantissa & (1 << (22 - i))){
            actualMantissa += power(2,-(i+1));
        }
    }


    float result = actualMantissa * power(2,actualExponent);
    if (sign == 1){
        result *= -1;
    }

  

    printf("Sign: %d\n",sign);
    printf("Exponent: %d\n",actualExponent);
    printf("Mantissa: %.7g\n",actualMantissa);
    printf("Value: %.7g",result);
 

}

void deserialize(const char *strNum){
 
    char *endptr;
    float num = strtof(strNum, &endptr);
    
 
    unsigned int binary = *((unsigned int*)&num);


    unsigned int sign = (binary >> 31) & 1; 
    unsigned int exponent = (binary >> 23) & 0xFF;  
    unsigned int mantissa = binary & 0x7FFFFF;  

    int actualExponent=0;
    float actualMantissa;

    if (exponent == 0){
        actualExponent = -126;
        actualMantissa = 0;
    }else{
        actualExponent = exponent - 127; 
        actualMantissa = 1.0;
    }
  
   
    for (int i = 0; i <= 22; i++) {
        if (mantissa & (1 << (22 - i))) {
            actualMantissa += power(2, -(i + 1));
        }
    }

 
    printf("Binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (binary >> i) & 1);
    }
    printf("\n");


    printf("Sign: %d\n", sign);
    printf("Exponent: %d\n", actualExponent);
    printf("Mantissa: %.7g\n", actualMantissa);  
    printf("Value: %.7g", num);
}

int main(int argc, char*argv[]){
    if (argc != 3){
        printf("Incorrect Number of Command Line Arguments");
        return 1;
    }
    char* type1 = "-b";
    char* type2 = "-f";
    if(compareStr(argv[1],type1)==1){
        serialize(argv[2]);
    }else if(compareStr(argv[1],type2)==1) {
        deserialize(argv[2]);
    }
}
