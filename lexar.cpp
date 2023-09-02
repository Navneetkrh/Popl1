#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "def.h"

using namespace std;

class Lexar{
    map<std::string, int> symbolmap;
    public:
    void init(char *str){
       removeComments(str); // returns the uncommented character array
        symbolmap = {
            {"+", PLUS}, {"-", MINUS}, {"%", PERCENT}, {"/", DIV}, {"*", MULT},
            {"++", PLUS_PLUS}, {"--", MINUS_MINUS}, {"=", EQ}, {"+=", PLUS_EQ},
            {"-=", MINUS_EQ}, {"*=", MULT_EQ}, {"/=", DIV_EQ}, {"<", LESSER},
            {">", GREATER}, {"<=", LESS_EQ}, {">=", GREAT_EQ}, {"==", EQ_EQ},
            {"[", L_SQUARE}, {"]", R_SQUARE}, {"(", L_CBRACE}, {")", R_CBRACE},
            {"{", L_PARAEN}, {"}", R_PARAEN}, {",", COMMA}, {";", SEMICOL},
            {"return", RETURN}, {"int", INT}, {"float", FLOAT}, {"double", DOUBLE},
            {"bool", BOOL}, {"char", CHAR}, {"signed", SIGNED}, {"unsigned", UNSIGNED},
            {"for", FOR}, {"while", WHILE}, {"do", DO}, {"struct", STRUCT}, {"const", CONST},
            {"void", VOID}, {"switch", SWITCH}, {"break", BREAK}, {"case", CASE},
            {"continue", CONTINUE}, {"goto", GOTO}, {"long", LONG}, {"static", STATIC},
            {"union", UNION}, {"default", DEFAULT}, {"if", IF}, {"else", ELSE}, {"short", SHORT}
        };
       
    }
    void tokenise(char* str){
        tokens(str);
    }

    // Detectin tokens from the input STRING.
    

    private:
    void tokens(char* str)
    {
        int left = 0, right = 0;
        int len = strlen(str);

        // forming sets
        map<string, int> mp;
        mp=symbolmap;
        set<string> sym;
        
        FILE *fp, *fr;
        fp = fopen("symbol_table_1.out", "w");
        fr = fopen("pa_1.out", "w");

        int prev = 0;

        while (right <= len && left <= right) {
            if (isDelimiter(str[right]) == false)
                right++;
    
            if (isDelimiter(str[right]) && left == right) {
                if (isOperator(str[right])) {
            if (prev > 330) {
                fprintf(fr, "%d %c\n", mp[string(1,str[right])], str[right]);
                prev = mp[string(1,str[right])];
            }
            else {
                if ((mp[string(1,str[right+1])] == PLUS || mp[string(1,str[right+1])] == MINUS || mp[string(1,str[right+1])] == EQ) && isDelimiter(str[right+1])) {
                    char comb[2];
                    comb[0]=str[right];
                    comb[1]=str[right+1];
                    right++;
                    fprintf(fr, "%d %s\n", mp[comb], comb);
                    prev = mp[comb];
                }
                else
                    fprintf(fr, "%d %c\n", mp[string(1,str[right])], str[right]);
                    prev = mp[string(1,str[right])];
            }
            }
            else if (isAssignmentOperator(str[right])) {
            fprintf(fr, "%d %c\n", mp[string(1,str[right])], str[right]);
            prev = mp[string(1,str[right])];
            }
            else if (isRelationalOperator(str[right])) {
            fprintf(fr, "%d %c\n", mp[string(1,str[right])], str[right]);
            prev = mp[string(1,str[right])];
            }
            else if (isSpecial(str[right])) {
            fprintf(fr, "%d %c\n", mp[string(1,str[right])], str[right]);
            prev = mp[string(1,str[right])];
            }
                right++;
                left = right;
            } else if (isDelimiter(str[right]) == true && left != right
                    || (right == len && left != right)) {
                char* subStr = subString(str, left, right - 1);
            
            int n = right - left;

                if (isKeyword(subStr) == true) {
            fprintf(fr, "%d %s\n", mp[subStr], subStr);
            prev = mp[subStr];

            auto it = sym.find(subStr);
            if (it == sym.end()) {
                sym.insert(subStr);

                if (fp) {
                    if (subStr[n-1]!='\n') fprintf(fp, "%s %d\n", subStr, 0);
                }
            }
            }
    
                else if (isInteger(subStr) == true) {
            fprintf(fr, "%d %s\n", INT, subStr);
            prev = mp[subStr];
            }
    
                else if (isFloat(subStr) == true) {
            fprintf(fr, "%d %s\n", FLOAT, subStr);
            prev = mp[subStr];
            }
    
                else if (validIdentifier(subStr) == true
                        && isDelimiter(str[right - 1]) == false)
            {
            if(subStr[n-1]!='\n') { 
                fprintf(fr, "%d %s\n", IDNTIFIER, subStr);
                prev = IDNTIFIER;
            }

            auto it = sym.find(subStr);
            if (it == sym.end()) {
                sym.insert(subStr);

                if (fp) {
                    if (subStr[n-1]!='\n') fprintf(fp, "%s %d\n", subStr, 1);
                }
            }
            }
                else if (validIdentifier(subStr) == false
                        && isDelimiter(str[right - 1]) == false)
            fprintf(fr, "%d\n", -1);
            left = right;
            }
        }
        fclose(fp);
        fclose(fr);
        return;
    }
    void removeComments(char str[5000])
{
    int n = 5000;
    char res[5000];
    int j = 0;
 
    bool s_cmt = false; // single line comment
    bool m_cmt = false; // multiple line comment
 
    for (int i=0; i<n; i++)
    {
	// turning of single line comment
        if (s_cmt == true && str[i] == '\n')
            s_cmt = false;
	// turning of multiple line comment
        else if  (m_cmt == true && str[i] == '*' && str[i+1] == '/')
            m_cmt = false,  i++; 
        // If this character is in a comment, ignore it
        else if (s_cmt || m_cmt)
            continue;
        else if (str[i] == '/' && str[i+1] == '/')
            s_cmt = true, i++;
        else if (str[i] == '/' && str[i+1] == '*')
            m_cmt = true,  i++;
        else  {
		res[j] += str[i];
		j++;
	}
    }
    str = res;
}
    // void removeComments(char str[5000]) {
    // int len = 5000;
    // bool inSingleLineComment = false;
    // bool inMultiLineComment = false;
    // int writeIndex = 0;

    // for (int i = 0; i < len; i++) {
    //     if (!inSingleLineComment && !inMultiLineComment) {
    //         // Check for the start of a single-line comment
    //         if (str[i] == '/' && i + 1 < len && str[i + 1] == '/') {
    //             inSingleLineComment = true;
    //             i++; // Skip the next character too
    //         }
    //         // Check for the start of a multi-line comment
    //         else if (str[i] == '/' && i + 1 < len && str[i + 1] == '*') {
    //             inMultiLineComment = true;
    //             i++; // Skip the next character too
    //         }
    //         // If not in a comment, copy the character to the result string
    //         else {
    //             str[writeIndex++] = str[i];
    //         }
    //     } else if (inSingleLineComment) {
    //         // Check for the end of a single-line comment
    //         if (str[i] == '\n') {
    //             inSingleLineComment = false;
    //             str[writeIndex++] = str[i]; // Include newline in the result
    //         }
    //     } else if (inMultiLineComment) {
    //         // Check for the end of a multi-line comment
    //         if (str[i] == '*' && i + 1 < len && str[i + 1] == '/') {
    //             inMultiLineComment = false;
    //             i++; // Skip the next character too
    //         }
    //     }
    // }

    // // Null-terminate the result string
    // str[writeIndex] = '\0';
    // } ;


    bool isDelimiter(char ch)
    {
        if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '%' ||
            ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
            ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
            ch == '[' || ch == ']' || ch == '{' || ch == '}')
            return (true);
        return (false);
    };

    bool isSpecial(char ch)
    {
        if (ch == ';' || ch == '"' || ch == '(' || ch == ')'
        || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ',')
            return (true);
        return (false);
    }

    bool isOperator(char ch)
    {
        if (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '%')
            return (true);
        return (false);
    }
    bool isAssignmentOperator(char ch) 
    {
        if (ch == '='
        )
            return(true);
        return(false);
    }

    bool isRelationalOperator(char ch){
	if (ch == '<' || 
		ch == '>')
		return (true);
	return(false);
    }
    // Returns 'true' if the string is a VALID IDENTIFIER.
    bool validIdentifier(char* str) {
    if (strlen(str) > 1) {
        if (str[0] == '_' && str[1] == '_') {
            return false; // Double underscore is not allowed.
        }
    }
    if (strlen(str) == 0 || ((str[0] >= '0' && str[0] <= '9') || isDelimiter(str[0]))) {
        return false; // Empty string, starts with a digit, or delimiter.
    }
    return true; // Valid identifier.
    }

    bool isKeyword(char* str)
    {
        if (!strcmp(str, "continue") || !strcmp(str, "int")
            || !strcmp(str, "double") || !strcmp(str, "float")
            || !strcmp(str, "return") || !strcmp(str, "signed")
            || !strcmp(str, "case") || !strcmp(str, "char")
            || !strcmp(str, "long") || !strcmp(str, "union")
            || !strcmp(str, "short") || !strcmp(str, "bool")
            || !strcmp(str, "switch") || !strcmp(str, "unsigned")
            || !strcmp(str, "void") || !strcmp(str, "static")
            || !strcmp(str, "default") || !strcmp(str, "goto")
        || !strcmp(str, "for") || !strcmp(str, "while")
        || !strcmp(str,"do") || !strcmp(str, "break"))
            return (true);
        return (false);
    }  
 


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
 
    bool isFloat(char* str)
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
 

};

int main()
{
    char str[5000] = "";
    read(0, str, 5000); 
    Lexar lexar;
    lexar.init(str);
    lexar.tokenise(str);
 

    return (0);
}