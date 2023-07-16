
#include "stdafx.h"
#include "ArithmeticCodingMFC.h"
#include "ArithmeticCodingMFCDlg.h"
#include "afxdialogex.h"
#include "ACC.h"
#include<cstdio>
#include<stdlib.h>
#include<windows.h>
using namespace::std;

/* TRANSLATION TABLES BETWEEN CHARACTERS AND SYMBOL INDEXES. */
int char_to_index[No_of_chars];        
unsigned char index_to_char[No_of_symbols + 1]; 

/*   2^14 - 1           +            */
long cum_freq[No_of_symbols + 1];        

//用来存储编码值，
char code[Max_code_length];
long code_index = 0;
int decode_index = 0;

//buffer暂时存放编码
static int buffer;
//buffer中还有几个比特没有用到，初始值为8
static int bits_to_go;
//超过了EOF的字符
static int garbage_bits;
int freq[No_of_symbols + 1];

void initACC() {
	code_index = 0;
	decode_index = 0;
	for (int i = 0; i < No_of_symbols; i++) {
		freq[i] = 0;
		cum_freq[i] = 0;
	}
}

void scanFreq(BYTE * source, long long length) {
	for (long long i = 0; i < length; i++) {
		BYTE b = *(source + i);
		freq[(b & 0x0f) + 1]++;
		freq[(b >> 4) + 1] ++;
	}
	freq[EOF_symbol] = 1;
}

void start_model() {

	int i;
	for (int i = 0; i < No_of_symbols; i++) {
		cum_freq[i] = 0;
	}
	for (i = 0; i < No_of_chars; i++) {
		char_to_index[i] = i + 1;
		index_to_char[i + 1] = i;
	}

	//累计频率cum_freq[i-1]=freq[i]+...+freq[257], cum_freq[257]=0;
	freq[EOF_symbol] = 1;
	cum_freq[No_of_symbols] = 0;

	for (i = No_of_symbols; i > 0; i--) {
		cum_freq[i - 1] = cum_freq[i] + freq[i];
	}
	while (cum_freq[0] > Max_frequency) {
		for (int i = 0; i < No_of_chars; i++) {
			cum_freq[i] /= 10;
		}
	}

}

//初始化缓冲区，便于开始接受编码值
void start_outputing_bits()
{
	buffer = 0;                                //缓冲区一开始为空
	bits_to_go = 8;
}

void output_bit(int bit)
{
	//编码数据是从左到右进入缓冲区
	buffer >>= 1;
	if (bit) buffer |= 0x80;
	bits_to_go -= 1;
	//缓冲区满
	if (bits_to_go == 0) {
		code[code_index] = buffer;
		code_index++;

		bits_to_go = 8; //重新恢复为8
	}
}

static void bit_plus_follow(int);                
static code_value low, high;             
static long bits_to_follow;    


void start_encoding()
{
	for (int i = 0; i < 100; i++)code[i] = '\0';

	low = 0;                           
	high = Top_value;
	bits_to_follow = 0;             
}

void encode_symbol(int symbol, long cum_freq[])
{
	long long range;                          
	range = (long long)(high - low) + 1;

	high = low + (range*cum_freq[symbol - 1]) / cum_freq[0] - 1;  
	low = low + (range*cum_freq[symbol]) / cum_freq[0]; 

	for (;;)
	{                                  
		if (high < Half) {
			bit_plus_follow(0);                 /* 上下界都在低区间. */
		}
		else if (low >= Half) {                   /* 上下界都在高区间.*/
			bit_plus_follow(1);
			low -= Half;
			high -= Half;                       
		}
		else if (low >= First_qtr && high < Third_qtr) {  /* 如果在中间，稍后输出相反位 */
			bits_to_follow += 1;
			low -= First_qtr;                 
			high -= First_qtr;
		}
		else break;                             /* 区间长度超过 1/2 退出     */
		low = 2 * low;
		high = 2 * high + 1;                        /*放缩区间  */
	}
}

/* FINISH ENCODING THE STREAM. */

void done_encoding()
{
	bits_to_follow += 1;                       /* Output two bits that      */
	if (low < First_qtr) bit_plus_follow(0);     /* select the quarter that   */
	else bit_plus_follow(1);                   /* the current code range    */
}
void done_outputing_bits()
{
	//编码最后的时候，当缓冲区没有满，则直接补充０
	code[code_index] = buffer >> bits_to_go;
	code_index++;
}
/* contains.                 */


static void bit_plus_follow(int bit)
{
	output_bit(bit);                           
	while (bits_to_follow > 0) {
		output_bit(!bit);                      /* 后续缓冲流中的字符取反   */
		bits_to_follow -= 1;                   
	}                                        
}




//解码

static code_value value;                 

void start_inputing_bits()
{
	bits_to_go = 0;                             
	garbage_bits = 0;                          
}


int input_bit()
{
	int t;

	if (bits_to_go == 0) {
		buffer = code[decode_index];
		decode_index++;

		if (decode_index > code_index) {
			garbage_bits += 1;                      
			if (garbage_bits > Code_value_bits - 2) {   
				fprintf(stderr, "Bad input file/n"); 
			}
		}
		bits_to_go = 8;
	}
	//从右到左取出二进制位
	t = buffer & 1;                              
	buffer >>= 1;                               
	bits_to_go -= 1;
	return t;
}

void start_decoding()
{
	int i;
	value = 0;                                 
	for (i = 1; i <= Code_value_bits; i++) {      
		value = 2 * value + input_bit();
	}


	low = 0;                                    
	high = Top_value;
}


char decode_symbol(long cum_freq[])
{
	long range;                 
	int cum;                    
	char symbol;                
	range = (long)(high - low) + 1;
	cum = (((long)(value - low) + 1)*cum_freq[0] - 1) / range;    

	for (symbol = 1; cum_freq[symbol] > cum; symbol++); 
	high = low + (range*cum_freq[symbol - 1]) / cum_freq[0] - 1;  
	low = low + (range*cum_freq[symbol]) / cum_freq[0];

	for (;;) {                                  
		if (high < Half) {
			/* nothing */                       /* 扩展低位        */
		}
		else if (low >= Half) {                   /* 扩展高位       */
			value -= Half;
			low -= Half;                       
			high -= Half;
		}
		else if (low >= First_qtr && high < Third_qtr) {
			value -= First_qtr;
			low -= First_qtr;                   //扩展中间
			high -= First_qtr;
		}
		else break;                             /* 不需扩展 */
		low = 2 * low;
		high = 2 * high + 1;                        
		value = 2 * value + input_bit();           
	}
	return symbol;
}

BYTE DecodeRS[Max_code_length];
int decode_length;

void decode() {
	decode_index = 0;
	decode_length = 0;
	start_model();                              
	start_inputing_bits();
	start_decoding();
	for (;;) {                                  
		int ch; int symbol;
		symbol = decode_symbol(cum_freq);       
		if (symbol == EOF_symbol) break;          
		ch = symbol - 1;
		DecodeRS[decode_length] = ch;                    
		symbol = decode_symbol(cum_freq);       
		if (symbol == EOF_symbol) break;
		ch = symbol - 1;						
		DecodeRS[decode_length] |= ch << 4;
		decode_length++;
	}
}

void encode(BYTE * source, int size) {
	HWND hWnd = ::FindWindow(NULL, _T("算术压缩工具"));      //得到对话框的句柄
	CDialog* pWnd = (CDialog*)CDialog::FromHandle(hWnd); 
	auto pMWnd = dynamic_cast<CArithmeticCodingMFCDlg *>(pWnd);//由句柄得到对话框的对象指针
	 
	initACC();
	pMWnd->ShowStatusMsg(_T("初始化完成"));
	CString msg;

	scanFreq(source, size);
	pMWnd->ShowStatusMsg(_T("词频统计完成"));
	start_model();                            
	start_outputing_bits();
	start_encoding();
	pMWnd->ShowStatusMsg(_T("编码中..."));
	for (int i = 0; i < size; i++) {
		BYTE b = *(source + i);
		encode_symbol(char_to_index[(b & 0x0f)], cum_freq);
		encode_symbol(char_to_index[b >> 4], cum_freq);
		if (i % 10000 == 0) {
			msg.Format(_T("编码中 %d / %d"), i, size);
			pMWnd->ShowStatusMsg(msg);
		}
	}
	//将EOF编码进去，作为终止符
	encode_symbol(EOF_symbol, cum_freq);
	done_encoding();                           
	done_outputing_bits();
	pMWnd->ShowStatusMsg(_T("算术编码完成"));
}