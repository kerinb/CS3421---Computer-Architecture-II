.686                                ; create 32 bit code
.model flat, C                      ; 32 bit memory model
 option casemap:none                ; case sensitive

.code


public      min_IA32a               ; make sure function name is exported

min_IA32a:  push    ebp             ; push frame pointer
            mov     ebp, esp        ; update ebp
            sub     esp, 4          ; space for local variables fi [ebp-4] and fj [ebp-8]
			push	ebx
            mov     eax, [ebp+8]    ; eax = a
			mov		[ebp-4], eax	; v = a = eax
			mov		eax, [ebp + 12] ; mov b into eax
			cmp		eax, [ebp - 4]  ; compare b with v
			jg		notIfB			; if(b > v) jmp to notIfC
			mov		[ebp-4], eax	; mov eax into v
notIfB:		mov		eax, [ebp + 16] ; mov c into eax
			cmp		eax, [ebp - 4]  ; cmp V with c
			jg		notIfC			; if(c > v) jmp to notIfC
			mov		eax, [ebp + 16] ; mov c into eax
			mov		[ebp - 4], eax	; mov eax into v
notIfC:		mov     eax, [ebp-4]    ; eax = fj
			mov     esp, ebp        ; restore esp
            pop     ebp             ; restore ebp
            ret     0               ; return
    
;
; example mixing C/C++ and IA32 assembly language
;
; makes better use of registers and instruction set
;

public      p_IA32a				   ; make sure function name is exported

									; set up the function on entry
p_IA32a:	push	ebp				; save ebp on the stack
			mov		ebp, esp		; ebp->new stack frame
			sub 	esp, 4			; allocate space for local variable V
			push	ebx				; save non-volatile registers used by function
									; not sure whether we need to save this – depends on what we do pre-function call

			push	ebp + 12		; = j push immediate values onto the stack
			push	ebp + 8			; = i from right to left
			mov 	eax, [g]		; eax = g
			push	eax				; = eax = g
			call 	min				; call the min function – how do you set V = min(...)?
			Add		esp, 12			; pop parameters from the stack
									; does it store the new value in  eax??

			Push	ebp + 20		; = l push immediate values onto the stack
			push	ebp + 16		; = k from right to left
			push	eax				; = eax = V = from min function
			call 	min				; call the min function – how do you set V = min(...)?
		
			ret 	0			

public      gcd_IA32a				; make sure function name is exported

									; set up the function on entry
gcd_IA32a:  push	ebp				; save ebp on the stack
			mov		ebp, esp		; ebp->new stack frame
			push	ebx				; save non-volatile registers used by function
									; not sure whether we need to save this – depends on what we do pre-function call
	
			mov		eax, [ebp + 12]	; eax = b
			cmp 	eax, 0			; if(b!=0)
			jne	notE				; jmp to notEqual
			mov 	eax, [ebp + 8]	; mov a into eax
			ret 	eax				; otherwise return a/eax
notE		push	eax				; push eax/b onto the stack to be the new a
			mov 	eax, [ebp + 8]	; store a in eax
			idiv	eax, [ebp + 12]	; eax = eax%b
			push 	eax				; push eax onto stack as b = a%b
			call 	gcd				; call function recursively

			ret 	0				; return tge min value from min(v,k,l)           																		
end