
        global  _set_bit_elem
        global  _get_bit_elem
        section .text

_set_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here
		; Index
        imul rsi, rdx
        add rsi, rcx
        push rsi
        ; Byte offset
        shr rsi, 3
        push rsi
        ; Bit offset
        imul rsi, 8
        pop rcx
        pop rdx
        push rcx
        sub rdx, rsi
        ; Create mask
        mov rcx, 1
        mov rsi, 7
        sub rsi, rdx
        mov cl, [rsi]
        sal rcx, cl
        ; Or them together
		pop rsi ; byte offset
		mov rdx, [rdi + rsi]
		or rdx, rcx
		mov [rdi + rsi], rdx

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax




_get_bit_elem:
        push rbp            ; save the base pointer on the stack (at rsp+8)
        mov rbp, rsp        ; set up the rbp for the bottom of this frame

        ; rdi contains array pointer
        ; rsi contains row width
        ; rdx contains row
        ; rcx contains col

        ; add your code here - for now returning 0
		; Index
        mov eax, [rsi]
        mul rdx
        mov rsi, [eax]
        add rsi, rcx
        push rsi
        ; Byte offset
        mov eax, [rsi]
        mov rsi, 8
        div rsi
        mov rsi, [eax]
        push rsi
        ; Bit offset
        mov eax, [rsi]
        mov rsi, 8
        mul rsi
        mov rsi, [eax]
        pop rcx
        pop rdx
        push rcx
        sub rdx, [rsi]
        ; Create mask
        mov rcx, 1
        mov cl, 7
        sub cl, [rdx]
        shl rcx, cl
        ; Or them together
		pop rsi ; byte offset
		mov rdx, [rdi + rsi]
		and rdx, rcx
		cmp rdi, 0          ; check if any bits set in rdi
        setg al
        movsx rax, al

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
