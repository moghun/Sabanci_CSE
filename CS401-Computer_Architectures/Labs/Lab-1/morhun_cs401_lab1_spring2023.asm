.data

array1: .word 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 # final 0 indicates the end of the array; 0 is excluded; it should return TRUE for this array
array2: .word 8, 9, 6, 7, 5, 4, 3, 2, 1, 0 # final 0 indicates the end of the array; 0 is excluded; it should return FALSE for this array

true: .asciiz "TRUE\n"
false: .asciiz "FALSE\n"
default: .asciiz "This is just a template. It always returns "

.text

main:
      la $a0, array1 # $a0 has the address of the A[0]
      jal lenArray  # Find the lenght of the array
      
      move $a1, $v0  # $a1 has the length of A
      
      jal Descending

      bne $v0, 0,  yes
      la  $a0, false
      li $v0, 4
      syscall
      j exit

yes:  la    $a0, true
      li $v0, 4
      syscall

exit:
      li $v0, 10
      syscall


Descending:
###############################################
#   Your code goes here
###############################################
      # Idea is to use recursion to check if the array is descended sorted
      # Starting from the 0th index, assure that current element is greater than next element
      # If condition holds, decrement the array size by one and check next two elements recursively
      # If array size is 1, then it should be descended sorted --> hit base case --> return TRUE
      # If not, then it is not descended sorted --> return FALSE immediately

      # a0 --> pointer to array
      # a1 --> array size
      # t1 --> current element to compare with next element
      # t2 --> next element to compare with current element
      # v0 --> flag


      beq $a1 ,1 , if # if array size is 1 then descended sorted --> jump to true --> base case

      lw $t0, ($a0) # load current element
      lw $t1, 4($a0) # load next element
      bgt $t1, $t0, else # if next element is greater than current element then not descended sorted --> jump to false

      addi $a0, $a0, 4 # increment pointer to set next element as current element for next call
      addi $a1, $a1, -1 # decrement array size --> eventually hit base case --> # if only one element left then it is descended sorted

      j Descending # recursive call


      if:
            li $v0, 1 # set flag as TRUE
      	jr $ra # return back

      else:
            li $v0, 0 # set flag as FALSE
      	jr $ra # return back

      
###############################################
# Everything in between should be deleted
###############################################
      jr $ra	

lenArray:       #Fn returns the number of elements in an array
      addi $sp, $sp, -8
      sw $ra,0($sp)
      sw $a0,4($sp)
      li $t1, 0

laWhile:       
      lw $t2, 0($a0)
      beq $t2, $0, endLaWh
      addi $t1,$t1,1
      addi $a0, $a0, 4
      j laWhile

endLaWh:
      move $v0, $t1
      lw $ra, 0($sp)
      lw $a0, 4($sp)
      addi $sp, $sp, 8
      jr $ra
