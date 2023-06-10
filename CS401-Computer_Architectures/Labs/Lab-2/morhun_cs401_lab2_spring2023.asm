.data

array1: .word 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 
array2: .word 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 

tempArray1: .space 40 #for storing different elements in array1
tempArray2: .space 40 #for storing different elements in array2


message: .asciiz "The sum of the same elements is "

.text


main:
	la $a0, array1
	la $a1, tempArray1 
      	jal DiffElement  
      	move $s0, $v0 
      	
      	la $a0, array2 
	la $a1, tempArray2 
      	jal DiffElement  
     	move $s1, $v0

     	la $a0, tempArray1
     	move $a1, $s0
     	la $a2, tempArray2
     	move $a3, $s1
     	
     	jal SumofElements
     	
     	move $t0, $v0
     	
     	la $a0, message
     	li $v0, 4
     	syscall	
     	
      	move $a0, $t0  
      	li $v0,1
      	syscall
      	
      	li $v0, 10
      	syscall   
      
      
     
#DiffElement:
###############################################
#   Your code goes here
###############################################
	# $a0 = input array
	# $a1 = address of dynamic array
	# $v0 = number of different elements
	# $t0 = counter for outer loop
	# $t3 = counter for inner loop

	# add unique numbers starting from 0($a1)
	# return number of unique elements in $v0
DiffElement:
	li $v0, 0 # initialize num unique numbers to 0
	li $t0, 0 # initialize outter loop counter to 0
	
	DiffLoop1:
		beq $t0, 40, EndDiffLoop1 # if outter loop counter == 9, end loop
		li $t3, 0

		add $t1, $a0, $t0
		lw $t2, 0($t1)

		DiffLoop2:
			add	$t4, $v0, $v0
			add	$t4, $t4, $t4
			beq $t3, $t4, EndDiffLoop2 # if inner loop counter == number of unique numbers, end loop
			
			add $t5, $t3, $a1 # $t5 = array[ct-inner]
			lbu $t6, 0($t5) 	  # t6 = value of the dynamic array at ct-inner

			beq $t2, $t6, NotUnique # if array[ct-outter] == dynamicArray[ct-inner], go to NotUnique
			addi $t3, $t3, 1 # increment inner loop counter
			j DiffLoop2 # go to DiffLoop2
			
			NotUnique:
				addi $t0, $t0, 4 # increment inner loop counter
				j DiffLoop1 # go to DiffLoop1

		EndDiffLoop2:
			add $t7, $t3, $a1
			sw $t2, 0($t7) # store array[ct-outter] in dynamicArray[ct-inner]
			addi $v0, $v0, 1 # increment number of unique numbers
			addi $t0, $t0, 4 # increment inner loop counter
			j DiffLoop1 # go to DiffLoop1

	EndDiffLoop1:
	jr $ra
	    
     
###############################################
# Everything in between should be deleted
############################################### 


#SumofElements:
###############################################
#   Your code goes here
###############################################
SumofElements:
	# $a0 = input array1
	# $a2 = input array2
	# $a1 = length of array2
	# $a3 = length of array2
	# $v0 = sum of same elements
	# $t0 = counter for outer loop
	# $t3 = counter for inner loop

	li $v0, 0 # initialize sum to 0
	li $t0, 0 # initialize outter loop counter to 0
	add $t6, $a1, $a1	
	add $t6, $t6, $t6	# num elements in dynamic array1
	add $t7, $a3, $a3	
	add $t7, $t7, $t7	# num elements in dynamic array1
	
	SumLoop1:
		beq $t0, $t6, EndSumLoop1 # if outter loop counter == 9, end loop
		li $t3, 0

		add $t1, $a0, $t0 
		lw $t2, 0($t1)	# t2 = array1[ct-outter]

		SumLoop2:
			beq $t3, $t7, EndSumLoop2 # if inner loop counter == number of unique numbers, end loop
			
			add $t4, $t3, $a2 # $t4 = array2[ct-inner]
			lbu $t5, 0($t4) 	  # t5 = value of the array2 at ct-inner

			beq $t2, $t5, Equal # if array1[ct-outter] == array2[ct-inner], go to Equal
			addi $t3, $t3, 4 # increment inner loop counter
			j SumLoop2 # go to SumLoop2
			
			Equal:
				addi $t0, $t0, 4 # increment inner loop counter
				add $v0, $v0, $t2 # add array1[ct-outter] to sum
				j SumLoop1 # go to SumLoop1

		EndSumLoop2:
			addi $t0, $t0, 4 # increment inner loop counter
			j SumLoop1 # go to SumLoop1

	EndSumLoop1:
	jr $ra

	    
     
###############################################
# Everything in between should be deleted
###############################################