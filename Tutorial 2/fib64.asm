option casemap:none             ; case sensitive
includelib legacy_stdio_definitions.lib
extern  printf:near             ; allows extern to link with printf
.data
	printQ	db	"a=%I64d b=%I64d c=%I64d d=%I64d e=%I64d sum = %I64d", 0AH, 00H

public	g
g	QWORD	4					; QWORD = quadword
.code


public		fibX64					; export function name

fibX64:		mov		rax, rcx		; rax = n
			cmp		rax, 1			; if (n <= 1)
			jle		fibX64_1		; return n
			xor		rdx, rdx		; fi = 0
			mov		rax, 1			; fj = 1
fibX64_0:	cmp		rcx, 1			; while (n > 1)
			jle		fibX64_1		;
			mov		r10, rax		; t = fj
			add		rax, rdx		; fi = fi + fj
			mov		rdx, r10		; fi = t
			dec		rcx				; n--
			jmp		fibX64_0		;
fibX64_1:	ret						; return rax

									; parameter a in rcx
									; parameter b in rdx
									; parameter c in r8
									; must assign shadow space - this is a tree function

public      minX64					; make sure function name is exported

minX64:     sub		rsp, 32			; allocate shaow space
			mov     rax, rcx        ; rax = v = a
			cmp		rax, rdx        ; compare b with v
			jl		notIfB			; if(b > v) jmp to notIfB
			mov		rax, rdx	    ; mov rdx/B into v
notIfB:		cmp		rax, r8         ; cmp V with c
			jl		notIfC			; if(c > v) jmp to notIfC
			mov		rax, r8			; mov c into eax
notIfC:		add		rsp, 32			; de-allocate shadow space
			ret                     ; return

 
									; parameter i in rcx
									; parameter j in rdx
									; parameter k in r8
									; parameter l in r9
public      pX64					; make sure function name is exported

pX64:		sub		rsp, 32			; allocate shadow space
			mov		r10, r8			; r10 = r8 = k
			mov		r11, r9			; r11 = r9 = l
			mov		r8,	 rdx		; r8 = rdx
			mov		rdx, rcx		; rdx = rcx	
			mov		rcx, [g]		; rcx = g
			call 	minX64			; call the min function – how do you set V = min(...)?
			mov		r8,	 r11		; r8 = r11
			mov		rdx, r10		; rdx = r10
			mov		rcx, rax		; rcx = rax 
			call 	minX64			; call the min function – how do you set V = min(...)?
			add		rsp, 32			; de-allocate shadow space
			ret 	0	

									; parameter a = rcx
									; parameter b = rdx
public		gcdX64					; make sure to export function

gcdX64:		
			cmp		rdx, 0			; if (b == 0)
			jne		notEqual		; {
			mov		rax, rcx		;	rax = rcx = a
			jmp		_END			; }
notEqual:							; else {
			mov		rax, rcx		; 
			mov		r10, rdx		; 
			cqo						; r10 = rdx = b
			idiv	r10				; rcx = rcx%rdx
			mov		rax, rdx
			mov		rdx, rax
			mov		rcx, r10
			call	gcdX64			; gcdX64(rdx, rcx%rdx)

_END:		ret


public		qX64

qX64:		push	rbx
			sub		rsp, 56				;allocate shadow space for 7 params
			
			lea		rax, [rcx+rdx]		; rax = a+b (rbx across call to printf)
			add		rax, r8				
			add		rax, r9
			mov		r10, [rsp+104]		;40 bytes + 56 bytes = 96 bytes
			add		rax, r10			; rax = sum 
			mov		[rsp+48], rax		; param sum
			mov		[rsp+40], r10		; param e
			mov		[rsp+32], r9		; param d
			mov		r9, r8				; param c
			mov		r8, rdx				; param b
			mov		rdx, rcx			; param	a
			mov		rcx, offset printQ	; param print statement
			call	printf

			mov		rax, [rsp+48]		;rax=sum
			add		rsp, 56				;deallocate shadow space
			pop		rbx
			ret

			end

; for print function
;	param 1 = print statement
;	param 2 = sum
;	param 3 = e
;	param 4 = d
;	param 5 = c
;	param 6 = b	
;   param 7 = a