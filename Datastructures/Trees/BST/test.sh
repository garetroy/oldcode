#!/bin/bash

echo "********************************************************************************"
echo "* Running Test 1/5: Compile                                                    *"

# Test to see if all files compile
javac $1/*.java
if [ $? != 0 ]; then
	echo Failed to compile.
	echo Estimated score \for lab 1: 0/50
	echo "********************************************************************************"
else
	echo Passed
	echo "********************************************************************************"
	echo "* Running Test 2/5: Data Structure Implementation - Insert                     *"
	echo "* Part a) Execution                                                            *"
	
	# Test Time Complexity of inserts
	start=$SECONDS
	java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/insertTest1.txt > $1/outputInsert1.txt
	I1=$?
	durI1=$(( SECONDS - start ))
	
	start=$SECONDS
	java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/insertTest2.txt > $1/outputInsert2.txt
	I2=$?
	durI2=$(( SECONDS - start ))
	
	# Check to see if insert ran correctly
	if [ $I1 != 0 -o $I2 != 0 ]; then
		echo Failed to execute insert commands correctly.
		echo Your \file must be \named lab2.java
		echo Estimated score \for lab 1: 10/50
		echo "********************************************************************************"
	else
		echo Passed
		echo "* Part b) Printing                                                             *"
		
		# Check to see if test 1 test printed enough
		A=$(wc -l < $1/outputInsert1.txt)
		B=$(wc -l < /home/users/smergend/public/cs313/lab2/outputInsert1.txt)
		
		# Check to see if test 2 printed enough
		C=$(wc -l < $1/outputInsert2.txt)
		D=$(wc -l < /home/users/smergend/public/cs313/lab2/outputInsert2.txt)	
			
		if [ $A != $B -o $C != $D ]; then
			echo Failed to print out insert commands correctly.
			echo Estimated score \for lab 1: 12.5/50
			echo "********************************************************************************"
		else
			echo Passed	
			echo "********************************************************************************"
			echo "* Part c) Correctness                                                          *"
			
			# Compare the outputs
			X1=$(diff -w -U 0 $1/outputInsert1.txt /home/users/smergend/public/cs313/lab2/outputInsert1.txt | grep -v ^@ | tail -n +3 | wc -l)
			Z1=$[$X1/2]
			
			if [ $Z1 -ne 0 ]; then
				echo Failed the first insert test. 
				echo Estimated score \for lab 1: 15/50
			else			
				X2=$(diff -w -U 0 $1/outputInsert2.txt /home/users/smergend/public/cs313/lab2/outputInsert2.txt | grep -v ^@ | tail -n +3 | wc -l)
				Z2=$[$X2/2]
				
				if [ $Z2 -ne 0 ]; then
					echo Failed the second insert test. 
					echo Estimated score \for lab 1: 17.5/50
				else
					echo Passed
					echo "********************************************************************************"
					echo "* Running Test 2/5: Data Structure Implementation - Delete                     *"
					echo "* Part a) Execution                                                            *"
					
					# Test Time Complexity of deletes
					start=$SECONDS
					java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/deleteTest1.txt > $1/outputDelete1.txt
					D1=$?
					durD1=$(( SECONDS - start ))
	
					start=$SECONDS
					java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/deleteTest2.txt > $1/outputDelete2.txt
					D2=$?
					durD2=$(( SECONDS - start ))
	
					start=$SECONDS
					java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/deleteTest3.txt > $1/outputDelete3.txt
					D3=$?
					durD3=$(( SECONDS - start ))
	
					start=$SECONDS
					java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/deleteTest4.txt > $1/outputDelete4.txt
					D4=$?
					durD4=$(( SECONDS - start ))
	
					start=$SECONDS
					java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/deleteTest5.txt > $1/outputDelete5.txt
					D5=$?
					durD5=$(( SECONDS - start ))
					
					# Check to see if delete ran correctly
					if [ $D1 != 0 -o $D2 != 0 -o $D3 != 0 -o $D4 != 0 -o $D5 != 0 ]; then
						echo Failed to execute delete commands correctly.
						echo Your \file must be \named lab2.java
						echo Estimated score \for lab 2: 20/50
						echo "********************************************************************************"
					else
						echo Passed
						echo "* Part b) Printing  											                 *"
						
						# Check to see if test 1 test printed enough
						A=$(wc -l < $1/outputDelete1.txt)
						B=$(wc -l < /home/users/smergend/public/cs313/lab2/outputDelete1.txt)
		
						# Check to see if test 2 printed enough
						C=$(wc -l < $1/outputDelete2.txt)
						D=$(wc -l < /home/users/smergend/public/cs313/lab2/outputDelete2.txt)	
						
						# Check to see if test 3 printed enough
						E=$(wc -l < $1/outputDelete3.txt)
						F=$(wc -l < /home/users/smergend/public/cs313/lab2/outputDelete3.txt)
						
						# Check to see if test 4 printed enough
						G=$(wc -l < $1/outputDelete4.txt)
						H=$(wc -l < /home/users/smergend/public/cs313/lab2/outputDelete4.txt)
						
						# Check to see if test 5 printed enough
						I=$(wc -l < $1/outputDelete5.txt)
						J=$(wc -l < /home/users/smergend/public/cs313/lab2/outputDelete5.txt)
						
						
			
						if [ $A != $B -o $C != $D -o $E != $F -o $G != $H -o $I != $J ]; then
							echo Failed to print out delete commands correctly.
							echo Estimated score \for lab 2: 22.5/50
							echo "********************************************************************************"
						else
							echo Passed	
							echo "********************************************************************************"
							echo "* Part c) Correctness                                                          *"
							
							# Compare the outputs
							X1=$(diff -w -U 0 $1/outputDelete1.txt /home/users/smergend/public/cs313/lab2/outputDelete1.txt | grep -v ^@ | tail -n +3 | wc -l)
							Z1=$[$X1/2]
			
							if [ $Z1 -ne 0 ]; then
								echo Failed the first delete test. 
								echo Estimated score \for lab 2: 25/50
							else			
								X2=$(diff -w -U 0 $1/outputDelete2.txt /home/users/smergend/public/cs313/lab2/outputDelete2.txt | grep -v ^@ | tail -n +3 | wc -l)
								Z2=$[$X2/2]
				
								if [ $Z2 -ne 0 ]; then
									echo Failed the second delete test. 
									echo Estimated score \for lab 2: 27.5/50
								else
									X3=$(diff -w -U 0 $1/outputDelete3.txt /home/users/smergend/public/cs313/lab2/outputDelete3.txt | grep -v ^@ | tail -n +3 | wc -l)
									Z3=$[$X3/2]
				
									if [ $Z3 -ne 0 ]; then
										echo Failed the third delete test. 
										echo Estimated score \for lab 2: 30/50
									else
										X4=$(diff -w -U 0 $1/outputDelete4.txt /home/users/smergend/public/cs313/lab2/outputDelete4.txt | grep -v ^@ | tail -n +3 | wc -l)
										Z4=$[$X4/2]
				
										if [ $Z4 -ne 0 ]; then
											echo Failed the fourth delete test. 
											echo Estimated score \for lab 2: 32.5/50
										else
											X5=$(diff -w -U 0 $1/outputDelete5.txt /home/users/smergend/public/cs313/lab2/outputDelete5.txt | grep -v ^@ | tail -n +3 | wc -l)
											Z5=$[$X5/2]
				
											if [ $Z5 -ne 0 ]; then
												echo Failed the fifth delete test. 
												echo Estimated score \for lab 2: 35/50
											else
												echo Passed
												echo "********************************************************************************"
												echo "* Running Test 2/5: Data Structure Implementation - Traverse                   *"
												echo "* Part a) Execution                                                            *"
												
												# Test Time Complexity of traverses
												start=$SECONDS
												java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/inoTest.txt > $1/outputINO.txt
												T1=$?
												durT1=$(( SECONDS - start ))
	
												start=$SECONDS
												java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/preoTest.txt > $1/outputPRE.txt
												T2=$?
												durT2=$(( SECONDS - start ))
	
												start=$SECONDS
												java -cp $1 lab2 < /home/users/smergend/public/cs313/lab2/postoTest.txt > $1/outputPOST.txt
												T3=$?
												durT3=$(( SECONDS - start ))
												
												# Check to see if delete ran correctly
												if [ $T1 != 0 -o $T2 != 0 -o $T3 != 0 ]; then
													echo Failed to execute traverse commands correctly.
													echo Your \file must be \named lab2.java
													echo Estimated score \for lab 2: 37.5/50
													echo "********************************************************************************"
												else
													echo Passed
													echo "* Part b) Printing  											                 *"
													
													# Check to see if test 1 test printed enough
													A=$(wc -l < $1/outputINO.txt)
													B=$(wc -l < /home/users/smergend/public/cs313/lab2/outputINO.txt)
		
													# Check to see if test 2 printed enough
													C=$(wc -l < $1/outputPRE.txt)
													D=$(wc -l < /home/users/smergend/public/cs313/lab2/outputPRE.txt)	
						
													# Check to see if test 3 printed enough
													E=$(wc -l < $1/outputPOST.txt)
													F=$(wc -l < /home/users/smergend/public/cs313/lab2/outputPOST.txt)
													
													if [ $A != $B -o $C != $D -o $E != $F -o $G != $H -o $I != $J ]; then
														echo Failed to print out traverse commands correctly.
														echo Estimated score \for lab 2: 40/50
														echo "********************************************************************************"
													else
														echo Passed	
														echo "********************************************************************************"
														echo "* Part c) Correctness                                                          *"
							
														# Compare the outputs
														X1=$(diff -w -U 0 $1/outputINO.txt /home/users/smergend/public/cs313/lab2/outputINO.txt | grep -v ^@ | tail -n +3 | wc -l)
														Z1=$[$X1/2]
				
														if [ $Z1 -ne 0 ]; then
															echo Failed the Inorder Traverse test. 
															echo Estimated score \for lab 2: 42.5/50
														else			
															X2=$(diff -w -U 0 $1/outputPRE.txt /home/users/smergend/public/cs313/lab2/outputPRE.txt | grep -v ^@ | tail -n +3 | wc -l)
															Z2=$[$X2/2]
				
															if [ $Z2 -ne 0 ]; then
																echo Failed the Preorder Traverse test. 
																echo Estimated score \for lab 2: 45/50
															else
																X3=$(diff -w -U 0 $1/outputPOST.txt /home/users/smergend/public/cs313/lab2/outputPOST.txt | grep -v ^@ | tail -n +3 | wc -l)
																Z3=$[$X3/2]
				
																if [ $Z3 -ne 0 ]; then
																	echo Failed the Postorder Traverse test. 
																	echo Estimated score \for lab 2: 47.5/50
																else
																	echo Passed
																	echo Estimated score \for lab 2: 50/50
																	
																	echo "********************************************************************************"	
																	echo "* Running Test 6/5: Extra Credit                                               *"
																	java -cp $1 TreeCompare < /home/users/smergend/public/cs313/lab2/ECin.txt > $1/ECout.txt
																	E1=$?
								
																	# EC Test (4points)
																	X7=$(diff -w -U 0 $1/ECout.txt /home/users/smergend/public/cs313/lab2/ECout.txt | grep -v ^@ | tail -n +3 | wc -l)
																	Z7=$[$X7/2]
								
																	if [ $Z7 -ne 0 -o $E1 != 0 ]; then
																		echo Extra Credit failed. 
																		Y7=50
																	else
																		echo Passed
																		Y7=60
																	fi
								
																	echo Estimated final score \for lab 1: $Y7/50
																	echo "********************************************************************************"	
																fi
															fi
														fi
													fi
												fi
											fi
										fi
									fi
								fi
							fi
						fi
					fi
				fi
			fi
		fi
	fi
fi
				
								

	
	
	
	
