#include <iostream> 
#include <string.h> 
#include <stdlib.h> 

using namespace std;
  
// Returns 'true' if the character is a DELIMITER. 
bool isDelimiter(char ch) 
{ 
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||  
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||  
        ch == '[' || ch == ']' || ch == '{' || ch == '}') 
        return (true); 
    return (false); 
} 
  
// Returns 'true' if the character is an OPERATOR. 
bool isOperator(char ch) 
{ 
    if (ch == '+' || ch == '-' || ch == '*' ||  
        ch == '/' || ch == '>' || ch == '<' ||  
        ch == '=') 
        return (true); 
    return (false); 
} 
  
// Returns 'true' if the string is a VALID IDENTIFIER. 
bool validIdentifier(char* str) 
{ 
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || 
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||  
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||  
        str[0] == '9' || isDelimiter(str[0]) == true) 
        return (false); 
    return (true); 
} 
  
// Returns 'true' if the string is a KEYWORD. 
bool isKeyword(char* str) 
{
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};
    int i, flag = 0;
    
    for(i = 0; i < 32; ++i){
        if(strcmp(keywords[i], str) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
} 
  
// Returns 'true' if the string is an INTEGER. 
bool isInteger(char* str) 
{ 
    int i, len = strlen(str); 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0)) 
            return (false); 
    } 
    return (true); 
} 
  
// Returns 'true' if the string is a REAL NUMBER. 
bool isRealNumber(char* str) 
{ 
    int i, len = strlen(str); 
    bool hasDecimal = false; 
  
    if (len == 0) 
        return (false); 
    for (i = 0; i < len; i++) { 
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||  
            (str[i] == '-' && i > 0)) 
            return (false); 
        if (str[i] == '.') 
            hasDecimal = true; 
    } 
    return (hasDecimal); 
} 
  
// Extracts the SUBSTRING. 
char* subString(char* str, int left, int right) 
{ 
    int i; 
    char* subStr = (char*)malloc( 
                  sizeof(char) * (right - left + 2)); 
  
    for (i = left; i <= right; i++) 
        subStr[i - left] = str[i]; 
    subStr[right - left + 1] = '\0'; 
    return (subStr); 
} 
  
// Parsing the input STRING. 
void parse(char* str) 
{ 
    int left = 0, right = 0; 
    int len = strlen(str); 
  
    while (right <= len && left <= right) { 
        if (isDelimiter(str[right]) == false) 
            right++; 
  
        if (isDelimiter(str[right]) == true && left == right) { 
            if (isOperator(str[right]) == true) 
                cout<<str[right]<<" is an OPERATOR"<<endl; 
  
            right++; 
            left = right; 
        } else if (isDelimiter(str[right]) == true && left != right 
                   || (right == len && left != right)) { 
            char* subStr = subString(str, left, right - 1); 
  
            if (isKeyword(subStr) == true) 
                cout<<subStr<<" is a KEYWORD"<<endl; 
  
            else if (isInteger(subStr) == true) 
                cout<<subStr<<" is an INTEGER"<<endl; 
  
            else if (isRealNumber(subStr) == true) 
                cout<<subStr<<" IS A REAL NUMBER"<<endl; 
  
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false) 
                cout<<subStr<<" IS A VALID IDENTIFIER"<<endl; 
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false) 
                cout<<"ERROR at col:"<<left<<" "<<subStr<<" IS NOT A VALID IDENTIFIER"<<endl; 
            left = right; 
        } 
    } 
    return; 
} 
  
// DRIVER FUNCTION 
int main() 
{ 
     // maximum legth of string is 100 here  
    char str[100] = "int a = b + 1c; "; 
  
    parse(str); // calling the parse function 
  
    return (0); 
} 