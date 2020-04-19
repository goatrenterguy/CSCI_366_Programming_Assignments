
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
        mov rsi, 1
        mov rcx, 7
        sub rcx, rdx
        ;loop that shifts left by 1
        .loop:
        cmp rcx, 0
        je .continue
		dec rcx
        sal rsi, 1
        jnz .loop
        ; Or them together
        .continue:
		pop rcx ; byte offset
		mov rdx, [rdi + rcx] ;move byte into rdx
		or rdx, rsi ; or them to gether to flip bit
		mov [rdi + rcx], rdx ; move byte back (not sure how this works)

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
        mov rsi, 1
        mov rcx, 7
        sub rcx, rdx
        ;loop that shifts left by 1
        .loop:
        cmp rcx, 0
        je .continue
		dec rcx
        sal rsi, 1
        jnz .loop
        ; Or them together
        .continue:
		pop rcx ; byte offset
		mov rdx, [rdi + rcx] ;move byte into rdx
        and rdx, rsi ; and them together to get bit
		cmp rdx, 0          ; check if any bits set in rdi
        setg al
        movsx rax, al

        mov rsp, rbp        ; restore stack pointer to before we pushed parameters onto the stack
        pop rbp             ; remove rbp from the stack to restore rsp to initial value
        ret                 ; return value in rax
