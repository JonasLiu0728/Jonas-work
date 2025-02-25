TEX:
	@.ascii "Hello World\0"
	stringD:     .asciz "Argv: %s\n"
	stringS:      .asciz "%c"
	stringE:      .asciz "End of program\n"
	.text
	.align 2
	.global main
main:
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4

	ldr r0, =stringD
	
	
	ldr r1,[r1, #4]
	mov r5, r1
	@第一個字
	
	
loop:
	ldrb r6, [r5], #1   @r6存第一個字 
	mov r1,r6
	ldr r0, =stringS
	cmp r1,#0	@看是不是中止
	beq end
	mov r1,r6
	ldr r0, =stringS
	cmp r1, #65	@判斷有沒有在大的範圍中(65~122)
	blt loop
	cmp r1, #122
	bgt loop
	cmp r1, #97 @是小寫
	bge print
	cmp r1, #91 @是大寫
	blt convert
	bl loop

	
print: @單純印出來
	bl printf
	bl loop
convert:
	add r1, r1, #32
	bl printf
	bl loop 
end:
	ldrb r6, [r5], #1   @r6存第一個字 
	mov r1,r6
	ldr r0, =stringS
	bl printf
	ldmfd sp!, {fp, lr}
	bx lr










