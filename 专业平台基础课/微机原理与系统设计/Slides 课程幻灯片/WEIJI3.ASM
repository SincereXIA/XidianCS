
MY_STACK	SEGMENT	PARA 'STACK' 
			DB		100 DUP(?)
MY_STACK	ENDS

MY_DATA 	SEGMENT	PARA 'DATA'
IO_9054base_address DB 4 DUP(0)						;PCI卡9054芯片I/O基地址暂存空间
IO_base_address     DB 4 DUP(0)						;PCI卡I/O基地址暂存空间
pcicardnotfind		DB 0DH,0AH,'pci card not find or address/interrupt error !!!',0DH,0AH,'$'
GOOD				DB 0DH,0AH,'The Program is Executing !',0DH,0AH,'$'
LS244    	DW  	00000H  		
LS273    	DW  	00020H
LS8255      DW      00000H
LS8255W   DW      00003H
RA          DB      ?
LB          DB      ?
;
;
DELAY_SET	EQU	 	0FFFH							;延时常数

MY_DATA 	ENDs

MY_CODE 	SEGMENT PARA 'CODE'

MY_PROC		PROC	FAR		
			ASSUME 	CS:MY_CODE,	DS:MY_DATA,	SS:MY_STACK			
MAIN:		
.386	;386模式编译
			MOV		AX,MY_DATA
			MOV		DS,AX
			MOV		ES,AX
			MOV		AX,MY_STACK
			MOV		SS,AX
			CALL	FINDPCI					;自动查找PCI卡资源及IO口基址
			MOV		CX,word ptr IO_base_address	
;			MOV		CX,0E800H				;直接加入(E800:本机PCI卡IO口基址)
			
        						;PCI卡IO基址+偏移
   
			ADD     LS8255,CX
			ADD     LS8255W,CX
; 插入功能实现代码
MOV		RA,7FH
MOV 	LB,0FEH

READ1:MOV AX,80H
	MOV	DX,LS8255W
	OUT DX,AX
	MOV	DX,LS8255
	MOV	AL,0E7H
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,0DBH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,0BDH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,07EH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV	DX,LS8255W
	OUT DX,AX
	MOV	DX,LS8255
	MOV	AL,0E7H
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,0DBH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,0BDH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	MOV AL,07EH
	MOV DX,LS8255
	OUT DX,AL
	CALL DELAY
	CALL BREAK
	JMP  READ1
	
	
MY_PROC  ENDp

BREAK		PROC   NEAR
PUSHF
PUSH  AX
PUSH  DX
MOV  AH,06H
MOV  DL,0FFH
INT 21H
JE  RETURN 
MOV AX,4C00H
INT 21H
RETURN:
	POP  DX
	POP  AX
	POPF
	RET
	BREAK  ENDP
	DELAY		PROC  NEAR


;*****************************************************************************
;			/*延时程序*/
;*****************************************************************************	
;
DELAY 		PROC  	NEAR					;延时程序
			PUSHF
			PUSH	DX
			PUSH	CX
			MOV 	DX,DELAY_SET
D1: 	   	MOV 	CX,-1
D2:    		DEC 	CX
       		JNZ 	D2
       		DEC		DX
       		JNZ		D1
       		POP		CX
       		POP		DX
       		POPF
       		RET
DELAY  		ENDp
;
;*****************************************************************************
;		/* 找卡子程序 */
;*****************************************************************************			
;
;FUNCTION CODE
IO_port_addre		EQU 0CF8H					;32位配置地址端口
IO_port_data		EQU	0CFCH					;32位配置数据端口
IO_PLX_ID			EQU	200810B5H				;PCI卡设备及厂商ID
BADR0				=	10H						;基地址寄存器0
BADR1				=	14H						;基地址寄存器1
BADR2				=	18H						;基地址寄存器2
BADR3				=	1CH						;基地址寄存器3

FINDPCI 	PROC	NEAR						;查找PCI卡资源并显示
			PUSHAD
			PUSHFD
			MOV		EBX,080000000H
FINDPCI_next:
			ADD		EBX,100H
			CMP 	EBX,081000000H
			JNZ 	findpci_continue
			MOV 	DX,offset pcicardnotfind	;显示未找到PCI卡提示信息
			MOV 	AH,09H
			INT 	21H
			MOV 	AH,4CH
			INT 	21H							;退出
findpci_continue:
			MOV 	DX,IO_port_addre
			MOV 	EAX,EBX
			OUT 	DX,EAX						;写地址口
			MOV 	DX,IO_port_data
			IN  	EAX,DX						;读数据口
			CMP 	EAX,IO_PLX_ID
			JNZ 	findpci_next				;检查是否发现PCI卡

			MOV 	DX,IO_port_addre
			MOV 	EAX,EBX
       		ADD 	EAX,BADR1
			OUT 	DX,EAX									;写地址口
			MOV 	DX,IO_port_data
			IN  	EAX,DX									;读数据口
			MOV 	dword ptr IO_9054base_address,EAX
			AND 	EAX,1
			JZ 		findPCI_next							;检查是否为i/o基址信息
       		MOV 	EAX,dword ptr IO_9054base_address
			AND 	EAX,0fffffffeh
        	MOV 	dword ptr IO_9054base_address,EAX		;去除i/o指示位并保存

			MOV 	DX,IO_port_addre
			MOV 	EAX,EBX
			ADD 	EAX,BADR2
			OUT 	DX,EAX									;写地址口
			MOV 	DX,IO_port_data
			IN  	EAX,DX									;读数据口
			MOV 	dword ptr IO_base_address,EAX
			AND 	EAX,1
			JZ 		findPCI_next							;检查是否为i/o基址信息
			MOV 	EAX,dword ptr IO_base_address
			AND 	EAX,0fffffffeh
			MOV 	dword ptr IO_base_address,EAX			;去除i/o指示位并保存
			MOV 	DX,offset good							;显示开始执行程序信息
			MOV 	AH,09H
			INT 	21H
			POPfd
			POPad
			RET
findPCI		ENDP


MY_CODE   	ENDS

			END    	MAIN	